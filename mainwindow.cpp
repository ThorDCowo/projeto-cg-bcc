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

float MOVE_SPEED = 20.0;

QList<QListWidgetItem*> filterListWidgetItemChecked(QListWidget* listWidget);
void translateObjectUp(Object* object);
void translateObjectDown(Object* object);
void translateObjectLeft(Object* object);
void translateObjectRight(Object* object);

void operateInCheckedObject(
    Ui::MainWindow* ui, 
    function<void(Object*)> operation
);
void executeOperationInList(
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

void operateInCheckedObject(
    Ui::MainWindow* ui, 
    function<void(Object*)>operation
) {
    QList<Object*> objectList = ui->screen->getObjectList();
    QList<QListWidgetItem*> checked = filterListWidgetItemChecked(ui->objectList); 

    executeOperationInList(
        checked,
        objectList,
        operation
    );

    ui->screen->setObjectList(objectList);
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

void translateObjectUp(Object* object) {
    object->translate(0, -MOVE_SPEED);
}

void translateObjectDown(Object* object) {
    object->translate(0, MOVE_SPEED);
}

void translateObjectLeft(Object* object) {
    object->translate(-MOVE_SPEED, 0);
}

void translateObjectRight(Object* object) {
    object->translate(MOVE_SPEED, 0);
}

void MainWindow::on_upButton_clicked()
{
    operateInCheckedObject(ui, &translateObjectUp);
    update();
}

void MainWindow::on_rightButton_clicked()
{
    operateInCheckedObject(ui, &translateObjectRight);
    update();
}

void MainWindow::on_downButton_clicked()
{
    operateInCheckedObject(ui, &translateObjectDown);
    update();
}

void MainWindow::on_leftButton_clicked()
{
    operateInCheckedObject(ui, &translateObjectLeft);
    update();
}

void MainWindow::on_scaleSlider_valueChanged(int value)
{
    operateInCheckedObject(
        ui, 
        [value](Object* object) -> void {
            object->scale(value);
        }
    );
    update();
}

void MainWindow::on_rotationDial_sliderMoved(int position)
{
    //cout << "position: " << position << endl;
    operateInCheckedObject(
        ui,
        [position](Object* object) -> void {
            object->rotate(position);
        }
    );
    update();
}

// Beta
void MainWindow::on_windowButton_clicked(float centerX, float centerY, float axisX, float axisY)
{
    // Aqui que definimos onde esta o centro do campo de visão e a inclinação
    // Tem que recalcular as cordenadas normalizadas

    pair<float, float> center;
    center.first = centerX;
    center.second = centerY;
    pair<float, float> axis;
    axis.first = axisX;
    axis.second = axisY;

    float teta = angle(center, axis);
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();

    operateInCheckedObject(
        ui,
        [teta, width, height](Object* object) -> void {
            pair<float, float> objectCenter = object->barycenter();
            object->translate(-objectCenter.first, -objectCenter.second);
            object->rotate(teta);
            object->normalize(width, height);
        }
    );
    update();
}

void MainWindow::on_viewportButton_clicked(int width, int height)
{
    // Transformada de Viewport
    // Aqui que definimos o tamanho da janela de visualização

    ui->screen->setWidth(width);
    ui->screen->setHeight(height);

    update();
}

float MainWindow::angle(pair<float, float> center, pair<float, float> axis)
{
    // Calculos do angulo de inclinação
    return 45.0;
}

