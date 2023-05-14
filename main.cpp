#include <QApplication>
#include "mainwindow.h"
#include "tests/tests_register.cpp"

int main(int argc, char *argv[])
{
    runTests();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}