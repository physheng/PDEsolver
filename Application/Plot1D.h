#ifndef PLOT1D_CLASS_
#define PLOT1D_CLASS_

#include <QMainWindow>
#include <QTimer>
#include "./QCustomPlot/qcustomplot.h" 
#include "MainSolverClass.h"
#include "./FieldsDefinition/Field1DClass.h"
#include "Plot1D.h"

namespace Ui {
class MainWindow;
}

class Plot1D : public QMainWindow
{
  Q_OBJECT

public:
  explicit Plot1D(QWidget *parent = 0);
  ~Plot1D();
  
  void setThePlot(string fileName, string fileName_ex, int gridSize);
  void setThePlot_error(string fileName, string fileName_ex, int gridSize);

private slots:
  void clickedGraph(QMouseEvent *event);

private:
  Ui::MainWindow *ui;
  QString demoName;
  QTimer dataTimer;
  QCPItemTracer *itemDemoPhaseTracer;

  double xPosition, yPosition;
  double *x_hist;
  double *y_hist;
  double *y_ex_hist;

  double xPosition_dis;
  double yPosition_dis;
  double yPosition_ex_dis;
};

#endif // PLOT1D_CLASS_
