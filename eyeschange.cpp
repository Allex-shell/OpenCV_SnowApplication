#include "eyeschange.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

eyeschange::eyeschange(Mat &tempImage_1, Mat &tempImage_2, vector <Rect> &temp_ep1, vector <Rect> &temp_ep2, vector <Rect> &temp_ep3,vector <Rect> &temp_ep4)
{
    originalMatImage=tempImage_1;
    convertMatImage=tempImage_2;
    eye_pos=temp_ep1;
    eye_pos_1=temp_ep2;
    face_pos=temp_ep3;
    face_pos1=temp_ep4;

    String face_cascade1 = "/Users/janghyukjin/untitled/resource/haarcascade_frontalface_default.xml";
    String eye_cascade1="/Users/janghyukjin/untitled/resource/haarcascade_eye.xml";

    CascadeClassifier face1;
    CascadeClassifier eye1;

    if(convertMatImage.data==NULL){
        cout<<"image open fail"<<endl;
    }

    if(!face1.load(face_cascade1) || !eye1.load(eye_cascade1)){
        cout << "Cascade fail" << endl;
    }
    cvtColor(convertMatImage, gray, CV_RGB2GRAY);


    face1.detectMultiScale(gray, face_pos1, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE,Size(10,10));//얼굴 검출



    for(int i=0;i<(int)face_pos1.size();i++){

        Mat roi1 = gray(face_pos1[i]);//관심영역 설정
        eye1.detectMultiScale(roi1, eye_pos_1,1.1,3,0|CV_HAAR_SCALE_IMAGE,Size(10,10));//눈 검출

        for(int j=0;j<(int)eye_pos_1.size();j++){
            Point center(face_pos1[i].x+eye_pos_1[j].x+(eye_pos_1[j].width/2),
                        face_pos1[i].y+eye_pos_1[j].y+(eye_pos_1[j].height/2));
            int radius = cvRound((eye_pos_1[j].width+eye_pos_1[j].height)*0.2);
            //circle(convertMatImage,center,radius,Scalar(0,0,255),2);
        }
    }
}

Mat eyeschange::swapEyes()
{
    rate = (double)eye_pos[0].width/(double)eye_pos_1[0].width;
    resize(convertMatImage, convertMatImage, cv::Size(originalMatImage.cols*rate,originalMatImage.rows*rate), 0, 0, CV_INTER_LINEAR);
    for(int i=0;i<1;i++){
        convertMatImage = combineImage(originalMatImage, convertMatImage);
    }
    return convertMatImage;
}

Mat eyeschange::combineImage(Mat baseImage, Mat addingImage)
{
    base = baseImage.clone();
    Mat add1 = addingImage.clone();
    uchar *data_input1 = baseImage.data;
    uchar *data_input2 = addingImage.data;
    uchar tempB;
    uchar tempG;
    uchar tempR;
    int blue=0;
    int green=0;
    int red=0;

    int x[2] = {face_pos[0].x+eye_pos[0].x, face_pos[0].x+eye_pos[1].x};
    int y[2] = {face_pos[0].y+eye_pos[0].y,face_pos[0].y+eye_pos[1].y};
    double x1[2] = {(int)(face_pos1[0].x+eye_pos_1[0].x)*rate,(int)(face_pos1[0].x+eye_pos_1[1].x)*rate};
    double y1[2] = {(int)(face_pos1[0].y+eye_pos_1[0].y)*rate,(int)(face_pos1[0].y+eye_pos_1[1].y)*rate};

    for(int k=0;k<2;k++){
        for(int i=0;i<eye_pos[k].width;i++){
            for(int j=0;j<eye_pos[k].height;j++){
                blue = base.at<Vec3b>(y[k]+i,x[k]+j)[0];
                green = base.at<Vec3b>(y[k]+i,x[k]+j)[1];
                red = base.at<Vec3b>(y[k]+i,x[k]+j)[2];
                add1.at<Vec3b>(y1[k]+i,x1[k]+j)[0] = blue;
                add1.at<Vec3b>(y1[k]+i,x1[k]+j)[1] = green;
                add1.at<Vec3b>(y1[k]+i,x1[k]+j)[2] = red;
            }
        }
    }
    return add1;
}


