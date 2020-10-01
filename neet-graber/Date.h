#ifndef DEF_DATE
#define DEF_DATE
//#include "Date.h"
#include <string>
#include <regex>

class Date
{
    private:
        int jour,mois,annee,seconde,minute,heur;
        std::string raw_data, jourHumain;
        std::regex patern();
        std::smatch match;
    public:
        //constructeur par def
        Date();
        Date(std::string date_raw);
        ~Date();
        int getSeconde()const;
        int getMinute()const;
        int getHeur()const;
        int getJour()const;
        int getMois()const;
        int getAnne()const;
        std::string getHumainJour()const;
        std::string getHumainMois()const;
        std::string toString();
        std::string getRawdata()const;

};
#endif