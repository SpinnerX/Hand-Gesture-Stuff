#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <ctime>
#include <thread>
#include "BackgroundParser.h"
#include "SkinDetection.h"
#include "FaceDetector.h"
#include "FingerPoints.h"
#include <thread>
using namespace cv;

class Camera{
public:
    Camera();
    Camera(int type);
    void calibrate(Mat&);
    // void calibrate(Mat& image); // calibrating camera

    void operator()(Mat& image);

    void setWindowProperties();

private:
    void mirrorCam();
    void show(std::string name, Mat& frame);
    void executeImshows();

private:
    int cameraType;
    BackgroundParser parser;
    SkinDetection skinDet;
    FaceDetector faceDet;
    FingerPoints fingerPoints;
    Mat foreground, handMask, points, output;
};