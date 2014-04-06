#ifndef __MAINWINDOW_CLASS__
#define __MAINWINDOW_CLASS__

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>

#include <iostream>
#include <string>
using namespace std;
#include "./SimulationMainWindow2D.h"
#include "./SimulationMainWindow1D.h"

class QAction;
class QActionGroup;
class QPushButton;
class QLabel;
class QMenu;

class SimulationMainWindow: public QMainWindow{

   Q_OBJECT

public:

   SimulationMainWindow();

private slots:

   void about();
   void goTo1DSimulation();   
   void goTo2DSimulation();   

private:

   void createActions();
   void createMenus();
   void createButtons();

   QMenu *fileMenu;
   QMenu *helpMenu;

   QAction *exitAct;
   QAction *aboutAct;

};

#endif
