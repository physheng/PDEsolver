#include <algorithm>

#include "Plot2D.h"
#include <QtGui>

using namespace std;

void MyMainWindow::paintEvent(QPaintEvent *)
{
   int R, G, B;
   int i=0,j=0;
   double max_ele, min_ele;
   max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
   min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));
   
   paint= new QPainter;
   paint->begin(this);
   
   image = new QImage(picWidth,picHeight,QImage::Format_ARGB32_Premultiplied);
   QRgb value;
   
   for(i=0;i<picHeight;i++)
   {
      for(j=0;j<picWidth;j++)
      {
         R = (int)((phiMatrix[j+i*picWidth]-min_ele)/(max_ele-min_ele)*255);
         G = 255-R;
         B = abs(128-R);
         value = qRgb(R, G, B);
         image->setPixel(j, i, value);
      }
   }
   
   paint->drawImage(50,50, *image);
   paint->end();
   
}


MyMainWindow::MyMainWindow(QWidget *parent):QWidget(parent)
{
   setGeometry(200,0,1000,1000);
}

bool MyMainWindow::initialCondition(int width, int height)
{
   picWidth = width;
   picHeight = height;
   return true;
}

void MyMainWindow::showResult(double Phi[])
{
   phiMatrix = Phi;
}


