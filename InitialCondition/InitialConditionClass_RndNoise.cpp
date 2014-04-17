#include "InitialConditionClass_RndNoise.h"

bool InitialConditionClass_RndNoise::Initialize(double r[],
                                                 double Phi[],
                                                 int gridSize){

   int freq = 6;
   int rndPhase = 2.0;

   const double PI_CONST = 3.1415926535897932384626433832795028841971693993751058209749;

   for (int i = 0; i < gridSize; i++){
       r[i] = (double)i * 2. * PI_CONST / (double)(gridSize) + \
              1.0 * PI_CONST / (double)(gridSize);
       Phi[i] = 0.0;
   }

   for (int iFreq = 0; iFreq < freq; iFreq++){
      rndPhase = (float)(rand()%1000) / 1000.0 * 2.0 * PI_CONST;
      for (int i = 0; i < gridSize; i++){
         Phi[i] += sin( (double)iFreq * r[i] + rndPhase );
      }
   }

   return true;

}

