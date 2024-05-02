#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "robot.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void spawnRobot();
    void tickUpdate();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<Robot> robots;
    void drawRobot(Robot &rob);
    void drawGrid(QPaintEvent *event);
    void drawAllRobots();
};
#endif // MAINWINDOW_H
