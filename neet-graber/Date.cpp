#include "Date.h"
#include <string>
#include <regex>
#include <iostream>

using namespace std;

Date::Date(string date_raw) //: raw_data(date_raw)
{
    //format de la date: 01/22/30(Sat)10:14:34
    raw_data = date_raw;

    smatch match;
    regex patern("(..)/(..)/(..)\\((.*)\\)(..):(..):(..)");
    if(regex_search(raw_data, match, patern))
    {
        mois = stoi(match.str(0));
        jour = stoi(match.str(2));
        annee = stoi(match.str(3));
        jourHumain = match.str(4);
        heur = stoi(match.str(5));
        minute = stoi(match.str(6));
        seconde = stoi(match.str(7));
    }
}

//constructeur par def
Date::Date()
{
    raw_data = "azer";
    annee = 1000;
    seconde =0;
    minute=0;
    heur=0;
    jour=0;
    mois=0;
    jourHumain = "lundi";
}

Date::~Date(){}

int Date::getSeconde()const{
    return seconde;
}
int Date::getMinute() const{
    return minute;
}
int Date::getHeur()const{
    return heur;
}
int Date::getJour()const{
    return jour;
}
int Date::getMois()const{

    return mois;
}
int Date::getAnne()const{
    return annee;
}
string Date::getRawdata()const{
    return raw_data;
}
string Date::getHumainJour()const{  
    return jourHumain;
}
string Date::getHumainMois()const{

    return "flm de calculer"; //calculer
}
string Date::toString(){
    // to_string(mois)
    return "\n        date: "+ to_string(jour)+"/"+to_string(mois)+"/"+to_string(annee)+"   Heur: "+to_string(heur)+":"+to_string(minute)+"."+to_string(seconde) + " Jour-Humain: " + getHumainJour() + " \n";
}
