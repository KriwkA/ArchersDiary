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
    precomp.cpp \
    database/sqltablemodel.cpp \
    tables/archerstablemodel.cpp \
    diarytables.cpp \
    tables/arrowstablemodel.cpp \
    tables/bowstablemodel.cpp \
    tables/scopestablemodel.cpp \
    database/sqlfield.cpp \
    tables/trainingtablemodel.cpp \
    tables/recordtablemodel.cpp \
    tables/targetmodel.cpp \
    tables/standardmodel.cpp \
    tables/standardexcercisemodel.cpp \
    tables/excercisemodel.cpp \
    tables/trainingstandardmodel.cpp \
    tables/shotmodel.cpp \
    serialization.cpp \
    tables/simpleshotmodel.cpp \
    tables/baseshotmodel.cpp


HEADERS += \
    core_global.h \
    precomp.h \
    database/sqltablemodel.h \
    tables/archerstablemodel.h \
    diarytables.h \
    diarytables_p.h \
    tables/arrowstablemodel.h \
    tables/bowstablemodel.h \
    tables/scopestablemodel.h \    
    tables/alltables.h \
    database/sqlfield.h \
    tables/trainingtablemodel.h \
    tables/recordtablemodel.h \
    tables/targetmodel.h \
    tables/standardmodel.h \
    tables/excercisemodel.h \
    tables/standardexcercisemodel.h \
    tables/trainingstandardmodel.h \
    tables/shotmodel.h \
    serialization.h \
    tables/simpleshotmodel.h \
    tables/baseshotmodel.h

PRECOMPILED_HEADER += precomp.h

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
