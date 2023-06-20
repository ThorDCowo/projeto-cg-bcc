#include <iostream>
#include <math.h>
#include <cmath>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QBrush>
#include "ui_camera.h"
#include "camera.h"



using namespace std;

const float MOVE_SPEED = 20.0;
const int WIDTH = 854;  //inicialize with viewport size
const int HEIGHT = 480; //inicialize with viewport size


Coordinate COP{10, 10, 30};
float TETA = 0.0;

float ALPHA = 0.0; //inicialize with viewport size
float BETA = 0.0; //inicialize with viewport size

Camera::Camera(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Camera),
    orthogonalProjectionUseCase(new OrthogonalProjectionUseCase(
        new ClippObjectUseCase(new Clipper())
    )),
    perspectiveProjectionUseCase(new PerspectiveProjectionUseCase(
        new ClippObjectUseCase(new Clipper())
    )),
    readCoordinateFileUseCase(new ReadCoordinateFileUseCase(
        new FileReader(),
        new CoordinateParser()
    ))
{
    ui->setupUi(this);

    this->distanceFromProjection = 88; 

    QList<Object*> objectList = ObjectListFactory::createObjectList();
    QList<Object*> charziardList = this->readCoordinateFileUseCase->execute("C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\charizard\\charizard.obj");

    objectList.append(charziardList);

    ui->screen->setObjectList(objectList);

    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    for (int i = 0; i < objectList.size(); i++){
        QListWidgetItem *item = new QListWidgetItem;

        chooseProjectionMode(objectList[i], ui->comboBox->currentIndex());
        
        item->setText(objectList[i]->getName());
        item->setCheckState(Qt::Unchecked);
        item->setForeground(Qt::white);

        ui->objectList->addItem(item);
    }
}

Camera::~Camera()
{
    delete ui;
}

void Camera::on_upButton_clicked()
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(ui, [this, width, height, center](Object* object) {
        object->translate(Coordinate::up() * MOVE_SPEED);
        chooseProjectionMode(object, ui->comboBox->currentIndex());
    });
    update();
}

void Camera::on_rightButton_clicked()
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(ui, [this, width, height, center](Object* object) {
        object->translate(Coordinate::right() * MOVE_SPEED);
        chooseProjectionMode(object, ui->comboBox->currentIndex());
    });
    update();
}

void Camera::on_downButton_clicked()
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(ui, [this, width, height, center](Object* object) {
        object->translate(Coordinate::down() * MOVE_SPEED);
        chooseProjectionMode(object, ui->comboBox->currentIndex());
    });
    update();
}

void Camera::on_leftButton_clicked()
{    
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(ui, [this, width, height, center](Object* object) {
       object->translate(Coordinate::left() * MOVE_SPEED);
       chooseProjectionMode(object, ui->comboBox->currentIndex());
    });
    update();
}

void Camera::on_scaleSlider_valueChanged(int value)
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();

    operateInCheckedObjects(
        ui, 
        [this, value, width, height, center](Object* object) -> void {
            object->scale(value);
            chooseProjectionMode(object, ui->comboBox->currentIndex());
        }
    );
    update();
}

void Camera::on_rotationDial_sliderMoved(int position)
{
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();
    Coordinate center = ui->screen->getCenter();
    Coordinate axis(0,0,1);

    operateInCheckedObjects(
        ui,
        [this, position, width, height, center](Object* object) -> void {
            object->rotate(position, Coordinate::forward());
            chooseProjectionMode(object, ui->comboBox->currentIndex());
        }
    );
    update();
}

void Camera::on_windowButton_clicked()
{
    // Aqui que definimos onde esta o centro do campo de visão e a inclinação
    // Tem que recalcular as cordenadas normalizadas

    ui->screen->setCenter(this->center);
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();

    applyOperationInObjects(
        ui->screen->getObjectList(),
        [this, width, height](Object* object) -> void {
            object->rotateWorld(TETA, Coordinate::forward());
            chooseProjectionMode(object, ui->comboBox->currentIndex());
        }
    );  

    update();
}


void Camera::operateInCheckedObjects(
    Ui::Camera* ui, 
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

QList<QListWidgetItem*> Camera::getCheckedListWidgetItems(QListWidget* listWidget) {
    QList<QListWidgetItem*> checked;
    
    for(qsizetype i = 0; i < listWidget->count(); i++)
        if(listWidget->item(i)->checkState()) {
            checked.append(listWidget->item(i));
        }

    return checked;
}

void Camera::applyOperationInCheckedObjects(
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

void Camera::applyOperationInObjects(QList<Object*> list, function<void(Object*)>operation) {
    for (qsizetype i = 0; i < list.length(); i++) {
        operation(list[i]);
    }
}

void Camera::on_change_zoom_input_textChanged(const QString &input)
{
    bool ok;
    this->distanceFromProjection = input.toFloat(&ok);
}

void Camera::on_projection_button_clicked()
{
    applyOperationInObjects(
        ui->screen->getObjectList(),
        [this](Object* object) -> void {
            chooseProjectionMode(object, ui->comboBox->currentIndex());
        }
    );  

    update();

}

void Camera::chooseProjectionMode(Object* object, int projectionMode) {
    
    Coordinate windowCenter = ui->screen->getCenter();
    int width = ui->screen->getWidth();
    int height = ui->screen->getHeight();

    if (projectionMode == PERSPECTIVE) {
        this->perspectiveProjectionUseCase->execute(
            object, 
            COP,
            windowCenter, 
            width, 
            height, 
            this->distanceFromProjection,
            ALPHA, 
            BETA
        );
    }

    if (projectionMode == ORTHOGONAL_IN_XY) {
        this->orthogonalProjectionUseCase->execute(
            object,
            width,
            height,
            windowCenter,
            Coordinate::axisZ()
        );
    }

    if (projectionMode == ORTHOGONAL_IN_XZ) {
        this->orthogonalProjectionUseCase->execute(
            object,
            width,
            height,
            windowCenter,
            Coordinate::axisY()
        );
    }

    if (projectionMode == ORTHOGONAL_IN_YZ) {
        this->orthogonalProjectionUseCase->execute(
            object,
            width,
            height,
            windowCenter,
            Coordinate::axisX()
        );
    }

}

void Camera::on_upButton_Move_clicked()
{

}

void Camera::on_rightButton_Move_clicked()
{

}

void Camera::on_downButton_Move_clicked()
{

}

void Camera::on_leftButton_Move_clicked()
{

}

void Camera::on_upButton_Cam_clicked()
{

}

void Camera::on_rightButton_Cam_clicked()
{

}

void Camera::on_downButton_Cam_clicked()
{

}

void Camera::on_leftButton_Cam_clicked()
{

}
