#ifndef MOSAIC_H
#define MOSAIC_H
#include <iostream>
#include <vector>
#include <cv.h>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;


#endif // MOSAIC_H

class Mosaic{
private:
    Mat originalImage;
    Mat convertImage;
    vector <Rect> facePos;
public:
    Mosaic(Mat& tempMat, vector <Rect> &tempPos);
    Mat convertMosaic();
};
