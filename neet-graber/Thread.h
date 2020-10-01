#ifndef DEF_THREAD
#define DEF_THREAD
#include <string>
#include <regex>
#include <vector>
#include "Poste.h"
#include <curl/curl.h>

class Thread : public Poste 
{
    private:
        //on va crée un tableaux (vector) d'object POSTE qui s'appelera liste poste 
        std::vector<Poste> liste_poste;
        std::string titre,url,webData,commentaire,lien;
        int nb_replies, nb_image;
        std::regex patern; //patern() ????
        std::smatch match;

    public:
        //constructeur par def
        Thread(std::string post_raw, std::string noms,std::string url); // constructeur recusiff

        Thread(std::string post_raw, std::string noms,std::string url, bool recursive); 

        // ~Thread();
        //std::string getCommentaire()const;
        std::string getTitre()const;

        unsigned int getNombreRep()const; //on va le compter a la main
        unsigned int getNombreImage()const; // on va le compter
        unsigned int getNombreMsg()const; // on va le compter
        std::string getThreadFlow()const;
        Poste getPoste(short numero)const;
        void dumpPoste();
        void toStringAll()const;

        
        void refresh();
        void fill();
        

};
#endif