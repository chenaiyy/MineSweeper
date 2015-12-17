#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T11:32:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MineSweeper
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    block.cpp \
    blockarea.cpp \
    mainarea.cpp

HEADERS  += dialog.h \
    block.h \
    blockarea.h \
    mainarea.h

RESOURCES += \
    img.qrc
