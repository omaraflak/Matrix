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
#### add(Matrix), add(value), +
### subtract(Matrix), subtract(value), -
### multiply(Matrix), multiply(value), *
### dot(Matrix)
### transpose()
### applyFunction(function)
### fill(value)
### get(y,x)
### put(y,x,value)
### cout << Matrix;

## example :
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
    
    cout << D << endl;
