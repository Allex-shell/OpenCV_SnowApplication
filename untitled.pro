#-------------------------------------------------
#
# Project created by QtCreator 2018-11-02T02:59:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    decoimage.cpp \
    mosaic.cpp \
    eyeschange.cpp \
    decoimage2.cpp \
    erasedot.cpp

HEADERS += \
        mainwindow.h \
    asmopencv.h \
    decoimage.h \
    mosaic.h \
    mosaic.h \
    eyeschange.h \
    eyeschange.h \
    decoimage2.h \
    erasedot.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_objdetect

DISTFILES += \
    opencv/data/haarcascades/haarcascade_frontalface_default.xml \
    resource/haarcascade_eye.xml \
    resource/haarcascade_frontalface_default.xml \
    ../Downloads/Mouth.xml \
    ../Downloads/Nariz.xml \
    opencv_contrib/modules/face/data/cascades/haarcascade_mcs_mouth.xml
