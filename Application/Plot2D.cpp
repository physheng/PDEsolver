#include <algorithm>

#include "Plot2D.h"
#include "ui_Plot2DWindow.h"
#include <QtGui>
#include <iostream>

using namespace std;

Plot2DWindow::Plot2DWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::Plot2DWindow)
{
   ui->setupUi(this);
   paint = new QPainter;
}

Plot2DWindow::~Plot2DWindow()
{
   delete phiMatrix;
   delete image;
   delete paint;
   delete ui;
   cout << "Freeing mem" << endl;
}

void Plot2DWindow::paintEvent(QPaintEvent *)
{
   int R, G, B;
   int i = 0,j = 0;
   //double max_ele, min_ele;
   // Get min and max value from the Phi Matrix
   //max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
   //min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));
   paint = new QPainter(this);
   //paint = new QPainter;
   paint->begin(this);
   
   // Set Image width, height and color to RGB2555
   image = new QImage(picWidth,picHeight,QImage::Format_ARGB32_Premultiplied);
   QRgb value;
   
   for(i=0;i<picHeight;i++)
   {
      for(j=0;j<picWidth;j++)
      {
         R = (int)(((phiMatrix[j+i*picWidth]-min_ele)/(max_ele-min_ele)*255));
    
         G = 255 - R;
         B = abs(128 - R);
         value = qRgb(R, G, B);
         image->setPixel(j, i, value);
      }
   }
   //image->scaled(200,200, Qt::IgnoreAspectRatio);
   paint->drawImage(50,50, *image);
   paint->end();
   
}

bool Plot2DWindow::initialCondition(int width, int height)
{
   picWidth = width;
   picHeight = height;
  cout << width << " " << height << endl;
   return true;
}

void Plot2DWindow::showResult(double *Phi)
{
   phiMatrix = Phi;
   max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
   min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));
   cout << max_ele << " " << min_ele << endl;

}

void Plot2DWindow::showError(double* ExactPhi, double* NumericalPhi)
{
  double *tempMatrix = new double[picHeight*picWidth];
  for(int i=0;i<picHeight;i++)
  {
    for(int j=0;j<picWidth;j++)
    {
      tempMatrix[j+i*picWidth] = (ExactPhi[j+i*picWidth] - NumericalPhi[j+i*picWidth]);
      //cout << tempMatrix[j+i*picWidth] << endl;
    }
  }

  phiMatrix = tempMatrix;
  //max_ele = *(std::max_element(phiMatrix, phiMatrix+picWidth*picHeight));
  //min_ele = *(std::min_element(phiMatrix, phiMatrix+picWidth*picHeight));
  //delete tempMatrix;
}

