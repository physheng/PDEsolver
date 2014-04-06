#ifndef __SOLVETRIDIAGONALMATRIX__
#define __SOLVETRIDIAGONALMATRIX__

// Source :: http://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
/* solves Ax = v where 
    A is a tridiagonal matrix consisting of vectors a, b, c
x[] - initially contains the input vector v, and returns the solution x.
     -- indexed from [0, ..., N - 1]
N — number of equations
a[] - subdiagonal (means it is the diagonal below the main diagonal) 
     -- indexed from [1, ..., N - 1]
b[] - the main diagonal, indexed from 
     -- [0, ..., N - 1]
c[] - superdiagonal (means it is the diagonal above the main diagonal) 
     -- indexed from [0, ..., N - 2]  */
bool solveTridiagonalMatrix(double x[], const int N, const double a[],
                            const double b[], const double c[]);

#endif

