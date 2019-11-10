#include <iostream>
#include "matrix.h"
using namespace std;

int main(){
    Matrix<float> M = random(3, 7);
    cout << M.max() << endl;
    return 0;
}