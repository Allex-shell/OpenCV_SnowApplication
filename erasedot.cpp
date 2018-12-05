#include "erasedot.h"
#include <QMouseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <opencv/cv.h>
#include <QFileDialog>
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

using namespace cv;
using namespace std;

EraseDot::EraseDot(Mat &tempMat, int x, int y){
    originalImage = tempMat;
    mouseX=x;
    mouseY=y;
}

Mat EraseDot::convert(){
    convertImage = originalImage.clone();
    Size s = convertImage.size();
    resize(convertImage, convertImage, Size(600, 600), 0, 0, CV_INTER_LINEAR);
    struct bgr{
        uchar blue;
        uchar green;
        uchar red;
    } ;
    bgr tempbgr;
    tempbgr.blue=179;
    tempbgr.green=222;
    tempbgr.red=245;
    int average=0;
    int blue=0;
    int green=0;
    int red=0;
    int count=0;
    if(mouseX>0&&mouseY>0){
        for(int x=mouseX*2-3;x<mouseX*2+2;x++){
            for(int y=mouseY*2-3;y<mouseY*2+2;y++){
                cout<<"blue : "<<(int)convertImage.at<Vec3b>(y,x)[0]<<endl;
                average=average+(int)convertImage.at<Vec3b>(y,x)[0];
                cout<<"average : "<<average<<endl;
            }
        }
    }
    average=average/25-8;
    cout<<"average : "<<average<<endl;
    if(mouseX>0 && mouseY>0){
    int x=mouseX*2-10;
    int y=mouseY*2-10;
    for(int a=0;a<6;a++){
        for(int b=0;b<6;b++){
            for(int k=x+a*3;(k<x+a*3+3)&&(k<s.width);k++){
                for(int l=y+b*3;(l<y+b*3+3)&&(k<s.height);l++){
                    if(convertImage.at<Vec3b>(l,k)[0]<(uchar)average){
                    }
                    else{
                        blue=blue+convertImage.at<Vec3b>(l,k)[0];
                        green=green+convertImage.at<Vec3b>(l,k)[1];
                        red=red+convertImage.at<Vec3b>(l,k)[2];
                        count++;
                        tempbgr.blue=convertImage.at<Vec3b>(l,k)[0];
                        tempbgr.green=convertImage.at<Vec3b>(l,k)[1];
                        tempbgr.red=convertImage.at<Vec3b>(l,k)[2];
                    }
                }
            }
            if(count==0){
                for(int k=x+a*3;(k<x+a*3+3)&&(k<s.width);k++){
                    for(int l=y+b*3;(l<y+b*3+3)&&(k<s.height);l++){
                         convertImage.at<Vec3b>(l,k)[0]=tempbgr.blue;
                         convertImage.at<Vec3b>(l,k)[1]=tempbgr.green;
                         convertImage.at<Vec3b>(l,k)[2]=tempbgr.red;
                    }
                }
            }
            else{
                blue=blue/count;
                green=green/count;
                red=red/count;
                tempbgr.blue=blue;
                tempbgr.green=green;
                tempbgr.red=red;
                for(int k=x+a*3;(k<x+a*3+3)&&(k<s.width);k++){
                    for(int l=y+b*3;(l<y+b*3+3)&&(k<s.height);l++){
                        convertImage.at<Vec3b>(l,k)[0]=blue;
                        convertImage.at<Vec3b>(l,k)[1]=green;
                        convertImage.at<Vec3b>(l,k)[2]=red;
                    }
                }
            }
            count=0;
            blue=0;
            green=0;
            red=0;
        }
    }
}
    return convertImage;
}
