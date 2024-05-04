/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**     2024     **
*****************/

/**
 * @file launcher/entry point of the application
*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
