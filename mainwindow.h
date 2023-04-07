#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slot1(int);

private slots:
    void on_translationButton_clicked();

    void on_scaleButton_clicked();

    void on_rotationButton_clicked();

    void on_toolButton_3_clicked();

    void on_upButton_clicked();

    void on_rightButton_clicked();

    void on_downButton_clicked();

    void on_leftButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
