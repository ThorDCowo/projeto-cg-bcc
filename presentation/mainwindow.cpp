#include <iostream>
#include <math.h>
#include <cmath>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QBrush>

#include "ui_mainwindow.h"
#include "mainwindow.h"


using namespace std;

float MOVE_SPEED = 20.0;
int WIDTH = 854;  //inicialize with viewport size
int HEIGHT = 480; //inicialize with viewport size
Coordinate CENTER{0,0};
float TETA = 0.0;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    transformFromWorldToViewportUseCase(new TransformFromWorldToViewportUseCase(
        new ClippObjectUseCase(new Clipper())
    )),
    readCoordinateFileUseCase(new ReadCoordinateFileUseCase(
        new FileReader(),
        new CoordinateParser()
    ))
{
    ui->setupUi(this);

    QList<Object*> list = ObjectListFactory::createObjectList();
    QList<Object*> charziardList = this->readCoordinateFileUseCase->execute("C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\charizard\\charizard.obj");

    list.append(charziardList);

    ui->screen->setObjectList(list);

    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    for (int i = 0; i < list.size(); i++){
        QListWidgetItem *item = new QListWidgetItem;
        this->transformFromWorldToViewportUseCase->execute(list[i], width, height, center);
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

void MainWindow::on_upButton_clicked()
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(ui, [this, width, height, center](Object* object) {
        object->translate(Coordinate::up() * MOVE_SPEED);
        this->transformFromWorldToViewportUseCase->execute(object, width, height, center);
    });
    update();
}

void MainWindow::on_rightButton_clicked()
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(ui, [this, width, height, center](Object* object) {
        object->translate(Coordinate::right() * MOVE_SPEED);
        this->transformFromWorldToViewportUseCase->execute(object, width, height, center);
    });
    update();
}

void MainWindow::on_downButton_clicked()
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(ui, [this, width, height, center](Object* object) {
        object->translate(Coordinate::down() * MOVE_SPEED);
        this->transformFromWorldToViewportUseCase->execute(object, width, height, center);
    });
    update();
}

void MainWindow::on_leftButton_clicked()
{    
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(ui, [this, width, height, center](Object* object) {
       object->translate(Coordinate::left() * MOVE_SPEED);
       this->transformFromWorldToViewportUseCase->execute(object, width, height, center);
    });
    update();
}

void MainWindow::on_scaleSlider_valueChanged(int value)
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(
        ui, 
        [this, value, width, height, center](Object* object) -> void {
            object->scale(value);
            this->transformFromWorldToViewportUseCase->execute(object, width, height, center);
        }
    );
    update();
}

void MainWindow::on_rotationDial_sliderMoved(int position)
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();
    Coordinate axis(0,0,1);

    operateInCheckedObjects(
        ui,
        [this, position, width, height, center](Object* object) -> void {
            object->rotate(position, Coordinate::forward());
            this->transformFromWorldToViewportUseCase->execute(object, width, height, center);
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
        [this, width, height](Object* object) -> void {
            object->rotateWorld(TETA, Coordinate::forward());
            this->transformFromWorldToViewportUseCase->execute(object, width, height, CENTER);
        }
    );  

    update();
}

void MainWindow::on_centerXLineEdit_textEdited(const QString &input)
{
    bool ok;
    CENTER.x = input.toFloat(&ok);
}

void MainWindow::on_centerYLineEdit_textEdited(const QString &input)
{
    bool ok;
    CENTER.y = input.toFloat(&ok);
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

void MainWindow::operateInCheckedObjects(
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

QList<QListWidgetItem*> MainWindow::getCheckedListWidgetItems(QListWidget* listWidget) {
    QList<QListWidgetItem*> checked;
    
    for(qsizetype i = 0; i < listWidget->count(); i++)
        if(listWidget->item(i)->checkState()) {
            checked.append(listWidget->item(i));
        }

    return checked;
}

void MainWindow::applyOperationInCheckedObjects(
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

void MainWindow::applyOperationInObjects(QList<Object*> list, function<void(Object*)>operation) {
    for (qsizetype i = 0; i < list.length(); i++) {
        operation(list[i]);
    }
}