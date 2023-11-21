//
// Created by Administrator on 2023/10/31.
//

#ifndef TEST1_H
#define TEST1_H
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

enum mode{
    Encryption = 0, //加密
    Decryption = 1 //解密
};
class caesar{
public:
    string C;
    string M;
    caesar(string str,mode mod){
        if(mod){C=str;}
        else M=str;
    };
    std::string caesarEncrypt(const std::string& M, int n);
    std::string caesarDecrypt(const std::string& C, int n);

};

class vigenere{
public:
    std::string vigenereEncrypt(const std::string& M, const std::string& key);
    std::string vigenereDecrypt(const std::string& C, const std::string& key);
};

class vernamEncrypt{
public:
    std::string vernamEncryptDecrypt(const std::string& str, const std::string& key);
};

class substitution {
public:
    void substitution_(const std::string &str, const std::string &key);
};

#endif //TEST1_H
