#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"

using namespace std;

double random(double x)
{
    return (double)(rand() % 10000 + 1)/10000;
}

int main(int argc, char *argv[])
{
    srand (time(NULL));

    Matrix<double> A(100, 100), B(100, 100);

    A = A.applyFunction(random);
    B = B.applyFunction(random);

    clock_t begin = clock();

    for (int i=0 ; i<1000 ; i++)
    {
        A.dot(B);
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "time: " << elapsed_secs/1000.0 << " s" << endl;
}
