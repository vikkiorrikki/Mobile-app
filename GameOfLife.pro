#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T13:45:10
#
#-------------------------------------------------

QT       += core gui xml

QT += widgets

TARGET = GameOfLife
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    widgetdraw.cpp \
    levels.cpp

HEADERS  += widget.h \
    widgetdraw.h \
    levels.h

FORMS    += widget.ui

RESOURCES += \
    res/res.qrc
