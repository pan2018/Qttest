#-------------------------------------------------
#
# Project created by QtCreator 2017-06-29T10:08:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyThread
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    clientthread.cpp

HEADERS  += widget.h \
    clientthread.h

FORMS    += widget.ui
