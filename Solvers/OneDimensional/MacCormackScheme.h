#ifndef __TIMESOLVER_CLASS_MACCORMACKSCHEME__
#define __TIMESOLVER_CLASS_MACCORMACKSCHEME__

#include "MainSolverClass.h"

class MacCormackScheme:public MainSolverClass{

   public:
      
      // Solve the field for 1 time step and return the 
      // new value of Phi (will modify Phi array)
      // return the value of dt dPhi/dt = rhs
      double Solve(const double r[], double Phi[] );

   private:

};


#endif
