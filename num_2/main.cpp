#include <iostream>

class logical_values_array {
    unsigned int _value;
public:
    logical_values_array(unsigned int value = 0) { _value = value; }
    void accessor(unsigned int value) { _value = value; }
    void inversion();
    logical_values_array conjunction(logical_values_array ob2) const;
    logical_values_array disjunction(logical_values_array ob2) const;
    logical_values_array implication(logical_values_array ob2) const;
    logical_values_array coimplication(logical_values_array ob) const;



    static bool equals(logical_values_array ob2);
    void convertation(char* &ob);
};


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
    temp.implication(ob2);
    temp.inversion();
    return temp;
}

int main() {
    logical_values_array ob1(1), ob2(0);
    ob1.coimplication(ob2);
    return 0;
}
