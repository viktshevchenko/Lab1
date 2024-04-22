#include <iostream>
#include <cmath>

#define expression atan(_real / _imaginary) * 180.0 / M_PI

class complex_num {
    double _real, _imaginary;
public:
    explicit complex_num(double real = 0, double imaginary = 0);
    complex_num(complex_num const &other) = default;
    ~complex_num() = default;
    complex_num & operator=(complex_num ob2);
    complex_num operator+(complex_num ob2) const;
    complex_num operator-(complex_num ob2) const;
    complex_num operator*(complex_num ob2) const;
    complex_num operator/(complex_num ob2) const;

    double module() const;
    double argument() const;

    double get_r() const;
    double get_im() const;
};

complex_num::complex_num(double real, double imaginary) {
    _real = real;
    _imaginary = imaginary;
}

complex_num & complex_num::operator=(complex_num ob2) {
    if(this != &ob2) {
        _real = ob2._real;
        _imaginary = ob2._imaginary;
    }
    return *this;
}

complex_num complex_num::operator+(complex_num ob2) const {
    complex_num temp;
    temp._real = _real + ob2._real;
    temp._imaginary = _imaginary + ob2._imaginary;
    return temp;
}

complex_num complex_num::operator-(complex_num ob2) const {
    complex_num temp;
    temp._real = _real - ob2._real;
    temp._imaginary = _imaginary - ob2._imaginary;
    return temp;
}

complex_num complex_num::operator*(complex_num ob2) const {
    complex_num temp;
    temp._real = _real * ob2._real + _imaginary * ob2._imaginary * (-1);
    temp._imaginary = _real * ob2._imaginary + _imaginary * ob2._real;
    return temp;
}

complex_num complex_num::operator/(complex_num ob2) const {
    complex_num numerator, temp = ob2;
    double denominator;
    temp._imaginary = -ob2._imaginary;
    numerator = this->operator*(temp);
    denominator = pow(ob2._real, 2) + pow(ob2._imaginary, 2);
    numerator._real = numerator._real / denominator;
    numerator._imaginary = numerator._imaginary / denominator;
    return numerator;
}

double complex_num::module() const {
    return _real * _real + _imaginary * _imaginary;
}

double complex_num::argument() const {
    if(_real < 0 && _imaginary > 0)
        return 180.0 + expression;

    else if(_real < 0 && _imaginary < 0)
        return -180.0 + expression;

    return expression;
}

double complex_num::get_r() const {
    return _real;
}

double complex_num::get_im() const {
    return _imaginary;
}

void show(int num, complex_num ob) {
    std::cout << "z" << num << " = " << ob.get_r();
    (ob.get_im() > 0)?(printf(" + ")):(printf(" - "));
    std::cout << std::abs(ob.get_im()) << "i" << std::endl;
}

void show(complex_num ob) {
    std::cout << "z = " << ob.get_r();
    (ob.get_im() > 0)?(printf(" + ")):(printf(" - "));
    std::cout << std::abs(ob.get_im()) << "i" << std::endl;
}

// all functions doing with logic http://www.mathprofi.ru/kompleksnye_chisla_dlya_chainikov.html

int main() {
    complex_num n1(1, 3), n2(4, -5), n3, n4(1, -1), n5(3, 6),
        n6(13, 1), n7(7, -6), n8(5, 2);

    show(1, n1);
    show(2, n2);
    n3 = n1 + n2;
    std::cout << "z1 + z2 = ";
    show(n3);

    n3 = n1 - n2;
    std::cout << "z1 - z2 = ";
    show(n3);

    std::cout << "---------------------" << std::endl;
    show(1, n4);
    show(2, n5);
    n3 = n4 * n5;
    std::cout << "z1 * z2 = ";
    show(n3);

    std::cout << "---------------------" << std::endl;
    show(1, n6);
    show(2, n7);
    n3 = n6 / n7;
    std::cout << "z1 / z2 = ";
    show(n3);

    std::cout << "---------------------" << std::endl;
    show(n8);
    double a = n8.module();
    std::cout << "|z|= " << a << std::endl;
    a = n8.argument();
    std::cout << "argument = " << a << std::endl;

    return 0;
}