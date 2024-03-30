#include <iostream>

class matrix {
    double** element;
    size_t _size;
public:
    matrix(size_t size, double args, ...);
    matrix(matrix const &ob);
    ~matrix();
    matrix &operator=(matrix &ob2);
    matrix &operator*(matrix const ob2);
    friend matrix& operator*(matrix ob, double num);
    friend matrix& operator*(double num, matrix ob);
    matrix &operator+(matrix const ob2);
    matrix &operator-(matrix const ob2);
    double determinant();
    matrix transponir();
    matrix inverse();
    double operator[](int index);
};

int main() {

    return 0;
}
