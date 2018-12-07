#include "decoimage2.h"

decoimage2::decoimage2(Mat& tempMatImage,vector<Rect> &temp_pos, vector<Rect> &temp_pos2)
{
    originalMatImage= tempMatImage;
    face_pos = temp_pos;
    eye_pos = temp_pos2;
}

Mat decoimage2::deco()
{
    QImage image;
    convertMatImage = originalMatImage.clone();
    cout<<convertMatImage.size()<<endl;
    decoMatImage = imread("/Users/janghyukjin/untitled/resource/cheek.png",cv::ImreadModes::IMREAD_COLOR);
    for(int i=0;i<(int)face_pos.size();i++){
        resize(decoMatImage, decoMatImage, cv::Size(eye_pos[i].width,eye_pos[i].height*0.6), 0, 0, CV_INTER_LINEAR);
        Point centerN(face_pos[i].x+eye_pos[i].x/2,
        face_pos[i].y+eye_pos[i].y+(eye_pos[i].height));
        Point centerE(face_pos[0].x+eye_pos[1].x*1.2,
        face_pos[0].y+eye_pos[1].y+(eye_pos[1].height));
        convertMatImage = addImage(convertMatImage, decoMatImage, centerN, centerE);
    }
    decoimage Deco = decoimage(convertMatImage, face_pos);
    convertMatImage = Deco.deco();
    return convertMatImage;

}


Mat decoimage2::addImage(Mat baseImage, Mat addingImage, Point location, Point center)
{
    base = baseImage.clone();
    Mat add1 = addingImage.clone();
    Size s2 = add1.size();
    Size s = base.size();
    cout<<s<<endl;
    cout<<add1.at<Vec3b>(0,0)<<endl;
    cout<<location.x<<" kkk "<<location.y<<endl;
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
        int x1 = center.x;
        int y1 = center.y;
        for(int i=0;i<add1.rows;i++){
            for(int j=0;j<add1.cols;j++){
                blue = add1.at<Vec3b>(i,j)[0];
                green = add1.at<Vec3b>(i,j)[1];
                red = add1.at<Vec3b>(i,j)[2];
                if(add1.at<Vec3b>(i,j)[0]!=0&&add1.at<Vec3b>(i,j)[1]!=0&&add1.at<Vec3b>(i,j)[2]!=0){
                    base.at<Vec3b>(i+y,j+x)[0] = blue;
                    base.at<Vec3b>(i+y,j+x)[1] = green;
                    base.at<Vec3b>(i+y,j+x)[2] = red;
                    base.at<Vec3b>(i+y1,j+x1)[0] = blue;
                    base.at<Vec3b>(i+y1,j+x1)[1] = green;
                    base.at<Vec3b>(i+y1,x1)[2] = red;
                }
            }
        }
    }
    return base;
}

