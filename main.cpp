#include <QApplication>
#include <QDir>
#include "presentation/mainwindow.h"
#include "tests/tests_register.cpp"

int main(int argc, char *argv[])
{
    runTests();

    QApplication a(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    MainWindow w;
    w.show();
    return a.exec();
}