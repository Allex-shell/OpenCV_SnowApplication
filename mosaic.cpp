#include "mosaic.h"
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

using namespace std;
using namespace cv;

Mosaic::Mosaic(Mat& tempMat, vector <Rect> &tempPos){
    originalImage=tempMat;
    facePos=tempPos;
}

Mat Mosaic::convertMosaic(){
    convertImage=originalImage.clone();
        Size s = convertImage.size();
        cout<<s<<endl;
        uchar *data_output = convertImage.data;
        uchar *data_input = convertImage.data;
        uchar tempB;
        uchar tempG;
        uchar tempR;
        int blue=0;
        int green=0;
        int red=0;
        int divider;
        if(s.height<1000){
            divider=10;
        }
        else{
            divider=80;
        }
        for(int k=0;k<facePos.size();k++){
            int x=facePos[k].x;
            int y=facePos[k].y;
            int widthEnd=facePos[k].width + x;
            int heightEnd=facePos[k].height + y;
            for(int i=0;i<(facePos[k].width/divider);i++){
                for(int j=0;j<(facePos[k].height/divider);j++){
                    for(int a=x+i*divider;(a<facePos[k].x+i*divider+divider)&&(a<widthEnd);a++){
                        for(int b=y+j*divider;(b<facePos[k].y+j*divider+divider)&&(b<heightEnd);b++){
                            blue=blue + data_input[b * s.width * 3 + a * 3 + 0];
                            green=green + data_input[b * s.width * 3 + a * 3 + 1];
                            red=red + data_input[b * s.width * 3 + a * 3 + 2];
                        }
                    }
                    tempB=blue/(divider*divider);
                    tempG=green/(divider*divider);
                    tempR=red/(divider*divider);
                    for(int a=x+i*divider;(a<facePos[k].x+i*divider+divider)&&(a<widthEnd);a++){
                        for(int b=y+j*divider;(b<facePos[k].y+j*divider+divider)&&(b<heightEnd);b++){
                            data_output[b * s.width * 3 + a * 3 + 0]=tempB;
                            data_output[b * s.width * 3 + a * 3 + 1]=tempG;
                            data_output[b * s.width * 3 + a * 3 + 2]=tempR;
                        }
                    }
                    blue=0;
                    green=0;
                    red=0;
                }
            }
        }
    return convertImage;
}
