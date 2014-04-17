#ifndef __MAINWINDOW_1D_CLASS__
#define __MAINWINDOW_1D_CLASS__

#include <QApplication>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QTimer>

#include <iostream>
#include <string>
using namespace std;
#include "../FieldsDefinition/Field1DClass.h"
#include "../Simulation/Simulation1DClass.h"
#include "./QCustomPlot/qcustomplot.h"
#include "./Plot1D.h"

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
   void delay();

private slots:

   void about();
   void aboutQt();

   void runSimulation();
   void pauseSimulation();
   void restartSimulation();
   
   // Input actions for setting the gridSize and error Tolerance
   void setRealizationTimeStep();
   void setTolerance();
   void setGridSize();
   void setDelaySec();

   // Initial Condition (string)
   void setICSin();
   void setICStep();
   void setICRndNoise();

   // Setting Main Solver (string)
   void setRK4Scheme();
   void setMacCormackScheme();
   void setForwardEulerScheme();
   void setLaxFriedrichsScheme();
   void setKurganovTadmor2000Scheme();
   void setRK4KurganovTadmor2000Scheme();
   void setKurganovTadmor2ndOrder2000Scheme();

   // Setting Flux Solver (string)
   void setMUSCLSScheme();
   void setLinearReconstructionScheme();
   void setPiecewiseParabolicReconstructionScheme();
  
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
   string initialConditionName;

   bool simIsRunning;

   double delaySecond;
   int realizationTimeStep;
   ///////////

   void createActions();
   void createMenus();
   void createButtons();

   QMenu *fileMenu;
   QMenu *helpMenu;
   QMenu *SimulationMenu;

   QMenu *InputMenu;
   QMenu *initialConditionMenu;
   QMenu *fluxSolverMenu;
   QMenu *mainSolverMenu;
  
   QActionGroup *solverGroup;
   QActionGroup *fluxGroup;
   QActionGroup *icGroup;

   QAction *exitAct;
   QAction *aboutAct;
   QAction *aboutQtAct;

   QLabel *infoLabel;
   QLabel *infoLabel2;
   QLabel *timeLabel;

   QAction *runAct;
   QAction *pauseAct;
   QAction *restartAct;

   // Input Parameters
   QAction *gridSizeAct;
   QAction *toleranceAct;
   QAction *delaySecAct;
   QAction *realizationTimeStepAct;
    
   // Initial Condition
   QAction *setICSinAct;
   QAction *setICStepAct;
   QAction *setICRndNoiseAct;
  
   // Flux Solver
   QAction *setMUSCLSAct;
   QAction *setLinearReconstructionAct;
   QAction *setPiecewiseParabolicReconstructionAct;

   // Main Solver
   QAction *setRK4Act;
   QAction *setMacCormackAct;
   QAction *setForwardEulerAct;
   QAction *setLaxFriedrichsAct;
   QAction *setKurganovTadmor2000Act;
   QAction *setRK4KurganovTadmor2000Act;
   QAction *setKurganovTadmor2ndOrder2000Act;

   // For plotting (plotting windows)
   Plot1D *pwSimulation;
   Plot1D *pwError;

};

#endif
