#include <iostream>
#include <cstring>

class queue {
    struct Node {
        char* str;
        int len;
        size_t priority;
    };
    Node* _q;
    size_t _physical_size, _virtual_size;

    static void create_Node(Node &node, char const *str, int priority){
        node.str = new char[strlen(str)*sizeof(char)+1];
        strcpy(node.str, str);
        node.priority = priority;
    }

public:
    queue();
    ~queue();
    queue(queue const &ob2);
    queue & operator=(queue const &ob2);
    void push(char const *str, int priority);
    void pop();
    void search_min();
    void merging(queue const &q1, queue const &q2);
    size_t get_phys() const;
    size_t get_virt() const;
    Node* get_q();
    void clear();
};

queue::queue() {
    _q = new Node[16];
    _physical_size = 16;
    _virtual_size = 0;
}

void queue::clear() {
    for(size_t i = 0; i < _virtual_size; i++) {
        delete[] _q[i].str;
    }
    delete[] _q;
}

queue::~queue() {
    clear();
}

queue::queue(queue const &ob2) {
    _physical_size = ob2._physical_size;
    _q = new Node[_physical_size];
    _virtual_size = ob2._virtual_size;
    for(size_t i = 0; i < _virtual_size; i++) {
        _q[i].len = ob2._q[i].len;
        _q[i].str = new char[_q[i].len + 1];
        strcpy(_q[i].str, ob2._q[i].str);
    }
}

queue & queue::operator=(queue const &ob2) {
    if(this != &ob2) {
        clear();
        _physical_size = ob2._physical_size;
        _q = new Node[_physical_size];
        _virtual_size = ob2._virtual_size;
        for(size_t i = 0; i < _virtual_size; i++) {
            _q[i].len = ob2._q[i].len;
            _q[i].str = new char[_q[i].len + 1];
            strcpy(_q[i].str, ob2._q[i].str);
        }
    }
    return *this;
}

void queue::push(char const *str, int priority) {
    create_Node(_q[_virtual_size++], str, priority);
    size_t i = _virtual_size - 1;
    while((i != 0) && (_q[(i - 1) / 2].priority > _q[i].priority)) {
        std::swap(_q[i], _q[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    if(_virtual_size == _physical_size) {
        _physical_size *= 2;
        Node* temp = nullptr;
        temp = (Node *)realloc(_q, _physical_size * sizeof(Node));
        if(temp == nullptr)
            return;
        _q = temp;
    }
}

void queue::pop() {
    std::swap(_q[0], _q[_virtual_size - 1]);
    _virtual_size--;
    std::cout << "Popped: " << _q[_virtual_size].str << std::endl;
    delete[] _q[_virtual_size].str;
    size_t i = 0, min = 0;
    while(i * 2 + 1 < _virtual_size) {
        min = i * 2 + 1;
        if(min + 1 < _virtual_size && _q[min].priority > _q[min + 1].priority)
            min++;
        if(_q[i].priority <= _q[min].priority)
            break;

        std::swap(_q[i], _q[min]);
        i = min;
    }
}

void queue::search_min() {
    std::cout << "Minimal priority: " << _q[0].str << std::endl;
}

void queue::merging(queue const &q1, queue const &q2) {
    for(size_t i = 0; i < q1._virtual_size; i++) {
        push(q1._q[i].str, q1._q->priority);
        if(i < q2._virtual_size)
            push(q2._q[i].str, q2._q->priority);
    }
}

size_t queue::get_phys() const {
    return _physical_size;
}

size_t queue::get_virt() const {
    return _virtual_size;
}

queue::Node* queue::get_q() {
    return _q;
}

void show(queue ob) {
    std::cout << "Virtual size: " << ob.get_virt() << std::endl;
    std::cout << "Physical size: " << ob.get_phys() << std::endl;
    for(size_t i = 0; i < ob.get_virt(); i++)
        std::cout << i << ' ' << ob.get_q()[i].str << std::endl;
    std::cout << std::endl;
}

int main() {
    queue q1, q2, q3, q4, q5;

    for(size_t i = 0; i < 5; i++)
        q1.push("1", 1);
    show(q1);

    for(size_t i = 0; i < 12; i++)
        q2.push("2", 2);
    show(q2);

    q3.merging(q1, q2);
    show(q3);

    for(int i = 0; i < 7; i++)
        q3.pop();

    q3.search_min();

    q5 = q3;
    show(q5);

    return 0;
}