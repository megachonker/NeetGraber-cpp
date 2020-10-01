#include "Poste.h"
#include <string>
#include "regex"
#include "Thread.h"
#include <curl/curl.h>
#include <iostream>

using namespace std;
static std::string webData;

//FONCTION DE FDP POUR stoquer la page dans un string 
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

//fonction GET PAGE
string httpGET(string link){
   
    string http_data;

    CURL *curl;
    CURLcode codeExit;

    char * lien = new char [link.length()+1]; ///////////////////////////////LIEN
    std::strcpy (lien, link.c_str());

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    curl_easy_setopt(curl, CURLOPT_URL, lien);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &http_data);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Fluffy-Awoo USER AGENT");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    codeExit = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if(codeExit != CURLE_OK){cout << "/!\\ " << codeExit << " /!\\"<<endl;}

    return http_data;
}


//VERSION OPTI MAIS BLOCKAGEEEE

/* 
Thread::Thread(string post_raw, string noms): Poste(post_raw)
{
    titre = noms; 
    // getId()
    // getRedirection()
    // webData = httpGET();
    regex patern("c=\"\\d*\">.*?</blockquote></div></div>");
    while(regex_search(webData, match , patern))
    {
        liste_poste.push_back(Poste(match.str(0)));
        webData = match.suffix();
    }

} */





Thread::Thread(string post_raw, string noms, string url, bool recursive): Poste(post_raw)
{
    titre = noms;   
    
    /* char * lien = new char [url.length()+1]; // on garde au chaud le lien fraichement convertie
    std::strcpy (lien, url.c_str());
     */
    lien = url;
    

    if(recursive){
        webData = httpGET(url);
        regex patern("c=\"\\d*\">.*?</blockquote></div></div>");
        while(regex_search(webData, match , patern))
        {
            //  cout << "ce qui va aller dans POSTE: " << match.str(0) << endl; 
            liste_poste.push_back(Poste(match.str(0)));
            webData = match.suffix();
        }
    }

}






//fait chier théoriquement on peut retrouver url mais ces pas opti, et il va falloir ajouter un autre truc ENNNCOR
Thread::Thread(string post_raw, string noms, string url) : Poste(post_raw)
{
    titre = noms; 
    smatch match;
    // string webData;
    CURL *curl;
    CURLcode codeExit;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    char * cstr = new char [url.length()+1];
    std::strcpy (cstr, url.c_str());
    
    curl_easy_setopt(curl, CURLOPT_URL, cstr);//url);//url+"thread/"+to_string(this->getId()));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &webData); //A VERIFIER
    //VERIFIER LE HTMLLLLl
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Fluffy-Awoo USER AGENT");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    codeExit = curl_easy_perform(curl);
    if(codeExit != CURLE_OK){cout << "/!\\ " << codeExit << " /!\\" << "url is : "<< url <<endl;}
    else{

        // AVEC CETTTE CHAINE JE POURAIT TOUT FAIRE regex patern("><span class=\"subject\">(.*?)</span>.*?\"\\d*\">(.*?)</blockquote></div><div class=\"postLink ");
        // if(regex_search(webData, match, patern))

        // cout << "\n\n\n\n\n" << webData << "\n\n\n\n\n" << endl;

        regex patern("c=\"\\d*\">.*?</blockquote></div></div>");//("c=\"\\d*\">(.*?)</blockquote></div></div>");
        while(regex_search(webData, match , patern))
        {
            liste_poste.push_back(Poste(match.str(0)));
            webData = match.suffix();
        }
    }
    curl_easy_cleanup(curl);

}

Poste Thread::getPoste(short numero)const{
    // if (numero =! -1){
        return liste_poste[numero];
    // }
    // else{
    //     for(unsigned int i = 0; i < liste_poste.size(); i++){
    //     return liste_poste[i];
    //     }
    // }
    // return liste_poste;
}

void Thread::dumpPoste(){
    cout << "il y a : "<<  liste_poste.size() << " thread."<< endl;
    for(int u = 0;u<liste_poste.size();u++){
        cout << "poste no: " << u <<" existe t'ill ?"<< liste_poste[u].getImage().getExist()<<" noms image : "<< liste_poste[u].getImage().getName() << " data en brute " << liste_poste[u].getImage().getRawData()<<endl;
    }
}

string Thread::getThreadFlow() const{
    return webData;
}
string Thread::getTitre() const{
    return titre;
}

unsigned int Thread::getNombreRep() const{
    return liste_poste.size();
}

unsigned int Thread::getNombreMsg() const{
    int tmp=0;
    for (unsigned int i = 0; i < liste_poste.size();i++){
        if(!liste_poste[i].getCommentaire().empty()){
            tmp++;
        }
    } 
    return tmp;
}

unsigned int Thread::getNombreImage() const{
    int tmp=0;
    for (unsigned int i = 0; i < liste_poste.size();i++){
        if(getPoste(i).getImage().getExist()){
            tmp++;
        }
    } 
    return tmp;
}

void Thread::toStringAll() const{
    ////////////////////////////////////////NOMS INTROUVABLE
    cout<< "noms: "<< titre<< "\n" <<
    toString() <<  // to string le poste du thread
    "url thread: " << lien <<

    "\n     nombre de poste: " << getNombreRep()<<//this->getNombreRep() <<   
    "\n     nombre d'image : " << getNombreImage() <<
    "\n     nombre de msg  : " << getNombreMsg() << endl; 


    
    cout << "\n     To string Poste :" << endl;
    cout << "noblre de poste\n" << liste_poste.size()<< endl;
    for(int u = 0;u<liste_poste.size();u++){
        cout << "\n     poste no " << u <<" :\n         "<< liste_poste[u].toString() << endl;
    }
}


//fonction pour réactualiser un thread

// void Thread::Actualisation(){
//     int tmp, temp;
//     while(0==0){
//         Sleep(5000);
//         tmp=+5;
//         if(temp =! liste_poste.size() )
//             temp = liste_poste.size();
//             cout << "temps écouler " << tmp << " seconde " << "combre de réponse " << temp << " nombre d'image "<< this->getNombreImage() <<endl;


//         ///////////////////////////////////////////////////////// ON RE DL LA PAGE

//         //mais on re dl tout comme un con
//         curl_global_init(CURL_GLOBAL_DEFAULT);
//         curl = curl_easy_init();
        
//         curl_easy_setopt(curl, CURLOPT_URL, lien);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &webData); //A VERIFIER
//         codeExit = curl_easy_perform(curl); 
//         if(codeExit != CURLE_OK){webData = "/!\\ bad url ?/!\\";}
//         curl_easy_cleanup(curl);
    

//         regex patern("c=\"\\d*\">.*?</blockquote></div></div>");
//         int a = 0;
//         while(regex_search(webData, match , patern))
//         {
//             a++;
//             if(a>temp){//   ON ne recrée pas le tableaux a chaque foit au moin mdrr
//                 liste_poste.push_back(Poste(match.str(0)));
//                 webData = match.suffix();
//             }
//         }
//     }
// }


// void nomFonction(arguments)
// {
//     //Instructions effectuées par la fonction
// }

// string Poste::toString()const{
//     return "identifiant : " + to_string(poste_id) +  "\ncommentaire : " + commentaire + "\n\n raw brut: " + raw_debug ;
// }


// Thread::~Thread()
// {
//     //   delete date;
// }