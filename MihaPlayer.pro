#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T21:32:22

#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MihaPlayer
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

unix:LIBS +=  -lvlc -lX11
unix:DEPENDPATH += .
unix:INCLUDEPATH += .

win32:LIBS += $$quote(C:/Program Files/VideoLAN/VLC/MinGW/sdk/lib/libvlc.lib)
win32:INCLUDEPATH += $$quote(C:/Program Files/VideoLAN/VLC/MinGW/sdk/include)


SOURCES += \
        filedialog.cpp \
        main.cpp \
        mainwindow.cpp \
        videowidget.cpp

HEADERS += \
        filedialog.h \
        mainwindow.h \
        videowidget.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
