#ifndef __INITIAL_CONDITION_CLASS_SIN__
#define __INITIAL_CONDITION_CLASS_SIN__

#include <InitialConditionClass.h>

class InitialConditionClass_Sin:public InitialConditionClass{

   public:
   
      bool Initialize(double r[], double Phi[], int gridSize);

   private:


};


#endif
