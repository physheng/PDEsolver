#ifndef __MAINWINDOW_2D_CLASS__
#define __MAINWINDOW_2D_CLASS__

#include <QApplication>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QTimer>

#include <iostream>
#include <string>
using namespace std;
#include "../FieldsDefinition/Field2DClass.h"
#include "../Simulation/Simulation2DClass.h"
#include "./Plot2D.h"

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
   void delay();

private slots:

   void about();
   void aboutQt();
   void setFilePath();

   // Simulation modules
   void runSimulation();
   void pauseSimulation();
   void restartSimulation();

   // Input actions for setting the input parameters
   void setRealizationTimeStep();
   void setTolerance();
   void setDelaySec();
   void setVelocityX();
   void setVelocityY();

   // Setting the main (string)
   void setRK4Scheme();
   void setForwardEulerScheme();
   void setLaxFriedrichsScheme();

   // Setting Flux Solver (string)
   void setLinearReconstructionScheme();
    
private:

   // 2D plot file path
   QString filePath;

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

   double delaySecond;
   int realizationTimeStep;
   ///////////

   void createActions();
   void createMenus();
   void createButtons();

   QMenu *fileMenu;
   QMenu *SimulationMenu;
   QMenu *helpMenu;

   QMenu *InputMenu;
   QMenu *initialConditionMenu;
   QMenu *fluxSolverMenu;
   QMenu *mainSolverMenu;

   QActionGroup *solverGroup;
   QActionGroup *fluxGroup;
   QActionGroup *initialConditionGroup;

   QAction *exitAct;
   QAction *aboutAct;
   QAction *aboutQtAct;
   QAction *filePathAct;

   QLabel *infoLabel;
   QLabel *infoLabel2;
   QLabel *timeLabel;
   QLabel *picLabel; 

   QAction *runAct;
   QAction *pauseAct;
   QAction *restartAct;

   // Input Parameters
   QAction *toleranceAct;
   QAction *delaySecAct;
   QAction *velocityXAct;
   QAction *velocityYAct;
   QAction *realizationTimeStepAct;

   // Flux Solver
   QAction *setLinearReconstructionAct;

   // Main Solver
   QAction *setRK4Act;
   QAction *setForwardEulerAct;
   QAction *setLaxFriedrichsAct;

  Plot2DWindow *picture2D;
  Plot2DWindow *exactPicture2D;

 };


#endif
