#include <QDebug>  // use this instead of std::cout
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "icp24.h"  // constants

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<Robot> robots = {};

    setWindowTitle(ICP_TITLE);
    resize(ICP_WIDTH, ICP_HEIGHT);

    /* QTimer for tick simulation */
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::tickUpdate);
    timer->start(1000 / ICP_TPS);

    /* SPAWN button */
    QPushButton *button = new QPushButton("spawn", this);
    button->setGeometry(20, 20, 60, 30);  // x, y, width, height
    connect(button, &QPushButton::clicked, this, &MainWindow::spawnRobot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    // QMainWindow::paintEvent(event);
    drawGrid(event);
    drawAllRobots();
}

void MainWindow::drawGrid(QPaintEvent *event)
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
        rob.update();
    }
}

void MainWindow::spawnRobot() {
    robots.push_back(Robot(ICP_INIT_X, ICP_INIT_Y, ICP_INIT_ANGLE));
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

    painter.drawEllipse(
        xpos - ICP_ROBSIZE,
        ypos - ICP_ROBSIZE,
        2 * ICP_ROBSIZE,
        2 * ICP_ROBSIZE
    );
}
