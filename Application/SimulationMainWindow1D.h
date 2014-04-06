#ifndef __MAINWINDOW_1D_CLASS__
#define __MAINWINDOW_1D_CLASS__

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QString>

#include <iostream>
#include <string>
using namespace std;
#include "../FieldsDefinition/Field1DClass.h"
#include "../Simulation/Simulation1DClass.h"

class QAction;
class QActionGroup;
class QPushButton;
class QLabel;
class QMenu;

class SimulationMainWindow1D: public QMainWindow{

   Q_OBJECT

public:

   SimulationMainWindow1D();

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
   int gridSize;
   int simIterator;

   double simulationErr;
   double simulationTime;
   double simulationErrorTolerance;

   Simulation1DClass *simulation;

   string mainSolverName;
   string fluxSolverName;

   bool simIsRunning;
   ///////////

   void createActions();
   void createMenus();
   void createButtons();

   QMenu *fileMenu;
   QMenu *editMenu;
   QMenu *formatMenu;
   QMenu *helpMenu;
   QMenu *SimulationMenu;

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
