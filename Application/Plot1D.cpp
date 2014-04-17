#include "Plot1D.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <iostream>
#include <string>
#include <fstream>

Plot1D::Plot1D(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  // constructor
  ui->setupUi(this);
  setGeometry(400, 250, 542, 390);
  statusBar()->clearMessage();
}

Plot1D::~Plot1D()
{
  // destructor
  delete ui;
}

void Plot1D::setThePlot(string fileName, string fileName_ex, int gridSize)
{
  // function for plotting the numerical and exact solution

  setWindowTitle("Numerical and Exact Solution Plot");

  QVector<double> x(gridSize), y(gridSize);
  QVector<double> x_ex(gridSize), y_ex(gridSize);

  x_hist = new double [gridSize];
  y_hist = new double [gridSize];
  y_ex_hist = new double [gridSize];

  ifstream inFile,inFile_ex;
  double maxX, minX, maxY, minY;
  maxX = 0;
  minX = 0;
  maxY = 0;
  minY = 0;

  // read the solutions from file
  inFile.open(fileName.c_str());
  inFile_ex.open(fileName_ex.c_str());
  string firstLine, firstLine_ex;
  getline(inFile, firstLine);
  getline(inFile_ex, firstLine_ex);

  for (int i = 0; i < gridSize; i++)
  {
    inFile >> x[i];
    x_hist[i] = x[i];
    inFile_ex >> x_ex[i];

    // update the minX
    if (x[i] < minX)
    {
      minX = x[i];
    }
    if (x_ex[i] < minX)
    {
      minX = x_ex[i];
    }

    // update the maxX
    if (x[i] > maxX)
    {
      maxX = x[i];
    }
    if (x_ex[i] > maxX)
    {
      maxX = x_ex[i];
    }

    inFile >> y[i];
    y_hist[i] = y[i];
    inFile_ex >> y_ex[i];
    y_ex_hist[i] = y_ex[i];

    // update the minY
    if (y[i] < minY)
    {
      minY = y[i];
    }
    if (y_ex[i] < minY)
    {
      minY = y_ex[i];
    }

    // update the maxY
    if (y[i] > maxY)
    {
      maxY = y[i];
    }
    if (y_ex[i] > maxY)
    {
      maxY = y_ex[i];
    }
  }

  inFile.close();
  inFile_ex.close();

  // create graph and assign data to it:
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x, y);
  ui->customPlot->graph(0)->setName("Numerical solution");

  // define the properties of the plot
  QPen pen;
  pen.setColor(QColor(0, 0, 0, 255));
  ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
  ui->customPlot->graph(0)->setPen(pen);

  ui->customPlot->addGraph();
  ui->customPlot->graph(1)->setData(x_ex, y_ex);
  ui->customPlot->graph(1)->setName("Exact solution");

  QPen pen_ex;
  pen_ex.setColor(QColor(150, 150, 150, 255));
  ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
  ui->customPlot->graph(1)->setPen(pen_ex);

  // give the axes some labels:
  ui->customPlot->xAxis->setLabel("r");
  ui->customPlot->yAxis->setLabel("Phi");
  // set axes ranges, so we see all data:
  ui->customPlot->xAxis->setRange(minX, maxX);
  ui->customPlot->yAxis->setRange(minY, maxY);
  ui->customPlot->setInteraction(QCP::iRangeDrag, true);
  ui->customPlot->setInteraction(QCP::iRangeZoom, true);

  // add interaction "mouse query for data points"
  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,
          SLOT(clickedGraph(QMouseEvent*)));

// other interaction options:
//  ui->customPlot->setInteraction(QCP::iSelectPlottables, true);
//  ui->customPlot->setInteraction(QCP::iMultiSelect, true);
//  ui->customPlot->setInteraction(QCP::iSelectAxes, true);
//  ui->customPlot->legend->setVisible(true);

  ui->customPlot->replot();
}

void Plot1D::setThePlot_error(string fileName, string fileName_ex,
                              int gridSize)
{
  // function for plotting the error
  setWindowTitle("Error PLot");

  QVector<double> x(gridSize), y(gridSize);
  QVector<double> x_ex(gridSize), y_ex(gridSize);
  QVector<double> x_error(gridSize), y_error(gridSize);

  ifstream inFile,inFile_ex;
  double maxX, minX, maxY, minY;
  maxX = 0;
  minX = 0;
  maxY = 0;
  minY = 0;

  inFile.open(fileName.c_str());
  inFile_ex.open(fileName_ex.c_str());
  string firstLine, firstLine_ex;
  getline(inFile, firstLine);
  getline(inFile_ex, firstLine_ex);

  for (int i = 0; i < gridSize; i++)
  {
    inFile >> x[i];
    inFile_ex >> x_ex[i];
    // update the minX
    if (x[i] < minX)
    {
      minX = x[i];
    }

    // update the maxX
    if (x[i] > maxX)
    {
      maxX = x[i];
    }

    inFile >> y[i];
    inFile_ex >> y_ex[i];
    y_error[i] = y[i] - y_ex[i];

    // update the minY
    if (y_error[i] < minY)
    {
      minY = y_error[i];
    }

    // update the maxY
    if (y_error[i] > maxY)
    {
      maxY = y_error[i];
    }
  }

  // create graph and assign data to it:
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x, y_error);
  ui->customPlot->graph(0)->setName("Error");

  // define the properties of the plot
  QPen pen;
  pen.setColor(QColor(255, 0, 0, 255));
  ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
  ui->customPlot->graph()->setPen(pen);
  // give the axes some labels:
  ui->customPlot->xAxis->setLabel("r");
  ui->customPlot->yAxis->setLabel("Phi");
  // set axes ranges, so we see all data:
  ui->customPlot->xAxis->setRange(minX, maxX);
  ui->customPlot->yAxis->setRange(minY, maxY);
  ui->customPlot->setInteraction(QCP::iRangeDrag, true);
  ui->customPlot->setInteraction(QCP::iRangeZoom, true);
  ui->customPlot->setInteraction(QCP::iSelectPlottables, true);
  ui->customPlot->setInteraction(QCP::iMultiSelect, true);
  ui->customPlot->setInteraction(QCP::iSelectAxes, true);

  ui->customPlot->replot();
}

void Plot1D::clickedGraph(QMouseEvent *event)
{
  // function for mouse interaction

  // ontain the mouse position when click on the plot and transfer the pixel
  // position to the coord position
  xPosition = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
  yPosition = ui->customPlot->yAxis->pixelToCoord(event->pos().y());

  // get the closest solution point w.r.t. the mouse clicked coord position
  int i = 0;
  while (xPosition > x_hist[i])
  {
    i = i+1;
  }

  xPosition_dis = x_hist[i];
  yPosition_dis = y_hist[i];
  yPosition_ex_dis = y_ex_hist[i];
  double error_dis = yPosition_dis - yPosition_ex_dis;

  // update the status bar message
  ui->statusBar->showMessage(QString("r: %1;  Phi(num.): %2;  "
                                     "Phi(exa.): %3;  Error: %4")
                             .arg(xPosition_dis)
                             .arg(yPosition_dis)
                             .arg(yPosition_ex_dis)
                             .arg(error_dis)
                             , 0);

  QVector<double> x(2), y(2);
  x[0] = xPosition_dis;
  x[1] = xPosition_dis;
  y[0] = yPosition_dis;
  y[1] = yPosition_ex_dis;

  // plot the clicked data points
  ui->customPlot->addGraph();
  ui->customPlot->graph(2)->setData(x, y);
  ui->customPlot->graph(2)->setName("Point track");
  ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
  ui->customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, QPen(Qt::red), QBrush(Qt::white), 10));
}
