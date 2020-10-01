#include "Image.h"
#include <string>

using namespace std;

Image::Image(string image_raw)//constructeu
{

    smatch match;

    regex patern("(i.4cdn.org/.*/(\\d*).(\\w*)).?\" target=.?\"_blank.?\">(.*)</a> \\((.*) (.*), (\\d*)x(\\d*)\\)");
    if(regex_search(image_raw, match, patern))
    {
        // string tmp;
        // tmp = match.str(1); //stoll
        img_url = match.str(1);
        img_id = stoll(match.str(2), nullptr, 10); //conversiont
        img_extention = match.str(3);
        img_name = match.str(4);

        //on regarde l'ordre  de grandeur est on multiplie par le nombre docter et on a une valeur en oncter 
        switch(match.str(6)[0]) {
        case 'B'://bite
            img_size = stof(match.str(5));
            break;
        case 'K'://un kilo de bite
            img_size = stof(match.str(5))*1000;
            break;
        case 'M':// un MIliiONNN de GROSSE BITE
            img_size = stof(match.str(5))*1000000;
            break;
        case 'G': // LE MIlliare de Byte
            img_size = stof(match.str(5))*1000000000;
            break;
        }

        img_dimention_x = stoi(match.str(7));
        img_dimention_y = stoi(match.str(8));

    }

}

Image::Image(){
}

Image::~Image(){}

float Image::getRatio()const{
    return img_dimention_x/img_dimention_y;
}
string Image::getExtention()const 
{
    return img_extention;
}
string Image::getName()const{
    return img_name;
}
long Image::getId()const{
    return img_id;
}
int Image::getSize()const{
    return img_size;
}
string Image::getDimention()const{
    return img_dimention_x + "x" + img_dimention_y; 
}
string Image::getUrl()const{
    return img_url;
}
bool Image::getExist(){
    if(!img_name.empty()){return true;} //pour opti au pti ognion voir si besoin de comparer autre chause
    else{return false;} // /truccc
}
string Image::getRawData()const{
    return raw_data;
}
string Image::toString()const {
    return 
    " \n        ID-image=" + to_string(img_id) + 
    " \n        img-noms=" + img_name + 
    " \n        img-size=" + to_string(img_size) + 
    " \n        extention=" + img_extention + 
    " \n        dimention=" +  to_string(img_dimention_x) + 
    "x" + to_string(img_dimention_y) +
    "\n        url: "+img_url;// +
   // "\n        Raw data:"+raw_data;

}