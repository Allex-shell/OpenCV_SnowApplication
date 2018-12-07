#ifndef DECOIMAGE_H
#define DECOIMAGE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "asmOpenCV.h"


#include <iostream>
#include <vector>

using namespace std;
using namespace cv;
using namespace ASM;

class decoimage
{
public:
    decoimage(Mat &tempMatImage,vector<Rect> &temp_pos);
    Mat deco();
    Mat addImage(Mat baseImage, Mat addingImage, Point location);
private:
    Mat originalMatImage;
    Mat decoMatImage;
    Mat convertMatImage;
    Mat base;
    Mat dec;
    //Mat originalMatImage;
    vector<Rect>face_pos;
};

#endif // DECOIMAGE_H
