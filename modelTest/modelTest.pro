#-------------------------------------------------
#
# Project created by QtCreator 2017-07-03T15:18:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = modelTest
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    currencymodel.cpp \
    citymodel.cpp

HEADERS  += widget.h \
    currencymodel.h \
    citymodel.h

FORMS    += widget.ui
