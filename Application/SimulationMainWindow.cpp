#include <QtGui>

#include "SimulationMainWindow.h"

SimulationMainWindow::SimulationMainWindow(){
	
   QWidget *widget = new QWidget;
   setCentralWidget(widget);
   
   QWidget *topFiller = new QWidget;
   topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   
   QWidget *bottomFiller = new QWidget;
   bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   QVBoxLayout *layout = new QVBoxLayout;

   layout->setMargin(5);
   layout->addWidget(topFiller);
   layout->addWidget(bottomFiller);
   widget->setLayout(layout);

   createActions();
   createMenus();
   createButtons();

   QString message = tr("Select the simulation mode.");
   statusBar()->showMessage(message);

   setWindowTitle(tr("PDE Simulation Project"));
   setMinimumSize(480, 320);
   resize(720, 480);

}
   
void SimulationMainWindow::about(){	
   QMessageBox::about(this, tr("About Menu"),
             tr("In this application you can choose the simulation mode.\n"
                "This program do the simulation for Convection " 
                "equation in 1 dimension and 2 dimenstion."));
}

void SimulationMainWindow::createActions(){

   exitAct = new QAction(tr("E&xit"), this);
   exitAct->setShortcuts(QKeySequence::Quit);
   exitAct->setStatusTip(tr("Exit the application"));
   connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

   aboutAct = new QAction(tr("&About"), this);
   aboutAct->setStatusTip(tr("Show the application's About box"));
   connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void SimulationMainWindow::goTo1DSimulation(){
   SimulationMainWindow1D *window = new SimulationMainWindow1D;
   window->show();
   this->close();
}

void SimulationMainWindow::goTo2DSimulation(){
   SimulationMainWindow2D *window = new SimulationMainWindow2D;
   window->show();	
   this->close();
}

void SimulationMainWindow::createMenus(){
	
   fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(exitAct);

   helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(aboutAct);

}


void SimulationMainWindow::createButtons(){

    QPushButton* simulation1D = new QPushButton("1D Simulatoin", this);
    simulation1D->setGeometry(QRect(QPoint(200, 200), QSize(240, 90)));
    connect(simulation1D, SIGNAL(clicked()), this, SLOT(goTo1DSimulation()));

    QPushButton* simulation2D = new QPushButton("2D Simulatoin", this);
    simulation2D->setGeometry(QRect(QPoint(200, 100), QSize(240, 90)));
    connect(simulation2D, SIGNAL(clicked()), this, SLOT(goTo2DSimulation()));
   
}
