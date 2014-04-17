#include <QtGui>
#include "SimulationMainWindow1D.h"

SimulationMainWindow1D::SimulationMainWindow1D(){

   menuBar()->setNativeMenuBar(false);
   QWidget *widget = new QWidget;
   setCentralWidget(widget);
  
   QWidget *topFiller = new QWidget;
   topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
   infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                            "invoke a context menu</i>"));
   infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
   infoLabel->setAlignment(Qt::AlignCenter);
  
   infoLabel2 = new QLabel(tr("<i>Simulation Status: "
                             "Field is not initialized</i>"));
   infoLabel2->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
   infoLabel2->setAlignment(Qt::AlignBottom);
  
   timeLabel = new QLabel(tr("Time : "));
   QString timeLabelString = tr("Time : ") + QString::number(simulationTime)
         + tr("   Error : ") + QString::number(simulationErr) ;
   timeLabel->setText(timeLabelString);
  
   QWidget *bottomFiller = new QWidget;
   bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
   QVBoxLayout *layout = new QVBoxLayout;
  
   layout->setMargin(5);
   layout->addWidget(topFiller);
   layout->addWidget(infoLabel);
   layout->addWidget(infoLabel2);
   layout->addWidget(timeLabel);
   layout->addWidget(bottomFiller);
   widget->setLayout(layout);
  
   createActions();
   createMenus();
   createButtons();
  
   QString message = tr("A context menu is available by right-clicking");
   statusBar()->showMessage(message);
  
   setWindowTitle(tr("PDE simulation"));
   setMinimumSize(480, 320);
   resize(720, 480);
  
   // Default Values
   gridSize = 100;
   delaySecond = 0.5;
   realizationTimeStep = 10;

   initialConditionName = "Sin";
  
   mainSolverName = "RK4";
   fluxSolverName = "LinearReconstruction";

   simulationErrorTolerance = 1e-1;
  
   // Plotting windows
   pwSimulation = new Plot1D(this);
   pwError = new Plot1D(this);

   simulation = new Simulation1DClass;
   restartSimulation();
  
}

void SimulationMainWindow1D::contextMenuEvent(QContextMenuEvent *event){
   QMenu menu(this);
   //menu.addAction(cutAct);
   //menu.addAction(copyAct);
   //menu.addAction(pasteAct);
   menu.exec(event->globalPos());
}

void SimulationMainWindow1D::runSimulation(){
  
   simIsRunning = true;
   simulationTime = simulation->getActualTime();
   simulationErr  = simulation->calcErrorNorm();
  
   QString timeLabelString = tr("Time : ") + QString::number(simulationTime)
                      + tr("   Error : ") + QString::number(simulationErr) ;
  
   QString saveFileDir       = tr("./output/snapshots/");
   QString saveFileNameField = tr("_Snapshot.txt");
   QString saveFileNameExact = tr("_Ex_Snapshot.txt");
   QString fileName, fileName_ex;
   string fname;
  
   while ( simIsRunning && simulationErr < simulationErrorTolerance ){
      simulation->runSimulationOneTimeStep();
      simIterator++;

      QApplication::processEvents();

      if ( simIterator%realizationTimeStep == 0 ){

         simulationTime = simulation->getActualTime();
         simulationErr  = simulation->calcErrorNorm();

         timeLabelString = tr("Time : ") + QString::number(simulationTime)
                    + tr("   Error : ") + QString::number(simulationErr);
         timeLabel->setText(timeLabelString);

         // Saving data into file
         fileName = saveFileDir 
                     + QString::number(simIterator/realizationTimeStep)
                     + saveFileNameField ;
         simulation->saveSnapShot(fileName.toStdString());

         // Saving exact solution into file
         fileName_ex = saveFileDir 
                    + QString::number(simIterator/realizationTimeStep)
                    + saveFileNameExact ;
         simulation->saveSnapShotExactSolution(fileName_ex.toStdString());

         pwSimulation->setThePlot(fileName.toStdString(),fileName_ex.toStdString(),gridSize);
         pwSimulation->show();
         pwError->setThePlot_error(fileName.toStdString(),fileName_ex.toStdString(),gridSize);
         pwError->show();
         delay();

	  }
	  
   }
  
   simulationTime = simulation->getActualTime();
   simulationErr  = simulation->calcErrorNorm();
  
   timeLabelString = tr("Time : ") + QString::number(simulationTime)
                     + tr("   Error : ") + QString::number(simulationErr);
   timeLabel->setText(timeLabelString);

}

void SimulationMainWindow1D::pauseSimulation(){
   simIsRunning = false;
   infoLabel->setText(tr("Simulation is Paused."));
}

void SimulationMainWindow1D::restartSimulation(){

   pwSimulation->close();
   pwError->close();

   simIterator    = 0;
   simulationTime = 0.0;
   simulationErr  = 0.0;
   simIsRunning   = false;
  
   infoLabel->setText(tr("Simulation is restarted."));
   QString timeLabelString = tr("Time : ") + QString::number(simulationTime)
                      + tr("   Error : ") + QString::number(simulationErr);
   timeLabel->setText(timeLabelString);
  
   simulation->initialize(gridSize, initialConditionName);
  
   simulation->setupSimulation(mainSolverName, fluxSolverName);
  
   simulation->saveSnapShot("./output/snapshots/IC_Snapshot.txt");
  
   QString infoLabel2String = tr("Main Solver Scheme: ")
                              + QString::fromStdString(mainSolverName) 
                              + tr(" - Flux Solver Scheme: ")
                              + QString::fromStdString(fluxSolverName)
                              + tr(" - Grid Size: ")
                              + QString::number(gridSize);
 
   infoLabel2->setText(infoLabel2String);

}

void SimulationMainWindow1D::about(){
   infoLabel->setText(tr("Invoked <b>Help|About</b>"));
   QMessageBox::about(this, tr("About Menu"),
                     tr("The <b>Menu</b> example shows how to create "
                        "menu-bar menus and context menus."));
}

void SimulationMainWindow1D::aboutQt(){
   infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void SimulationMainWindow1D::createActions(){
  
   exitAct = new QAction(tr("E&xit"), this);
   exitAct->setShortcuts(QKeySequence::Quit);
   exitAct->setStatusTip(tr("Exit the application"));
   connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
  
   aboutAct = new QAction(tr("&About"), this);
   aboutAct->setStatusTip(tr("Show the application's About box"));
   connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
  
   aboutQtAct = new QAction(tr("About &Qt"), this);
   aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
   connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
   connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

   // Simulation menu actions 
   runAct = new QAction(tr("&Run"), this);
   runAct->setShortcut(tr("Ctrl+Alt+R"));
   runAct->setStatusTip(tr("Running the simulation"));
   connect(runAct, SIGNAL(triggered()), this, SLOT(runSimulation()));
  
   pauseAct = new QAction(tr("&Pause"), this);
   pauseAct->setShortcut(tr("Ctrl+Alt+P"));
   pauseAct->setStatusTip(tr("Pause the simulation"));
   connect(pauseAct, SIGNAL(triggered()), this, SLOT(pauseSimulation()));
  
   restartAct = new QAction(tr("&Restart"), this);
   restartAct->setShortcut(tr("Ctrl+Alt+N"));
   restartAct->setStatusTip(tr("Restart the simulation"));
   connect(restartAct, SIGNAL(triggered()), this, SLOT(restartSimulation()));
  
   // Input manu actions
   gridSizeAct = new QAction(tr("&Grid Size"), this);
   connect(gridSizeAct, SIGNAL(triggered()), this, SLOT(setGridSize()));
  
   toleranceAct = new QAction(tr("&Error Tolerance"), this);
   connect(toleranceAct, SIGNAL(triggered()), this, SLOT(setTolerance()));

   delaySecAct = new QAction(tr("&Animation Delay"), this);
   connect(delaySecAct, SIGNAL(triggered()), this, SLOT(setDelaySec()));
  
   realizationTimeStepAct = new QAction(tr("&Realization Time Step"), this);
   connect(realizationTimeStepAct, SIGNAL(triggered()),
           this, SLOT(setRealizationTimeStep()));
  
   // Setting the initial condition
   setICSinAct = new QAction(tr("&Sin"), this);
   setICSinAct->setCheckable(true);
   connect(setICSinAct, SIGNAL(triggered()), this, SLOT(setICSin()));

   setICStepAct = new QAction(tr("&Step"), this);
   setICStepAct->setCheckable(true);
   connect(setICStepAct, SIGNAL(triggered()), this, SLOT(setICStep()));

   setICRndNoiseAct = new QAction(tr("&Random Noise"), this);
   setICRndNoiseAct->setCheckable(true);
   connect(setICRndNoiseAct, SIGNAL(triggered()), this, SLOT(setICRndNoise()));

   icGroup = new QActionGroup(this);
   icGroup->addAction(setICSinAct);
   icGroup->addAction(setICStepAct);
   icGroup->addAction(setICRndNoiseAct);
   setICSinAct->setChecked(true);
  
   // Setting main solver
   setLaxFriedrichsAct = new QAction(tr("Lax-FriedRichs Scheme"), this);
   setLaxFriedrichsAct->setCheckable(true);
   connect(setLaxFriedrichsAct, SIGNAL(triggered()), this,
            SLOT(setLaxFriedrichsScheme()));

   setRK4Act = new QAction(tr("RK4 Scheme"), this);
   setRK4Act->setCheckable(true);
   connect(setRK4Act, SIGNAL(triggered()), this,SLOT(setRK4Scheme()));

   setMacCormackAct = new QAction(tr("MacCormack Scheme"), this);
   setMacCormackAct->setCheckable(true);
   connect(setMacCormackAct, SIGNAL(triggered()), this,
            SLOT(setMacCormackScheme()));

   setForwardEulerAct = new QAction(tr("Forward Euler Scheme"), this);
   setForwardEulerAct->setCheckable(true);
   connect(setForwardEulerAct, SIGNAL(triggered()), this,
            SLOT(setForwardEulerScheme()));
  
   setKurganovTadmor2000Act = new QAction(tr("Kurganov-Tadmor Scheme"), this);
   setKurganovTadmor2000Act->setCheckable(true);
   connect(setKurganovTadmor2000Act, SIGNAL(triggered()), this,
            SLOT(setKurganovTadmor2000Scheme()));

   setRK4KurganovTadmor2000Act = 
           new QAction(tr("RK4 Kurganov-Tadmor Scheme"), this);
   setRK4KurganovTadmor2000Act->setCheckable(true);
   connect(setRK4KurganovTadmor2000Act, SIGNAL(triggered()), this,
            SLOT(setRK4KurganovTadmor2000Scheme()));

   setKurganovTadmor2ndOrder2000Act = 
           new QAction(tr("2nd Order Kurganov-Tadmor Scheme"), this);
   setKurganovTadmor2ndOrder2000Act->setCheckable(true);
   connect(setKurganovTadmor2ndOrder2000Act, SIGNAL(triggered()), this,
            SLOT(setKurganovTadmor2ndOrder2000Scheme()));
 
   solverGroup = new QActionGroup(this);
   solverGroup->addAction(setMacCormackAct);
   solverGroup->addAction(setForwardEulerAct);
   solverGroup->addAction(setLaxFriedrichsAct);
   solverGroup->addAction(setKurganovTadmor2000Act);
   solverGroup->addAction(setRK4KurganovTadmor2000Act);
   solverGroup->addAction(setKurganovTadmor2ndOrder2000Act);
   solverGroup->addAction(setRK4Act);
   setRK4Act->setChecked(true);
 
   // Setting flux solver
   setMUSCLSAct = new QAction(tr("MUSCL Scheme"), this);
   setMUSCLSAct->setCheckable(true);
   connect(setMUSCLSAct, SIGNAL(triggered()), this, SLOT(setMUSCLSScheme()));

   setLinearReconstructionAct = 
             new QAction(tr("Linear Reconstruction Scheme"), this);
   setLinearReconstructionAct->setCheckable(true);
   connect(setLinearReconstructionAct, SIGNAL(triggered()), this,
             SLOT(setLinearReconstructionScheme()));

   setPiecewiseParabolicReconstructionAct = 
             new QAction(tr("Piecewise Parabolic Reconstruction Scheme"), this);
   setPiecewiseParabolicReconstructionAct->setCheckable(true);
   connect(setPiecewiseParabolicReconstructionAct, SIGNAL(triggered()), this,
             SLOT(setPiecewiseParabolicReconstructionScheme()));

   fluxGroup = new QActionGroup(this);
   fluxGroup->addAction(setMUSCLSAct);
   fluxGroup->addAction(setPiecewiseParabolicReconstructionAct);
   fluxGroup->addAction(setLinearReconstructionAct);
   setLinearReconstructionAct->setChecked(true);
 
}

void SimulationMainWindow1D::createMenus(){
	
   fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addSeparator();
   fileMenu->addAction(exitAct);
  
   SimulationMenu = menuBar()->addMenu(tr("&Simulation"));
   SimulationMenu->addAction(runAct);
   SimulationMenu->addAction(pauseAct);
   SimulationMenu->addAction(restartAct);
  
   InputMenu = menuBar()->addMenu(tr("&Input"));
   InputMenu->addAction(gridSizeAct);
   InputMenu->addAction(toleranceAct);
   InputMenu->addAction(delaySecAct);
   InputMenu->addAction(realizationTimeStepAct);
   
   initialConditionMenu = InputMenu->addMenu(tr("&Initial Condition"));
   initialConditionMenu->addAction(setICSinAct);
   initialConditionMenu->addAction(setICStepAct);
   initialConditionMenu->addAction(setICRndNoiseAct);

   fluxSolverMenu = InputMenu->addMenu(tr("&Flux Solver"));
   fluxSolverMenu->addSeparator()->setText(tr("Alignment"));
   fluxSolverMenu->addAction(setMUSCLSAct);
   fluxSolverMenu->addAction(setLinearReconstructionAct);
   fluxSolverMenu->addAction(setPiecewiseParabolicReconstructionAct);
   fluxSolverMenu->addSeparator();
 
   
   mainSolverMenu = InputMenu->addMenu(tr("&Main Solver"));
   mainSolverMenu->addAction(setRK4Act);
   mainSolverMenu->addAction(setMacCormackAct);
   mainSolverMenu->addAction(setForwardEulerAct);
   mainSolverMenu->addAction(setLaxFriedrichsAct);
   mainSolverMenu->addAction(setKurganovTadmor2000Act);
   mainSolverMenu->addAction(setRK4KurganovTadmor2000Act);
   mainSolverMenu->addAction(setKurganovTadmor2ndOrder2000Act);

   helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(aboutAct);
   helpMenu->addAction(aboutQtAct);
  
}


void SimulationMainWindow1D::createButtons(){
  
   QPushButton *runButton = new QPushButton("&Run", this);
   runButton->setGeometry(QRect(QPoint(10, 40), QSize(80, 30)));
   connect(runButton, SIGNAL(released()), this, SLOT(runSimulation()));
  
   QPushButton *pauseButton = new QPushButton("&Pause", this);
   pauseButton->setGeometry(QRect(QPoint(10, 80), QSize(80, 30)));
   connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseSimulation()));
  
   QPushButton *restartButton = new QPushButton("&Restart", this);
   restartButton->setGeometry(QRect(QPoint(10, 120), QSize(80, 30)));
   connect(restartButton, SIGNAL(clicked()), this, SLOT(restartSimulation()));

}

void SimulationMainWindow1D::setGridSize(){
   bool ok;
   int gridSizeInput = QInputDialog::getInt(this, tr("Get Grid Size"),
                               tr("Grid Size:"), 100, 10, 200000, 100, &ok);
   if ( ok ){
      gridSize = gridSizeInput;
      restartSimulation();
   }
}

void SimulationMainWindow1D::setTolerance(){
   bool ok;
   double errorToleranceInput = 
               QInputDialog::getDouble(this, tr("Get Error Tolerance"),
                       tr("Error Tolerance:"), 0.1, 0.0001, 10, 4, &ok);
   if ( ok ){
      simulationErrorTolerance = errorToleranceInput;
   }
}

void SimulationMainWindow1D::setDelaySec(){
   bool ok;
   double delaySecondInput = 
               QInputDialog::getDouble(this, tr("Get Animation Delay Time"),
                       tr("Delay (in second):"), 0.5, 0.1, 10, 2, &ok);
   if ( ok ){
      delaySecond = delaySecondInput;
   }
}

void SimulationMainWindow1D::setRealizationTimeStep(){
   bool ok;
   int inputVal = QInputDialog::getInt(this, tr("Get Grid Size"),
                               tr("Grid Size:"), 10, 1, 2000, 10, &ok);
   if ( ok ){
         realizationTimeStep = inputVal;
      restartSimulation();
   }
}


// Setting the initial condition
void SimulationMainWindow1D::setICSin(){
   initialConditionName =  "Sin";
   restartSimulation();
}

void SimulationMainWindow1D::setICStep(){
   initialConditionName =  "Step";
   restartSimulation();
}

void SimulationMainWindow1D::setICRndNoise(){
   initialConditionName =  "RndNoise";
   restartSimulation();
}

// Setting the main solver
void SimulationMainWindow1D::setLaxFriedrichsScheme(){
   mainSolverName =  "LaxFriedrichs";
   restartSimulation();
}

void SimulationMainWindow1D::setRK4Scheme(){
   mainSolverName =  "RK4";
   restartSimulation();
}

void SimulationMainWindow1D::setMacCormackScheme(){
   mainSolverName =  "MacCormack";
   restartSimulation();
}

void SimulationMainWindow1D::setRK4KurganovTadmor2000Scheme(){
   mainSolverName =  "RK4KurganovTadmor2000";
   restartSimulation();
}

void SimulationMainWindow1D::setKurganovTadmor2ndOrder2000Scheme(){
   mainSolverName =  "KurganovTadmor2ndOrder2000";
   restartSimulation();
}

void SimulationMainWindow1D::setKurganovTadmor2000Scheme(){
   mainSolverName =  "KurganovTadmor2000";
   restartSimulation();
}

void SimulationMainWindow1D::setForwardEulerScheme(){
   mainSolverName =  "ForwardEuler";
   restartSimulation();
}

// Setting the flux solver
void SimulationMainWindow1D::setMUSCLSScheme(){
   fluxSolverName =  "MUSCLS";
   restartSimulation();
}

void SimulationMainWindow1D::setLinearReconstructionScheme(){
   fluxSolverName =  "LinearReconstruction";
   restartSimulation();
}

void SimulationMainWindow1D::setPiecewiseParabolicReconstructionScheme(){
   fluxSolverName =  "PiecewiseParabolicReconstruction";
   restartSimulation();
}

// Delay function
void SimulationMainWindow1D::delay(){
   QTime dieTime= QTime::currentTime().addMSecs(1000.0*delaySecond);
   while( QTime::currentTime() < dieTime ){
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
   }
}
