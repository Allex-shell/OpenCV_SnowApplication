#ifndef ERASEDOT_H
#define ERASEDOT_H

#include <iostream>
#include <vector>
#include <opencv/cv.h>
#include <QFileDialog>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>
#include <QString>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

class EraseDot{

private:
    Mat originalImage;
    Mat convertImage;
    int mouseX;
    int mouseY;
    vector<Rect> facePos;


public:
    EraseDot(Mat &tempMat, int x, int y);
    Mat convert();
};


#endif // ERASEDOT_H
