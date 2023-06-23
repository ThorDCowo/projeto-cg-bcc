QT       += core gui
QT += widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data\entities\border.cpp \
    data\entities\line.cpp \
    data\entities\line.test.cpp \
    data\entities\object.cpp \
    data\entities\object.test.cpp \
    data\entities\point.cpp \
    data\entities\point.test.cpp \
    data\entities\polygon.cpp \
    data\entities\polygon.test.cpp \
    helper\geometric.helper.cpp \
    infra\clipper\clipper.cpp \
    infra\clipper\clipper.test.cpp \
    infra\coordinate_parser\coordinate_parser.cpp \
    infra\coordinate_parser\coordinate_parser.test.cpp \
    infra\face_parser\face_parser.cpp \
    infra\face_parser\face_parser.test.cpp \
    infra\file_reader\file_reader.cpp \
    infra\object_list_factory\object_list_factory.cpp \
    tests\framework_test.cpp \
    tests\tests_register.cpp \
    presentation\camera.cpp \
    use_cases\clipp_object\clipp_object.use_case.cpp \
    use_cases\read_coordinate_file\read_coordinate_file.use_case.cpp \
    use_cases\read_coordinate_file\read_coordinate_file.use_case.test.cpp \
    use_cases\orthogonal_projection\orthogonal_projection.use_case.cpp \
    use_cases\orthogonal_projection\orthogonal_projection.use_case.test.cpp \
    use_cases\perspective_projection\perspective_projection.use_case.cpp \
    use_cases\perspective_projection\perspective_projection.use_case.test.cpp \
    screen.cpp \
    main.cpp

HEADERS += \
    data\entities\coordinate.h \
    data\entities\border.h \
    data\entities\line.h \
    data\entities\object.h \
    data\entities\point.h \
    data\entities\polygon.h \
    data\interfaces\comparable.h \
    helper\geometric.helper.h \
    infra\clipper\clipper.h \
    infra\clipper\clipper.h \
    infra\coordinate_parser\coordinate_parser.h \
    infra\face_parser\face_parser.cpp \
    infra\file_reader\file_reader.h \
    infra\object_list_factory\object_list_factory.h \
    presentation\camera.h \
    tests\framework_test.h \
    tests\test_suite.h \
    use_cases\clipp_object\clipp_object.use_case.h \
    use_cases\read_coordinate_file\read_coordinate_file.use_case.h \
    use_cases\orthogonal_projection\orthogonal_projection.use_case.h \
    use_cases\perspective_projection\perspective_projection.use_case.h \
    screen.h

FORMS += \
    presentation\camera.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    objects.qrc

DISTFILES += \
    data/charizard/charizard.obj


