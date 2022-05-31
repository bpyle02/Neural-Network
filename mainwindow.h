#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "network.h"

#include <vector>

#include <QMainWindow>
#include <QtGui>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    std::vector<double> inputVals;
    std::vector<double> targetVals;
    std::vector<double> resultVals;
    std::vector<unsigned> topology;

    //Variables to account for the number of nodes in each column as
    //well as one to determine the number of hidden node columns
    int inputNodeNum = 0;
    int hiddenNodeCols = 0;
    int hiddenNodeNum = 0;
    int outputNodeNum = 0;

    //Neural Network Variables
    int numCols;
    int hDistance;
    int vDistance;
    int nodeSize;
    int maxNodeHeight;

    //Boolean used to update whether the submit button has been clicked
    //or not
    bool submitClicked = false;

    //Function that handles the drawing of nodes on the screen
    void paintEvent(QPaintEvent *e);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void doNeuralNetwork();
    void showVectorVals(QString label, std::vector<double> &v);

private slots:
    //This function is called every time the submit button is clicked
    void on_pushButton_clicked();

    //This program is called when the submit button is clicked and
    //updates the submitClicked vvariable and calls the update()
    //function to update the program to allow the visualization
    //to be reset
    void updateProgram();
};
#endif // MAINWINDOW_H
