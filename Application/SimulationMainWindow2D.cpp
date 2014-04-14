#include <QtGui>

#include "SimulationMainWindow2D.h"

SimulationMainWindow2D::SimulationMainWindow2D(){
	
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

   // choose a picture from file
   picLabel = new QLabel;
   // To do: member function to get filename
   filePath = tr("./dog.ppm");
   pixmap.load(filePath);
   picLabel->setPixmap(pixmap);   

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

   // Default values
   xGridSize = 200;
   yGridSize = 400;

   delaySecond = 0.5;

   gridSize  = xGridSize * yGridSize;

   vx = 1.0;
   vy = 1.0;

   mainSolverName = "RK4";
   fluxSolverName = "LinearReconstruction";

   simulationErrorTolerance = 1e-2;

   simulation = new Simulation2DClass;
   restartSimulation();
   
}

void SimulationMainWindow2D::contextMenuEvent(QContextMenuEvent *event){
   QMenu menu(this);
   //menu.addAction(cutAct);
   //menu.addAction(copyAct);
   //menu.addAction(pasteAct);
   menu.exec(event->globalPos());
}


void SimulationMainWindow2D::runSimulation(){

   simIsRunning = true;   
   simulationTime = simulation->getActualTime();
   simulationErr  = simulation->calcErrorNorm();

   QString timeLabelString = tr("Time : ") + QString::number(simulationTime)
                     + tr("   Error : ") + QString::number(simulationErr) ; 	

   QString saveFileDir       = tr("./output/snapshots/");
   QString saveFileNameField = tr("_Snapshot.txt");
   QString saveFileNameExact = tr("_Ex_Snapshot.txt");
   QString fileName;
   string fname;

   while ( simIsRunning && simulationErr < simulationErrorTolerance ){

      simulation->runSimulationOneTimeStep();
      simIterator++;

      QApplication::processEvents();

      if ( simIterator%50 == 0 ){

         simulationTime = simulation->getActualTime();
         simulationErr  = simulation->calcErrorNorm();

         timeLabelString = tr("Time : ") + QString::number(simulationTime)
                   + tr("   Error : ") + QString::number(simulationErr); 	
         timeLabel->setText(timeLabelString);

         // Saving data into file
         fileName = saveFileDir + QString::number(simIterator/50)
                    + saveFileNameField ;
         simulation->saveSnapShot(fileName.toStdString());

         // Saving exact solution into file
         fileName = saveFileDir + QString::number(simIterator/50)
                    + saveFileNameExact ;
         simulation->saveSnapShotExactSolution(fileName.toStdString());

     }
	  
   }

   simulationTime = simulation->getActualTime();
   simulationErr  = simulation->calcErrorNorm();

   timeLabelString = tr("Time : ") + QString::number(simulationTime)
                   + tr("   Error : ") + QString::number(simulationErr); 	
   timeLabel->setText(timeLabelString);

}

void SimulationMainWindow2D::pauseSimulation(){
   simIsRunning = false;
   infoLabel->setText(tr("Simulation is Paused."));
}

void SimulationMainWindow2D::restartSimulation(){

   simIterator    = 0;
   simulationTime = 0.0;
   simulationErr  = 0.0;
   simIsRunning   = false;

   infoLabel->setText(tr("Simulation is restarted and ready to run."));

   QString timeLabelString = tr("Time : ") + QString::number(simulationTime)
                   + tr("   Error : ") + QString::number(simulationErr) ; 	
   timeLabel->setText(timeLabelString);	

   simulation->initialize(xGridSize, yGridSize, vx, vy);

   simulation->setupSimulation(mainSolverName, fluxSolverName);

   simulation->saveSnapShot("./output/snapshots/IC_Snapshot.txt");

   QString infoLabel2String = tr("Main Solver Scheme: ")
                   + QString::fromStdString(mainSolverName)
                   + tr(" - X Grid Size: ")
                   + QString::number(xGridSize) 
                   + tr(" - Y Grid Size: ")
                   + QString::number(yGridSize); 	
   infoLabel2->setText(infoLabel2String);

}

void SimulationMainWindow2D::about(){	
   infoLabel->setText(tr("Invoked <b>Help|About</b>"));
   QMessageBox::about(this, tr("About Menu"),
             tr("The <b>Menu</b> example shows how to create "
                "menu-bar menus and context menus."));
}

void SimulationMainWindow2D::aboutQt(){
   infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void SimulationMainWindow2D::createActions(){

   filePathAct = new QAction(tr("&File Path"),this);
   filePathAct->setShortcut(tr("Ctrl+O"));
   connect(filePathAct, SIGNAL(triggered()), this, SLOT(setFilePath()));
   

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

   // Simulation actions
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

   // Input actinos  
   toleranceAct = new QAction(tr("&Error Tolerance"), this);
   connect(toleranceAct, SIGNAL(triggered()), this, SLOT(setTolerance()));

   delaySecAct = new QAction(tr("&Animation Delay"), this);
   connect(delaySecAct, SIGNAL(triggered()), this, SLOT(setDelaySec()));

   // Setting the initial condition
  
   // Setting main solver
   setLaxFriedrichsAct = new QAction(tr("Lax-FriedRichs Scheme"), this);
   setLaxFriedrichsAct->setCheckable(true);
   connect(setLaxFriedrichsAct, SIGNAL(triggered()), this,
            SLOT(setLaxFriedrichsScheme()));

   setRK4Act = new QAction(tr("RK4 Scheme"), this);
   setRK4Act->setCheckable(true);
   connect(setRK4Act, SIGNAL(triggered()), this,SLOT(setRK4Scheme()));

   setForwardEulerAct = new QAction(tr("Forward Euler Scheme"), this);
   setForwardEulerAct->setCheckable(true);
   connect(setForwardEulerAct, SIGNAL(triggered()), this,
            SLOT(setForwardEulerScheme()));
   
   solverGroup = new QActionGroup(this);
   solverGroup->addAction(setForwardEulerAct);
   solverGroup->addAction(setLaxFriedrichsAct);
   solverGroup->addAction(setRK4Act);
   setRK4Act->setChecked(true);
 
   // Setting flux solver
   setLinearReconstructionAct = 
             new QAction(tr("Linear Reconstruction Scheme"), this);
   setLinearReconstructionAct->setCheckable(true);
   connect(setLinearReconstructionAct, SIGNAL(triggered()), this,
             SLOT(setLinearReconstructionScheme()));

   fluxGroup = new QActionGroup(this);
   fluxGroup->addAction(setLinearReconstructionAct);
   setLinearReconstructionAct->setChecked(true);

}

void SimulationMainWindow2D::createMenus(){
	
   fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addSeparator();
   fileMenu->addAction(filePathAct);
   fileMenu->addAction(exitAct);

   SimulationMenu = menuBar()->addMenu(tr("&Simulation"));
   SimulationMenu->addAction(runAct);
   SimulationMenu->addAction(pauseAct);
   SimulationMenu->addAction(restartAct);

   InputMenu = menuBar()->addMenu(tr("&Input"));
   InputMenu->addAction(toleranceAct);
   InputMenu->addAction(delaySecAct);
   
   fluxSolverMenu = InputMenu->addMenu(tr("&Flux Solver"));
   fluxSolverMenu->addSeparator()->setText(tr("Alignment"));
   fluxSolverMenu->addAction(setLinearReconstructionAct);
   fluxSolverMenu->addSeparator();
 
   mainSolverMenu = InputMenu->addMenu(tr("&Main Solver"));
   mainSolverMenu->addAction(setRK4Act);
   mainSolverMenu->addAction(setForwardEulerAct);
   mainSolverMenu->addAction(setLaxFriedrichsAct);

   helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(aboutAct);
   helpMenu->addAction(aboutQtAct);

}


void SimulationMainWindow2D::createButtons(){

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


// Setting the main solver
void SimulationMainWindow2D::setLaxFriedrichsScheme(){
   mainSolverName =  "LaxFriedrichs";
   restartSimulation();
}

void SimulationMainWindow2D::setRK4Scheme(){
   mainSolverName =  "RK4";
   restartSimulation();
}

void SimulationMainWindow2D::setForwardEulerScheme(){
   mainSolverName =  "ForwardEuler";
   restartSimulation();
}


// Setting the flux solver
void SimulationMainWindow2D::setLinearReconstructionScheme(){
   fluxSolverName =  "LinearReconstruction";
   restartSimulation();
}


// Setting inputs
void SimulationMainWindow2D::setTolerance(){
   bool ok;
   double errorToleranceInput = 
               QInputDialog::getDouble(this, tr("Get Error Tolerance"),
                       tr("Error Tolerance:"), 0.1, 0.0001, 10, 4, &ok);
   if ( ok ){
      simulationErrorTolerance = errorToleranceInput;
   }
}

void SimulationMainWindow2D::setDelaySec(){
   bool ok;
   double delaySecondInput = 
               QInputDialog::getDouble(this, tr("Get Animation Delay Time"),
                       tr("Delay (in second):"), 0.5, 0.1, 10, 1, &ok);
   if ( ok ){
      delaySecond = delaySecondInput;
   }
}


// Delay function
void SimulationMainWindow2D::delay(){
   QTime dieTime= QTime::currentTime().addMSecs(1000.0*delaySecond);
   while( QTime::currentTime() < dieTime ){
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
   }
}

void SimulationMainWindow2D::setFilePath(){
   bool status;
   QString inputFileName = QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Input File Path:"),QLineEdit::Normal, QDir::home().dirName(), &status);
   if (status){
      filePath = inputFileName;
      restartSimulation();
   }
}

