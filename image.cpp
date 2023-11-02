#include <fstream>
#include <vector>
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
struct Data{
    vector<Pixel> pixels;
    Header header;
    Pixel pixel;

};
Data change(Data& data);
Data Multiply(Data& data1, Data& data2);
void Screen();
Data Subtract(Data& top, Data& bottom);
void Overlay();
Data Screen(Data& top, Data& bottom);
Data readFile(ifstream& file);
void writeFile(ofstream& file, Data& data);


int main(){
    //reading car object 
    ifstream layerFile("layer1.tga", ios_base::binary);
    if (!layerFile.is_open()){
        cout<<"file 1 not open";
    }
    cout<<"file 1 open"<<endl;

    //18 bytes lngth for header
    Data layer1 = readFile(layerFile);
    ifstream patterFile("pattern1.tga", ios_base::binary);
    if (!patterFile.is_open()){
        cout<<"2. Not open";
    }
    cout<<"file 2 open"<<endl;
    Data pattern1 = readFile(patterFile);
    Data newdata = Multiply(pattern1,layer1);
    ofstream newfile("test1.tga");
    if (!newfile.is_open()){
        cout<<"3. Not open";
    }
    cout<<"file for output is open"<<endl;
  
    writeFile(newfile, newdata);    
    //test 2
    ifstream carFile("car.tga", ios_base::binary);
    if (!carFile.is_open()){
        cout<<"Car image is not open";
    }
     ifstream layer2("layer2.tga", ios_base::binary);
    if (!layer2.is_open()){
        cout<<"layer2 image is not open";
    }
    Data carImage = readFile(carFile);
    Data layer2Image = readFile(layer2);
    Data newImage2= Subtract(layer2Image, carImage);
    ofstream newFile2("test2.tga");
    writeFile(newFile2, newImage2);
   //test 3
    ifstream pattern2("pattern2.tga", ios_base::binary);
    Data pattern2Image =  readFile(pattern2);
    ifstream textFile("text.tga", ios_base::binary);
    Data textImage = readFile(textFile);
    Data temp = Multiply(layer1, pattern2Image);
    Data test3 = Screen(layer1, pattern1);
    ofstream newFile3("test3.tga");
    writeFile(newFile3, test3);
    
    


    //pixels start bottom left corner -0
    return 0;
}
Data readFile(ifstream& file){
    Data data;
    
    file.read(&data.header.idLength, sizeof(data.header.idLength));
    file.read(&data.header.colorMapType, sizeof(data.header.colorMapType));
    file.read(&data.header.dataTypeCode, sizeof(data.header.dataTypeCode));
    file.read(reinterpret_cast<char*>(&data.header.colorMapOrigin), sizeof(data.header.colorMapOrigin));
    file.read(reinterpret_cast<char*>(&data.header.colorMapLength), sizeof(data.header.colorMapLength));
    file.read(reinterpret_cast<char*>(&data.header.colorMapDepth), sizeof(data.header.colorMapDepth));
    file.read(reinterpret_cast<char*>(&data.header.xOrigin), sizeof(data.header.xOrigin));
    file.read(reinterpret_cast<char*>(&data.header.yOrigin), sizeof(data.header.yOrigin));
    file.read(reinterpret_cast<char*>(&data.header.width), sizeof(data.header.width));
    file.read(reinterpret_cast<char*>(&data.header.height), sizeof(data.header.height));
    file.read(&data.header.bitsPerPixel, sizeof(data.header.bitsPerPixel));
    file.read(&data.header.imageDescriptor, sizeof(data.header.imageDescriptor));
    vector<Pixel> pixels(data.header.width*data.header.height);
    data.pixels.resize(data.header.width*data.header.height);
    for(int i=0;i<pixels.size();i++){
        
        file.read(reinterpret_cast<char*>(&data.pixel.blue), sizeof(data.pixel.blue));
        file.read(reinterpret_cast<char*>(&data.pixel.green), sizeof(data.pixel.green));
        file.read(reinterpret_cast<char*>(&data.pixel.red), sizeof(data.pixel.red));
        data.pixels[i] = data.pixel;
    }
    return data;
}
void writeFile(ofstream& file, Data& data){
    file.write(reinterpret_cast<char*>(&data.header.idLength), sizeof(data.header.idLength));
    file.write(reinterpret_cast<char*>(&data.header.colorMapType), sizeof(data.header.colorMapType));
    file.write(reinterpret_cast<char*>(&data.header.dataTypeCode), sizeof(data.header.dataTypeCode));
    file.write(reinterpret_cast<char*>(&data.header.colorMapOrigin), sizeof(data.header.colorMapOrigin));
    file.write(reinterpret_cast<char*>(&data.header.colorMapLength), sizeof(data.header.colorMapLength));
    file.write(reinterpret_cast<char*>(&data.header.colorMapDepth), sizeof(data.header.colorMapDepth));
    file.write(reinterpret_cast<char*>(&data.header.xOrigin), sizeof(data.header.xOrigin));
    file.write(reinterpret_cast<char*>(&data.header.yOrigin), sizeof(data.header.yOrigin));
    file.write(reinterpret_cast<char*>(&data.header.width), sizeof(data.header.width));
    file.write(reinterpret_cast<char*>(&data.header.height), sizeof(data.header.height));
    file.write(&data.header.bitsPerPixel, sizeof(data.header.bitsPerPixel));
    file.write(&data.header.imageDescriptor, sizeof(data.header.imageDescriptor));
    for (unsigned int i=0; i< data.pixels.size();i++){
        file.write(reinterpret_cast<char*>(&data.pixels[i].blue), sizeof(data.pixels[i].blue));
        file.write(reinterpret_cast<char*>(&data.pixels[i].green), sizeof(data.pixels[i].green));
        file.write(reinterpret_cast<char*>(&data.pixels[i].red), sizeof(data.pixels[i].red));



    }file.close();
    




}
//for initial testing
Data change(Data& data){
    Data newImage;
    newImage.pixels.resize(data.pixels.size());
    for (int i=0;i<data.pixels.size();i++){
        newImage.pixels[i].blue = 255;
      //  if(newImage.pixels[i].blue >255){newImage.pixels[i].blue=255;}
        newImage.pixels[i].green = 100;
       // if(newImage.pixels[i].green >255){newImage.pixels[i].green=255;}
        newImage.pixels[i].red = 150;
       // if(newImage.pixels[i].red >255){newImage.pixels[i].red=255;}
    }
    newImage.header= data.header;
    return newImage;
}

Data Multiply(Data& data, Data& otherData){
    Data newImage;
    newImage.pixels.resize(data.pixels.size());
    for (unsigned int i=0;i<data.pixels.size();i++){
       float temp1 = (float)(data.pixels[i].blue*otherData.pixels[i].blue);
       newImage.pixels[i].blue=float((temp1/255.05)+0.5f);
       float temp2 = (float)(data.pixels[i].green*otherData.pixels[i].green);
       newImage.pixels[i].green = float((temp2/255)+0.5f);
       float temp3 = (float)(data.pixels[i].blue*otherData.pixels[i].red);
       newImage.pixels[i].red=float((temp3/255)+0.5f);
 
    }
    newImage.header=data.header;
    return newImage;
    }
Data Subtract(Data& top, Data& bottom){
    Data newImage;
    newImage.pixels.resize(top.pixels.size());
    for(unsigned int i=0; i<newImage.pixels.size();i++){
        newImage.pixels[i].blue = max(0, (int)(bottom.pixels[i].blue - top.pixels[i].blue));
        newImage.pixels[i].green = max(0, (int)(bottom.pixels[i].green - top.pixels[i].green));
        newImage.pixels[i].red = max(0,(int)(bottom.pixels[i].red - bottom.pixels[i].red));

    }
    newImage.header=top.header;
    return newImage;

  
}

Data Screen(Data& top, Data& bottom){
    Data newImage;
    newImage.pixels.resize(top.pixels.size());
    for(unsigned int i=0; i<newImage.pixels.size();i++){
        newImage.pixels[i].blue= max(0, int( 1-((1-top.pixels[i].blue)*(1-bottom.pixels[i].blue))/255.0f));
        newImage.pixels[i].green= max(0, int( 1-((1-top.pixels[i].green)*(1-bottom.pixels[i].green))/255.0f));
        newImage.pixels[i].green= max(0, int( 1-((1-top.pixels[i].red)*(1-bottom.pixels[i].red))/255.0f));


    }
    newImage.header=top.header;
    return newImage;

}

    






