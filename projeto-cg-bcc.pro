QT       += core gui
QT += widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core\entities\border.cpp \
    core\entities\line.cpp \
    core\entities\object.cpp \
    core\entities\point.cpp \
    core\entities\polygon.cpp \
    infra\clipper\clipper.cpp \
    infra\clipper\clipper.test.cpp \
    infra\object_list_factory.cpp \
    tests\framework_test.cpp \
    tests\object_test.cpp \
    tests\tests_register.cpp \
    presentation\mainwindow.cpp \
    presentation\screen.cpp \
    use_cases\clipp_object\clipp_object.use_case.cpp \
    main.cpp

HEADERS += \
    core\entities\border.h \
    core\entities\line.h \
    core\entities\object.h \
    core\entities\point.h \
    core\entities\polygon.h \
    infra\clipper\clipper.h \
    infra\object_list_factory.h \
    presentation\mainwindow.h \
    presentation\screen.h \
    tests\framework_test.h \
    tests\object_test.h \
    tests\test_suite.h \
    use_cases\clipp_object\clipp_object.use_case.h

FORMS += \
    presentation\mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
