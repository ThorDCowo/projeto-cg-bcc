#include <QApplication>
#include <QDir>
#include "presentation/camera.h"
#include "tests/tests_register.cpp"

int main(int argc, char *argv[])
{
    runTests();

    QApplication a(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    Camera w;
    w.show();
    return a.exec();
}