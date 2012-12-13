SOURCES += \
    src/main.cpp \
    src/classes/eventzone.cpp \
    src/classes/handdescriptor.cpp \
    src/classes/handtracking.cpp \
    src/classes/RtMidi.cpp \
    src/classes/subconfig.cpp \
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
    src/UI/notenumberwindow.cpp

HEADERS += \
    src/classes/eventzone.h \
    src/classes/handdescriptor.h \
    src/classes/handtracking.h \
    src/classes/subconfig.h \
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
    src/UI/notenumberwindow.h

FORMS += \
    src/UI/configwindow.ui \
    src/UI/handclosewindow.ui \
    src/UI/handopenwindow.ui \
    src/UI/mainwindow.ui \
    src/UI/maskwindow.ui \
    src/UI/zoneeditor.ui \
    src/UI/notenumberwindow.ui

win32 {
    LIBS += -Lc:/opencv/build/x86/mingw/lib #or whereever your opencv is installed
}

LIBS += \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc

unix {
macx {
    LIBS += -ljack
}
!macx { #linux
    LIBS += -lasound
}
}
!unix { #windows
    LIBS += -lwinmm
}


QMAKE_CXXFLAGS += \
    -std=c++0x

CONFIG += \
    console

RESOURCES += \
    src/ressources.qrc
