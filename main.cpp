/*
    05/23/2022

    Neural Network Visualization Application written by Brandon Pyle
    using Qt6 and C++
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
