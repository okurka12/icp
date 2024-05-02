#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <vector>
#include "robot.h"
#include "ui_mainwindow.h"
#include "obstacle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void spawnRobot();
    void tickUpdate();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<Robot> robots;
    std::vector<Obstacle> obstacles;
    void drawRobot(Robot &rob);
    void drawGrid(QPaintEvent *event);
    void drawObstacle(unsigned int x, unsigned int y);
    void drawAllRobots();
    void updateAllRobots();
    void drawAllObstacles();
    bool leftButtonPressed;
};
#endif // MAINWINDOW_H
