#ifndef __INITIAL_CONDITION_CLASS__
#define __INITIAL_CONDITION_CLASS__


#include <cmath>
//#include <random>
#include <iostream>
using namespace std;

class InitialConditionClass{

   public:

     virtual bool Initialize(double r[], double Phi[], int gridSize) = 0;

   private:

};

#include "InitialConditionClass_Sin.h"
#include "InitialConditionClass_Step.h"
#include "InitialConditionClass_RndNoise.h"

#endif
