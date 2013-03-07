#-------------------------------------------------
#
# Project created by QtCreator 2013-02-26T13:49:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MDMA_core
TEMPLATE = app

OBJECTS_DIR = build/obj/
MOC_DIR     = build/moc/
UI_DIR      = build/ui/
RCC_DIR     = build/rcc/

QMAKE_CXXFLAGS += \
    -std=c++11



SOURCES += \
    src/main.cpp\
    src/UI/mainwindow.cpp \
    src/Interfaces/interface.cpp \
    src/Interfaces/mouse.cpp \
    src/Interfaces/webcam.cpp \
    src/Interfaces/kinect.cpp \
    src/Classes/pointer.cpp \
    src/Classes/zone.cpp \
    src/Classes/configuration.cpp \
    src/core.cpp \
    src/Utils/define.cpp

HEADERS  += \
    src/core.h \
    src/UI/mainwindow.h \
    src/Interfaces/interface.h \
    src/Interfaces/mouse.h \
    src/Interfaces/webcam.h \
    src/Interfaces/kinect.h \
    src/Classes/pointer.h \
    src/Utils/define.h \
    src/Classes/zone.h \
    src/Classes/configuration.h

FORMS    += \
    src/UI/mainwindow.ui \
    src/UI/zoneeditor.ui


LIBS += \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc

