QT       += core gui
QT += widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    infra\clipper\clipper.cpp \
    infra\clipper\clipper.test.cpp \
    use_cases\clipp_object.use_case.cpp \
    tests\framework_test.cpp \
    tests\object_test.cpp \
    tests\tests_register.cpp \
    border.cpp \
    line.cpp \
    main.cpp \
    mainwindow.cpp \
    object.cpp \
    object_list_factory.cpp \
    point.cpp \
    polygon.cpp \
    screen.cpp

HEADERS += \
    infra\clipper\clipper.h \
    use_cases\clipp_object.use_case.h \
    tests\framework_test.h \
    tests\object_test.h \
    tests\test_suite.h \
    border.h \
    line.h \
    mainwindow.h \
    object.h \
    object_list_factory.h \
    point.h \
    polygon.h \
    screen.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
