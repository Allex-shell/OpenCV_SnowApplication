#include "decoimage.h"


decoimage::decoimage(Mat& tempMatImage,vector<Rect> &temp_pos)
{
    originalMatImage= tempMatImage;
    face_pos = temp_pos;
}

Mat decoimage::deco()
{
    QImage image;
    convertMatImage = originalMatImage.clone();
    decoMatImage = imread("/Users/janghyukjin/untitled/resource/rudolph.png",cv::ImreadModes::IMREAD_COLOR);
    for(int i=0;i<(int)face_pos.size();i++){
        resize(decoMatImage, decoMatImage, cv::Size(face_pos[i].width,face_pos[i].height*0.8), 0, 0, CV_INTER_LINEAR);
        Point center(face_pos[i].x, face_pos[i].y-face_pos[i].height/1.2);
        convertMatImage = addImage(convertMatImage, decoMatImage, center);
    }
    return convertMatImage;
}


Mat decoimage::addImage(Mat baseImage, Mat addingImage, Point location)
{
    base = baseImage.clone();
    Mat add1 = addingImage.clone();
    Size s2 = add1.size();
    Size s = base.size();
    uchar *data_input1 = baseImage.data;
    uchar *data_input2 = addingImage.data;
    uchar tempB;
    uchar tempG;
    uchar tempR;
    int blue=0;
    int green=0;
    int red=0;
    for(int k=0;k<1;k++){
        int x = location.x;
        int y = location.y;
        for(int i=0;i<add1.rows;i++){
            for(int j=0;j<add1.cols;j++){
                blue = add1.at<Vec3b>(i,j)[0];
                green = add1.at<Vec3b>(i,j)[1];
                red = add1.at<Vec3b>(i,j)[2];
                if(add1.at<Vec3b>(i,j)[0]!=0&&add1.at<Vec3b>(i,j)[1]!=0&&add1.at<Vec3b>(i,j)[2]!=0){
                    base.at<Vec3b>(i+y,j+x)[0] = blue;
                    base.at<Vec3b>(i+y,j+x)[1] = green;
                    base.at<Vec3b>(i+y,j+x)[2] = red;
                }
            }
        }
    }
    return base;
}

