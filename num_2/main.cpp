#include <iostream>
#include <cstring>

char* dec_to_bin(int num);

class logical_values_array {
    unsigned int _value;
public:
    logical_values_array(unsigned int value = 0);
    void accessor(unsigned int value);
    void inversion();
    logical_values_array operator=(logical_values_array ob2);
    logical_values_array conjunction(logical_values_array ob2) const;
    logical_values_array disjunction(logical_values_array ob2) const;
    logical_values_array implication(logical_values_array ob2) const;
    logical_values_array coimplication(logical_values_array ob2) const;
    logical_values_array addition_mod_2(logical_values_array ob2) const;
    logical_values_array equivalence(logical_values_array ob2) const;
    logical_values_array pier_arrow(logical_values_array ob2) const;
    logical_values_array stroke_schaeffer(logical_values_array ob2) const;
    static bool equals(unsigned int ob1, unsigned int ob2);
    bool get_bit(unsigned int position);
    void position(char* &p) const;
    unsigned int get() const;
};

logical_values_array::logical_values_array(unsigned int value) {
    _value = value;
}

void logical_values_array::accessor(unsigned int value) {
    _value = value;
}

logical_values_array logical_values_array::operator=(logical_values_array ob2) {
    _value = ob2._value;
    return *this;
}

void logical_values_array::inversion() {
    (_value > 0)?(_value = 0):(_value = 1);
}

logical_values_array logical_values_array::conjunction(logical_values_array ob2) const {
    logical_values_array temp;
    (_value > 0 && ob2._value > 0)?(temp._value = 1):(temp._value = 0);
    return temp;
}

logical_values_array logical_values_array::disjunction(logical_values_array ob2) const {
    logical_values_array temp;
    (_value > 0 || ob2._value > 0)?(temp._value = 1):(temp._value = 0);
    return temp;
}

logical_values_array logical_values_array::implication(logical_values_array ob2) const {
    logical_values_array temp;
    (_value > 0 && ob2._value == 0)?(temp._value = 0):(temp._value = 1);
    return temp;
}

logical_values_array logical_values_array::coimplication(logical_values_array ob2) const {
    logical_values_array temp;
    //(_value > 0 && ob2._value == 0)?(temp._value = 1):(temp._value = 0);
    temp = this->implication(ob2);
    temp.inversion();
    return temp;
}

logical_values_array logical_values_array::addition_mod_2(logical_values_array ob2) const {
    logical_values_array temp;
    (_value > 0 && ob2._value > 0 || _value == 0 && ob2._value == 0)?(temp._value = 0):(temp._value = 1);
    return temp;
}

logical_values_array logical_values_array::equivalence(logical_values_array ob2) const {
    logical_values_array temp;
    //(_value > 0 && ob2._value > 0 || _value == 0 && ob2._value == 0)?(temp._value = 1):(temp._value = 0);
    temp = this->addition_mod_2(ob2);
    temp.inversion();
    return temp;
}

logical_values_array logical_values_array::pier_arrow(logical_values_array ob2) const{
    logical_values_array temp;
    temp = this->disjunction(ob2);
    temp.inversion();
    return temp;
}

logical_values_array logical_values_array::stroke_schaeffer(logical_values_array ob2) const{
    logical_values_array temp;
    temp = this->conjunction(ob2);
    temp.inversion();
    return temp;
}

char* dec_to_bin(int num) {
    int k;
    char* buf = new char [sizeof(unsigned int) + 1];
    char *p = buf + sizeof(unsigned int), *temp;
    buf[sizeof(unsigned int) + 1] = '\0';
    while(num != 0) {
        k = num & 0x00000001;
        *p = '0' + k;
        p--;
        num = num >> 1;
    }
    temp = strdup(++p);
    delete [] buf;
    return temp;
}

bool logical_values_array::equals(unsigned int ob1, unsigned int ob2) {
    return ob1 == ob2;
}

bool logical_values_array::get_bit(unsigned int position) {
    char *p = dec_to_bin(_value);
    int len = strlen(p);
    bool res;
    if(position > len) {
        res = p[len - 1] - '0';
        return res;
    }
    res = p[position - 1] - '0';
    delete [] p;
    return res;
}

void logical_values_array::position(char* &p) const {
    p = strdup(dec_to_bin(_value));
}

unsigned int logical_values_array::get() const {
    return _value;
}

void show(int num, logical_values_array ob) {
    std::cout << "value" << num << ": " << ob.get() << std::endl;
}

void show(logical_values_array ob) {
    std::cout << ob.get() << std::endl;
}

int main() {
    // values > 1 = 1

    logical_values_array ob1(1), ob2(100), ob3, ob4(1), ob5(0), ob6(100); // constructor

    // accessor
    std::cout << "accessor:" << std::endl;
    show(ob2);
    ob2.accessor(3);
    show(ob2);
    std::cout << "----------" << std::endl;

    // inversion
    show(1, ob1);
    std::cout << "inversion: ";
    ob1.inversion();
    show(ob1);
    std::cout << "----------" << std::endl;

    // conjunction
    show(1, ob1);
    show(2, ob2);
    ob3 = ob1.conjunction(ob2);
    std::cout << "conjunction: ";
    show(ob3);
    std::cout << "----------" << std::endl;

    // disjunction
    show(1, ob1);
    show(2, ob2);
    ob3 = ob1.disjunction(ob2);
    std::cout << "disjunction: ";
    show(ob3);
    std::cout << "----------" << std::endl;

    // implication
    show(1, ob1);
    show(2, ob4);
    std::cout << "implication (v1->v2): ";
    ob3 = ob1.implication(ob4);
    show(ob3);
    std::cout << "implication (v2->v1): ";
    ob3 = ob4.implication(ob1);
    show(ob3);
    std::cout << "----------" << std::endl;

    // coimplication
    show(1, ob1);
    show(2, ob4);
    std::cout << "coimplication !(v1->v2): ";
    ob3 = ob1.coimplication(ob4);
    show(ob3);
    std::cout << "coimplication !(v2->v1): ";
    ob3 = ob4.coimplication(ob1);
    show(ob3);
    std::cout << "----------" << std::endl;

    // addition mod 2
    show(1, ob1);
    show(2, ob2);
    show(3, ob5);
    ob3 = ob1.addition_mod_2(ob2);
    std::cout << "addition mod 2 (v1 v2): ";
    show(ob3);
    ob3 = ob1.addition_mod_2(ob5);
    std::cout << "addition mod 2 (v1 v3): ";
    show(ob3);
    std::cout << "----------" << std::endl;

    // equivalence
    show(1, ob1);
    show(2, ob2);
    show(3, ob5);
    ob3 = ob1.equivalence(ob2);
    std::cout << "equivalence (v1~v2): ";
    show(ob3);
    ob3 = ob1.equivalence(ob5);
    std::cout << "equivalence (v1~v3): ";
    show(ob3);
    std::cout << "----------" << std::endl;

    // Pier arrow
    show(1, ob1);
    show(2, ob2);
    show(3, ob5);
    ob3 = ob1.pier_arrow(ob2);
    std::cout << "Pier arrow (v1 v2): ";
    show(ob3);
    ob3 = ob1.pier_arrow(ob5);
    std::cout << "Pier arrow (v1 v3): ";
    show(ob3);
    std::cout << "----------" << std::endl;

    // stroke Schaeffer
    show(1, ob1);
    show(2, ob2);
    show(3, ob4);
    ob3 = ob1.stroke_schaeffer(ob2);
    std::cout << "stroke Schaeffer (v1 | v2): ";
    show(ob3);
    ob3 = ob2.stroke_schaeffer(ob4);
    std::cout << "stroke Schaeffer (v2 | v3): ";
    show(ob3);
    std::cout << "----------" << std::endl;

    // get_bit()
    std::cout << dec_to_bin(ob6.get()) << " element 5: " << ob6.get_bit(5) << std::endl;
    std::cout << dec_to_bin(ob6.get()) << " element 3: " << ob6.get_bit(3) << std::endl;
    std::cout << "----------" << std::endl;

    // position
    char *p = new char [20];
    ob6.position(p);
    std::cout << p << std::endl;
    delete [] p;

    return 0;
}
