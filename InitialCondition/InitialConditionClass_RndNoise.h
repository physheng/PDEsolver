#ifndef __INITIAL_CONDITION_CLASS_RNDNOISE__
#define __INITIAL_CONDITION_CLASS_RNDNOISE__

#include <InitialConditionClass.h>

class InitialConditionClass_RndNoise:public InitialConditionClass{

   public:
   
      bool Initialize(double r[], double Phi[], int gridSize);

   private:

};

#endif
