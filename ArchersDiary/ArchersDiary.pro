win32: QMAKE_CXXFLAGS += /std:c++17
else: QMAKE_CXXFLAGS += -std=c++17

QT += core qml quick sql quickcontrols2

CONFIG += qtquickcompiler

SOURCES += main.cpp \
    calendar/trainingcalendar.cpp \
    targetview.cpp \
    shottablemodel.cpp

RESOURCES += \
    qml.qrc

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    calendar/trainingcalendar.h \
    targetview.h \
    shottablemodel.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BL/release/ -lBL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BL/debug/ -lBL
else:unix: LIBS += -L$$OUT_PWD/../BL/ -lBL

INCLUDEPATH += $$PWD/../BL
DEPENDPATH += $$PWD/../BL



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core
