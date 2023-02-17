#include "../include/Camera.h"
#include <thread>
#include <atomic>
using namespace std;

Camera::Camera(){
    cameraType = 0;
    parser = BackgroundParser();
    skinDet = SkinDetection();
    faceDet = FaceDetector();
    fingerPoints = FingerPoints();
}

Camera::Camera(int type){
    cameraType = type;
    parser = BackgroundParser();
    skinDet = SkinDetection();
    faceDet = FaceDetector();
    fingerPoints = FingerPoints();
}

void Camera::calibrate(Mat& root){
    VideoCapture camera(cameraType);
    // setWindowProperties();

    bool cameraOpen = camera.isOpened();

    if(!cameraOpen){
        cout << "Cannot open camera index!" << endl;
        return;
    }



    while(cameraOpen){
        camera >> root;

        output = root.clone();

        int key = waitKey(1);

        if(key == 27) cameraOpen = false;

        skinDet.drawSkinColorSampler(output);
        foreground = parser.getForeground(output);

        faceDet.removeFaces(output, foreground);
        
        handMask = skinDet.getSkinMask(foreground);
        points = fingerPoints.findFingersPoints(handMask, output);

        parser.calibrate(root);
        skinDet.calibrate(root);
        // else if(key == 98) parser.calibrate(frame); // B
        // else if(key == 115) skinDet.calibrate(frame); // S

        mirrorCam();
        
        executeImshows();
    }
}

void Camera::setWindowProperties(){
    // namedWindow("Name", WINDOW_NORMAL);
    // setWindowProperty("Name", WND_PROP_FULLSCREEN);
}

// Handle rotating images/videos
void Camera::mirrorCam(){
    // flip(handMask, handMask, 0); // This flips the video upside down.
    flip(handMask, handMask, 1); // This flips the video upside down.
    setWindowProperties();
}

void Camera::show(string name, Mat& frame){
    imshow(name, frame);
}

void Camera::executeImshows(){
    //thread th1(output);
    //th1.join();
    imshow("Output",output);

    // thread th2(show, nullptr);
    // th2.join();
    imshow("Hand Mask",handMask);

    //thread th3(skinDet);
    //th3.join();
    //imshow("Skin Detection", skinDet);

    //thread th4(foreground));
    //th4.join();
    //imshow("Foreground", foreground);
}

void Camera::operator()(Mat& cam){
    calibrate(cam);
}
