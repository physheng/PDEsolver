#ifndef __TIMESOLVER_CLASS_RK4KURGANOVTADMOR2000SCHEME__
#define __TIMESOLVER_CLASS_RK4KURGANOVTADMOR2000SCHEME__

#include "MainSolverClass.h"

class RK4KurganovTadmor2000Scheme:public MainSolverClass{

   public:
      
      // Solve the field for 1 time step and return the 
      // new value of Phi (will modify Phi array)
      // return the value of dt dPhi/dt = rhs
      double Solve(const double r[], double Phi[] );

   private:

};


#endif
