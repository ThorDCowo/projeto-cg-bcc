#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include "../use_cases/transform_from_world_to_viewport/transform_from_world_to_viewport.use_case.h"
#include "../screen.h"
#include "../core/entities/object.h"
#include "../infra/object_list_factory/object_list_factory.h"
#include "../use_cases/transform_from_world_to_viewport/transform_from_world_to_viewport.use_case.h"
#include "../use_cases/clipp_object/clipp_object.use_case.h"
#include "../use_cases/read_coordinate_file/read_coordinate_file.use_case.h"
#include "../infra/clipper/clipper.h"
#include "../infra/file_reader/file_reader.h"
#include "../infra/coordinate_parser/coordinate_parser.h"
#include "../core/entities/coordinate.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Camera; }
QT_END_NAMESPACE

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    Camera(QWidget* parent = nullptr);
    ~Camera();

private slots:

    void on_upButton_clicked();
    void on_rightButton_clicked();
    void on_downButton_clicked();
    void on_leftButton_clicked();
    void on_scaleSlider_valueChanged(int value);
    void on_rotationDial_sliderMoved(int position);
    void on_windowButton_clicked();
    void on_change_zoom_input_textChanged(const QString &input);

private:
    Ui::Camera* ui;
    TransformFromWorldToViewportUseCase* transformFromWorldToViewportUseCase;
    ReadCoordinateFileUseCase* readCoordinateFileUseCase;

    float distanceFromProjection;
    Coordinate center = Coordinate::zero();          

    QList<QListWidgetItem*> getCheckedListWidgetItems(QListWidget* listWidget);

    void operateInCheckedObjects(
        Ui::Camera* ui, 
        function<void(Object*)> operation
    );

    void applyOperationInObjects(QList<Object*> list, function<void(Object*)>operation);
    void applyOperationInCheckedObjects(
        QList<QListWidgetItem*> checked, 
        QList<Object*> list,
        function<void(Object*)> operation
    );
    void operateInViewport(
        Ui::Camera* ui, 
        function<void(Screen*)> screen
    );
};
#endif // CAMERA_H
