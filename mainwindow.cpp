#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    originalScene = new QGraphicsScene(this);
    convertScene = new QGraphicsScene(this);
    originalImage = new QGraphicsPixmapItem();
    convertImage = new QGraphicsPixmapItem();
    originalScene->addItem(originalImage);
    convertScene->addItem(convertImage);
    ui->convertGraphicsView->setScene(convertScene);
    ui->originalGraphicsView->setScene(originalScene);

    this->setWindowTitle("의무경찰");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_clicked()
{
    cout<<"open click"<<endl;
    QString qsfileName = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "../", tr("Image Files (*.png *.jpeg *.bmp)"));
    if(!qsfileName.isEmpty()){
        openFile(qsfileName);
    }
}

QImage Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

cv::Mat QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}

void MainWindow::openFile(const QString &qsfileName){
    QImage qimage(qsfileName);
    originalMatImage = imread(qsfileName.toStdString());

    String face_cascade = "/Users/janghyukjin/untitled/resource/haarcascade_frontalface_default.xml";
    String eye_cascade="/Users/janghyukjin/untitled/resource/haarcascade_eye.xml";
    String mouth_cascade="/Users/janghyukjin/untitled/opencv_contrib/modules/face/data/cascades/haarcascade_mcs_mouth.xml";
    String nose_cascade="/Users/janghyukjin/Downloads/Nariz.xml";

    CascadeClassifier face;
    CascadeClassifier eye;
    CascadeClassifier mouth;
    CascadeClassifier nose;

    if(originalMatImage.data==NULL){
        cout<<"image open fail"<<endl;
    }

    if(!face.load(face_cascade) || !eye.load(eye_cascade)){
        cout << "Cascade fail" << endl;
    }

    if(!mouth.load(mouth_cascade) || !nose.load(nose_cascade)){
        cout << "Cascade2 fail" << endl;
    }

    cvtColor(originalMatImage, gray, CV_RGB2GRAY);

    face.detectMultiScale(gray, face_pos, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE,Size(10,10));//얼굴 검출

    for(int i=0;i<(int)face_pos.size();i++){
        //rectangle(originalMatImage, face_pos[i],Scalar(0,255,0),2);
    }//얼굴영역 표시

    for(int i=0;i<(int)face_pos.size();i++){

        Mat roi = gray(face_pos[i]);//관심영역 설정
        eye.detectMultiScale(roi, eye_pos,1.1,3,0|CV_HAAR_SCALE_IMAGE,Size(10,10));//눈 검출

        for(int j=0;j<(int)eye_pos.size();j++){
            Point center(face_pos[i].x+eye_pos[j].x+(eye_pos[j].width/2),
                        face_pos[i].y+eye_pos[j].y+(eye_pos[j].height/2));
            int radius = cvRound((eye_pos[j].width+eye_pos[j].height)*0.2);
            //circle(originalMatImage,center,radius,Scalar(0,0,255),2);
            cout<<eye_pos[j]<<endl;
        }
    }

    for(int i=face_pos.size();i<(int)face_pos.size();i++){
        Mat roi = gray(face_pos[i]);
        mouth.detectMultiScale(roi, mouth_pos,1.1,3,0|CV_HAAR_SCALE_IMAGE,Size(10,10));
        for(int j=0;j<(int)mouth_pos.size();j++){
            Point centerM(face_pos[i].x+mouth_pos[j].x+(mouth_pos[j].width/2),
            face_pos[i].y+mouth_pos[j].y+(mouth_pos[j].height/2));
            int radius = cvRound((mouth_pos[j].width+mouth_pos[j].height)*0.2);
            //circle(originalMatImage,centerM,radius,Scalar(255,0,0),2);
        }
    }
    for(int i=0;i<(int)face_pos.size();i++){
        Mat roi = gray(face_pos[i]);
        nose.detectMultiScale(roi, nose_pos,1.1,3,0|CV_HAAR_SCALE_IMAGE,Size(10,10));
        for(int j=0;j<(int)nose_pos.size();j++){
            Point centerN(face_pos[i].x+nose_pos[j].x+(nose_pos[j].width/2),
            face_pos[i].y+nose_pos[j].y+(nose_pos[j].height/2));
            int radius = cvRound((nose_pos[j].width+nose_pos[j].height)*0.2);
            //circle(originalMatImage,centerN,radius,Scalar(0,0,0),2);
        }
    }

    qimage=Mat2QImage(originalMatImage);
    originalImage->setPixmap(QPixmap::fromImage(qimage));
    ui->originalGraphicsView->fitInView(originalImage,Qt::KeepAspectRatio);
}

void MainWindow::on_deco_clicked()
{
    decoimage Deco = decoimage(originalMatImage, face_pos);
    convertMatImage = Deco.deco();
    QImage image = Mat2QImage(convertMatImage);
    convertImage->setPixmap(QPixmap::fromImage(image));
    ui->convertGraphicsView->fitInView(convertImage,Qt::KeepAspectRatio);
}
void MainWindow::on_deco2_clicked()
{
    decoimage2 Deco2 = decoimage2(originalMatImage, face_pos, eye_pos);
    convertMatImage = Deco2.deco();
    QImage image = Mat2QImage(convertMatImage);
    convertImage->setPixmap(QPixmap::fromImage(image));
    ui->convertGraphicsView->fitInView(convertImage,Qt::KeepAspectRatio);
}

void MainWindow::on_mosaic_clicked()
{
    cout<<"mosaic click"<<endl;
    Mosaic mosaic(originalMatImage, face_pos);
    convertMatImage = mosaic.convertMosaic();
    QImage image;
    image= Mat2QImage(convertMatImage);
    convertImage->setPixmap(QPixmap::fromImage(image));
    ui->convertGraphicsView->fitInView(convertImage,Qt::KeepAspectRatio);
}

void MainWindow::mousePressEvent(QMouseEvent *eve){
    int tempX, tempY;

    if(eve->button()==Qt::LeftButton){
   tempX = eve->pos().x()-ui->originalGraphicsView->x();
   tempY = eve->pos().y()-ui->originalGraphicsView->y()-12;
    }
   if((tempX >=0 && tempX <= 300) && ((tempY >=0 && tempY <= 300))){
       x=tempX;
       y=tempY;
   }
   else{
       x=0;
       y=0;
   }
   cout << x << "  " << y << endl;
}

void MainWindow::on_dot_clicked()
{


    cout<<mousePos_x<<mousePos_y<<endl;
}

void MainWindow::on_eyeschange_clicked()
{
    QString qsfileName1 = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "../", tr("Image Files (*.png *.jpeg *.bmp)"));
    QImage qimage(qsfileName1);
    convertMatImage = imread(qsfileName1.toStdString());
    eyeschange eyechange = eyeschange(originalMatImage, convertMatImage, eye_pos, eye_pos1, face_pos, face_pos1);
    convertMatImage = eyechange.swapEyes();
    QImage image;
    image= Mat2QImage(convertMatImage);
    convertImage->setPixmap(QPixmap::fromImage(image));
    ui->convertGraphicsView->fitInView(convertImage,Qt::KeepAspectRatio);
}
void MainWindow::on_erasedot_clicked()
{

    EraseDot initial_image = EraseDot(originalMatImage, x, y);

    convertMatImage = originalMatImage;

    convertMatImage = initial_image.convert();
    originalMatImage = convertMatImage.clone();
    QImage qimage=Mat2QImage(convertMatImage);
    convertImage->setPixmap(QPixmap::fromImage(qimage));

    ui->convertGraphicsView->fitInView(convertImage,Qt::KeepAspectRatio);

}
void MainWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr,
              tr("Save File"), "",
              tr("All Files (*)"));
    string jpgFileName = fileName.toStdString() + ".jpg";
    imwrite(jpgFileName, convertMatImage);
}
