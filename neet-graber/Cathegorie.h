#ifndef DEF_CATHEGORIE
#define DEF_CATHEGORIE

#include <string> 
#include "Thread.h"


class Cathegorie
{
private:
    std::string cat,full_page;
    char * lien;//redirection !!!
    std::vector<Thread> liste_thread;


public:
    Cathegorie(std::string cath, int page_max, bool recusive);
    ~Cathegorie();

    void getListThread()const;
    void toString()const;
    char * getRedirection()const; //je sais pas ce que * :()
    Thread getThread(short numero)const;

};




#endif