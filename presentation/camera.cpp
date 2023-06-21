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

Coordinate COP{0, 0, 0};

// float ALPHA = 0.0; //inicialize with viewport size
// float BETA = 0.0; //inicialize with viewport size

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

    this->distanceFromProjection = 1; 

    QList<Object*> objectList = ObjectListFactory::createObjectList();
    QList<Object*> charizardList = this->readCoordinateFileUseCase->execute("C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\charizard\\charizard.obj");

    objectList.append(charizardList);

    ui->screen->setObjectList(objectList);
    
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

float Camera::angleBetweenViewPlaneProjectionAndAxis(Coordinate axis) {

    return Coordinate::angle(axis, center);
}

void Camera::on_upButton_clicked()
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
        object->translate(Coordinate::up() * MOVE_SPEED);
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

void Camera::on_zoomButton_clicked()
{
    applyOperationInObjects(
        ui->screen->getObjectList(),
        [this](Object* object) -> void {
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
    this->distanceFromProjection = this->distanceFromProjection * (-input.toFloat(&ok) / 100);
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
    float alpha = angleBetweenViewPlaneProjectionAndAxis(Coordinate::axisX());
    float beta = angleBetweenViewPlaneProjectionAndAxis(Coordinate::axisY());

    if (projectionMode == PERSPECTIVE) {
        this->perspectiveProjectionUseCase->execute(
            object,
            COP,
            windowCenter,
            width,
            height,
            this->distanceFromProjection,
            alpha,
            beta
        );
        
        ui->upButton_Cam->setDisabled(false);
        ui->rightButton_Cam->setDisabled(false);
        ui->downButton_Cam->setDisabled(false);
        ui->leftButton_Cam->setDisabled(false);
    }

    if (projectionMode == ORTHOGONAL_IN_XY) {
        this->orthogonalProjectionUseCase->execute(
            object,
            width,
            height,
            windowCenter,
            Coordinate::axisZ()
        );

        ui->upButton_Cam->setDisabled(true);
        ui->rightButton_Cam->setDisabled(true);
        ui->downButton_Cam->setDisabled(true);
        ui->leftButton_Cam->setDisabled(true);
    }

    if (projectionMode == ORTHOGONAL_IN_XZ) {
        this->orthogonalProjectionUseCase->execute(
            object,
            width,
            height,
            windowCenter,
            Coordinate::axisY()
        );

        ui->upButton_Cam->setDisabled(true);
        ui->rightButton_Cam->setDisabled(true);
        ui->downButton_Cam->setDisabled(true);
        ui->leftButton_Cam->setDisabled(true);
    }

    if (projectionMode == ORTHOGONAL_IN_YZ) {
        this->orthogonalProjectionUseCase->execute(
            object,
            width,
            height,
            windowCenter,
            Coordinate::axisX()
        );

        ui->upButton_Cam->setDisabled(true);
        ui->rightButton_Cam->setDisabled(true);
        ui->downButton_Cam->setDisabled(true);
        ui->leftButton_Cam->setDisabled(true);
    }

}

void Camera::makeMovement(int projectionMode, Coordinate direction) {
    if (projectionMode == PERSPECTIVE) {
        perspectiveMovement(direction);
        return;
    }
    orthogonalMovement(direction);
}

void Camera::perspectiveMovement(Coordinate direction)
{
    if(direction == Coordinate::up()){
        applyOperationInObjects(
            ui->screen->getObjectList(),
            [this](Object* object) -> void {
                object->translate(Coordinate::up() * MOVE_SPEED);
            }
        );
    }
    if(direction == Coordinate::right()){
        applyOperationInObjects(
            ui->screen->getObjectList(),
            [this](Object* object) -> void {
                object->translate(Coordinate::right() * MOVE_SPEED);
            }   
        );
    }
    if(direction == Coordinate::down()){
        applyOperationInObjects(
            ui->screen->getObjectList(),
            [this](Object* object) -> void {
                object->translate(Coordinate::down() * MOVE_SPEED);
            }
        ); 
    }
    if(direction == Coordinate::left()){
        applyOperationInObjects(
            ui->screen->getObjectList(),
            [this](Object* object) -> void {
                object->translate(Coordinate::left() * MOVE_SPEED);
            }
        );
    }

    update();
}

void Camera::orthogonalMovement(Coordinate direction)
{
    if(direction == Coordinate::up()){
        applyOperationInObjects(
            ui->screen->getObjectList(),
            [this](Object* object) -> void {
                object->translateProjection(Coordinate::down() * MOVE_SPEED);
            }
        ); 
    }

    if(direction == Coordinate::right()){
        applyOperationInObjects(
            ui->screen->getObjectList(),
            [this](Object* object) -> void {
                object->translateProjection(Coordinate::right() * MOVE_SPEED);
            }
        ); 
    }
    
    if(direction == Coordinate::down()){
        applyOperationInObjects(
            ui->screen->getObjectList(),
            [this](Object* object) -> void {
                object->translateProjection(Coordinate::up() * MOVE_SPEED);
            }
        ); 
    }
    
    if(direction == Coordinate::left()){
        applyOperationInObjects(
            ui->screen->getObjectList(),
            [this](Object* object) -> void {
                object->translateProjection(Coordinate::left() * MOVE_SPEED);
            }
        ); 
    }
    update();
}

void Camera::on_upButton_Move_clicked()
{
    makeMovement(ui->comboBox->currentIndex(), Coordinate::up()); 
}

void Camera::on_rightButton_Move_clicked()
{
    makeMovement(ui->comboBox->currentIndex(), Coordinate::right());  
}

void Camera::on_downButton_Move_clicked()
{
    makeMovement(ui->comboBox->currentIndex(), Coordinate::down()); 
}

void Camera::on_leftButton_Move_clicked()
{
    makeMovement(ui->comboBox->currentIndex(), Coordinate::left()); 
}

void Camera::on_upButton_Cam_clicked()
{
    Coordinate newCenter = ui->screen->getCenter();
    newCenter.x += MOVE_SPEED;
    ui->screen->setCenter(newCenter);
}

void Camera::on_rightButton_Cam_clicked()
{
    Coordinate newCenter = ui->screen->getCenter();
    newCenter.y -= MOVE_SPEED;
    ui->screen->setCenter(newCenter);
}

void Camera::on_downButton_Cam_clicked()
{
    Coordinate newCenter = ui->screen->getCenter();
    newCenter.x -= MOVE_SPEED;
    ui->screen->setCenter(newCenter);
}

void Camera::on_leftButton_Cam_clicked()
{
    Coordinate newCenter = ui->screen->getCenter();
    newCenter.y += MOVE_SPEED;
    ui->screen->setCenter(newCenter);
}
