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
    src/UI/notenumberwindow.cpp \
    src/UI/secondwindow.cpp

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
    src/UI/notenumberwindow.h \
    src/UI/secondwindow.h

FORMS += \
    src/UI/configwindow.ui \
    src/UI/handclosewindow.ui \
    src/UI/handopenwindow.ui \
    src/UI/mainwindow.ui \
    src/UI/maskwindow.ui \
    src/UI/zoneeditor.ui \
    src/UI/notenumberwindow.ui \
    src/UI/secondwindow.ui

#DESTDIR = build/target/
OBJECTS_DIR = build/obj/
MOC_DIR     = build/moc/
UI_DIR      = build/ui/
RCC_DIR     = build/rcc/

win32 {
    INCLUDEPATH += c:/lib/opencv/build/include/
    LIBS += -Lc:/lib/opencv/build/x86/mingw/lib/ #or wherever your opencv is installed
    LIBS += \ #the windows libs have filenames like libopencv_core243.dll.a -> needs opencv version number
        -lopencv_core243 \
        -lopencv_highgui243 \
        -lopencv_imgproc243
    
    #LIBS += ../MDMA/teVirtualMIDI32.lib

    QMAKE_RCC = $$[QT_INSTALL_BINS]$${DIR_SEPARATOR}rcc.exe #fix for QT 4.8.3 bug in qmake win32 conf files (see windows.txt)
}

# what about win64 compilation? not tested (don't have a windows 64bits compiler)

unix{
    LIBS += \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc
}

unix {
	macx {
	    LIBS += -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
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

win32 {
    CONFIG += exceptions #necessaire sous windows
}

RESOURCES += \
    src/ressources.qrc
