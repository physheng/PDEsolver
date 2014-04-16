#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "./QCustomPlot/qcustomplot.h" 
#include "MainSolverClass.h"
#include "./FieldsDefinition/Field1DClass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void setThePlot(string fileName, string fileName_ex, int gridSize);
  void setThePlot_error(string fileName, string fileName_ex, int gridSize);

private slots:
  void realtimeDataSlot();
  void bracketDataSlot();
  void screenShot();
  void allScreenShots();
  void clickedGraph(QMouseEvent *event);

private:
  Ui::MainWindow *ui;
  QString demoName;
  QTimer dataTimer;
  QCPItemTracer *itemDemoPhaseTracer;
//  QPoint *p;
  double xPosition, yPosition;
  double *x_hist;
  double *y_hist;
  double *y_ex_hist;

  double xPosition_dis;
  double yPosition_dis;
  double yPosition_ex_dis;
};

#endif // MAINWINDOW_H
