#-------------------------------------------------
#
# Project created by QtCreator 2013-04-03T09:14:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MemoryGame
TEMPLATE = app


SOURCES += main.cpp \
    gamemanager.cpp \
    gamewindow2.cpp \
    savegamewidget.cpp \
    dataaccess.cpp \
    loadgamewidget.cpp

HEADERS  += \
    gamemanager.h \
    gamewindow2.h \
    savegamewidget.h \
    dataaccess.h \
    loadgamewidget.h

RESOURCES += \
   images.qrc
