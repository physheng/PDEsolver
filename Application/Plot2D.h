#ifndef _PLOT2D_CLASS_
#define _PLOT2D_CLASS_

#include <QApplication>
#include <QWidget>
#include <QPainter>

using namespace std;

class MyMainWindow:public QWidget
{

public:
  MyMainWindow(QWidget *parent = 0);
  bool initialCondition(int width, int height);
  void showResult(double* Phi);
  
  
private:
  int picWidth, picHeight;
  double* phiMatrix;
  QImage *image;
  QPainter *paint;
  void paintEvent(QPaintEvent *);
 
};
#endif