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
    void on_windowButton_clicked();
    void on_centerXLineEdit_textEdited(const QString &input);
    void on_centerYLineEdit_textEdited(const QString &input);
    void on_angleLineEdit_textChanged(const QString &input);
    void on_zoomSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
