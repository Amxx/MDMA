#-------------------------------------------------
#
# Project created by QtCreator 2012-12-10T11:27:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openni2
TEMPLATE = app

INCLUDEPATH += c:/dev/opencv/build/include/
LIBS += -Lc:/dev/opencv/build/x86/mingw/lib/ #or wherever your opencv is installed
LIBS += \ #the windows libs have filenames like libopencv_core243.dll.a -> needs opencv version number
        -lopencv_core243 \
        -lopencv_highgui243 \
        -lopencv_imgproc243

INCLUDEPATH += c:/dev/OpenNI2/x86/Include/
LIBS += -Lc:/dev/OpenNI2/x86/Lib/
LIBS += -lOpenNI2

INCLUDEPATH += c:/dev/NiTE2/x86/Include/
LIBS += -Lc:/dev/NiTE2/x86/Lib/
LIBS += -lNiTE2

SOURCES += main.cpp\
        mainwindow.cpp \
    kinect.cpp \
    handdescriptor.cpp

HEADERS  += mainwindow.h \
    kinect.h \
    handdescriptor.h

