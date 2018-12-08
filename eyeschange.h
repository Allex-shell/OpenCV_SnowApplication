#ifndef EYESCHANGE_H
#define EYESCHANGE_H

#include <iostream>

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QString>
#include <cv.h>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <QMouseEvent>
#include "asmOpenCV.h"

using namespace cv;
using namespace std;
using namespace ASM;

namespace Ui {
class MainWindow;
}

class eyeschange{
private:
    Ui::MainWindow *ui;
    QGraphicsScene *originalScene;
    QGraphicsScene *convertScene;
    QGraphicsPixmapItem *originalImage;
    QGraphicsPixmapItem *convertImage;

    vector <Rect> eye_pos_1;
    vector <Rect> eye_pos_2;



    Mat originalMatImage;
    Mat convertMatImage;
    Mat base;
    Mat gray;
public:
    eyeschange(Mat &tempImage_1, Mat &tempImage_2, vector <Rect> &temp_ep1, vector <Rect> &temp_ep2,vector <Rect> &temp_ep3,vector <Rect> &temp_ep4);
    Mat combineImage(Mat baseImage, Mat addingImage);
    Mat swapEyes();
    vector<Rect> eye_pos;
    vector<Rect> face_pos;
    vector<Rect> face_pos1;
    double rate;
private slots:

};

#endif // EYESCHANGE_H
