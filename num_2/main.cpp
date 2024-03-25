#include <iostream>

class logical_values_array {
    unsigned int _value;
public:
    logical_values_array(unsigned int value = 0) { _value = value; }
    void accessor(unsigned int value) { _value = value; }







    static bool equals(logical_values_array ob2);
    void convertation(char* &ob);
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
