#include <iostream>
#include <cmath>

class complex_num {
    double _real, _imaginary;
public:
    complex_num(double real = 0, double imaginary = 0) { _real = real; _imaginary = imaginary; }

    complex_num & operator=(complex_num ob2);
    complex_num operator+(complex_num ob2) const;
    complex_num operator-(complex_num ob2) const;
    complex_num operator*(complex_num ob2) const;
    complex_num operator/(complex_num ob2) const;

    double module() { return sqrt(pow(_real, 2) + pow(_imaginary, 2)); }
    double argument() const;
    void show(int num);
    void show();
};

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

double complex_num::argument() const {
    if(_real < 0 && _imaginary > 0)
        return 180.0 + atan(_real / _imaginary) * 180.0 / M_PI;

    else if(_real < 0 && _imaginary < 0)
        return -180.0 + atan(_real / _imaginary) * 180.0 / M_PI;

    return atan(_real / _imaginary) * 180.0 / M_PI;
}

void complex_num::show(int num) {
    std::cout << "z" << num << " = " << _real;
    (_imaginary > 0)?(printf(" + ")):(printf(" - "));
    std::cout << abs(_imaginary) << "i" << std::endl;
}

void complex_num::show() {
    std::cout << "z = " << _real;
    (_imaginary > 0)?(printf(" + ")):(printf(" - "));
    std::cout << abs(_imaginary) << "i" << std::endl;
}

// all functions doing with logic http://www.mathprofi.ru/kompleksnye_chisla_dlya_chainikov.html

int main() {
    complex_num n1(1, 3), n2(4, -5), n3, n4(1, -1), n5(3, 6),
        n6(13, 1), n7(7, -6), n8(5, 2);

    n1.show(1);
    n2.show(2);
    n3 = n1 + n2;
    std::cout << "z1 + z2 = ";
    n3.show();

    n3 = n1 - n2;
    std::cout << "z1 - z2 = ";
    n3.show();

    std::cout << "---------------------" << std::endl;
    n4.show(1);
    n5.show(2);
    n3 = n4 * n5;
    std::cout << "z1 * z2 = ";
    n3.show();

    std::cout << "---------------------" << std::endl;
    n6.show(1);
    n7.show(2);
    n3 = n6 / n7;
    std::cout << "z1 / z2 = ";
    n3.show();

    std::cout << "---------------------" << std::endl;
    n8.show();
    double a = n8.module();
    std::cout << "|z|= " << a << std::endl;
    a = n8.argument();
    std::cout << "argument = " << a << std::endl;

    return 0;
}