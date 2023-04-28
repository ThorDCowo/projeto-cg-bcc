QT       += core gui
QT += widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    line.cpp \
    main.cpp \
    mainwindow.cpp \
    object.cpp \
    object_list_factory.cpp \
    point.cpp \
    rect.cpp \
    screen.cpp \
    tests/example.spec.cpp

HEADERS += \
    line.h \
    mainwindow.h \
    object.h \
    object_list_factory.h \
    point.h \
    rect.h \
    screen.h \
    tests/example.spec.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qtestlib/tutorial1
INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES += \
    CMakeLists.txt

