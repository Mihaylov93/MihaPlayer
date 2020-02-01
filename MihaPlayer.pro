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
