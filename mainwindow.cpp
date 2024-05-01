#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "icp24.h"  // constants

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(ICP_TITLE);
    resize(ICP_WIDTH, ICP_HEIGHT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    int cellWidth = width() / 13;
    int cellHeight = height() / 7;

    // Draw grid
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 7; ++j) {
            painter.drawRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
        }
    }
}

