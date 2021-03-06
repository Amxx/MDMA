#-------------------------------------------------
#
# Project created by QtCreator 2012-12-10T11:27:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openni
TEMPLATE = app

LIBS += -lOpenNI \
    -lopencv_core \
    -lopencv_imgproc

QMAKE_CXXFLAGS += -isystem /usr/include/ni
INCLUDEPATH += /usr/include/ni

SOURCES += main.cpp\
        mainwindow.cpp \
    kinect.cpp \
    handdescriptor.cpp

HEADERS  += mainwindow.h \
    kinect.h \
    handdescriptor.h

FORMS    +=

OTHER_FILES += \
    Sample-Tracking.xml
