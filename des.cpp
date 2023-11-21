//
// Created by Administrator on 2023/11/7.
//
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <bitset>
#include<string>
#include <cstdio>
#include"des.h"

void get_key() {
    for (i = 0; i < 8; i++)
    {
        int a[8] = { 0,0,0,0,0,0,0,0 };
        m = InputKey[i];
        for (j = 0; m != 0; j++)
        {
            a[j] = m % 2;
            m = m / 2;
        }
        for (j = 0; j < 8; j++)
            key[(i * 8) + j] = a[7 - j];
    }

    printf("64bit key: ");
    for (i = 0; i < 64; i++)
        printf("%d", key[i]);
    printf("\n");
}
void encrypt() {
    printf("passage: \n");
    gets_s(MingWen, sizeof(MingWen));
    while (MingWen[0] == '\0')
    {
        printf("wrong\n");
        gets_s(MingWen, sizeof(MingWen));
    }

    i = 0;
    n = 0;
    while (MingWen[i] != '\0')
    {
        n++;
        i++;
    }
    k = n % 8;
    n = (n - 1) / 8 + 1;

    for (l = 0; l < n; l++)
    {
        if (l == (n - 1) && k != 0)
        {
            for (i = 0; i < k; i++)
                target[i] = MingWen[i + (8 * l)];
            for (i = k; i < 8; i++)
                target[i] = ' ';
        }
        else
            for (i = 0; i < 8; i++)
                target[i] = MingWen[i + (8 * l)];

        for (i = 0; i < 8; i++)
        {
            int a[8] = { 0,0,0,0,0,0,0,0 };
            m = target[i];
            for (j = 0; m != 0; j++)
            {
                a[j] = m % 2;
                m = m / 2;
            }
            for (j = 0; j < 8; j++)
                text[(i * 8) + j] = a[7 - j];
        }


        for (i = 0; i < 64; i++)
            text[i] = text_out[l][i] ^ text[i];


        for (i = 0; i < 64; i++)
            text_ip[i] = text[IP[i] - 1];

        for (i = 0; i < 32; i++)
        {
            L0[i] = text_ip[i];
            R0[i] = text_ip[i + 32];
        }

        for (t = 0; t < 16; t++)
        {
            for (i = 0; i < 48; i++)
                RE0[i] = R0[E[i] - 1];


            for (i = 0; i < 48; i++)
                RK[i] = RE0[i] ^ K[t][i];


            for (i = 0; i < 8; i++)
            {
                r[i] = RK[(i * 6) + 0] * 2 + RK[(i * 6) + 5];
                c[i] = RK[(i * 6) + 1] * 8 + RK[(i * 6) + 2] * 4 + RK[(i * 6) + 3] * 2 + RK[(i * 6) + 4];
            }
            RKS[0] = S1[r[0]][c[0]];
            RKS[1] = S2[r[1]][c[1]];
            RKS[2] = S3[r[2]][c[2]];
            RKS[3] = S4[r[3]][c[3]];
            RKS[4] = S5[r[4]][c[4]];
            RKS[5] = S6[r[5]][c[5]];
            RKS[6] = S7[r[6]][c[6]];
            RKS[7] = S8[r[7]][c[7]];

            for (i = 0; i < 8; i++)
            {
                int b[4] = { 0,0,0,0 };
                m = RKS[i];
                for (j = 3; m != 0; j--)
                {
                    b[j] = m % 2;
                    m = m / 2;
                }
                for (j = 0; j < 4; j++)
                    SP[j + (i * 4)] = b[j];
            }

            for (i = 0; i < 32; i++)
                RKSP[i] = SP[P[i] - 1];

            for (i = 0; i < 32; i++)
                Ri[i] = L0[i] ^ RKSP[i];

            for (i = 0; i < 32; i++)
            {
                L0[i] = R0[i];
                R0[i] = Ri[i];
            }
        }

        for (i = 0; i < 32; i++)
            Li[i] = R0[i];
        for (i = 0; i < 32; i++)
            R0[i] = L0[i];
        for (i = 0; i < 32; i++)
            L0[i] = Li[i];

        for (i = 0; i < 32; i++)
            text_end[i] = L0[i];
        for (i = 32; i < 64; i++)
            text_end[i] = R0[i - 32];

        for (i = 0; i < 64; i++)
            text_out[l + 1][IP[i] - 1] = text_end[i];

        for (i = 0; i < 64; i++)
            result[l][i] = text_out[l + 1][i];

    }

    for (j = 0; j < n; j++)
        for (i = 0; i < 16; i++)
            H[i + (j * 16)] = result[j][0 + (i * 4)] * 8 + result[j][1 + (i * 4)] * 4 + result[j][2 + (i * 4)] * 2 + result[j][3 + (i * 4)];

    for (i = 0; i < n * 16; i++)
    {
        if (H[i] < 10)
            MiWen[i] = H[i] + 48;
        else if (H[i] == 10)
            MiWen[i] = 'A';
        else if (H[i] == 11)
            MiWen[i] = 'B';
        else if (H[i] == 12)
            MiWen[i] = 'C';
        else if (H[i] == 13)
            MiWen[i] = 'D';
        else if (H[i] == 14)
            MiWen[i] = 'E';
        else if (H[i] == 15)
            MiWen[i] = 'F';
    }
    for (i = l * 16; i < 208; i++)
        MiWen[i] = '\0';

    printf("after des:\n");
    printf("%s\n", MiWen);
    printf("\n\n");
}

void decrypt() {

    printf("passage: \n");
    gets_s(MiWen, sizeof(MiWen));

    for (i = 0; i < 208; i++)
        H[i] = 0;

    for (i = 0; MiWen[i] != '\0'; i++)
    {
        if (MiWen[i] >= '0' && MiWen[i] <= '9')
            H[i] = MiWen[i] - '0';
        else if (MiWen[i] >= 'A' && MiWen[i] <= 'F')
            H[i] = MiWen[i] - 'A' + 10;
        else if (MiWen[i] >= 'a' && MiWen[i] <= 'f')
            H[i] = MiWen[i] - 'a' + 10;
        else
        {
            printf("OX passage: \n");
            gets_s(MiWen, sizeof(MiWen));
            i = 0;
        }
    }
    n = i;
    if (n % 16 != 0)
    {
        printf("���Ĳ���ȷ,���ĵ��ַ���Ӧ��16�ı�����\n");
        printf("passage: \n");
        gets_s(MiWen, sizeof(MiWen));

        for (i = 0; i < 208; i++)
            H[i] = 0;
        for (i = 0; MiWen[i] != '\0'; i++)
        {
            if (MiWen[i] >= '0' && MiWen[i] <= '9')
                H[i] = MiWen[i] - '0';
            else if (MiWen[i] >= 'A' && MiWen[i] <= 'F')
                H[i] = MiWen[i] - 'A' + 10;
            else if (MiWen[i] >= 'a' && MiWen[i] <= 'f')
                H[i] = MiWen[i] - 'a' + 10;
        }
    }

    for (i = 0; i < n; i++)
    {
        int he[4] = { 0,0,0,0 };
        for (j = 3; H[i] != 0; j--)
        {
            he[j] = H[i] % 2;
            H[i] = H[i] / 2;
        }
        for (j = 0; j < 4; j++)
            C[j + (i * 4)] = he[j];
    }

    k = n / 16;
    for (l = 0; l < k; l++)
    {
        for (i = 0; i < 64; i++)
            text_out[l + 1][i] = C[i + (l * 64)];

        for (i = 0; i < 64; i++)
            text_ip[i] = text_out[l + 1][IP[i] - 1];

        for (i = 0; i < 32; i++)
        {
            L0[i] = text_ip[i];
            R0[i] = text_ip[i + 32];
        }

        for (t = 0; t < 16; t++)
        {
            for (i = 0; i < 48; i++)
                RE0[i] = R0[E[i] - 1];

            for (i = 0; i < 48; i++)
                RK[i] = RE0[i] ^ K[15 - t][i];


            for (i = 0; i < 8; i++)
            {
                r[i] = RK[(i * 6) + 0] * 2 + RK[(i * 6) + 5];
                c[i] = RK[(i * 6) + 1] * 8 + RK[(i * 6) + 2] * 4 + RK[(i * 6) + 3] * 2 + RK[(i * 6) + 4];
            }

            RKS[0] = S1[r[0]][c[0]];
            RKS[1] = S2[r[1]][c[1]];
            RKS[2] = S3[r[2]][c[2]];
            RKS[3] = S4[r[3]][c[3]];
            RKS[4] = S5[r[4]][c[4]];
            RKS[5] = S6[r[5]][c[5]];
            RKS[6] = S7[r[6]][c[6]];
            RKS[7] = S8[r[7]][c[7]];

            for (i = 0; i < 8; i++)
            {
                int b[4] = { 0,0,0,0 };
                m = RKS[i];
                for (j = 3; m != 0; j--)
                {
                    b[j] = m % 2;
                    m = m / 2;
                }
                for (j = 0; j < 4; j++)
                    SP[j + (i * 4)] = b[j];
            }

            for (i = 0; i < 32; i++)
                RKSP[i] = SP[P[i] - 1];

            for (i = 0; i < 32; i++)
                Ri[i] = L0[i] ^ RKSP[i];

            for (i = 0; i < 32; i++)
            {
                L0[i] = R0[i];
                R0[i] = Ri[i];
            }
        }

        for (i = 0; i < 32; i++)
            Li[i] = R0[i];
        for (i = 0; i < 32; i++)
            R0[i] = L0[i];
        for (i = 0; i < 32; i++)
            L0[i] = Li[i];


        for (i = 0; i < 32; i++)
            text_end[i] = L0[i];
        for (i = 32; i < 64; i++)
            text_end[i] = R0[i - 32];

        for (i = 0; i < 64; i++)
            text[IP[i] - 1] = text_end[i];

        for (i = 0; i < 64; i++)
            result[l][i] = text_out[l][i] ^ text[i];

    }

    for (i = 0; i < (n / 16); i++)
        for (j = 0; j < 8; j++)
            M[i][j] = result[i][(j * 8) + 0] * 128 + result[i][(j * 8) + 1] * 64 + result[i][(j * 8) + 2] * 32 + result[i][(j * 8) + 3] * 16 + result[i][(j * 8) + 4] * 8 + result[i][(j * 8) + 5] * 4 + result[i][(j * 8) + 6] * 2 + result[i][(j * 8) + 7];

    printf("After DES\n");
    for (i = 0; i < (n / 16); i++)
        for (j = 0; j < 8; j++)
            printf("%c", M[i][j]);
    printf("\n\n\n");
}

void encryptAnddecrypt() {
    if (choice == 'A' || choice == 'a')
    {
        encrypt();
    }
    else if (choice == 'B' || choice == 'b')
    {
        decrypt();
    }
}

int main()
{
 

    while (flag)
    {
        printf("/*******************\\\n");
        printf("*  des����/des����  *\n");
        printf("* A.����            *\n* B.����            *\n");
        printf("\\*******************/\n");
        scanf("%c", &choice);

        while (choice != 'A' && choice != 'B' && choice != 'a' && choice != 'b')
        {
            printf("���벻�Ϸ�\n");
            scanf("%c", &choice);
        }
        getchar();

      
        printf("������8λ��Կ��\n");
        gets_s(InputKey, sizeof(InputKey));
        while (InputKey[7] == '\0' || InputKey[8] != '\0')
        {
            printf("���������Կλ����������������8λ��Կ��\n");
            gets_s(InputKey, sizeof(InputKey));
        }

        get_key();

        for (i = 0; i < 56; i++) 
            keyPC1[i] = key[PC1[i] - 1];

        for (i = 0; i < 28; i++) 
        {
            A[i] = keyPC1[i];
            B[i] = keyPC1[i + 28];
        }

        for (t = 0; t < 16; t++)
        {
            if (move[t] == 1) 
            {
                n = A[0];
                for (i = 0; i < 27; i++)
                    A[i] = A[i + 1];
                A[27] = n;
                n = B[0];
                for (i = 0; i < 28; i++)
                    B[i] = B[i + 1];
                B[27] = n;
            }
            else
            {
                n = A[0];
                m = A[1];
                for (i = 0; i < 26; i++)
                    A[i] = A[i + 2];
                A[26] = n;
                A[27] = m;
                n = B[0];
                m = B[1];
                for (i = 0; i < 26; i++)
                    B[i] = B[i + 2];
                B[26] = n;
                B[27] = m;
            }

            for (i = 0; i < 28; i++) 
            {
                keyAB[i] = A[i];
                keyAB[i + 28] = B[i];
            }

            for (i = 0; i < 48; i++) 
                K[t][i] = keyAB[PC2[i] - 1];
        }


        for (i = 0; i < 8; i++)
        {
            int a[8] = { 0,0,0,0,0,0,0,0 };
            m = init[i];
            for (j = 0; m != 0; j++)
            {
                a[j] = m % 2;
                m = m / 2;
            }
            for (j = 0; j < 8; j++)
                text_out[0][(i * 8) + j] = a[7 - j];
        }

        encryptAnddecrypt();


        flag = 0;
        printf("continue? \n");
        printf("Y.continue��N.quit ��\n");
        scanf("%c", &choice);

        while (choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n')
        {
            printf("���벻�Ϸ�\n");
            scanf("%c", &choice);
        }
        getchar();
        if (choice == 'Y' || choice == 'y')
            flag = 1;
    }
}