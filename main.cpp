/************************************************
**  EECS 402 - Winter 2014                     **
**  Project 4                                  **
************************************************/
/////////////////////////////////////////////////
/////////////////////////////////////////////////
// Libraries ////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

#include <QApplication>
#include "./Application/SimulationMainWindow.h"

/////////////////////////////////////////////////
/////////////////////////////////////////////////
// Main Code ////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
int main( int argc, char **argv ){

   QApplication app(argc, argv);
   SimulationMainWindow window;
   window.show();
   
   return app.exec(); 
}




