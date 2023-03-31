#include <iostream>
#include <QList>

#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "screen.h"
#include "object.h"
#include "point.h"
#include "line.h"
#include "rect.h"
#include "object_list_factory.h"
using namespace std;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<Object*> list = ObjectListFactory::createObjectList();
    ui->frame->setObjectList(list);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot1(int v)
{
    std::cout << "dentro do MainWindow::slot1" << std::endl;
    ui->lineEdit->setText(QString("valor lido: ").append(QString::number(v)));

}

void MainWindow::on_translationButton_clicked()
{

    QList<Object*> list = ui->frame->getObjectList();
    // Maths
    ui->frame->setObjectList(list);
}

