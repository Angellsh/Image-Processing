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
    bool operator ==(const Data& otherData) const;


};

void addGreenChannel(Data& data, int scaleFactor);
void scaleRedChannel(Data& data, float scaleFactor);
void scaleBlueChannel(Data& data, float scaleFactor);
void scaleGreenChannel(Data& data, float scaleFactor);
Data change(Data& data);
Data Multiply(Data& data1, Data& data2);
Data Subtract(Data& top, Data& bottom);
Data Overlay(Data& top, Data& bottom);
Data Screen(Data& top, Data& bottom);
Data collage4(Data& data1,Data& data2,Data& data3,Data& data4);
Data readFile(ifstream& file);
Data rotate180(Data& data);
void writeFile(ofstream& file, Data& data);
void Test(string resultFile, string exampleFile);


bool Data::operator==(const Data& otherData) const{
     for (unsigned int i = 0; i < pixels.size(); i++){ 
       if((pixels[i].red != otherData.pixels[i].red )|| (pixels[i].blue != otherData.pixels[i].blue)|| (pixels[i].green != otherData.pixels[i].green)){
        return false;}
        }return true;
}
int main(){
    //reading car object 
    ifstream layerFile("input/layer1.tga", ios_base::binary);
    if (!layerFile.is_open()){   cout<<"file 1 not open";}
    ifstream patterFile("input/pattern1.tga", ios_base::binary);
    if (!patterFile.is_open()){cout<<"patter 1 Not open";}
    ifstream carFile("input/car.tga", ios_base::binary);
    if (!carFile.is_open()){cout<<"Car image is not open"; }
     ifstream layer2("input/layer2.tga", ios_base::binary);
    if (!layer2.is_open()){ cout<<"layer2 image is not open";}
    ifstream pattern2("input/pattern2.tga", ios_base::binary);
    if (!pattern2.is_open()){ cout<<"pattern2 image is not open";}
    ifstream textFile("input/text.tga", ios_base::binary);
   if (!textFile.is_open()){ cout<<"text1 image is not open";}
    ifstream textFile2("input/text2.tga", ios_base::binary);
   if (!textFile2.is_open()){ cout<<"text2 image is not open";}
    ifstream layerRed("input/layer_red.tga", ios_base::binary);
    if (!layerRed.is_open()){ cout<<"layer red image is not open";}
     ifstream layerGreen("input/layer_green.tga", ios_base::binary);
    if (!layerGreen.is_open()){ cout<<"layer green image is not open";}
    ifstream layerBlue("input/layer_blue.tga", ios_base::binary);
    if (!layerBlue.is_open()){ cout<<"layer blue image is not open";}
    ifstream circles("input/circles.tga", ios_base::binary);
    if (!circles.is_open()){ cout<<"circles image is not open";}
    cout<<"all images read"<<endl;


   

   //loading data 
    Data pattern1 = readFile(patterFile);
    Data layer1 = readFile(layerFile);
    Data carImage = readFile(carFile);
    Data layer2Image = readFile(layer2);
    Data pattern2Image =  readFile(pattern2);
    Data textImage = readFile(textFile);
    Data layerBlueImage = readFile(layerBlue);    
    Data layerGreenImage = readFile(layerGreen);
     Data layerRedImage = readFile(layerRed);
     Data text2Image = readFile(textFile2);
     Data circlesImage = readFile(circles);



    //test1
     Data newdata = Multiply(pattern1,layer1);
     ofstream newfile("output/test1.tga", ios_base::binary);
    if (!newfile.is_open()){cout<<"newfile 1 not open";}
     writeFile(newfile, newdata);    
     newfile.close();
     string examplePath1 = "examples/EXAMPLE_part1.tga";
     string resultPath1 = "output/test1.tga";
     cout<<"Test #1: ";
     Test(resultPath1, examplePath1);

    //test 2
    Data newImage2= Subtract(layer2Image, carImage);
    ofstream newFile2("output/test2.tga", ios_base::binary);
    writeFile(newFile2, newImage2);
    newFile2.close();
    string resultPath2 = "output/test2.tga";
    string examplePath2= "examples/EXAMPLE_part2.tga";
    cout<<"Test #2: ";
    Test(resultPath2, examplePath2);


   //test 3
    Data temp = Multiply(pattern2Image,layer1);
    Data newData3 = Screen(textImage, temp);
    ofstream newFile3("output/test3.tga", ios_base::binary);
    if(!newFile3.is_open()){cout<< "it is not open";}
    writeFile(newFile3, newData3);
    newFile3.close();
    string resultPath3 = "output/test3.tga";
    string examplePath3= "examples/EXAMPLE_part3.tga";
    cout<<"Test #3: ";
    Test(resultPath3, examplePath3);


    //test 4
    Data temp2 = Multiply(circlesImage, layer2Image);
    Data newData4= Subtract(pattern2Image,temp2);
    ofstream newFile4("output/test4.tga", ios_base::binary);
    writeFile(newFile4, newData4);
    newFile4.close();
    string resultPath4 = "output/test4.tga";
    string examplePath4= "examples/EXAMPLE_part4.tga";
    cout<<"Test #4: ";
    Test(resultPath4, examplePath4);


    //test 5
     Data newData5= Overlay(layer1,pattern1);
     ofstream newFile5("output/test5.tga", ios_base::binary);
     writeFile(newFile5, newData5);
     string resultPath5 = "output/test5.tga";
     string examplePath5= "examples/EXAMPLE_part5.tga";
     cout<<"Test #5: ";
     Test(resultPath5, examplePath5);


     //test 6
    Data newData6 =carImage;
    addGreenChannel(newData6, 200);
    ofstream newFile6("output/test6.tga", ios_base::binary);
    writeFile( newFile6, newData6);
    string resultPath6 = "output/test6.tga";
     string examplePath6= "examples/EXAMPLE_part6.tga";
     cout<<"Test #6: ";
     Test(resultPath6, examplePath6);


     
     //test 7
     Data newData7 = carImage;
     scaleRedChannel(newData7, 4);
     scaleBlueChannel(newData7, 0);
     ofstream newFile7("output/test7.tga", ios_base::binary);
     writeFile( newFile7, newData7);
     string resultPath7 = "output/test7.tga";
     string examplePath7= "examples/EXAMPLE_part7.tga";
     cout<<"Test #7: ";
     Test(resultPath7, examplePath7);


     
    //test 8
     Data newData8 = carImage;
     ofstream part8_r("output/part8_r.tga", ios_base::binary);
     ofstream part8_g("output/part8_g.tga", ios_base::binary);
     ofstream part8_b("output/part8_b.tga", ios_base::binary);
     Data part8_rImage = carImage; //red
     Data part8_gImage = carImage; //green
     Data part8_bImage = carImage; //blue
     for (int i=0; i<newData7.pixels.size();i++){
          part8_rImage.pixels[i].green=part8_rImage.pixels[i].red;
          part8_rImage.pixels[i].blue=part8_rImage.pixels[i].red;
          part8_gImage.pixels[i].red=part8_gImage.pixels[i].green;
          part8_gImage.pixels[i].blue=part8_gImage.pixels[i].green;
          part8_bImage.pixels[i].red=part8_bImage.pixels[i].blue;
          part8_bImage.pixels[i].green=part8_bImage.pixels[i].blue;

     }
    writeFile(part8_r, part8_rImage );
    cout<<"Test #8_r: ";
    Test("output/part8_r.tga","examples/EXAMPLE_part8_r.tga");
    writeFile(part8_g, part8_gImage );
    cout<<"Test #8_g: ";
    Test("output/part8_g.tga","examples/EXAMPLE_part8_g.tga");
    cout<<"Test #8_b: ";
    writeFile(part8_b,part8_bImage);
    Test("output/part8_b.tga","examples/EXAMPLE_part8_b.tga");


    
    //test 9
    Data combined;
    combined.header=layerRedImage.header;
    combined.pixels.resize(layerRedImage.pixels.size());
    for(unsigned int i=0;i<layerRedImage.pixels.size(); i++){
         combined.pixels[i].red = layerRedImage.pixels[i].red;
         combined.pixels[i].green = layerGreenImage.pixels[i].green;
         combined.pixels[i].blue = layerBlueImage.pixels[i].blue;
     }  
     ofstream newFile9("output/test9.tga", ios_base::binary);
     writeFile(newFile9, combined);
     string resultPath9 = "output/test9.tga";
     string examplePath9 = "examples/EXAMPLE_part9.tga";
     cout<<"Test #9: ";
     Test(resultPath9, examplePath9);


    //test 10
    Data rotated = rotate180(text2Image);
    ofstream newFile10("output/test10.tga", ios_base::binary);
    writeFile(newFile10, rotated);
     cout<<"Test #10: ";
     Test("output/test10.tga", "examples/EXAMPLE_part10.tga");


     //test 11 extra credit
     Data collage= collage4(carImage, circlesImage, pattern1,textImage );     
     ofstream newFile11("output/test11.tga", ios_base::binary);
     writeFile(newFile11, collage);
     cout<<"Test #11 - extra credit: ";
     Test("output/test11.tga", "examples/EXAMPLE_extracredit.tga");


   

    


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
    newImage.header= otherData.header;
    newImage.pixels.resize(data.pixels.size());
    for (unsigned int i=0;i<data.pixels.size();i++){
    float normalBlue = data.pixels[i].blue/255.0f;
    float normalBlueOther = otherData.pixels[i].blue/255.0f;
    float normalRed = data.pixels[i].red/255.0f;
    float normalRedOther = otherData.pixels[i].red/255.0f;
    float normalGreen = data.pixels[i].green/255.0f;
    float normalGreenOther = otherData.pixels[i].green/255.0f;

    newImage.pixels[i].blue=((normalBlue*normalBlueOther)*255.0f)+0.5f;
    newImage.pixels[i].red=((normalRed*normalRedOther)*255.0f)+0.5f;
    newImage.pixels[i].green=((normalGreen*normalGreenOther)*255.0f)+0.5f;
    }return newImage;
  
  }

Data Subtract(Data& top, Data& bottom){
    Data newImage;
    newImage.header=top.header;

    newImage.pixels.resize(top.pixels.size());
    for(unsigned int i=0; i<newImage.pixels.size();i++){
        newImage.pixels[i].blue = max(0, (int)((bottom.pixels[i].blue - top.pixels[i].blue)));
        newImage.pixels[i].green = max(0, (int)((bottom.pixels[i].green - top.pixels[i].green)));
        newImage.pixels[i].red = max(0,(int)((bottom.pixels[i].red - top.pixels[i].red)));

    }
    return newImage;

  
}

Data Screen(Data& top, Data& bottom){
    Data newImage;
    newImage.pixels.resize(top.pixels.size());
    for(unsigned int i=0; i<newImage.pixels.size();i++){
        double normalBlueTop = (double)(top.pixels[i].blue)/255.0f;
        double normalRedTop = (double)(top.pixels[i].red)/255.0f;
        double normalGreenTop = (double)(top.pixels[i].green)/255.0f;
        double normalBlueBottom = (double)(bottom.pixels[i].blue)/255.0f;
        double normalRedBottom = (double)(bottom.pixels[i].red)/255.0f;
        float normalGreenBottom = (double)(bottom.pixels[i].green)/255.0f;

       // newImage.pixels[i].blue= max(0, int( 255.0f-(((255.0f-top.pixels[i].blue)*(255.0f-bottom.pixels[i].blue))/255.)0f)+0.5f));
        newImage.pixels[i].blue=  ((1.0-((1.0-normalBlueTop)*(1.0-normalBlueBottom)))*255.0)+0.5;
        newImage.pixels[i].green= ((1.0-((1.0-normalGreenTop)*(1.0-normalGreenBottom)))*255.0)+0.5;
        newImage.pixels[i].red=  ((1.0-((1.0-normalRedTop)*(1.0-normalRedBottom)))*255.0)+0.5;

    }newImage.header=top.header;
    return newImage;}


Data Overlay(Data& top, Data& bottom){
     Data newImage;
    newImage.pixels.resize(top.pixels.size());
    for(unsigned int i=0; i<newImage.pixels.size();i++){
        float normalBlueTop = (float)(top.pixels[i].blue)/255;
        float normalRedTop = (float)(top.pixels[i].red)/255;
        float normalGreenTop = (float)(top.pixels[i].green)/255;
        float normalBlueBottom = (float)(bottom.pixels[i].blue)/255;
        float normalRedBottom = (float)(bottom.pixels[i].red)/255;
        float normalGreenBottom = (float)(bottom.pixels[i].green)/255;
        if (normalBlueBottom<= 0.5f){newImage.pixels[i].blue = (2*normalBlueBottom*normalBlueTop*255.0f)+0.5f;}
        else{ newImage.pixels[i].blue = ((1-2*(1-normalBlueTop)*(1-normalBlueBottom))*255.0f)+0.5f;}
        if (normalGreenBottom<= 0.5f){newImage.pixels[i].green = (2*normalGreenBottom*normalGreenTop*255.0f)+0.5f;}
        else{ newImage.pixels[i].green = ((1-2*(1-normalGreenTop)*(1-normalGreenBottom))*255.0f)+0.5f;}
        if (normalRedBottom<= 0.5f){newImage.pixels[i].red = (2*normalRedBottom*normalRedTop*255.0f)+0.5f;}
        else{ newImage.pixels[i].red = ((1-2*(1-normalRedTop)*(1-normalRedBottom))*255.0f)+0.5f;}
        }
    newImage.header=top.header;
    return newImage;
}



void addGreenChannel(Data& data, int scaleFactor){
    for (unsigned int i=0; i<data.pixels.size(); i++){
       data.pixels[i].green = min(255, data.pixels[i].green+scaleFactor);
    }
}
void scaleRedChannel(Data& data, float scaleFactor){
     for (unsigned int i=0; i<data.pixels.size(); i++){
       float normalRed= (float)(data.pixels[i].red)/255;
       data.pixels[i].red = min(255, (int)((normalRed*scaleFactor*255)+0.5f));
    }
}
void scaleBlueChannel(Data& data, float scaleFactor){
     for (unsigned int i=0; i<data.pixels.size(); i++){
       float normalBlue= (float)(data.pixels[i].blue)/255;
       data.pixels[i].blue = min(255, (int)((normalBlue*scaleFactor*255.0f)+0.5f));
    }
}
void scaleGreenChannel(Data& data, float scaleFactor){
     for (unsigned int i=0; i<data.pixels.size(); i++){
     float normalGreen= (float)(data.pixels[i].green)/255;
     data.pixels[i].green = min(255, (int)((normalGreen*scaleFactor*255.0f)+0.5f));
    }
}

void Test(string resultFile, string exampleFile){
    ifstream result(resultFile, ios_base::binary);
    ifstream example(exampleFile, ios_base::binary);
    if(! example.is_open()){cout<<"Example didnt open.Failed.";}
    if(! result.is_open()){cout<<"Result didnt open.Failed.";}
    Data resultImage = readFile(result);
    Data exampleImage = readFile(example);
    if(exampleImage==resultImage){
        cout<<"Passed"<<endl;
    }else{ cout<<"Failed"<<endl;}
    
}
Data rotate180(Data& data){
    Data rotated;
    rotated.header=data.header;
    rotated.pixels.resize(data.pixels.size());
    for (unsigned int i=0;i <rotated.pixels.size(); i++){
        rotated.pixels[(rotated.pixels.size() - i-1)].blue = data.pixels[i].blue;
        rotated.pixels[(rotated.pixels.size() - i-1)].red = data.pixels[i].red;
        rotated.pixels[(rotated.pixels.size() - i-1)].green = data.pixels[i].green;
    }return rotated;
}
Data collage4(Data& data1,Data& data2,Data& data3,Data& data4){

    int width  = data1.header.width;
    int height = data1.header.height;
    int newWidth = data1.header.width * 2;
    int newHeight = data1.header.height * 2;
    const int newSize = newWidth * newHeight;
    Data newImage;
    newImage.header = data1.header;
    newImage.header.width = newWidth;
    newImage.header.height = newHeight;
    newImage.pixels.resize(newSize);
    int index = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            newImage.pixels[row * newWidth + col] = data4.pixels[row * width + col];
            newImage.pixels[(row+height)*newWidth+col] = data1.pixels[row * width + col];
            newImage.pixels[row * newWidth + width + col] = data3.pixels[row * width + col];
            newImage.pixels[(row+height)* newWidth +width + col] = data2.pixels[row * width + col];


            }
    } return newImage;
}
