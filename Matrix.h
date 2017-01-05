#ifndef DEF_MATRIX
#define DEF_MATRIX

#include <iostream>
#include <sstream>
#include <vector>

template <class T>
class Matrix
{
public:
    Matrix<T>(int height, int width);
    Matrix<T>(std::vector<std::vector<T> > &array);
    Matrix<T>();

    void fill(T value);
    T get(int h, int w) const;
    void put(int h, int w, T value);

    Matrix add(T value);
    Matrix subtract(T value);
    Matrix multiply(T value);

    Matrix add(Matrix const &m) const;
    Matrix subtract(Matrix const &m) const;
    Matrix multiply(Matrix const &m) const;
    Matrix dot(Matrix const &m) const;
    Matrix transpose() const;

    Matrix applyFunction(T (*function)(T)) const;
    Matrix subMatrix(int startH, int startW, int h, int w) const;
    void print(std::ostream &flux) const;

    bool operator==(Matrix const &m);
    bool operator!=(Matrix const &m);
    void operator+=(Matrix const &m);
    void operator-=(Matrix const &m);
    void operator*=(Matrix const &m);

private:
    std::vector<std::vector<T> > array;
    int height;
    int width;
};

template <class T>
Matrix<T> operator+(Matrix<T> const &a, Matrix<T> const &b);

template <class T>
Matrix<T> operator-(Matrix<T> const &a, Matrix<T> const &b);

template <class T>
Matrix<T> operator*(Matrix<T> const &a, Matrix<T> const &b);

template <class T>
std::ostream& operator<<(std::ostream &flux, Matrix<T> const &m);

#endif


template <class T>
Matrix<T>::Matrix(int height, int width)
{
    this->height = height;
    this->width = width;

    this->array.resize(height);
    for (int i=0 ; i<height ; i++)
    {
        this->array[i].resize(width, 0);
    }
}

template <class T>
Matrix<T>::Matrix(std::vector<std::vector<T> > &array)
{
    if(array.size()!=0)
    {
        this->height = array.size();
        this->width = array[0].size();
        this->array = array;
    }
}

template <class T>
Matrix<T>::Matrix(){}

template <class T>
void Matrix<T>::fill(T value)
{
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            this->array[i][j] = value;
        }
    }
}

template <class T>
T Matrix<T>::get(int h, int w) const
{
    return this->array[h][w];
}

template <class T>
void Matrix<T>::put(int h, int w, T value)
{
    this->array[h][w] = value;
}

template <class T>
Matrix<T> Matrix<T>::add(T value)
{
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            this->array[i][j] += value;
        }
    }

    return *this;
}

template <class T>
Matrix<T> Matrix<T>::subtract(T value)
{
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            this->array[i][j] -= value;
        }
    }

    return *this;
}

template <class T>
Matrix<T> Matrix<T>::multiply(T value)
{
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            this->array[i][j] *= value;
        }
    }

    return *this;
}

template <class T>
Matrix<T> Matrix<T>::add(Matrix const &m) const
{
    if(height==m.height && width==m.width)
    {
        Matrix result(height, width);
        for (int i=0 ; i<height ; i++)
        {
            for (int j=0 ; j<width ; j++)
            {
                result.array[i][j] = this->array[i][j] + m.array[i][j];
            }
        }
        return result;
    }
    else
    {
        return Matrix(0,0);
    }
}

template <class T>
Matrix<T> Matrix<T>::subtract(Matrix const &m) const
{
    if(height==m.height && width==m.width)
    {
        Matrix result(height, width);
        for (int i=0 ; i<height ; i++)
        {
            for (int j=0 ; j<width ; j++)
            {
                result.array[i][j] = this->array[i][j] - m.array[i][j];
            }
        }
        return result;
    }
    else
    {
        return Matrix(0,0);
    }
}

template <class T>
Matrix<T> Matrix<T>::multiply(Matrix const &m) const
{
    if(height==m.height && width==m.width)
    {
        Matrix result(height, width);
        for (int i=0 ; i<height ; i++)
        {
            for (int j=0 ; j<width ; j++)
            {
                result.array[i][j] = this->array[i][j] * m.array[i][j];
            }
        }
        return result;
    }
    else
    {
        return Matrix(0,0);
    }
}

template <class T>
Matrix<T> Matrix<T>::dot(Matrix const &m) const
{
    if(width!=m.height)
    {
        return Matrix<T>(0,0);
    }

    Matrix<T> result(height, m.width);
    int w=0;

    for (int i=0 ; i<m.width ; i++){
        for (int j=0 ; j<m.height ; j++){
            for (int h=0 ; h<height ; h++){
                result.array[h][i] += this->array[h][w]*m.array[j][i];
            }
            w++;
        }
        w=0;
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> result(width, height);
    for (int i=0 ; i<result.height ; i++){
        for (int j=0 ; j<result.width ; j++){
            result.array[i][j] = this->array[j][i];
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::applyFunction(T (*function)(T)) const
{
    Matrix<T> result(height, width);

    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++){
            result.array[i][j] = (*function)(array[i][j]);
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::subMatrix(int startH, int startW, int h, int w) const
{
    if(startH+h<=this->height && startW+w<=this->width)
    {
        Matrix<T> result(h,w);
        for (int i=startH ; i<startH+h ; i++)
        {
            for (int j=startW ; j<startW+w ; j++)
            {
                result.put(i-startH, j-startW, this->array[i][j]);
            }
        }
        return result;
    }
    else
    {
        return Matrix<T>(-1,-1);
    }
}

template <class T>
void Matrix<T>::print(std::ostream &flux) const
{
    int maxLength[width] = {};
    std::stringstream ss;

    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            ss << this->array[i][j];
            if(maxLength[j] < ss.str().size())
            {
                maxLength[j] = ss.str().size();
            }
            ss.str(std::string());
        }
    }

    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            flux << array[i][j];
            ss << array[i][j];
            for (int k=0 ; k<maxLength[j]-ss.str().size()+1 ; k++)
            {
                flux << " ";
            }
            ss.str(std::string());
        }
        flux << std::endl;
    }
}

template <class T>
bool Matrix<T>::operator==(Matrix const &m)
{
    if(height==m.height && width==m.width)
    {
        for (int i=0 ; i<height ; i++)
        {
            for (int j=0 ; j<width ; j++)
            {
                if(this->array[i][j]!=m.array[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

template <class T>
bool Matrix<T>::operator!=(Matrix const &m)
{
    return !operator==(m);
}

template <class T>
void Matrix<T>::operator+=(Matrix const &m)
{
    this->array = add(m).array;
}

template <class T>
void Matrix<T>::operator-=(Matrix const &m)
{
    this->array = subtract(m).array;
}

template <class T>
void Matrix<T>::operator*=(Matrix const &m)
{
    this->array = multiply(m).array;
}

template <class T>
Matrix<T> operator+(Matrix<T> const &a, Matrix<T> const &b)
{
    return a.add(b);
}

template <class T>
Matrix<T> operator-(Matrix<T> const &a, Matrix<T> const &b)
{
    return a.subtract(b);
}

template <class T>
Matrix<T> operator*(Matrix<T> const &a, Matrix<T> const &b)
{
    return a.multiply(b);
}

template <class T>
std::ostream& operator<<(std::ostream &flux, Matrix<T> const &m)
{
    m.print(flux);
    return flux;
}
