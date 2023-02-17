#include <iostream>
//#include "include/BackgroundParser.h"
//#include "include/SkinDetection.h"
//#include "include/FaceDetector.h"
//#include "include/FingerPoints.h"
#include "include/Camera.h"
using namespace std;

int main(){
    Camera cam(0);

    Mat frame;
    cam.calibrate(frame);
    return 0;
}
