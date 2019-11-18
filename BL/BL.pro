#-------------------------------------------------
#
# Project created by QtCreator 2017-05-28T11:14:05
#
#-------------------------------------------------

QT       -= gui
QT       += sql core

TARGET = BL

win32: QMAKE_CXXFLAGS += /std:c++17
else: QMAKE_CXXFLAGS += -std=c++17

TEMPLATE = lib

#android: TEMPLATE = app  # for Android this is an "app"
#else: TEMPLATE = lib

DEFINES += BL_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    precomp.cpp \
    tables/archerstablemodel.cpp \
    tables/dbtables.cpp \
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
    bl_global.h \
    precomp.h \
    tables/archerstablemodel.h \
    diarytables_p.h \
    tables/alltables.h \
    tables/dbtables.h \
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

#PRECOMPILED_HEADER += precomp.h

#precompile_header:!isEmpty(PRECOMPILED_HEADER) {
#DEFINES += USING_PCH
#}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core
