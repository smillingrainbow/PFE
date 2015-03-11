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
    filterbilateral.cpp \
    controller.cpp \
    widgetImage.cpp

HEADERS  += mainwindow.h \
    filterbilateral.h \
    CImg.h \
    controller.h \
    widgetImage.h

FORMS    += mainwindow.ui \
    window.ui
