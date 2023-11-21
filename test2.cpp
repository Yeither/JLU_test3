//
// Created by Administrator on 2023/10/31.
//
#include "test2.h"

std::bitset<64> DES::generateKey() {
//    std::srand(std::time(nullptr));  // 使用当前时间初始化随机数生成器
//
//    for (int i = 0; i < 64; i += 8) {
//        int count = 0;
//        for (int j = 0; j < 7; ++j) {
//            bool bit = std::rand() % 2;
//            KEY[i + j] = bit;
//            count += bit;
//        }
//        // 设置奇校验位
//        KEY[i + 7] = count % 2 ? 0 : 1;
//    }
vector<int>tmp=
    {0,1,1,1,0,1,0,0,
     1,0,1,1,0,1,0,1,
     1,1,0,1,1,0,1,1,
     0,0,1,0,1,1,1,0,
     0,1,0,1,0,1,0,1,
     1,0,1,0,0,1,0,1,
     1,0,0,1,0,1,0,1,
     0,1,1,0,0,1,1,0};
    for (int i = 0; i < 64; ++i) {
        KEY[i]=tmp[i];
    }
     return KEY;
}

void DES::leftShift(std::bitset<56>& bits, int shift) {
    std::bitset<56> temp = bits;

    for(int i = 0; i < 56; ++i) {
        bits[i] = temp[(i + shift) % 56];
    }
}

std::bitset<28> DES::leftShift(std::bitset<28>& bits, int shift) {
    std::bitset<28> temp ;

    for(int i = 0; i < 28; ++i) {
        temp[i] = bits[(i + shift) % 28];
    }
    return temp;
}

void DES::getSubkey_init(){
    std::bitset<56> output;
        for (int i = 0; i < 56; ++i) {
            output[i] = KEY[PC1[i]];
        }
        for (int i = 0; i < 28; ++i) {
            C[0][i] = output[i];
        }
        for (int i = 28; i < 56; ++i) {
            D[0][i] = output[i];
        }
};

void DES::getSubkey(int count){
    C[count+1]=leftShift(C[count],SHIFT[count]);
    D[count+1]=leftShift(D[count],SHIFT[count]);
}

void DES::test2_1(){
    generateKey();
    getSubkey_init();
    for (int i = 0; i < 16; ++i) {
        getSubkey(i);
        std::bitset<56> output;
        for (int j = 0; j < 28; ++j) {
            output[j]=C[i][j];
            output[j+28]=D[i][j];
        }
        for (int h = 0; h < 48; ++h) {
            K[i][h] = output[PC2[h]];
        }
        std::cout<<"key"<<i+1<<": "<<K[i]<<endl;
    }
}

vector<int> DES::binary(int x){
vector<int>temp;
    while(x > 0) {
        temp.push_back(x % 2);
        x = x / 2;
    }
    return temp;
}

void DES::SP_box(int count){
    std::bitset<48> temp;
    for (int i = 0; i < 48; ++i) {
        temp[i] = L[count][E[i]];
    }
    temp=temp^K[count];
    for (int i = 0; i < 8; ++i) {
        int rows=2*temp[0+i*6]+temp[5+i*6];
        int cols=8*temp[1+i*6]+4*temp[2+i*6]+2*temp[3+i*6]+temp[4+i*6];
        vector<int> binary = DES::binary(S[i][rows*16+cols]);
        for (int j = 0; j < binary.size(); ++j) {
            R[count+1][i*4+j]=binary[j];
        }
    }
    bitset<32>temp_bit=R[count+1];
    for (int i = 0; i < 32; ++i) {
        R[count+1][i]=temp_bit[P[i]];
    }
    L[count+1]=R[count];
}
void DES::SP_box2(int count){
    std::bitset<48> temp;
    for (int i = 0; i < 48; ++i) {
        temp[i] = L[count][E[i]];
    }
    temp=temp^K[16-count];
    for (int i = 0; i < 8; ++i) {
        int rows=2*temp[0+i*6]+temp[5+i*6];
        int cols=8*temp[1+i*6]+4*temp[2+i*6]+2*temp[3+i*6]+temp[4+i*6];
        vector<int> binary = DES::binary(S[i][rows*16+cols]);
        for (int j = 0; j < binary.size(); ++j) {
            R[count+1][i*4+j]=binary[j];
        }
    }
    bitset<32>temp_bit=R[count+1];
    for (int i = 0; i < 32; ++i) {
        R[count+1][i]=temp_bit[P[i]];
    }
    L[count+1]=R[count];
}

bitset<64> DES::test2_2(){
    bitset<64>temp;
    for (int i = 0; i < 64; ++i) {
        temp[i]=CIPHERTEXT[PC[i]];
    }
    for (int i = 0; i < 32; ++i) {
        L[0][i]=temp[i+32];
        R[0][i]=temp[i];
    }
    for (int i = 0; i < 16; ++i) {
        SP_box(i);
    }

    bitset<64>result,final;
    for (int i = 0; i < 16; ++i) {
        result[i+32]=L[16][i];
        result[i]=R[16][i];
    }
    for (int i = 0; i < 64; ++i) {
        final[i]=result[PC_1[i]];
    }
    cout<<"oringe: ";
    for(auto it:CIPHERTEXT)cout<<it;
    cout<<endl<<"final : "<<final<<endl;
    return final;
}

void DES::test2_3(bitset<64>final){
    bitset<64>temp;
    for (int i = 0; i < 64; ++i) {
        temp[i]=final[PC_1[i]];
    }
    for (int i = 0; i < 32; ++i) {
        L[0][i]=temp[i+32];
        R[0][i]=temp[i];
    }
    for (int i = 0; i < 16; ++i) {
        SP_box2(i);
    }

    bitset<64>result,final1;
    for (int i = 0; i < 16; ++i) {
        result[i+32]=L[16][i];
        result[i]=R[16][i];
    }
    for (int i = 0; i < 64; ++i) {
        final1[i]=result[PC[i]];
    }
    cout<<"final1: "<<final1;
}

int main(){
    DES d;bitset<64>final;
    d.test2_1();
    final=d.test2_2();
    d.test2_3(final);
}

