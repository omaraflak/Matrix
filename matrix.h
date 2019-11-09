#ifndef DEF_MATRIX
#define DEF_MATRIX

#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <math.h>

template <class T>
class Matrix{
    private:
        std::vector<std::vector<T> > array;
        int height;
        int width;

    public:
        Matrix<T>(int height, int width);
        Matrix<T>(std::vector<std::vector<T> > const &array);
        Matrix<T>();

        int getHeight() const;
        int getWidth() const;

        Matrix<T> add(const Matrix<T>& m) const;
        Matrix<T> subtract(const Matrix<T>& m) const;
        Matrix<T> multiply(const Matrix<T>& m) const;
        Matrix<T> dot(const Matrix<T>& m) const;
        Matrix<T> transpose() const;
        Matrix<T> multiply(const T& value) const;
        Matrix<T> divide(const T& value) const;

        Matrix<T> applyFunction(T (*function)(T)) const;
        Matrix<T> subMat(int startH, int startW, int h, int w) const;

        void fill(const T& value);
        void put(int h, int w, const T& value);
        T get(int h, int w) const;

        void print(std::ostream &flux) const;

        bool operator==(const Matrix<T>& m);
        bool operator!=(const Matrix<T>& m);
        Matrix<T> operator+=(const Matrix<T>& m);
        Matrix<T> operator-=(const Matrix<T>& m);
        Matrix<T> operator*=(const Matrix<T>& m);
        Matrix<T> operator*=(const T &m);
        Matrix<T> operator/=(const T &m);
        T& operator()(int y, int x);

        Matrix<T> sign() const;
};

template <class T> Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b);
template <class T> Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b);
template <class T> Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b);
template <class T> Matrix<T> operator*(const T &b, const Matrix<T>& a);
template <class T> Matrix<T> operator/(const Matrix<T>& a, const T &b);
template <class T> std::ostream& operator<<(std::ostream &flux, const Matrix<T>& m);

#endif


template <class T>
Matrix<T>::Matrix(int height, int width){
    this->height = height;
    this->width = width;
    this->array = std::vector<std::vector<T> >(height, std::vector<T>(width));
}

template <class T>
Matrix<T>::Matrix(std::vector<std::vector<T> > const &array){
    if(array.size()==0)
        throw std::invalid_argument("Size of array must be greater than 0.");

    this->height = array.size();
    this->width = array[0].size();
    this->array = array;
}

template <class T>
Matrix<T>::Matrix(){
    height = 0;
    width = 0;
}

template <class T>
int Matrix<T>::getHeight() const{
    return height;
}

template <class T>
int Matrix<T>::getWidth() const{
    return width;
}

template <class T>
void Matrix<T>::fill(const T& value){
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            array[i][j] = value;
        }
    }
}

template <class T>
void Matrix<T>::put(int h, int w, const T& value){
    if(!(h>=0 && h<height && w>=0 && w<width))
        throw std::invalid_argument("Index out of bounds.");

    array[h][w] = value;
}

template <class T>
T Matrix<T>::get(int h, int w) const{
    if(!(h>=0 && h<height && w>=0 && w<width))
        throw std::invalid_argument("Index out of bounds.");

    return array[h][w];
}

template <class T>
Matrix<T> Matrix<T>::multiply(const T& value) const{
    Matrix result(array);
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            result.array[i][j] *= value;
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::divide(const T& value) const{
    Matrix result(array);
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            result.array[i][j] /= value;
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::add(const Matrix& m) const{
    if(!(height==m.height && width==m.width))
        throw std::invalid_argument("Matrix dimension must be the same.");

    Matrix result(height, width);
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            result.array[i][j] = array[i][j] + m.array[i][j];
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::subtract(const Matrix& m) const{
    if(!(height==m.height && width==m.width))
        throw std::invalid_argument("Matrix dimension must be the same.");

    Matrix result(height, width);
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            result.array[i][j] = array[i][j] - m.array[i][j];
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::multiply(const Matrix& m) const{
    if(!(height==m.height && width==m.width))
        throw std::invalid_argument("Matrix dimension must be the same.");

    Matrix result(height, width);

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            result.array[i][j] = array[i][j] * m.array[i][j];
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::dot(const Matrix& m) const{
    if(!(width==m.height))
        throw std::invalid_argument("Dot product not compatible.");

    T w=0;
    int mwidth = m.width;

    Matrix<T> result(height, mwidth);
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<mwidth ; j++){
            for (int h=0 ; h<width ; h++){
                w += array[i][h]*m.array[h][j];
            }
            result.array[i][j] = w;
            w=0;
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const{
    Matrix<T> result(width, height);

    for (int i=0 ; i<width ; i++){
        for (int j=0 ; j<height ; j++){
            result.array[i][j] = array[j][i];
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::applyFunction(T (*function)(T)) const{
    Matrix<T> result(height, width);

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            result.array[i][j] = (*function)(array[i][j]);
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::subMat(int startH, int startW, int h, int w) const{
    if(!(startH>=0 && startH+h<=height && startW>=0 && startW+w<=width))
        throw std::invalid_argument("Index out of bounds");

    Matrix<T> result(h,w);
    for (int i=startH ; i<startH+h ; i++){
        for (int j=startW ; j<startW+w ; j++){
            result.array[i-startH][j-startW] = array[i][j];
        }
    }
    return result;
}

template <class T>
void Matrix<T>::print(std::ostream &flux) const{
    int maxLength[width] = {};
    std::stringstream ss;

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            ss << array[i][j];
            if(maxLength[j] < ss.str().size()){
                maxLength[j] = ss.str().size();
            }
            ss.str(std::string());
        }
    }

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            flux << array[i][j];
            ss << array[i][j];
            for (int k=0 ; k<maxLength[j]-ss.str().size()+1 ; k++){
                flux << " ";
            }
            ss.str(std::string());
        }
        flux << std::endl;
    }
}

template <class T>
bool Matrix<T>::operator==(const Matrix& m){
    if(height==m.height && width==m.width){
        for (int i=0 ; i<height ; i++){
            for (int j=0 ; j<width ; j++){
                if(array[i][j]!=m.array[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix& m){
    return !operator==(m);
}

template <class T>
Matrix<T> Matrix<T>::operator+=(const Matrix& m){
    this->array = add(m).array;
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-=(const Matrix& m){
    this->array = subtract(m).array;
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*=(const Matrix& m){
    this->array = multiply(m).array;
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*=(const T &m){
    *this = this->multiply(m);
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator/=(const T &m){
    *this = this->divide(m);
    return *this;
}

template <class T>
T& Matrix<T>::operator()(int y, int x){
    if(!(y>=0 && y<height && x>=0 && x<width))
        throw std::invalid_argument("Index out of bounds.");
    return array[y][x];
}

template <class T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b){
    return a.add(b);
}

template <class T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b){
    return a.subtract(b);
}

template <class T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b){
    return a.multiply(b);
}

template <class T>
Matrix<T> operator*(const T &b, const Matrix<T>& a){
    return a.multiply(b);
}
template <class T>
Matrix<T> operator/(const Matrix<T>& a, const T &b){
    return a.divide(b);
}

template <class T>
std::ostream& operator<<(std::ostream &flux, const Matrix<T>& m){
    m.print(flux);
    return flux;
}

template <class T = float>
Matrix<T> random(int height, int width){
    srand(time(NULL));
    Matrix<T> M(height, width);
    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++){
            float random = fmod(rand() / 5136.9 , 1);
            M.put(i, j,  random);
        }
        
    }
    return M;
}
template <class T>
Matrix<T> Matrix<T>::sign() const{
    Matrix<T> result(height, width);

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            if(array[i][j] > 0) result.array[i][j] =  1;
            else if(array[i][j] < 0) result.array[i][j] =  -1;
            else result.array[i][j] =  0;
        }
    }
    return result;
}


template <class T = float>
Matrix<T> random_like(const Matrix<T> other){
    srand(time(NULL));
    Matrix<T> M(other.getHeight(), other.getWidth());
    for (size_t i = 0; i < other.getHeight(); i++){
        for (size_t j = 0; j < other.getWidth(); j++){
            float random = fmod(rand() / 5136.9 , 1);
            M.put(i, j,  random);
        }
        
    }
    return M;
}

template <class T>
Matrix<T> ones(int height, int width){
    Matrix<T> M(height, width);
    M.fill(1);
    return M;
}

template <class T>
Matrix<T> ones_like(const Matrix<T>& other){
    return ones<T>(other.getHeight(), other.getWidth());
}

