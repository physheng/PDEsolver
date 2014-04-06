#include <QtGui>

#include "SimulationMainWindow1D.h"

SimulationMainWindow1D::SimulationMainWindow1D(){
	
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

   mainSolverName = "LaxFriedrichs";
   fluxSolverName = "LinearReconstruction";
      //RK4KurganovTadmor2000Scheme; //IS NOT WORKING ?! --> RK4KurganovTadmor2000
      //KurganovTadmor2ndOrder2000Scheme; //IS NOT WORKING ?! --> KurganovTadmor2ndOrder2000
      //KurganovTadmor2000Scheme; //OK --> KurganovTadmor2000
      //LaxFriedrichsScheme; // OK --> LaxFriedrichs
      //ForwardEulerScheme; //OK --> ForwardEuler
      //RK4
      //MacCormackScheme; // OK --> MacCormack
   simulationErrorTolerance = 1e-1;

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
   QString fileName;
   string fname;

   while ( simIsRunning && simulationErr < simulationErrorTolerance ){

      simulation->runSimulationOneTimeStep();
      simIterator++;

      QApplication::processEvents();

      if ( simIterator%200 == 0 ){

         simulationTime = simulation->getActualTime();
         simulationErr  = simulation->calcErrorNorm();

         timeLabelString = tr("Time : ") + QString::number(simulationTime)
                   + tr("   Error : ") + QString::number(simulationErr); 	
         timeLabel->setText(timeLabelString);	

         // Saving data into file
         fileName = saveFileDir + QString::number(simIterator/200)
                    + saveFileNameField ;
         simulation->saveSnapShot(fileName.toStdString());

         // Saving exact solution into file
         fileName = saveFileDir + QString::number(simIterator/200)
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

void SimulationMainWindow1D::pauseSimulation(){
   simIsRunning = false;
   infoLabel->setText(tr("Simulation is Paused."));
}

void SimulationMainWindow1D::restartSimulation(){

   simIterator    = 0;
   simulationTime = 0.0;
   simulationErr  = 0.0;
   simIsRunning   = false;

   infoLabel->setText(tr("Simulation is restarted."));
   QString timeLabelString = tr("Time : ") + QString::number(simulationTime)
                   + tr("   Error : ") + QString::number(simulationErr) ; 	
   timeLabel->setText(timeLabelString);	
  
   simulation->initialize(gridSize);

   simulation->setupSimulation( mainSolverName, fluxSolverName);

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

   alignmentGroup = new QActionGroup(this);
   //alignmentGroup->addAction(leftAlignAct);
   //alignmentGroup->addAction(rightAlignAct);
   //alignmentGroup->addAction(justifyAct);
   //alignmentGroup->addAction(centerAct);
   //leftAlignAct->setChecked(true);

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

}

void SimulationMainWindow1D::createMenus(){
	
   fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addSeparator();
   fileMenu->addAction(exitAct);

   SimulationMenu = menuBar()->addMenu(tr("&Simulation"));
   SimulationMenu->addAction(runAct);
   SimulationMenu->addAction(pauseAct);
   SimulationMenu->addAction(restartAct);

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
