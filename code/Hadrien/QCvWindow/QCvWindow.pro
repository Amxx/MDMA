SOURCES += \
    src/main.cpp \
    src/classes/eventzone.cpp \
    src/classes/handdescriptor.cpp \
    src/classes/RtMidi.cpp \
    src/config/constant.cpp \
    src/objects/cameramanager.cpp \
    src/objects/configuration.cpp \
    src/objects/eventmanager.cpp \
    src/objects/midimanager.cpp \
    src/objects/zonemanager.cpp \
    src/UI/configwindow.cpp \
    src/UI/handclosewindow.cpp \
    src/UI/handopenwindow.cpp \
    src/UI/maskwindow.cpp \
    src/UI/mainwindow.cpp \
    src/UI/zoneeditor.cpp \
    src/classes/subconfig.cpp

HEADERS += \
    src/classes/eventzone.h \
    src/classes/handdescriptor.h \
    src/classes/RtMidi.h \
    src/classes/RtError.h \
    src/config/constant.h \
    src/objects/cameramanager.h \
    src/objects/configuration.h \
    src/objects/eventmanager.h \
    src/objects/midimanager.h \
    src/objects/zonemanager.h \
    src/UI/configwindow.h \
    src/UI/handclosewindow.h \
    src/UI/handopenwindow.h \
    src/UI/mainwindow.h \
    src/UI/maskwindow.h \
    src/UI/zoneeditor.h \
    src/classes/subconfig.h

FORMS += \
    src/UI/configwindow.ui \
    src/UI/handclosewindow.ui \
    src/UI/handopenwindow.ui \
    src/UI/mainwindow.ui \
    src/UI/maskwindow.ui \
    src/UI/zoneeditor.ui

LIBS += \
    /usr/lib/libopencv_calib3d.so \
    /usr/lib/libopencv_core.so \
    /usr/lib/libopencv_flann.so \
    /usr/lib/libopencv_highgui.so \
    /usr/lib/libopencv_legacy.so \
    /usr/lib/libopencv_objdetect.so \
    /usr/lib/libopencv_contrib.so \
    /usr/lib/libopencv_features2d.so \
    /usr/lib/libopencv_gpu.so \
    /usr/lib/libopencv_imgproc.so \
    /usr/lib/libopencv_ml.so \
    /usr/lib/libopencv_video.so

QMAKE_CXXFLAGS += \
    -std=c++11

CONFIG += \
    console

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
