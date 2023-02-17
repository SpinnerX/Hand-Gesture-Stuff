#include "../include/Video.h"
using namespace std;

Video::Video(string filename, string label){
    if(filename == ""){
        this->label = label;
        return;
    }
    if(label == ""){
        this->filename = filename;
        return;
    }
}

bool Video::cameraOpen() const {
    return camera.isOpened();
}

bool Video::videoShow(){
    if(cameraOpen()) imshow(label, frame);
}
