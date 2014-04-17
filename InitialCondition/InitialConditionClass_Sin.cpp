#include "InitialConditionClass_Sin.h"

bool InitialConditionClass_Sin::Initialize(double r[],
                                           double Phi[],
                                           int gridSize){

    int freq = 5;

    const double PI_CONST = 3.1415926535897932384626433832795028841971693993751058209749;

    for (int i = 0; i < gridSize; i++){
       r[i]   = (double)i * 2. * PI_CONST / (double)(gridSize) + \
                1.0 * PI_CONST / (double)(gridSize);
       Phi[i] = sin( (double)freq * r[i] + 0.2 );
    }

    return true;

}

