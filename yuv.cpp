#include <iostream>
#include <string>
#include <fstream>
#define CIF_WIDTH 352
#define CIF_HEIGHT 288
#define WVGA_WIDTH 832
#define WVGA_HEIGHT 480
#define HD_WIDTH 1280
#define HD_HEIGHT 720
#define FHD_WIDTH 1920
#define FHD_HEIGHT 1080
#define UHD_WIDTH 3840
#define UHD_HEIGHT 2160

class YuvImage
{
private:
    std::string filename_;
    int width_;
    int height_;

public:
    YuvImage(std::string filename);
    ~YuvImage();
    virtual void getPixel(int x, int y){}

};

YuvImage::YuvImage(std::string filename) : filename_(filename)
{
    std::ifstream file(filename);
    int lenght = filename.length();
    int bytes = lenght /3*2;
    if (bytes ==)





}

YuvImage::~YuvImage()
{
}
