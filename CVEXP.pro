#-------------------------------------------------
#
# Project created by QtCreator 2016-10-05T18:52:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CVEXP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cvtools.cpp \
    videoprocessing.cpp \
    quantizer.cpp

HEADERS  += mainwindow.h \
    cvtools.h \
    videoprocessing.h \
    quantizer.h \
    quadtree.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/
LIBS += "/usr/lib/x86_64-linux-gnu/libopencv*.so"
