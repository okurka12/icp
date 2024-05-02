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

void MainWindow::spawnRobot() {
    qDebug() << "robot spawned";
    int init_x = 100;
    int init_y = 100;
    int init_angle = 270;
    robots.push_back(Robot(init_x, init_y, init_angle));
}

void MainWindow::tickUpdate() {
    // qDebug() << "tick";

    update();

}

void MainWindow::drawRobot(Robot &rob) {
    QPainter painter(this);
    painter.drawEllipse(rob.x - ICP_ROBSIZE, rob.y - ICP_ROBSIZE, 2 * ICP_ROBSIZE, 2 * ICP_ROBSIZE);
}
