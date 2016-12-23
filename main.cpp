#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"

using namespace std;

double random(double x)
{
    return (double)(rand() % 10000 + 1)/10000-0.5;
}

int main(int argc, char *argv[])
{
    srand (time(NULL));

    Matrix<double> A(5, 5);
    A = A.applyFunction(random);
    cout << A << endl;
}
