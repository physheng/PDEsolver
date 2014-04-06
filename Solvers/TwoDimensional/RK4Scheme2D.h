#ifndef __TIMESOLVER_CLASS_RK4_2D__
#define __TIMESOLVER_CLASS_RK4_2D__

#include "MainSolverClass2D.h"

class RK4Scheme2D:public MainSolverClass2D{

   public:
      
      // Solve the field for 1 time step and return the 
      // new value of Phi (will modify Phi array)
      // return the value of dt dPhi/dt = rhs
      double Solve( double Phi[], double vx,  double vy );

   private:

};


#endif
