#ifndef DECOIMAGE2_H
#define DECOIMAGE2_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "asmOpenCV.h"
#include "decoimage.h"


#include <iostream>
#include <vector>

using namespace std;
using namespace cv;
using namespace ASM;

class decoimage2
{
public:
    decoimage2(Mat &tempMatImage,vector<Rect> &temp_pos,vector<Rect> &temp_pos2);
    Mat deco();
    Mat addImage(Mat baseImage, Mat addingImage, Point location, Point center);
private:
    Mat originalMatImage;
    Mat decoMatImage;
    Mat convertMatImage;
    Mat base;
    Mat dec;
    //Mat originalMatImage;
    vector<Rect>face_pos;
    vector<Rect>eye_pos;
};

#endif // DECOIMAGE2_H
