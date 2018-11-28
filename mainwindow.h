#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "eyeschange.h"
#include "mosaic.h"
#include "decoimage.h"
#include "decoimage2.h"
#include "erasedot.h"
#include "asmopencv.h"
#include <iostream>

using namespace cv;
using namespace std;
using namespace ASM;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<Rect> eye_pos;
    vector<Rect> face_pos;
private slots:
    void on_open_clicked();
    void on_deco_clicked();
    void on_mosaic_clicked();
    void openFile(const QString &qsfileName);
    void on_dot_clicked();
    void mousePressEvent(QMouseEvent *event);
    void on_deco2_clicked();
    void on_save_clicked();
    void on_eyeschange_clicked();
    void on_erasedot_clicked();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *originalScene;
    QGraphicsScene *convertScene;
    QGraphicsPixmapItem *originalImage;
    QGraphicsPixmapItem *convertImage;
    Mat gray;
    Mat originalMatImage;
    Mat convertMatImage;
    vector<Rect> face_pos1;
    vector<Rect> eye_pos1;
    vector<Rect> mouth_pos;
    vector<Rect> nose_pos;
    int mousePos_x;
    int mousePos_y;
    int x,y;
};

#endif // MAINWINDOW_H
