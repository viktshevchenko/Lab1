#include <iostream>
#include <cstring>
#include <fstream>

class encoder {
     unsigned char* _key;
    int _len;
public:
    encoder(unsigned char const* key, int len);
    encoder(const encoder &p);
    ~encoder() { delete [] _key; }
    void mutator(unsigned char const* key, int len);
    void encode(char const* input_file, char const* output_file, bool flag);
    //void show() { std::cout << _key << ' ' << _len << std::endl; }
};

encoder::encoder(unsigned char const* key, int len) {
    _key = new unsigned char[256];
    mutator(key, len);
}

encoder::encoder(const encoder &p) {
    _key = new unsigned char[256];
    memcpy(_key, p._key, 256);
}


void encoder::mutator(unsigned char const* key, int len) {
    int j = 0;
    for (int i = 0; i < 256; i++)
        _key[i] = i;
    for (int i = 0; i < 256; i++) {
        j = (j + _key[i] + key[i%len]) % 256;
        std::swap(_key[i], _key[j]);
    }
}

void encoder::encode(const char *input_file, const char *output_file, bool flag) {
    std::ifstream fin;
    std::ofstream fout;

    switch(flag) {
        case 0:
            fin.open(input_file, std::ios::binary);
            fout.open(output_file, std::ios::binary);
            break;
        case 1:
            fin.open(output_file, std::ios::binary);
            fout.open(input_file, std::ios::binary);
            break;
    }

    if(!fin || !fout) {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    char data[BUFSIZ] = "", out[BUFSIZ] = "";
    data[BUFSIZ - 1] = out[BUFSIZ - 1] = '\0';
    int i = 0, j = 0;
    unsigned char ch;
    while(!fin.eof()){
        fin.read(data, BUFSIZ-1);
        for (int k = 0; k < sizeof(data); k++) {
            i = (i + 1) % 256;
            j = (j + _key[i]) % 256;
            std::swap(_key[i], _key[j]);
            ch = _key[(_key[i] + _key[j]) % 256];
            out[k] = ch ^ data[k];
        }
        fout.write(out, fin.gcount());
    }
    fin.close();
    fout.close();
}

int main() {
    unsigned char const a[] = "1001010";
    encoder o1(a, 7);

    o1.encode("input.txt", "output.txt", 0);

    return 0;
}
