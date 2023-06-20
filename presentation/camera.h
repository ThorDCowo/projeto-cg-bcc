#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include "../screen.h"
#include "../core/entities/object.h"
#include "../infra/object_list_factory/object_list_factory.h"
#include "../use_cases/orthogonal_projection/orthogonal_projection.use_case.h"
#include "../use_cases/perspective_projection/perspective_projection.use_case.h"
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

enum ProjectionMode {
    PERSPECTIVE,
    ORTHOGONAL_IN_XY,
    ORTHOGONAL_IN_XZ,
    ORTHOGONAL_IN_YZ,
};

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
    void on_projection_button_clicked();
    void on_upButton_Move_clicked();
    void on_rightButton_Move_clicked();
    void on_downButton_Move_clicked();
    void on_leftButton_Move_clicked();
    void on_upButton_Cam_clicked();
    void on_rightButton_Cam_clicked();
    void on_downButton_Cam_clicked();
    void on_leftButton_Cam_clicked();

private:
    Ui::Camera* ui;
    OrthogonalProjectionUseCase* orthogonalProjectionUseCase;
    PerspectiveProjectionUseCase* perspectiveProjectionUseCase;
    ReadCoordinateFileUseCase* readCoordinateFileUseCase;

    float distanceFromProjection;
    Coordinate center = Coordinate::zero();          

    QList<QListWidgetItem*> getCheckedListWidgetItems(QListWidget* listWidget);

    void operateInCheckedObjects(
        Ui::Camera* ui, 
        function<void(Object*)> operation
    );

    void chooseProjectionMode( Object* object, int projectionMode);

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
