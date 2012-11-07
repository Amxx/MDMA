SOURCES += \
    src/main.cpp \
    src/UI/mainwindow.cpp \
    src/UI/configwindow.cpp \
    src/objects/cvcameradisplay.cpp \
    src/classes/eventzone.cpp \
    src/classes/midisignal.cpp \
    src/classes/configuration.cpp \
    src/objects/zonedisplay.cpp \
    src/UI/zoneeditor.cpp

HEADERS += \
    src/UI/mainwindow.h \
    src/UI/configwindow.h \
		src/objects/cvcameradisplay.h \
    src/classes/eventzone.h \
    src/classes/midisignal.h \
    src/classes/configuration.h \
    src/objects/zonedisplay.h \
    src/UI/zoneeditor.h

FORMS += \
    src/UI/mainwindow.ui \
    src/UI/configwindow.ui \
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
    -std=c++0x

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
