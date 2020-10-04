#-------------------------------------------------
#
# Project created by QtCreator 2017-05-28T11:14:05
#
#-------------------------------------------------

QT       -= gui
QT       += sql core

TARGET = Core

CONFIG += c++17

#android: TEMPLATE = app  # for Android this is an "app"
#else:
TEMPLATE = lib


DEFINES += CORE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    db/sql_transaction.cpp \
    precomp.cpp \
    db/version_table.cpp \
    db/sqltablemodel.cpp \
    db/sqlfield.cpp \
    private/db/database.cpp \
    utils/hash_specialization.cpp


HEADERS += \
    db/sql_transaction.h \
    precomp.h \
    core_global.h \
    db/field_types.h \
    db/sql_column.hpp \
    db/version_table.h \
    db/sqltablemodel.h \
    db/sqlfield.h \
    private/db/database.h \
    utils/container_view.hpp \
    utils/hash_specialization.h \
    utils/utils.hpp

PRECOMPILED_HEADER += precomp.h

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
DEFINES += USING_PCH
}

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

