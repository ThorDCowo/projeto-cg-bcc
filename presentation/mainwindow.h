#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void on_upButton_clicked();
    void on_rightButton_clicked();
    void on_downButton_clicked();
    void on_leftButton_clicked();
    void on_scaleSlider_valueChanged(int value);
    void on_rotationDial_sliderMoved(int position);
    void on_windowButton_clicked();
    void on_centerXLineEdit_textEdited(const QString &input);
    void on_centerYLineEdit_textEdited(const QString &input);
    void on_angleLineEdit_textChanged(const QString &input);
    void on_zoomSlider_valueChanged(int value);

private:
    Ui::MainWindow* ui;
    TransformFromWorldToViewportUseCase* transformFromWorldToViewportUseCase;
    ReadCoordinateFileUseCase* readCoordinateFileUseCase;

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
};
#endif // MAINWINDOW_H
