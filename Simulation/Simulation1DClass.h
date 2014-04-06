#ifndef __SIMULATION_1D_CLASS__
#define __SIMULATION_1D_CLASS__

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "../GlobalFunctions/saveDataIntoFile.h"
#include "../FieldsDefinition/Field1DClass.h"
#include "../Solvers/OneDimensional/MainSolverClass.h"

class Simulation1DClass:public Field1DClass{

   public:
      
      Simulation1DClass( );
      ~Simulation1DClass( );

      // This function prepare the simulation to run. It sets up the
      // solvers and gridSize
      void setupSimulation( string mainSolverSchemeName,
                            string fluxSolverSchemeName );

      void runSimulationOneTimeStep( void );

      // These two functions set the  main/flux solvers 
      // and return true if it was successful otherwise false
      bool setMainSolver( string mainSolverSchemeName );
      bool setFluxSolver( string fluxSolverSchemeName );

      // This function calculate the the Error Norm
      // sum_i(Numerical-Exact)^2
      double calcErrorNorm( void );
 
      // This function make the snapshot of data / exact solution
      // and save it into given file
      bool saveSnapShot( string fname );

      bool saveSnapShotExactSolution( string fname );

      double getActualTime( void ){ return actualTime; }

   private:

      // Actual time of simulation
      double actualTime;

      // Snapshot and phase space header
      string snapShotHeader;
      string phaseSpaceHeader;

      // Simulation did setup correctly
      bool status;

      MainSolverClass *solver;

};

#endif
