#ifndef DEF_POSTE
#define DEF_POSTE
#include "Poste.h"
#include "Image.h"
#include "Date.h"
#include <string>
#include "regex"

class Poste
{
private:

    Image *meta_image; // *
    int poste_id;
    Date *date;
    std::string commentaire, raw_debug,patern;
    std::smatch match;


public:
    Poste(std::string raw_poste);
    // Date();
    ~Poste();
    std::string getCommentaire()const;
    int getId()const;
    std::string getRaw_debug()const;
    std::string toString()const;
    Date getDate();
    Image getImage();
    bool getExist();
};
#endif