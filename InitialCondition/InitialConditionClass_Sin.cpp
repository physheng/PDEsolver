#include "InitialConditionClass_Sin.h"

InitialConditionClass_Sin::InitialConditionClass_Sin( double AMP,
                                                      int FREQ ){
   amp  = AMP;
   freq = FREQ;
   cout << "SIN INITILIZATION SCHEME IS USED FOR INITIAL CONDTION" << endl;
}

bool InitialConditionClass_Sin::Initialize(double r[],
                                           double Phi[],
                                           int gridSize){

    const double PI_CONST = 3.1415926535897932384626433832795028841971693993751058209749;

    for (int i = 0; i < gridSize; i++){
       r[i]   = (double)i * 2. * PI_CONST / (double)(gridSize) + \
                1.0 * PI_CONST / (double)(gridSize);
       if (r[i] > 1. && r[i] < 2.0 ){
          Phi[i] = 1.0;
       }
       else{
          Phi[i] = 0.0;
       }
       Phi[i] = amp * sin( (double)freq * r[i] + 0.2 );
    }

    return true;

}

