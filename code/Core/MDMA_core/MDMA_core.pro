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
    src/core.cpp \
    src/main.cpp\
    src/Classes/configuration.cpp \
    src/Classes/pointer.cpp \
    src/Classes/zone.cpp \
    src/Interfaces/interface.cpp \
    src/Interfaces/kinect.cpp \
    src/Interfaces/mouse.cpp \
    src/Interfaces/webcam.cpp \
    src/UI/mainwindow.cpp \
    src/UI/zoneeditor.cpp\
    src/Utils/define.cpp \
    src/Widgets/hotspot.cpp \
    src/Widgets/zonedrager.cpp

HEADERS  += \
    src/core.h \
    src/Classes/configuration.h \
    src/Classes/pointer.h \
    src/Classes/zone.h \
    src/Interfaces/interface.h \
    src/Interfaces/kinect.h \
    src/Interfaces/mouse.h \
    src/Interfaces/webcam.h \
    src/UI/mainwindow.h \
    src/UI/zoneeditor.h \
    src/Utils/define.h \
    src/Widgets/hotspot.h \
    src/Widgets/zonedrager.h

FORMS    += \
    src/UI/mainwindow.ui \
    src/UI/zoneeditor.ui

RESOURCES += \
    src/ressources.qrc

LIBS += \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc

