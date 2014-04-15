#include "PlottingMainWindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <iostream>
#include <string>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setGeometry(400, 250, 542, 390);

  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();
}

void MainWindow::setThePlot(string fileName, string fileName_ex, int gridSize)
{
   QVector<double> x(gridSize), y(gridSize);
   QVector<double> x_ex(gridSize), y_ex(gridSize);

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
      inFile_ex >> y_ex[i];
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

   QPen pen;
   pen.setColor(QColor(0, 0, 0, 255));
   ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
   ui->customPlot->graph(0)->setPen(pen);

   ui->customPlot->addGraph();
   ui->customPlot->graph(1)->setData(x_ex, y_ex);
   ui->customPlot->graph(1)->setName("Exact solution");

   QPen pen_ex;
   pen_ex.setColor(QColor(192, 192, 192, 255));
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
   ui->customPlot->setInteraction(QCP::iSelectPlottables, true);
   ui->customPlot->setInteraction(QCP::iMultiSelect, true);
   ui->customPlot->setInteraction(QCP::iSelectAxes, true);

//   ui->customPlot->legend->setVisible(true);

   ui->customPlot->replot();
}

void MainWindow::setThePlot_error(string fileName, string fileName_ex, int gridSize)
{
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

//   ui->customPlot->legend->setVisible(true);

   ui->customPlot->replot();
}



void MainWindow::realtimeDataSlot()
{
  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    double value0 = qSin(key); //sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
    double value1 = qCos(key); //sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, value0);
    ui->customPlot->graph(1)->addData(key, value1);
    // set data of dots:
    ui->customPlot->graph(2)->clearData();
    ui->customPlot->graph(2)->addData(key, value0);
    ui->customPlot->graph(3)->clearData();
    ui->customPlot->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->customPlot->graph(0)->removeDataBefore(key-8);
    ui->customPlot->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->customPlot->graph(0)->rescaleValueAxis();
    ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
  ui->customPlot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

void MainWindow::bracketDataSlot()
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double secs = 0;
#else
  double secs = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif

  // update data to make phase move:
  int n = 500;
  double phase = secs*5;
  double k = 3;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; ++i)
  {
    x[i] = i/(double)(n-1)*34 - 17;
    y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
  }
  ui->customPlot->graph()->setData(x, y);

  itemDemoPhaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);

  ui->customPlot->replot();

  // calculate frames per second:
  double key = secs;
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->count())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

//void MainWindow::setupPlayground(QCustomPlot *customPlot)
//{
//  Q_UNUSED(customPlot)
//}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::screenShot()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#endif
  QString fileName = demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);
  qApp->quit();
}

void MainWindow::allScreenShots()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#endif
  QString fileName = demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);
  qApp->quit();
}
