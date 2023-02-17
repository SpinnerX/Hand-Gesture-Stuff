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

/*
    Handling video frames
*/
class Video{
public:
    Video() = default;
    Video(std::string filename="", std::string label="");

    bool cameraOpen() const;

    bool videoShow();

    friend VideoCapture& operator>>(VideoCapture& cam, Video& video){
        cam >> video.frame;
        return cam;
    }

private:
    VideoCapture camera;
    Mat frame;
    std::string filename;
    std::string label;
};
