QT += qml quick sql quickcontrols2

CONFIG += c++11

SOURCES += main.cpp

RESOURCES += \
    qml.qrc

#Release:DESTDIR = release
#Release:OBJECTS_DIR = release/binary/.obj
#Release:MOC_DIR = release/binary/.moc
#Release:RCC_DIR = release/binary/.rcc
#Release:UI_DIR = release/binary/.ui

#Debug:DESTDIR = debug
#Debug:OBJECTS_DIR = debug/binary/.obj
#Debug:MOC_DIR = debug/binary/.moc
#Debug:RCC_DIR = debug/binary/.rcc
#Debug:UI_DIR = debug/binary/.ui

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core
