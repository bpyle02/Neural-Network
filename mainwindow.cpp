#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trainingdata.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showVectorVals(QString label, std::vector<double> &v)
{
    qInfo() << label << " ";

    for (unsigned i = 0; i < v.size(); i++)
    {
        qInfo() << v[i] << " ";
    }
}

//This function is called every time the submit button is clicked
void MainWindow::on_pushButton_clicked()
{
    updateProgram();

    //Initializes all of the node variables
    inputNodeNum = ui->inputNodesSpinBox->value();
    hiddenNodeCols = ui->hiddenNodeColsSpinBox->value();
    hiddenNodeNum = ui->hiddenNodesSpinBox->value();
    outputNodeNum = ui->outputNodesSpinBox->value();

    doNeuralNetwork();
}

//Function that handles the drawing of nodes on the screen
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setBrush(Qt::BrushStyle::SolidPattern); //Sets a solid brush so the circle is filled

    if (submitClicked)
    {
        //Loops through each column and each node in each column
        for (int i = 0; i < numCols; i++)
        {
            for (unsigned j = 0; j < topology[i]; j++)
            {
                int nodeX = hDistance + 261; //Sets the x position of each node (adds 261 to account for the sidebar)

                //Sets the y position of each node: vDistance + (current node index * twice the size of each node)
                //+ ((number of nodes in the largest column - the number of nodes in the current column) * the size of each node)
                int nodeY = vDistance + (j * nodeSize * 2) + ((maxNodeHeight - topology[i]) * nodeSize);

                painter.drawEllipse(nodeX, nodeY, nodeSize, nodeSize); //Draws the nodes
            }

            hDistance = hDistance + (nodeSize * 2); //Increments the horizontal distance of each node by twice the size fo each node
        }
    }
}

//This program is called when the submit button is clicked and
//updates the submitClicked vvariable and calls the update()
//function to update the program to allow the visualization
//to be reset
void MainWindow::updateProgram()
{
    submitClicked = !submitClicked; //Inver the boolean
    update(); //update the prgram
}

void MainWindow::doNeuralNetwork()
{
    int width = 939; //Screen width after removing the width of the sidebar
    nodeSize = 30; //Variable to determine the node size in pixels (diameter)
    numCols = hiddenNodeCols + 2; //Variable to determine the number of columns

    int trainingPass = 0;
    TrainingData trainData("C:\\Users\\Mail4\\OneDrive\\Documents\\Programming\\Qt\\Neural-Network\\trainingData.txt");

    //If-else block to determine the largest column of nodes
    if (inputNodeNum >= hiddenNodeNum && inputNodeNum >= outputNodeNum)
        maxNodeHeight = inputNodeNum;
    else if (hiddenNodeNum >= inputNodeNum && hiddenNodeNum >= outputNodeNum)
        maxNodeHeight = hiddenNodeNum;
    else
        maxNodeHeight = outputNodeNum;

/*    topology.push_back(inputNodeNum); //Adds the number of nodes in the input column

    //Adds the number of nodes in the hidden column for as many hidden columns as the user specifies
    for (int i = 0; i < hiddenNodeCols; i++)
    {
        topology.push_back(hiddenNodeNum);
    }

    topology.push_back(outputNodeNum);*/ //Adds the number of nodes in the output column

    trainData.getTopology(topology);

    hDistance = width / (1 + numCols); //Determines the horizontal distance each node should be from each other
    vDistance = this->height() / (1 + maxNodeHeight); //Determines the vertical distance each node should be from each other

    Network myNet(topology);

    while (!trainData.isEof())
    {
        trainingPass++;

        qInfo() << "Pass " << trainingPass;

        if (trainData.getNextInputs(inputVals) != topology[0])
        {
            qDebug() << "Bruh?";
            qDebug() << topology[0];
            break;
        }

        showVectorVals("Inputs:", inputVals);
        myNet.feedForward(inputVals);

        myNet.getResults(resultVals);
        showVectorVals("Outputs:", resultVals);

        trainData.getTargetOutputs(targetVals);
        showVectorVals("Targets:", targetVals);
        assert(targetVals.size() == topology.back());

        myNet.backProp(targetVals);

        qDebug() << "Net recent average error: " << myNet.getRecentAverageError();
    }
}




















