#include <string> 
#include "Cathegorie.h"
#include <curl/curl.h>
using namespace std;
#include <iostream>


/////////////////////////////////////
///faire une biblio pour ranger ça :) 
///////////////////////////////////


//FONCTION DE FDP POUR stoquer la page dans un string 
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{ ////////////////////////////////////////////////SEMENETATION FAUTE
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t curl_devnull(char *ptr, size_t size, size_t nmemb, void *userdata) {
        return size * nmemb;
} 


//fonction GET PAGE
string httpGET_Page(string link){
   
   //declare un string
    string http_data;

    //noms du sockette
    CURL *curl;
    CURLcode codeExit;

    // On convertie un String en char
    char * lien = new char [link.length()+1];
    strcpy (lien, link.c_str());

    //initialise 
    curl_global_init(CURL_GLOBAL_DEFAULT);
    //on declar un sockette
    curl = curl_easy_init();
    
    //on set le lien de destination
    curl_easy_setopt(curl, CURLOPT_URL, lien);
    //on va sortire les data dans la Fonction WriteCallback
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    //on va ecrire dans la variable http_data
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &http_data);
    // //On autorise a suivre une redirection d'url
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    //on simule un fake user agent pour berner le cite 
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Fluffy-Awoo USER AGENT");
    //on desactive la verification du destinataire DANGEUREUX !!!
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    //on applique la requette et on stoquae le code d'erreur
    codeExit = curl_easy_perform(curl);
    //si on est sur un code d'erreur
    if(codeExit != CURLE_OK)
    //on dit quelle numero d'erreur 
    {http_data = "/!\\ " + to_string(codeExit) + " /!\\ URL is : " + lien + " dans GET de cathegorie";}
    //on effectue un clean up pour reset les variable
    curl_easy_cleanup(curl);
    return http_data; //on sort la variable oK
}

//Construceur !
Cathegorie::Cathegorie(string cath, int page_max, bool recusive)//faire valeur par defaut de page max
{
    //on met dans une variable statique la valleur de cathegorie
    cat = cath;

    /////////////////////////////////////////////////////////////
    ///on declar au constructeur un lien addapter a la cahegorie
    /////////////////////////////////////////////////////////////

//on se laisse redireger une foit puis on enregistre la redirection

    //initialise CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    //on crée un object trycurl
    CURL *trycurl;
    //on declar un sockette
    trycurl = curl_easy_init();

    string linkTMP = "https://4chan.org/"+cath+"/";
    //Convertie 
    char *lien = new char [linkTMP.length()+1]; // char * lien
    strcpy (lien, linkTMP.c_str());
    //on va tester le lien
    curl_easy_setopt(trycurl, CURLOPT_URL, lien);
    curl_easy_setopt(trycurl, CURLOPT_USERAGENT, "Fluffy-Awoo USER AGENT");
    curl_easy_setopt(trycurl, CURLOPT_WRITEFUNCTION, curl_devnull); // pour se taire
    curl_easy_setopt(trycurl, CURLOPT_WRITEDATA , NULL); // pour se taire
    curl_easy_setopt(trycurl, CURLOPT_SSL_VERIFYPEER, 0L);    
    curl_easy_perform(trycurl);

    curl_easy_getinfo(trycurl, CURLINFO_REDIRECT_URL, &lien);

    // delete &link;
    //on utilise le destructeur pour detruire link         /// marche pass !
    //link.~string();

    //on redeclare link avec un char en utilisant le constructeur 
    string link = string(lien);

    ////////////////////////////////////////////////////////
    //  string link = "https://boards.4chan.org/"+cath+"/";
    ////////////////////////////////////////////////////////

    //On download les page pour en faire une géante 
    cout << "cathegorie: " << cat << endl;
    for(int v = 0; v < page_max; v++){
        //resultat de la requette + resulta precedant

        //on affiche le numero de page effectuer 
        cout << "j'usqua page 1-9 " << v << ":" << endl;
        full_page = full_page + httpGET_Page(link+to_string(v)); //lien varriable pas oublier 
    }

    cout << "download de " << page_max * 15 <<"environ..."<<endl;

                    // pas oublier de fair un mode quik qui marche avec les cathalogue


    ////////////////////////
    // Creation des Thread//
    ////////////////////////


    //declaration de l'object smatch qui va servire a stoquer le resultat
    smatch match;
    //declaration d'une expression regulierre 
    regex patern("pContainer\" id=\"pc(\\d*?)\".*?<span class=\"subject\">(.*?)</span>.*?data-ut(.*?</blockquote></div><div)");
    
    //la boucle va rechercher en boucle la premierre occurence trouver
    int tmp = 0;
    while(regex_search(full_page, match , patern))
    {
        tmp++;
        cout << "Thread "<< tmp << ": " << match.str(2) << "URL==>" << link + "thread/"+match.str(1)<<endl; //<< lien +'/'+cat+'/'+match.str(1) <<endl;
        //on ajoute a la fin du tableaux de liste_thread la construction d'un thread  
        liste_thread.push_back(Thread(match.str(3),match.str(2),( link + "thread/"+match.str(1)),recusive));
        //on retire l'occurance trouver
        full_page = match.suffix();
    }
    //on sort de la boucle quand il n'y a plus d'occurance 
    
}

//destructeur 
Cathegorie::~Cathegorie(){}


char *Cathegorie::getRedirection() const
{
    return lien;
}

void Cathegorie::toString() const
{
    cout << "to string Cathegorie :\n" << endl;
    //boucle qui va parcourire tout les thread
    for(int u = 0;u<liste_thread.size();u++){
        cout << "\nThread " << u <<" :\n"<<endl;
        //va appliquer un tostringALL a chaque thread trouver 
        liste_thread[u].toStringAll();
    } 
}

void Cathegorie::getListThread()const
{
    for(int u = 0;u<liste_thread.size();u++){
        cout << "noms Thread: " << u <<": "<< liste_thread[u].getTitre() <<endl;
        cout << "to string \n" << liste_thread[u].toString()<<  endl;
        //va appliquer un tostringALL a chaque thread trouver 
    } 
}

Thread Cathegorie::getThread(short numero)const
{
    return liste_thread[numero];
}