#include <iostream>
#include <cstring>
#include <fstream>

const int max=256;
const int BOX_LEN=256;

char* ByteToHex(const unsigned char* Byte, const int Len);
unsigned char* HexToByte(const char* szHex);
static void swap_byte(unsigned char* a, unsigned char* b);
int GetKey(const unsigned char* pass, int pass_len, unsigned char* out);
int RC4(const unsigned char* data, int data_len, const unsigned char* key, int key_len, unsigned char* out, int* out_len);
char* Encrypt(const char* szSource, const char* szPassWord);
char* Decrypt(const char* szSource, const char* szPassWord);


class encoder {
    unsigned char const* _key;
    int _len;
public:
    encoder(unsigned char const* key, int len);
    ~encoder();
    encoder(const encoder &p);
    void encode(char const* input_file, char const* output_file, bool flag);
    void mutator(unsigned char const* key) { _key = key; }
    void show() { std::cout << _key << ' ' << _len << std::endl; }
};

encoder::encoder(unsigned char const* key, int len) {
    _len = len;
    _key = new unsigned char [_len + 1];
    if(_key == nullptr){
        std::cout << "Memory error" << std::endl;
        exit(1);
    }
    memcpy((void *) _key, key, len + 1);
}

encoder::encoder(const encoder &p) {
    _len = p._len;
    _key = new unsigned char [_len + 1];
    if(_key == nullptr){
        std::cout << "Memory error" << std::endl;
        exit(1);
    }
    memcpy((void *) _key, p._key, p._len + 1);
}

encoder::~encoder() {
    delete [] _key;
    //TODO: close files;
}

void encoder::encode(const char *input_file, const char *output_file, bool flag) {
    if(flag == 1) {
        //TODO Enscrypt
        std::ifstream fin;
        fin.open(input_file);
        if(!fin.is_open()){
            std::cout << "Error opening file" << std::endl;
            exit(1);
        }
        std::basic_ifstream<char> line;
        char* result = nullptr;
        while (std::getline(fin, line)){
            result = Encrypt(line, _key);
        }
        fin.close();
    }
    else if(flag == 0) {
        //TODO Descrypt
        std::ifstream fout(output_file);
        fout.close();
    }
    else {

    }
}

char* ByteToHex(const unsigned char* Byte, const int Len)
{
    if(!Byte)
        return NULL;
    char* tmp = new char[Len * 2 + 1];
    int tmp2;
    for (int i=0;i<Len;i++)
    {
        tmp2 = (int)(Byte[i])/16;
        tmp[i*2] = (char)(tmp2+((tmp2>9)?'A'-10:'0'));
        tmp2 = (int)(Byte[i])%16;
        tmp[i*2+1] = (char)(tmp2+((tmp2>9)?'A'-10:'0'));
    }
    tmp[Len * 2] = '\0';
    return tmp;
}
// Convert the hex string to bytecode, every two hexadecimal characters as a byte
unsigned char* HexToByte(const char* szHex)
{
    int length = strlen(szHex);
    unsigned char* pbBuf = new unsigned char[length/2]; //data buffer
    int tmp1, tmp2;
    for (int i=0;i<length/2;i++)
    {
        tmp1 = (int)szHex[i*2] - (((int)szHex[i*2]>='A')?'A'-10:'0');
        if(tmp1>=16)
            return NULL;
        tmp2 = (int)szHex[i*2+1] - (((int)szHex[i*2+1]>='A')?'A'-10:'0');
        if(tmp2>=16)
            return NULL;
        pbBuf[i] = (tmp1*16+tmp2);
    }
    return pbBuf;
}
//exchange
static void swap_byte(unsigned char* a, unsigned char* b)
{
    unsigned char swapByte;
    swapByte = *a;
    *a = *b;
    *b = swapByte;
}
int GetKey(const unsigned char* pass, int pass_len, unsigned char* out)
{
    int i;
    for(i = 0; i < BOX_LEN; i++)
    {
        out[i] = i;
    }
    int j = 0;
    for(i = 0; i < BOX_LEN; i++)
    {
        j = (pass[i % pass_len] + out[i] + j) % BOX_LEN;
        swap_byte(&out[i], &out[j]);
    }
    return -1;
}
int RC4(const unsigned char* data, int data_len, const unsigned char* key, int key_len, unsigned char* out, int* out_len)
{
    unsigned char* mBox = new unsigned char[BOX_LEN];
    int i=0;
    int x=0;
    int y=0;
    for(int k = 0; k < data_len; k++)
    {
        x = (x + 1) % BOX_LEN;
        y = (mBox[x] + y) % BOX_LEN;
        swap_byte(&mBox[x], &mBox[y]);
        out[k] = data[k] ^ mBox[(mBox[x] + mBox[y]) % BOX_LEN];
    }
    *out_len = data_len;
    delete[] mBox;
    return -1;
}
// Encrypt, return the result of the encryption
char* Encrypt(const char* szSource, const char* szPassWord)
{
    unsigned char* ret = new unsigned char[strlen(szSource)];
    int ret_len = 0;
    if(RC4((unsigned char*)szSource,
           strlen(szSource),
           (unsigned char*)szPassWord,
           strlen(szPassWord),
           ret,
           &ret_len) == NULL)
        return NULL;
    char* ret2 = ByteToHex(ret, ret_len);
    delete[] ret;
    return ret2;
}
// decrypt, return the decryption result
char* Decrypt(const char* szSource, const char* szPassWord)
{
    unsigned char* src = HexToByte(szSource);
    unsigned char* ret = new unsigned char[strlen(szSource) / 2 + 1];
    int ret_len = 0;
    memset(ret, strlen(szSource) / 2 + 1,0);
    if(RC4(src, strlen(szSource) / 2, (unsigned char*)szPassWord, strlen(szPassWord), ret, &ret_len) == NULL)
        return NULL;
    ret[ret_len] = '\0';
    return (char*)ret;
}

int main() {
    unsigned char const a[] = "100";
    encoder o1(a, 3);
    o1.show();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
