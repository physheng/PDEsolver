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

   gridSize  = xGridSize * yGridSize;

   vx = 1.0;
   vy = 1.0;

   mainSolverName = "LaxFriedrichs";
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
                   //+ tr(" - Flux Solver Scheme: ")
                   //+ QString::fromStdString(fluxSolverName) 
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

void SimulationMainWindow2D::createMenus(){
	
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
