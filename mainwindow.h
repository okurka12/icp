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
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void spawnRobot();
    void tickUpdate();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::vector<Robot> robots;
    std::vector<Obstacle> obstacles;
    void drawRobot(Robot &rob);
    void drawGrid(QPaintEvent *event);
    void drawObstacle(unsigned int x, unsigned int y);
    void drawAllRobots();
    void updateAllRobots();
    void drawAllObstacles();
    void spawnControlled();
    void toggleSimulation();

    /**
     * finds the controlled robot in the vector of all robots
    */
    void updateCrob();

    void CRUp();
    void CRDown();
    void CRLeft();
    void CRRight();
    Robot *crob;  // the one robot that is controlled;
    bool controlled_robot_spawned;
    bool leftButtonPressed;
    bool paused;
};
#endif // MAINWINDOW_H
