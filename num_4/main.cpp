#include <iostream>
#include <cstdarg>
#include <cmath>
#include <iomanip>

class matrix {
    double** element;
    size_t _size;

public:
    matrix(size_t size, unsigned int args, ...);
    matrix();
    matrix(matrix const &ob);
    ~matrix();
    matrix & operator=(matrix const &ob2);
    matrix operator*(matrix const ob2);
    friend matrix operator*(const matrix& ob, double num);
    friend matrix operator*(double num, const matrix& ob);
    matrix operator+(matrix const ob2);
    matrix operator-(matrix const ob2);
    double determinant();
    void transponir();
    void inverse(matrix &newMat);
    size_t get_size() const;
    double** get_element();
    void clear();

    class Proxy {
        double* _array;
    public:
        Proxy(double* _array) : _array(_array) { }

        double operator[](int index) {
            return _array[index];
        }
    };

    Proxy operator[](int index) {
        return Proxy(element[index]);
    }
};

matrix::matrix(size_t size, unsigned int args, ...) {
    _size = size;
    va_list va;
    va_start(va, args);
    element = new double *[size];
    for(size_t i = 0; i < size; i++) {
        element[i] = new double[size];
        for(size_t j = 0; j < size; j++) {
            if(args > 0){
                element[i][j] = va_arg(va, double);
                args--;
            }
            else
                element[i][j] = 0.0;
        }
    }
    va_end(va);
}

matrix::matrix() {
    element = nullptr;
    _size = 0;
}

matrix::matrix(matrix const &ob) {
    _size = ob._size;
    element = new double *[_size];
    for(size_t i = 0; i < _size; i++) {
        element[i] = new double[_size];
        for(size_t j = 0; j < _size; j++) {
            element[i][j] = ob.element[i][j];
        }
    }
}

matrix::~matrix() {
    clear();
}

matrix & matrix::operator=(matrix const &ob2) {
    if(&ob2 != this) {
        clear();
        _size = ob2._size;
        element = new double *[_size];
        for(size_t i = 0; i < _size; i++) {
            element[i] = new double[_size];
            for(size_t j = 0; j < _size; j++) {
                element[i][j] = ob2.element[i][j];
            }
        }
    }
    return *this;
}

matrix matrix::operator+(matrix const ob2) {
    if(_size != ob2._size) return *this;
    matrix temp = *this;
    for(size_t i = 0; i < _size; i++) {
        for(size_t j = 0; j < _size; j++)
            temp.element[i][j] += ob2.element[i][j];
    }
    return temp;
}

matrix matrix::operator-(matrix const ob2) {
    if(_size != ob2._size) return *this;
    matrix temp = *this;
    for(size_t i = 0; i < _size; i++) {
        for(size_t j = 0; j < _size; j++)
            temp.element[i][j] -= ob2.element[i][j];
    }
    return temp;
}

matrix matrix::operator*(matrix const ob2) {
    matrix temp = *this;
    double value;
    for(size_t i = 0; i < _size; i++) {
        for(size_t j = 0; j < _size; j++) {
            value = 0.0;
            for(size_t k = 0; k < _size; k++) {
                value += element[i][k] * ob2.element[k][j];
            }
            temp.element[i][j] = value;
        }
    }
    return temp;
}

matrix operator*(const matrix& ob, double num) {
    matrix temp = ob;
    for(size_t i = 0; i < ob._size; i++) {
        for(size_t j = 0; j < ob._size; j++) {
            temp.element[i][j] *= num;
        }
    }
    return temp;
}

matrix operator*(double num, const matrix& ob) {
    return ob * num;
}

double matrix::determinant() {
    matrix temp = *this;
    size_t n = temp._size;
    double det = 1.0;

    for (size_t i = 0; i < n; ++i) {

        double pivotElement = temp.element[i][i];
        size_t pivotRow = i;
        for (size_t row = i + 1; row < n; ++row) {
            if (std::abs(temp.element[row][i]) > std::abs(pivotElement)) {
                pivotElement = temp.element[row][i];
                pivotRow = row;
            }
        }
        if (pivotElement == 0.0)
            return 0.0;

        if (pivotRow != i) {
            std::swap(temp.element[i], temp.element[pivotRow]);
            det *= -1.0;
        }
        det *= pivotElement;

        for (size_t row = i + 1; row < n; ++row) {
            for (size_t col = i + 1; col < n; ++col)
                temp.element[row][col] -= temp.element[row][i] * temp.element[i][col] / pivotElement;
        }
    }
    return det;
}

void matrix::transponir() {
    matrix temp = *this;
    for(size_t i = 0; i < temp._size; i++){
        for(size_t j = 0; j < temp._size; j++){
            temp.element[i][j] = this->element[j][i];
        }
    }
    *this = temp;
}

void matrix::inverse(matrix &newMat){
    if(determinant() == 0.0)  return;
    if(_size != newMat._size) return;
    matrix mat = *this;
    size_t prom = 0;
    double dprom = 0;
    for(size_t i = 0; i < mat._size; i++) {
        if (mat.element[i][i] == 0) {
            prom = i;
            while (mat.element[prom][i] != 0) {
                prom++;
                if (prom == mat._size) return;
            }
            for (size_t j = i; j < mat._size; j++) {
                std::swap(mat.element[prom][j], mat.element[i][j]);
                std::swap(newMat.element[prom][j], newMat.element[i][j]);
            }
        }
        dprom = mat.element[i][i];
        for(size_t j = 0; j < mat._size; j++){
            mat.element[i][j] /= dprom;
            newMat.element[i][j] /= dprom;
        }
        for(size_t j = i+1; j < mat._size; j++){
            dprom = mat.element[j][i];
            for(size_t k = 0; k < mat._size; k++){
                mat.element[j][k] -= mat.element[i][k]*dprom;
                newMat.element[j][k] -= newMat.element[i][k]*dprom;
            }
        }
    }
    for(long long int i = mat._size-1; i >= 0; i--){
        for(long long int j = i-1; j >= 0; j--){
            dprom = mat.element[j][i];
            for(size_t k = 0; k < mat._size; k++){
                mat.element[j][k] -= mat.element[i][k]*dprom;
                newMat.element[j][k] -= newMat.element[i][k]*dprom;
            }
        }
    }
}

size_t matrix::get_size() const {
    return _size;
}

double** matrix::get_element() {
    return element;
}

void show(matrix ob) {
    for(size_t i = 0; i < ob.get_size(); i++) {
        for(size_t j = 0; j < ob.get_size(); j++) {
            std::cout << std::showpoint << std::left << std::setw(10) << ob.get_element()[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    printf("\n\n");
}

void matrix::clear() {
    for(size_t i = 0; i < _size; i++) delete[] element[i];
    delete[] element;
}

int main() {
    matrix m1(3, 9, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0), m2(3, 1, 2.0), m3(2, 0);
    matrix m4(3, 5, 4, 3, 2, 1, 0), m5(3, 9, 3.0, 3.0, -1.0, 4.0, 1.0, 3.0, 1.0, -2.0, -2.0),
    m6(2, 4, 1, 2, 3, 4);

    m3 = m1 + m2;
    show(m3);

    m3 = m1 - m2;
    show(m3);

    m3 = m1 * 2;
    show(m3);

    m3 = 5 * m1;
    show(m3);

    m3 = m1 * m4;
    show(m3);

    std::cout << m5.determinant() << std::endl << std::endl;

    m1.transponir();
    show(m1);

    m5.inverse(m3);
    show(m3);

    std::cout << m1[0][2] << std::endl;

    return 0;
}
