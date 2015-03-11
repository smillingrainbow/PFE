#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T13:46:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterfaceQt
TEMPLATE = app
LIBS += -lreadline -lpthread -lm -lX11

SOURCES += main.cpp\
        mainwindow.cpp \
    window.cpp \
    filterbilateral.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    window.h \
    filterbilateral.h \
    CImg.h \
    controller.h

FORMS    += mainwindow.ui \
    window.ui
