#-------------------------------------------------
#
# Project created by QtCreator 2017-05-28T11:14:05
#
#-------------------------------------------------

QT       -= gui
QT       += sql

TARGET = Core
TEMPLATE = lib
android {
    TEMPLATE = app  # for Android this is an "app"
}

DEFINES += CORE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database/sqltablemodel.cpp \
    tables/archerstablemodel.cpp \
    diarytables.cpp \
    tables/arrowstablemodel.cpp \
    tables/bowstablemodel.cpp \
    tables/scopestablemodel.cpp

HEADERS += core_global.h \
    database/sqltablemodel.h \
    tables/archerstablemodel.h \
    diarytables.h \
    diarytables_p.h \
    tables/arrowstablemodel.h \
    tables/bowstablemodel.h \
    tables/scopestablemodel.h \
    precomp.h \
    tables/alltables.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
