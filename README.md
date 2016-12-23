# Matrix
Matrix class in C++ with operators implemented.

# Usage

    #include "Matrix.h"
    ...

    // Constructors :
    Matrix<type_of_variable> matrix(int height, int width);
    Matrix<type_of_variable> matrix(vector<vector<type_of_variable> > array);
    Matrix<type_of_variable> matrix();

## Methods available :
1) add(Matrix), add(value), +
2) subtract(Matrix), subtract(value), -
3) multiply(Matrix), multiply(value), *
4) dot(Matrix)
5) transpose()
6) applyFunction(function)
7) fill(value)
8) get(y,x)
9) put(y,x,value)

    // example :
    Matrix<int> A(4,5);
    Matrix<int> B(4,5);
    Matrix<int> C(5,6);

    Matrix<int> D = A + B;  // = A.add(B)
    Matrix<int> D = A - B;  // = A.subtract(B)
    Matrix<int> D = A * B;  // = A.multiply(B)
    Matrix<int> D = B.dot(C);
    Matrix<int> D = A.transpose();

    int multiplyBy2Function(int x)
    {
        return 2*x;
    }

    Matrix<int> D = A.applyFunction(multiplyBy2Function);

    // you can combine operation :

    Matrix<int> D = (A+B).dot(C).applyFunction(multiplyBy2Function);
