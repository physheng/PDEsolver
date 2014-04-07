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
  
  // Input action
  void setGridSize();
  void setTolerance();
  // Initial Condition
  void fSin();
  // Main Solver
  void laxFriedrichs();
  // Flux Solver
  
  
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
  QMenu *InputMenu;
  QMenu *initialConditionMenu;
  QMenu *fluxSolverMenu;
  QMenu *mainSolverMenu;
  
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
  QAction *gridSizeAct;
  QPushButton *gridSizeButton;
  QAction *toleranceAct;
  QPushButton *toleranceButton;
  
  // Initial Condition
  QAction *fSinAct;
  QPushButton *fSinButton;
  
  // Flux Solver

  // Main Solver
  QAction *laxFriedrichsAct;
  QPushButton *laxFriedrichsButton;
};

#endif
