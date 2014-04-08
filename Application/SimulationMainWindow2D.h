#ifndef __MAINWINDOW_2D_CLASS__
#define __MAINWINDOW_2D_CLASS__

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QString>

#include <iostream>
#include <string>
using namespace std;
#include "../FieldsDefinition/Field2DClass.h"
#include "../Simulation/Simulation2DClass.h"

class QAction;
class QActionGroup;
class QPushButton;
class QLabel;
class QMenu;

class SimulationMainWindow2D: public QMainWindow{

   Q_OBJECT

public:

   SimulationMainWindow2D();

protected:

   void contextMenuEvent(QContextMenuEvent *event);

private slots:

   void about();
   void aboutQt();

   void runSimulation();
   void pauseSimulation();
   void restartSimulation();
   
private:
   // Simulation attributes    
   int xGridSize;
   int yGridSize;
   int gridSize;
   int simIterator;

   double vx;
   double vy;

   double simulationErr;
   double simulationTime;
   double simulationErrorTolerance;

   Simulation2DClass *simulation;

   string mainSolverName;
   string fluxSolverName;

   bool simIsRunning;
   ///////////

   void createActions();
   void createMenus();
   void createButtons();

   QMenu *fileMenu;
   QMenu *SimulationMenu;
   QMenu *helpMenu;

   QActionGroup *alignmentGroup;
   QAction *exitAct;
   QAction *aboutAct;
   QAction *aboutQtAct;

   QLabel *infoLabel;
   QLabel *infoLabel2;
   QLabel *timeLabel;

   QAction *runAct;
   QAction *pauseAct;
   QAction *restartAct;

};

#endif
