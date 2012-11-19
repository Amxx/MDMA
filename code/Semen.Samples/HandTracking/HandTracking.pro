TEMPLATE = app
CONFIG += console
CONFIG += qt

LIBS += -L/usr/local/lib -lopencv_video
LIBS += -L/usr/local/lib -lopencv_core
LIBS += -L/usr/local/lib -lopencv_highgui
LIBS += -L/usr/local/lib -lopencv_imgproc
LIBS += -L/usr/local/lib -lopencv_objdetect

SOURCES += main.cpp \
    handtracking.cpp \
    handdescriptor.cpp

HEADERS += \
    handtracking.h \
    handdescriptor.h

