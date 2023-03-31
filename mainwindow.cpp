#include <iostream>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QBrush>

#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "screen.h"
#include "object.h"
#include "point.h"
#include "line.h"
#include "rect.h"
#include "object_list_factory.h"
using namespace std;

void executeOperationInList(
    QList<QListWidgetItem*> checked, 
    QList<Object*> list,
    void (*cb)(Object*)
);
void transtateObject(Object* object);
void rotateObject(Object* object);
void scaleObject(Object* object);
QList<QListWidgetItem*> filterListWidgetItemChecked(QListWidget* listWidget);
void operateInCheckedObject(
    Ui::MainWindow* ui, 
    void (*cb)(Object*)
);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<Object*> list = ObjectListFactory::createObjectList();
    ui->frame->setObjectList(list);

    for (int i = 0; i < list.size(); i++){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(list[i]->getName());
        item->setCheckState(Qt::Unchecked);
        item->setForeground(Qt::white);

        ui->objectList->addItem(item);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot1(int v)
{
    cout << "dentro do MainWindow::slot1" << endl;
    ui->lineEdit->setText(QString("valor lido: ").append(QString::number(v)));

}

void MainWindow::on_translationButton_clicked()
{
    operateInCheckedObject(ui, transtateObject);
    update();
}

void MainWindow::on_scaleButton_clicked()
{
    operateInCheckedObject(ui, scaleObject);
    update();
}

void MainWindow::on_rotationButton_clicked()
{
    operateInCheckedObject(ui, rotateObject);
    update();
}

void operateInCheckedObject(
    Ui::MainWindow* ui, 
    void (*cb)(Object*)
) {
    QList<Object*> objectList = ui->frame->getObjectList();
    QList<QListWidgetItem*> checked = filterListWidgetItemChecked(ui->objectList); 

    executeOperationInList(
        checked,
        objectList,
        cb
    );

    ui->frame->setObjectList(objectList);
}

QList<QListWidgetItem*> filterListWidgetItemChecked(QListWidget* listWidget) {
    QList<QListWidgetItem*> checked;
    
    for(qsizetype i = 0; i < listWidget->count(); i++)
        if(listWidget->item(i)->checkState()) {
            checked.append(listWidget->item(i));
            cout << listWidget->item(i)->text().toStdString() << endl;
        }

    return checked;
}

void executeOperationInList(
    QList<QListWidgetItem*> checked, 
    QList<Object*> list,
    void (*operationCallback)(Object*)
) {
    for(qsizetype i = 0; i < checked.length(); i++){
        for (qsizetype j = 0; j < list.length(); j++){
            if(checked.at(i)->text().compare(list[j]->getName(), Qt::CaseInsensitive) == 0){
                operationCallback(list[j]);
            }
        }
    }
}

void transtateObject(Object* object) {
    object->translate(20.0,20.0);
}

void rotateObject(Object* object) {
    object->rotate(45.0);
}

void scaleObject(Object* object) {
    object->scale(0.2);
}
