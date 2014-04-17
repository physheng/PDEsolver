#ifndef _PLOT2DWINDOW_CLASS_
#define _PLOT2DWINDOW_CLASS_

#include <QMainWindow>
#include "./QCustomPlot/qcustomplot.h"

#include <QApplication>
#include <QWidget>
#include <QPainter>

namespace Ui {
  class Plot2DWindow;
}

class Plot2DWindow:public QMainWindow
{
   Q_OBJECT
   
   public:
      explicit Plot2DWindow(QWidget *parent = 0);
      bool initialCondition(int width, int height);
      void showResult(double* Phi);
      void showError(double* ExactPhi, double* NumericalPhi);
      ~Plot2DWindow();
   
   private:
  Ui::Plot2DWindow *ui;
      int picWidth, picHeight;
      double* phiMatrix;
      QImage *image;
      QPainter *paint;
      void paintEvent(QPaintEvent *);
  double max_ele, min_ele;
   
};
#endif