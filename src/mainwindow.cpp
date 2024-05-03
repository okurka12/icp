#include <vector>
#include <cmath>

#include <QDebug>  // use this instead of std::cout
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QtWidgets>
#include <QKeyEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "icp24.h"  // constants

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<Robot> robots = {};
    std::vector<Obstacle> obstacles = {};
    leftButtonPressed = false;
    paused = false;
    controlled_robot_spawned = false;
    crob = new Robot(0, 0, 0);  // blank robot to be deleted


    setWindowTitle(ICP_TITLE);
    resize(ICP_WIDTH, ICP_HEIGHT);

    /* QTimer for tick simulation */
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::tickUpdate);
    timer->start(1000 / ICP_TPS);

    /* SPAWN button */
    QPushButton *spawn_button = new QPushButton("spawn (s)", this);
    spawn_button->setGeometry(20, 20, 80, 35);  // x, y, width, height
    connect(spawn_button, &QPushButton::clicked, this,
        &MainWindow::spawnRobot);

    /* PAUSE button */
    QPushButton *pause_button = new QPushButton("pause (p)", this);
    pause_button->setGeometry(120, 20, 80, 35);  // x, y, width, height
    connect(pause_button, &QPushButton::clicked, this,
        &MainWindow::toggleSimulation);

    /* SPAWN CONTROLLED button */
    QPushButton *sc_button = new QPushButton("spawn controlled (c)", this);
    sc_button->setGeometry(220, 20, 120, 35);  // x, y, width, height
    connect(sc_button, &QPushButton::clicked, this,
        &MainWindow::spawnControlled);
}

void MainWindow::spawnControlled() {
    if (controlled_robot_spawned) return;  // only spawn one

    Robot crob_local = Robot(
        ICP_INIT_X,
        ICP_INIT_Y,
        ICP_INIT_ANGLE
    );

    if (crob_local.collidesWithAnyone(robots)) {
        return;
    }

    robots.push_back(crob_local);
    delete crob;
    // crob = &robots[robots.size() - 1];
    crob = &robots.back();
    crob->setControlled();

    controlled_robot_spawned = true;
}

void MainWindow::updateCrob() {
    for (Robot &rob : robots) {
        if (rob.isControlled()) {
            crob = &rob;
        }
    }
}

void MainWindow::toggleSimulation() {
    if (paused) {
        timer->start(1000 / ICP_TPS);
        paused = false;
    } else {
        timer->stop();
        paused = true;
    }
}



void MainWindow::keyPressEvent(QKeyEvent *event) {

    /* without this, control of the controlled robot can be lost and undefined
    behaviour can occur */
    updateCrob();

    if (event->key() == Qt::Key_S) {
        qDebug() << "S key pressed!";
        spawnRobot();
    } else if (event->key() == Qt::Key_P) {
        qDebug() << "P key pressed!";
        toggleSimulation();
    } else if (event->key() == Qt::Key_Escape) {
        qDebug() << "ESC key pressed!";
        toggleSimulation();
    } else if (event->key() == Qt::Key_W && event->modifiers() & Qt::CTRL) {
        qDebug() << "CTRL + W pressed!";
        close();
    } else if (event->key() == Qt::Key_C) {
        qDebug() << "C pressed!";
        spawnControlled();

    /* stuff for controlling the controlled robot */
    } else if (event->key() == Qt::Key_I) {
        crob->moveForward(true);
    } else if (event->key() == Qt::Key_J) {
        crob->rotate(1);  // CCW
    } else if (event->key() == Qt::Key_K) {
        crob->flip();
        crob->moveForward(true);
    } else if (event->key() == Qt::Key_L) {
        crob->rotate(-1);  // CW

    } else {
        /* Call base class implementation for other keys */
        QMainWindow::keyPressEvent(event);
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {

    updateCrob();

    if (event->key() == Qt::Key_I) {
        crob->moveForward(false);
    } else if (event->key() == Qt::Key_J) {
        crob->rotate(0);
    } else if (event->key() == Qt::Key_K) {
        crob->flip();
        crob->moveForward(false);
    } else if (event->key() == Qt::Key_L) {
        crob->rotate(0);
    } else {
        QMainWindow::keyPressEvent(event);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        QPoint clickPos = event->pos();

        qDebug() << "Clicked at" << clickPos;
        leftButtonPressed = true;
        obstacles.push_back(Obstacle(clickPos.x() / ICP_OBSIZE, clickPos.y() / ICP_OBSIZE));
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (leftButtonPressed) {
        unsigned int posx = event->pos().x() / ICP_OBSIZE;
        unsigned int posy = event->pos().y() / ICP_OBSIZE;
        bool obstacle_already_present = false;
        for (Obstacle &obs : obstacles) {
            if (obs.x == posx && obs.y == posy) {
                obstacle_already_present = true;
            }
        }
        if (!obstacle_already_present) {
            obstacles.push_back(Obstacle(posx, posy));
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        leftButtonPressed = false;
    }
}

void MainWindow::drawAllObstacles() {
    for (Obstacle &obs : obstacles) {
        drawObstacle(obs.x, obs.y);
    }
}

void MainWindow::drawObstacle(unsigned int x, unsigned int y) {
    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRect(
        x * ICP_OBSIZE,
        y * ICP_OBSIZE,
        ICP_OBSIZE,
        ICP_OBSIZE
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
    drawGrid();
    drawAllRobots();
    drawAllObstacles();
}

void MainWindow::drawGrid()
{
    QPainter painter(this);
    for (int i = 0; i < width(); i += ICP_OBSIZE) {
        for (int j = 0; j < height(); j += ICP_OBSIZE) {
            painter.drawRect(i, j, ICP_OBSIZE, ICP_OBSIZE);
        }
    }

}

void MainWindow::drawAllRobots() {
    for (Robot &rob : robots) {
        this->drawRobot(rob);
    }
}

void MainWindow::updateAllRobots() {
    for (Robot &rob : robots) {
        rob.update(robots, obstacles);
    }
}

void MainWindow::spawnRobot() {

    Robot r = Robot(ICP_INIT_X, ICP_INIT_Y, ICP_INIT_ANGLE);
    if (r.collidesWithAnyone(robots)) return;  // don't spawn
    robots.push_back(r);
    qDebug() << "robot spawned";
}

void MainWindow::tickUpdate() {
    // qDebug() << "tick";

    updateAllRobots();
    update();  // this calls paintEvent

}

void MainWindow::drawRobot(Robot &rob) {
    QPainter painter(this);

    /* convert to integer */
    int xpos = rob.x;
    int ypos = rob.y;

    auto robot_fill_color = rob.isControlled() ? Qt::white : Qt::lightGray;

    /* draw the robot itself */
    painter.setBrush(robot_fill_color);
    painter.setPen(QPen(Qt::black, ICP_ROBOT_OUTLINE));
    painter.drawEllipse(
        xpos - ICP_ROBSIZE,
        ypos - ICP_ROBSIZE,
        2 * ICP_ROBSIZE,
        2 * ICP_ROBSIZE
    );

    /* draw the robot head */
    double radians = ICPdeg2rad(rob.r);
    double headx =
        rob.x + (double)(ICP_ROBSIZE - ICP_ROBHEAD_SIZE) * cos(radians);
    double heady =
        rob.y - (double)(ICP_ROBSIZE - ICP_ROBHEAD_SIZE) * sin(radians);
    painter.setBrush(Qt::black);
    painter.setPen(QPen(Qt::black, 1));
    painter.drawEllipse(
        headx - ICP_ROBHEAD_SIZE,
        heady - ICP_ROBHEAD_SIZE,
        2 * ICP_ROBHEAD_SIZE,
        2 * ICP_ROBHEAD_SIZE
    );



}
