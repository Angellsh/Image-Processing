#pragma once
#include <iostream>
using namespace std;
struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

};
struct Pixel{
    //reverse order of colors for RGB
    unsigned char blue; //1 byte of data
    unsigned char green;
    unsigned char red;

};