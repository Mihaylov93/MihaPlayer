QT       += core gui avwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MihaPlayer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

unix:LIBS += -lX11
unix:DEPENDPATH += .
unix:INCLUDEPATH += .


SOURCES += \
        filedialog.cpp \
        main.cpp \
        mainwindow.cpp \
        videowidget.cpp

HEADERS += \
        filedialog.hpp \
        mainwindow.hpp \
        videowidget.hpp

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
