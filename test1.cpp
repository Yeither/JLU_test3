//
// Created by Administrator on 2023/10/31.
//
#include "test1.h"

std::string caesar::caesarEncrypt(const std::string& M, int n) {
    std::string C = M;
    int len = C.length();
    for (int i = 0; i < len; i++) {
        if (isalpha(C[i])) {
            if (islower(C[i])) {
                C[i] = 'a' + (C[i] - 'a' + n) % 26;
            } else {
                C[i] = 'A' + (C[i] - 'A' + n) % 26;
            }
        }
    }
    return C;
}
std::string caesar::caesarDecrypt(const std::string& C, int n) {
    std::string M = C;
    int len = M.length();
    for (int i = 0; i < len; i++) {
        if (isalpha(M[i])) {
            if (islower(M[i])) {
                M[i] = 'a' + (M[i] - 'a' - n + 26) % 26;
            } else {
                M[i] = 'A' + (M[i] - 'A' - n + 26) % 26;
            }
        }
    }
    return M;
}
void run_caesar(){
    int choose;
    string str;
    int n;
    cout<<"-------------------------"<<endl;
    cout<<"*choose mode            *"<<endl;
    cout<<"*1.Encryption           *"<<endl;
    cout<<"*2.Decryption           *"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"you choose:";
    cin>>choose;
    if(choose==1)
    {
        cout<<"passage:";
        cin>>str;
        cout<<"key:";
        cin>>n;
        caesar a(str,Encryption);
        cout<<"result:"<<a.caesarEncrypt(a.M,n)<<endl;
    }
    else if(choose==2)
    {
        cout<<"passage:";
        cin>>str;
        cout<<"key:";
        cin>>n;
        caesar a(str,Decryption);
        cout<<"result:"<<a.caesarDecrypt(a.C,n)<<endl;
    }
    else{cerr<<"wrong number";}
}


std::string vigenere::vigenereEncrypt(const std::string& M, const std::string& key) {
    std::string C = M;
    int len = C.length();
    int keyLen = key.length();
    for (int i = 0; i < len; i++) {
        if (isalpha(C[i])) {
            if (islower(C[i])) {
                C[i] = 'a' + (C[i] - 'a' + (key[i % keyLen] - 'a')) % 26;
            } else {
                C[i] = 'A' + (C[i] - 'A' + (key[i % keyLen] - 'a')) % 26;
            }
        }
    }
    return C;
}
std::string vigenere::vigenereDecrypt(const std::string& C, const std::string& key) {
    std::string M = C;
    int len = M.length();
    int keyLen = key.length();
    for (int i = 0; i < len; i++) {
        if (isalpha(M[i])) {
            if (islower(M[i])) {
                M[i] = 'a' + (M[i] - 'a' - (key[i % keyLen] - 'a') + 26) % 26;
            } else {
                M[i] = 'A' + (M[i] - 'A' - (key[i % keyLen] - 'a') + 26) % 26;
            }
        }
    }
    return M;
}
void run_vigenere(){
    int choose;
    string str;
    string n;
    cout<<"-------------------------"<<endl;
    cout<<"*choose mode            *"<<endl;
    cout<<"*1.Encryption           *"<<endl;
    cout<<"*2.Decryption           *"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"you choose:";
    cin>>choose;
    cout<<"passage:";
    cin>>str;
    cout<<"key:";
    cin>>n;
    vigenere b;
    if(choose==1)
    {
        cout<<"result:"<<b.vigenereEncrypt(str,n)<<endl;
    }
    else if(choose==2)
    {
        cout<<"result:"<<b.vigenereDecrypt(str,n)<<endl;
    }
    else{cerr<<"wrong number";}
}




std::string vernamEncryptDecryptBinary(const std::string& str, const std::string& key) {
    std::string result;
    int strLen = str.length();
    int keyLen = key.length();

    for (int i = 0; i < strLen; i++) {
        char encryptedChar = str[i] ^ key[i % keyLen];
        result += encryptedChar;
    }

    return result;
}


int run_vernam() {
    std::string plaintext ;
    std::string key ;
    cout<<"passage:";
    cin>>plaintext;
    cout<<"key:";
    cin>>key;
    std::string ciphertextBinary = vernamEncryptDecryptBinary(plaintext, key);
    std::cout << "Binary Ciphertext: " << ciphertextBinary << std::endl;
    std::string decryptedTextBinary = vernamEncryptDecryptBinary(ciphertextBinary, key);
    std::cout << "Binary Decrypted Text: " << decryptedTextBinary << std::endl;
    return 0;
}


void substitution::substitution_(const std::string& str, const std::string& key) {
    int cols=key.length();
    vector<char> arr;
    for (auto it:key) {
        arr.push_back(it);
    }
    std::sort(arr.begin(), arr.end());
    int rows=0;
    while(cols*rows<str.length())rows++;
//    char output[rows][cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(i*cols+key.find(arr[j])<str.length())
            cout<<str[i*cols+key.find(arr[j])];
        }
    }cout<<endl;
}
void run_substitution(){
    int choose;
    string str;
    string n;
    cout<<"passage:";
    cin>>str;
    cout<<"key:";
    cin>>n;
    substitution b;
    cout<<"result:";
    b.substitution_(str,n);
}

int main(){
while(1)
    run_vernam();
}
