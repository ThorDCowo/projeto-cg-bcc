#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_upButton_clicked();
    void on_rightButton_clicked();
    void on_downButton_clicked();
    void on_leftButton_clicked();
    void on_scaleSlider_valueChanged(int value);
    void on_rotationDial_sliderMoved(int position);

    // Beta
    void on_windowButton_clicked(float centerX, float centerY, float axisX, float axisY);
    void on_viewportButton_clicked(int width, int height);
    float angle(pair<float, float> center, pair<float, float> axis);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
