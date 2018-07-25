# Matrix

Matrix class in C++ with operators implemented.

# Usage

```c++
#include "matrix.h"
...

// Constructors :
Matrix<type_of_variable> matrix(int height, int width);
Matrix<type_of_variable> matrix(vector<vector<type_of_variable> > &array);
Matrix<type_of_variable> matrix();
```

# Operators

```c++
Matrix<int> a,b,c;
int z;

c = a + b;
c = a - b;
c = a * b;
c = z * a;
c = a / z;
```

# Example

```c++
Matrix<int> A(4,5);
Matrix<int> B(4,5);
Matrix<int> C(5,6);

Matrix<int> D = A + B;  // = A.add(B)
Matrix<int> D = A - B;  // = A.subtract(B)
Matrix<int> D = A * B;  // = A.multiply(B)
Matrix<int> D = B.dot(C);
Matrix<int> D = A.transpose();
Matrix<int> D = A.subMatrix(0,0, 2,2); // get a sub matrix of size 2x2 from coordinates 0;0 in A

A += B;
A -= B;
A *= B;

int multiplyByTwo(int x){
    return 2*x;
}

Matrix<int> D = A.applyFunction(multiplyByTwo);

// you can combine operations :

Matrix<int> D = (A+B).dot(C).applyFunction(multiplyByTwo);

std::cout << D << std::endl;
```
