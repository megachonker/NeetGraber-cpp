#include "Image.h"
#include "Poste.h"
#include "Date.h"
#include <string>
#include "regex"


using namespace std;

Poste::Poste(std::string raw_poste)
{


//trouver les id d'un tread
//id="pc\d*"


//Thread construit poste avec:
    //c="\d*">(.*?)</blockquote></div></div>


//Constructeur de poste

//^(.*?)<a.*<a href="(.*)</div><a.*id="m(\d*)">(.*?)$   // BETERRRRRRRRR

    //groupe 1 >> dans date
        //FAIT
    //groupe 2 >> dans image
        //FAIT:
        // ^(i.4cdn.org/.*/(\d*).(\w*))" target="_blank">(.*)</a> \((.*) (.*), (\d*)x(\d*)\)$

    //groupe 3  = id
    //groupe 4 = comentaire

    //tmp img         <div class="fileText" id="fT199691108">File: <a href="//i.4cdn.org/a/1582817593491.jpg" target="_blank">321901000608.jpg</a> \(370 KB, 674x(\d*)\)</div>

    //trouver les commentaire
    //<blockquote class="postMessage" id="m\d*">(.*?)$ 

    //trouver les date
    //<span class="dateTime postNum" data-utc="\d*">(.*?)<a
    

    smatch match;
    //regex patern("^(.*?)<a.*<a href=\"//(.*)</div><a.*id=\"m(\\d*)\">(.*?)$");
    //regex patern("^c=\"\\d*\">(.*?)<a.*<a href=\"(.*)<\\/div><a.*id=\"m(\\d*)\">(.*?)</blockquote></div></div>");
    regex patern("^c=\"\\d*\">(.*?)(?:<a.*<a href=\"(.*)<\\/div>)?<a.*id=\"m(\\d*)\">(.*?)</blockquote>");//</div></div>");
    if(regex_search(raw_poste, match, patern))
    {
        date = new Date(match.str(1));
        meta_image = new Image(match.str(2));

        //Image meta_image(match.str(2));

        // string tmp;
        // tmp = match.str(1);
        // Date date(match.str(1));
        // Image meta_image(match.str(2));
        poste_id = stoi(match.str(3));
        commentaire = match.str(4);

    }
    //else{cout<< "Probleme pour trouver la chaine image" <<endl;}
    raw_debug = raw_poste;
}


// Date const & getDate(){
//     return *date;
// }



// Date const & getDate(){
//     return *this;
// }

Date Poste::getDate(){
    return *date;
}

Image Poste::getImage(){
    return *meta_image;
}

string Poste::getCommentaire()const{
    return commentaire;
}
string Poste::getRaw_debug()const{
    return raw_debug;
}
int Poste::getId()const{
    return poste_id;
}
string Poste::toString()const{
    string temp;
    temp = "     identifiant = " + to_string(poste_id);
    if(!commentaire.empty()){temp =temp + "\n        commentaire : " + commentaire;}    
    if(meta_image->getExist()){temp =temp + "\n         Dump Image: " + meta_image->toString();}    ///BUUG
    temp = temp + "\n       Dump Date: " + date->toString();
    
     // + "\n\n raw brut: " + raw_debug ;
    return temp;
}


Poste::~Poste()
{
    //   delete date;
}