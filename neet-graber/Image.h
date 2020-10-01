#ifndef DEF_IMAGE
#define DEF_IMAGE
#include "Image.h"
#include <regex>
#include <string>

class Image
{
    private:
        long long img_id;
        std::string img_name, img_extention,image_raw,raw_data,img_url;
        int img_dimention_x, img_dimention_y, img_size,existance;
        std::regex patern();
        std::smatch match;
    public:
        Image();
        Image(std::string image_raw);
        ~Image();
        float getRatio()const;
        std::string getExtention()const;
        std::string getName()const;
        std::string getRawData()const;
        long getId()const;
        int getSize()const;
        std::string getDimention()const;
        std::string getUrl()const;
        std::string toString()const;
        bool getExist();


};
#endif