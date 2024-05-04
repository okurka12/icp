/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**     2024     **
*****************/

/**
 * @file a class for the GUI plus methods for timing and
 * controlling the simulation
*/

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

    /**
     * IO events below
    */

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    /**
     * Updates robot positions + redraws the window
    */
    void tickUpdate();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::vector<Robot> robots;
    std::vector<Obstacle> obstacles;
    void drawRobot(Robot &rob);
    void drawGrid();
    void drawObstacle(unsigned int x, unsigned int y);
    void drawAllRobots();
    void updateAllRobots();
    void drawAllObstacles();

    /**
     * add controlled robot to the simulation or do nothing if there
     * already is one
    */
    void spawnControlled();

    /**
     * add autonomous robot to the simulation
    */
    void spawnRobot();

    /**
     * pause/unpause the simulation
    */
    void toggleSimulation();

    void loadObstacles();
    void saveObstacles();

    /**
     * finds the controlled robot in the vector of all robots
     * and update attribute `crob`
    */
    void updateCrob();

    /**
     * these methods would be added if there were GUI buttons for
     * controlling the controlled robot
    */
    // void CRUp();
    // void CRDown();
    // void CRLeft();
    // void CRRight();

    /* controlled robot - the one robot that is controlled */
    Robot *crob;

    bool controlled_robot_spawned;
    bool leftButtonPressed;
    bool paused;
};
#endif // MAINWINDOW_H
