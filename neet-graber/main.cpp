#include "Image.h"
#include "Poste.h"
#include "Date.h" 
#include "Thread.h"
#include <iostream>
#include "Cathegorie.h"
#include <regex>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Bienvenu dans Nee-graber Version Beta"<< endl;

    // for (int i = 0; i < argc; ++i){
    //     cout << argv[i] << "\n"; 
    // }

    // Cathegorie animer(argv[0],argv[1],argv[2]);

    // string cat = argv[0];
    // int page = int(argv[1]);
    // bool recurs = int(argv[2]);


    Cathegorie animer("a",1,false);
    animer.getListThread();

    /*
    while (true)
    {
        bool booole;
        string choixCat,choixRecurs;
        int choixPage;    
        cout << "cathegorie : " <<endl;
        cin >> choixCat;
        cout << "nombre de page a tester" << endl;
        cin >> choixPage;
        cout << "recherche récustive yes ou no" <<endl;
        cin >> choixRecurs;
        if(choixRecurs == "yes"){booole= true;}else{ booole = false;}
        Cathegorie animer(choixCat,choixPage,booole);
        animer.getListThread();
        cout << "afficher quoi ? tout, thread"<< endl;
        cin >> choixCat;
        if(choixCat == "tout"){
            animer.toString();
        }
        else if(choixCat == "thread"){
            cout << "numero de thread stp"<<endl;
            cin >> choixPage;
            cout << animer.getThread(choixPage).toString()<<endl;
            cout << "afficher tout ? yes no" << endl;
            cin >> choixCat;
            if(choixCat == "yes"){
                animer.getThread(choixPage).toStringAll();
            }
            else{
                cout << "quelle thread afficher "<<endl;
                cin >> choixPage;
                animer.getThread(choixPage).getPoste(choixPage).toString();
            }
        }

    // Cathegorie animer("a",3,true);
    }
    */
    // Cathegorie animer("b",11,false);
    // Cathegorie cute("c",1,true);
    // Cathegorie wallpaper("w",2,false);  

    // animer.toString();
    // cute.toString();
    // wallpaper.toString();

    return 0;
}