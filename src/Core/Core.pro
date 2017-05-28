#-------------------------------------------------
#
# Project created by QtCreator 2017-05-28T11:14:05
#
#-------------------------------------------------

QT       -= gui
QT       += sql

RCC_DIR= binary

TARGET = Core
TEMPLATE = lib

Release:DESTDIR = release
Release:OBJECTS_DIR = release/binary/.obj
Release:MOC_DIR = release/binary/.moc
Release:RCC_DIR = release/binary/.rcc
Release:UI_DIR = release/binary/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/binary/.obj
Debug:MOC_DIR = debug/binary/.moc
Debug:RCC_DIR = debug/binary/.rcc
Debug:UI_DIR = debug/binary/.ui

DEFINES += CORE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    trainingmodel.cpp

HEADERS += core_global.h \
    trainingmodel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
