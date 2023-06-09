#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
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

float MOVE_SPEED = 20.0;
int WIDTH = 854;  //inicialize with viewport size
int HEIGHT = 480; //inicialize with viewport size
pair <float,float> CENTER = {0,0};
float TETA = 0.0;

QList<QListWidgetItem*> getCheckedListWidgetItems(QListWidget* listWidget);

void operateInCheckedObjects(
    Ui::MainWindow* ui, 
    function<void(Object*)> operation
);

void applyOperationInObjects(QList<Object*> list, function<void(Object*)>operation);
void applyOperationInCheckedObjects(
    QList<QListWidgetItem*> checked, 
    QList<Object*> list,
    function<void(Object*)> operation
);
void operateInViewport(
    Ui::MainWindow* ui, 
    function<void(Screen*)> screen
);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<Object*> list = ObjectListFactory::createObjectList();
    ui->screen->setObjectList(list);

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

void operateInCheckedObjects(
    Ui::MainWindow* ui, 
    function<void(Object*)>operation
) {
    QList<Object*> objectList = ui->screen->getObjectList();
    QList<QListWidgetItem*> checked = getCheckedListWidgetItems(ui->objectList); 

   applyOperationInCheckedObjects(
    checked,
    objectList,
    operation
   );

    ui->screen->setObjectList(objectList);
}

QList<QListWidgetItem*> getCheckedListWidgetItems(QListWidget* listWidget) {
    QList<QListWidgetItem*> checked;
    
    for(qsizetype i = 0; i < listWidget->count(); i++)
        if(listWidget->item(i)->checkState()) {
            checked.append(listWidget->item(i));
        }

    return checked;
}

void applyOperationInCheckedObjects(
    QList<QListWidgetItem*> checked, 
    QList<Object*> list,
    function<void(Object*)>operation)
 {
    for(qsizetype i = 0; i < checked.length(); i++){
        for (qsizetype j = 0; j < list.length(); j++){
            if(checked.at(i)->text().compare(list[j]->getName(), Qt::CaseInsensitive) == 0){
                operation(list[j]);
            }
        }
    }
}

void applyOperationInObjects(QList<Object*> list, function<void(Object*)>operation) {
    for (qsizetype i = 0; i < list.length(); i++) {
        operation(list[i]);
    }
}

void MainWindow::on_upButton_clicked()
{
    operateInCheckedObjects(ui, [](Object* object) {
        object->translate(0, -MOVE_SPEED);
    });
    update();
}

void MainWindow::on_rightButton_clicked()
{
    operateInCheckedObjects(ui, [](Object* object) {
        object->translate(MOVE_SPEED, 0);
    });
    update();
}

void MainWindow::on_downButton_clicked()
{
    operateInCheckedObjects(ui, [](Object* object) {
        object->translate(0, MOVE_SPEED);
    });
    update();
}

void MainWindow::on_leftButton_clicked()
{    
    operateInCheckedObjects(ui, [](Object* object) {
       object->translate(-MOVE_SPEED, 0);
    });
    update();
}

void MainWindow::on_scaleSlider_valueChanged(int value)
{
    operateInCheckedObjects(
        ui, 
        [value](Object* object) -> void {
            object->scale(value);
        }
    );
    update();
}

void MainWindow::on_rotationDial_sliderMoved(int position)
{
    operateInCheckedObjects(
        ui,
        [position](Object* object) -> void {
            object->rotate(position);
        }
    );
    update();
}

void MainWindow::on_windowButton_clicked()
{
    // Aqui que definimos onde esta o centro do campo de visão e a inclinação
    // Tem que recalcular as cordenadas normalizadas

    ui->screen->setCenter(CENTER);
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();

    applyOperationInObjects(
        ui->screen->getObjectList(),
        [width, height](Object* object) -> void {
            pair<float, float> objectCenter = object->barycenter();
            //object->translate(-objectCenter.first, -objectCenter.second);
            object->rotateWorld(TETA);
            //object->translate(objectCenter.first, objectCenter.second);
            object->normalize(width, height, CENTER);
            //object->translate(CENTER.first, CENTER.second);
        }
    );  

    update();
}

void MainWindow::on_viewportHeightLineEdit_textEdited(const QString &input)
{ 
    bool ok;
    HEIGHT = input.toInt(&ok, 10);
}

void MainWindow::on_viewportWidthLineEdit_textEdited(const QString &input)
{
    bool ok;
    WIDTH = input.toInt(&ok, 10);
}

void MainWindow::on_centerXLineEdit_textEdited(const QString &input)
{
    bool ok;
    CENTER.first = input.toFloat(&ok);
}

void MainWindow::on_centerYLineEdit_textEdited(const QString &input)
{
    bool ok;
    CENTER.second = input.toFloat(&ok);
}

void MainWindow::on_angleLineEdit_textChanged(const QString &input)
{
    bool ok;
    TETA = input.toFloat(&ok);
}

void MainWindow::on_zoomSlider_valueChanged(int value)
{
    applyOperationInObjects(
        ui->screen->getObjectList(), 
        [value](Object* object) -> void {
            object->scale(value);
        }
    );
    update();
}


