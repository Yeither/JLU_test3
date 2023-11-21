//
// Created by Administrator on 2023/11/21.
//
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
// 求最大公约数
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
// 检查一个数是否为素数
bool isPrime(int num) {
    if (num <= 1)
        return false;

    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

// 生成随机素数
int generateRandomPrime() {
    int prime;
    do {
        prime = rand() % 100 + 1; // 生成1到100之间的随机数
    } while (!isPrime(prime));

    return prime;
}

// 求模反元素
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}
// 加密运算
int encrypt(int message, int e, int n) {
    int cipher = 1;
    for (int i = 0; i < e; i++) {
        cipher = (cipher * message) % n;
        //std::cout<<"cipher: "<<cipher<<std::endl;
    }
    return cipher;
}

// 解密运算
int decrypt(int cipher, int d, int n) {
    int message = 1;
    for (int i = 0; i < d; i++) {
        message = (message * cipher) % n;
    }
    return message;
}
// 生成随机互质数
int findCoprime(int n) {
    while (true) {
        int e = rand() % (n - 2) + 2; // 生成2到n-1之间的随机数
        int gcd1 = gcd(e, n);
        if (gcd1 == 1) {
            return e;
        }
    }
}
void run() {
    srand(time(0)); // 使用当前时间作为随机数种子

    int p, q, n, phi, e, d;
    int message, encrypted, decrypted;

    // 步骤一：生成密钥对
    std::cout << "Generating random prime numbers (p and q)..." << std::endl;
    p = generateRandomPrime();
    q = generateRandomPrime();
    std::cout << "p=" << p<<";q="<<q<<std::endl;
    n = p * q;
    phi = (p - 1) * (q - 1);

    e=findCoprime(phi);
    std::cout << "auto random e=" << e<<std::endl;

    // 步骤二：计算私钥 d
    d = modInverse(e, phi);

    std::cout << "Public key (n, e): (" << n << ", " << e << ")" << std::endl;
    std::cout << "Private key (n, d): (" << n << ", " << d << ")" << std::endl;

    // 步骤三：加密和解密
    std::cout << "Enter a message to encrypt: ";
    std::cin >> message;

    encrypted = encrypt(message, e, n);
    decrypted = decrypt(encrypted, d, n);

    std::cout << "Encrypted message: " << encrypted << std::endl;
    std::cout << "Decrypted message: " << decrypted << std::endl;

}

int main(){
    while (1){
        std::string s;
        std::cout << "Continue?(y or else)";
        std::cin>>s;
        if(s=="y")
            run();
        else
            return 0;
    }

}