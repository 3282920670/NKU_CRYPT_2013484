// DES_CRYPTO.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"des_test_data.h"
using namespace std;

int* child_key[16];//储存子密钥
const int IP_table[64] = { 
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7 };

const int IP_1_table[64] = { 
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};
const int LS_table[16] = {
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
const int PC_1_table[56] = {
    57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4 };
const int PC_2_table[48] = {
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32 };
const int E_table[48] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1 };
const int S_Box_table[32][16] = { 
14, 4, 13, 1, 2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
    0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
    4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
    //S2盒 
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
     3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
     0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
    //S3盒 
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
     1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
     //S4盒 
      7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
     13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
     10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
     3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
     //S5盒
     2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
     14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
     4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
     11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
     //S6盒
     12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
     10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
     9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,6,
     4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
     //S7盒
     4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
     13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
     1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
     6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
     //S8盒
     13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
     1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
     7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
     2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 };
const int P_table[32] =
{
    16, 7, 20, 21,
    29, 12, 28, 17,
    1,  15, 23, 26,
    5,  18, 31, 10,
    2,  8, 24, 14,
    32, 27, 3,  9,
    19, 13, 30, 6,
    22, 11, 4,  25
};

int* int2dec(int a)//a是int型，比如140
{
    int* b = new int[2];
    if (!a)
        b[0] = b[1] = 0;
    else
    {
        b[1] = a % 16;
        b[0] = a / 16;
    }
    //cout << a << " to hex is :";
    //for (int i = 0; i < 2; i++)
    //    cout << b[i] << " ";//b[0]=8,b[1]=12,8x16+12=140
    //cout << endl;
    return b;
}

void DEC2BIN(int a, int* b, int k)//将10进制数转换成2进制数，并用长度为4的int数组保存
{
    for (int i = 0; i < 8; i++)
        b[k + i] = 0;
    int* c = new int[2];
    c = int2dec(a);
    //for (int i = 0; i < 2; i++)
    //    cout << c[i] << " ";
    //cout << endl;
    int temp;
    for (int i = 0; i < 2; i++)
    {
        if (!i)
            temp = k + 3;
        else
            temp = k + 7;
		while (c[i])
		{
			int j = c[i] % 2;
			c[i] /= 2;
			b[temp--] = j;
		}
    }
}

int* IP_replace(int* text)//IP置换
{
    int* temp = new int[64];
    for (int i = 0; i < 64; i++)
    {
        temp[i] = text[IP_table[i] - 1];
    }
    return temp;
}

int* IP_1_replace(int* text)//IP逆置换
{
    int* temp = new int[64];
    for (int i = 0; i < 64; i++)
    {
        temp[i] = text[IP_1_table[i] - 1];
    }
    return temp;
}

int* PC_1_replace(int* text)//压缩置换PC-1
{
    int k = 0;
    int* temp = new int[56];
	for (int i = 0; i < 56; i++)
	{
		temp[i] = text[PC_1_table[i] - 1];
	}
    return temp;
}

int* PC_2_replace(int* text)//压缩置换PC-2
{
    int* temp = new int[48];
    for (int i = 0; i < 48; i++)
    {
        temp[i] = text[PC_2_table[i] - 1];
    }
    return temp;
}

void LS(int* text,int K_num)//循环左移,K_num是第几个子密钥
{
    for (int j = 0; j < LS_table[K_num]; j++)
    {
        int* L = &text[0];
        int* R = &text[28];
        int temp1_1, temp1_2;
        temp1_1 = L[0], temp1_2 = R[0];
        for (int i = 0; i < 27; i++)
        {
            L[i] = L[i + 1];
            R[i] = R[i + 1];
        }
        L[27] = temp1_1;
        R[27] = temp1_2;
    }
}

int* f(int* R, int* K)
{
    int* temp = new int[48];
    for (int i = 0; i < 48; i++)
    {
		temp[i] = R[E_table[i] - 1];//E拓展
		if (temp[i] == K[i])//E拓展后与子密钥异或
			temp[i] = 0;
		else
			temp[i] = 1;
    }
    /*cout << "R thourgh E_replace and xor with K: ";*/
    //for (int i = 0; i < 48; i++)
    //{
    //    if (i % 6 == 0)
    //        cout << endl;
    //    cout << temp[i] << " ";
    //}
    //cout << endl << "num: ";
    int* tmp = new int[32];
    for (int i = 0; i < 32; i++)
        tmp[i] = 0;
    for (int s = 0; s < 8; s++)//s代表盒号
    {
        int k = s * 6;
        int i= temp[k] * 2 + temp[k + 5];//i，j用来定位在盒里的坐标s[i][j]
        int j = temp[k + 1] * 8 + temp[k + 2] * 4 + temp[k + 3] * 2 + temp[k + 4];
        int num = S_Box_table[s * 4 + i][j];
        int N = s * 4 + 3;
        //cout << num << " ";
        while (num)
        {
            int i = num % 2;
            num /= 2;
            tmp[N--] = i;
        }
    }
    //cout << endl;
    //cout << "R thourgh S_Box_replace: ";
    //for (int i = 0; i < 32; i++)
    //{
    //    if (i % 4 == 0)
    //        cout << endl;
    //    cout << tmp[i] << " ";
    //}
    //cout << endl;
    int* tmpp = new int[32];
    for (int i = 0; i < 32; i++)
    {
        tmpp[i] = tmp[P_table[i] - 1];
    }
    //cout << "R thourgh f: ";
    //for (int i = 0; i < 32; i++)
    //{
    //    if (i % 4 == 0)
    //        cout << endl;
    //    cout << tmpp[i] << " ";
    //}
    //cout << endl;
    return tmpp;
}

int main()
{
    //验证16进制转2进制
    //int2dec(8);
    //int* a = new int[8];
    //DEC2BIN((int)cases[0].key[0], a, 0);
    //for (int i = 0; i < 8; i++)
    //    cout << a[i] << " ";


	//int k = 0;
	//int* key = new int[64];
	//int* plaintext = new int[64];
	//int* ciphertext = new int[64];
	//for (int j = 0; j < 8; j++)
 //   {
 //       DEC2BIN((int)cases[0].key[j], key, k);
 //       DEC2BIN((int)cases[0].txt[j], plaintext, k);
 //       k += 8;
 //   }
 //   //生成子密钥
 ////   cout << "key: ";
	////for (int i = 0; i < 64; i++)
 ////   {
 ////       if (i % 8 == 0)
 ////           cout << endl;
 ////       cout << key[i] << " ";
 ////   }
 ////   cout << endl;
 ////   cout << "plaintext: ";
 ////   for (int i = 0; i < 64; i++)
 ////   {
 ////       if (i % 8 == 0)
 ////           cout << endl;
 ////       cout << plaintext[i] << " \t";
 ////   }
 ////   cout << endl;
 //   int* temp = PC_1_replace(key);//压缩置换1
 //   //for (int i = 0; i < 56; i++)
 //   //{
 //   //    if (i % 7 == 0)
 //   //        cout << endl;
 //   //    cout << temp[i] << " ";
 //   //}
 //   //cout << endl;
 //   for (int i = 0; i <16; i++)
 //   {
 //       LS(temp, i);//循环左移
 //       //cout << "K after LS: ";
 //       //for (int i = 0; i < 56; i++)
 //       //{
 //       //    if (i % 7 == 0)
 //       //        cout << endl;
 //       //    cout << temp[i] << " ";
 //       //}
 //       //cout << endl;
 //       child_key[i] = PC_2_replace(temp);//压缩置换2
 //       //cout << "K" << i + 1 << ":";
 //       //for (int j = 0; j < 48; j++)
 //       //{
 //       //    if (j % 6 == 0)
 //       //        cout << endl;
 //       //    cout << child_key[i][j] << " ";
 //       //}
 //       //cout << endl << endl;
 //   }
 //   //for (int i = 0; i < 56; i++)
 //   //{
 //   //    if (i % 7 == 0)
 //   //        cout << endl;
 //   //    cout << temp[i] << " \t";
 //   //}
 //   //cout << endl;
 //   plaintext = IP_replace(plaintext);
 //   //cout << "plaintext through IP_replace: ";
 //   //for (int i = 0; i < 64; i++)
 //   //{
 //   //    if (i % 8 == 0)
 //   //        cout << endl;
 //   //    cout << plaintext[i] << " \t";
 //   //}
 //   //cout << endl << endl;
 //   int* L = &plaintext[0];
 //   //cout << "L0: ";
 //   //for (int i = 0; i < 32; i++)
 //   //{
 //   //    cout << L[i] << " ";
 //   //}
 //   //cout << endl;
 //   int* R = &plaintext[32];
 //   //cout << "R0: ";
 //   //for (int i = 0; i < 32; i++)
 //   //{
 //   //    cout << R[i] << " ";
 //   //}
 //   //cout << endl;
 //   for (int k = 0; k < 16; k++)
 //   {
 //       cout << "L" << k << ": ";
 //       for (int i = 0; i < 32; i++)
 //       {
 //           cout << L[i] << " ";
 //       }
 //       cout << endl;
 //       cout << "R" << k << ": ";
 //       for (int i = 0; i < 32; i++)
 //       {
 //           cout << R[i] << " ";
 //       }
 //       cout << endl;
 //       int* tmpp = f(R, child_key[k]);//f(Rk,Kk+1)
 //       //cout << "f(R"<<k<<", K" << k + 1 << "): ";
 //       //for (int i = 0; i < 32; i++)
 //       //{
 //       //    cout << tmpp[i] << " ";
 //       //}
 //       //cout << endl;
 //       //cout << "R0.5" << ": ";
 //       //for (int i = 0; i < 32; i++)
 //       //{
 //       //    cout << R[i] << " ";
 //       //}
 //       //cout << endl;
 //       //cout << "L" << k << " throuth xor with f(R" << k << ", K" << k + 1 << "): ";
 //       //cout << "L0.5" << ": ";
 //       cout << "R" << k <<" K"<<k+1<< ": ";
 //       for (int i = 0; i < 32; i++)
 //       {
 //           if (tmpp[i] == L[i])//Ri=Li-1+f(Ri-1,Ki)
 //               L[i] = 0;
 //           else
 //               L[i] = 1;
 //           //cout << L[i] << " ";
 //       }
 //       cout << endl;
 //       //cout << "plaintext: ";
 //       //for (int i = 0; i < 64; i++)
 //       //{
 //       //    if (i % 8 == 0)
 //       //        cout << endl;
 //       //    cout << plaintext[i] << " \t";
 //       //}
 //       //cout << endl << endl;
 //       int* temp = L;
 //       L = R;
 //       R = temp;
 //       //cout << "L" << k + 1 << ": ";
 //       //for (int i = 0; i < 32; i++)
 //       //{
 //       //    cout << L[i] << " ";
 //       //}
 //       //cout << endl;
 //       //cout << "R" << k + 1 << ": ";
 //       //for (int i = 0; i < 32; i++)
 //       //{
 //       //    cout << R[i] << " ";
 //       //}
 //       //cout << endl;
 //   }
 //   cout << "plaintext: ";
 //   for (int i = 0; i < 64; i++)
 //   {
 //       if (i % 8 == 0)
 //           cout << endl;
 //       cout << plaintext[i] << " \t";
 //   }
 //   cout << endl << endl;
 //   for (int i = 0; i < 32; i++)
 //   {
 //       swap(L[i], R[i]);
 //   }
	////cout << "plaintext: ";
	////for (int i = 0; i < 64; i++)
	////{
	////	if (i % 8 == 0)
	////		cout << endl;
	////	cout << plaintext[i] << " \t";
	////}
	////cout << endl << endl;
 //   ciphertext = IP_1_replace(plaintext);
 //   for (int i = 0; i < 64; i++)
 //   {
 //       if (i % 8 == 0)
 //           cout << endl;
 //       cout << ciphertext[i] << " \t";
 //   }
 //   cout << endl;

    //验证IP置换和IP逆置换
    //int cipher[64] = { 0, 1 ,0 ,1 ,1 ,0 ,1 ,0 ,
    //               0 ,0 ,0 ,1 ,1 ,1 ,1 ,0 ,
    //               0 ,1 ,0 ,1 ,0 ,0 ,1 ,0 ,
    //               0 ,0 ,1 ,0 ,1 ,0 ,0 ,0,1, 0, 1, 1, 0, 0, 1, 1,
    //               0, 1, 1, 0, 0, 1, 1, 1,
    //               1, 1, 0, 1, 1, 1, 1, 0,
    //               1, 1, 0, 0, 1, 0, 0, 1 
    //                };
    ////ciphertext = IP_replace(ciphertext);
    //for (int i = 0; i < 64; i++)
    //{
    //    //if (i % 8 == 0)
    //    //    cout << endl;
    //    //cout << ciphertext[i]<< " \t";
    //    ciphertext[i] = cipher[i];
    //}
    //cout << endl;
    //ciphertext = IP_1_replace(ciphertext);
    //for (int i = 0; i < 64; i++)
    //{
    //    if (i % 8 == 0)
    //        cout << endl;
    //    cout << ciphertext[i] << " \t";
    //}
    //cout << endl;
    //int* L = &ciphertext[0];
    //int* R = &ciphertext[32];
    //for (int i = 0; i < 32; i++)
    //    cout << L[i] << " ";
    //cout << endl;
    //for (int i = 0; i < 32; i++)
    //    cout << R[i] << " ";

    //验证压缩置换1
    /*for (int i = 0; i < 64; i++)
        key[i] = i + 1;
	for (int i = 0; i < 64; i++)
	{
		if (i % 8 == 0)
			cout << endl;
		cout << key[i] << " \t";
	}
	cout << endl;
    int* temp = PC_1_replace(key);
	for (int i = 0; i < 56; i++)
	{
		if (i % 7 == 0)
			cout << endl;
		cout << temp[i] << " \t";
	}
	cout << endl;*/
    
    //验证压缩置换2
    /*int* tmp = new int[56];
    for (int i = 0; i < 56; i++)
        tmp[i] = i + 1;
	for (int i = 0; i < 56; i++)
	{
		if (i % 7 == 0)
			cout << endl;
		cout << tmp[i] << " \t";
	}
	cout << endl;
    int* temp = PC_2_replace(tmp);
    for (int i = 0; i < 48; i++)
    {
        if (i % 6 == 0)
            cout << endl;
        cout << temp[i] << " \t";
    }
    cout << endl;*/
    
    //验证循环左移
    //for (int i = 0; i < 64; i++)
    //    key[i] = i + 1;
    //for (int i = 0; i < 64; i++)
    //{
    //    if (i % 8 == 0)
    //        cout << endl;
    //    cout << key[i] << " \t";
    //}
    //cout << endl;
    //int* temp = PC_1_replace(key);
    //for (int i = 0; i < 56; i++)
    //{
    //    if (i % 7 == 0)
    //        cout << endl;
    //    cout << temp[i] << " \t";
    //}
    //cout << endl;
    //for (int i = 0; i < 16; i++)
    //{
    //    LS(temp, i);
    //    cout << endl;
    //    cout << "K" << i + 1;
    //    for (int i = 0; i < 56; i++)
    //    {
    //        if (i % 7 == 0)
    //            cout << endl;
    //        if (i == 28)
    //            cout << endl;
    //        cout << temp[i] << " \t";
    //    }
    //    cout << endl;
    //}

    //验证E拓展
    /*int* R = new int[32];
    for (int i = 0; i < 32; i++)
        R[i] = i + 1;
    int n = 0;
    int* temp = new int[48];
    for (int i = 0; i < 8; i++)
    {
	    for (int j = 0; j < 6; j++)
	    {
		    temp[n] = R[E_table[i][j] - 1];
		    n++;
	    }
    }
    for (int i = 0; i < 48; i++)
    {
        if (i % 6 == 0)
            cout << endl;
        cout << temp[i] << " ";
    }*/

    //验证S盒
    /*int* temp = new int[48];
    for (int i = 0; i < 48; i++)
        temp[i] = 1;
    int* tmp = new int[32];
    for (int i = 0; i < 32; i++)
        tmp[i] = 0;
    for (int s = 0; s < 8; s++)//s代表盒号
    {
        int k = s * 6;
        int i = temp[k] * 2 + temp[k + 5];//i，j用来定位在盒里的坐标s[i][j]
        //cout << "i: " << i << endl;
        int j = temp[k + 1] * 8 + temp[k + 2] * 4 + temp[k + 3] * 2 + temp[k + 4];
        //cout << "j: " << j << endl;
        int num = S_Box_table[s * 4 + i][j];
        //cout << "num: " << num << endl;
        int N = s * 4 + 3;
        while (num)
        {
            int i = num % 2;
            num /=2;
            tmp[N] = i;
            N--;
        }
    }
    for (int i = 0; i < 32; i++)
    {
        if (i % 4 == 0)
            cout << endl;
        cout << tmp[i] << " ";
    }*/

    //验证f
    //int* R = new int[32];
    //int* K = new int[48];
    //for (int i = 0; i < 32; i++)
    //{
    //    if (i % 4 == 0)
    //    {
    //        R[i] = 1;
    //        cout << endl;
    //    }
    //    else
    //        R[i] = 0;
    //    cout << R[i] << " ";
    //}
    //cout << endl;
    //for (int i = 0; i < 48; i++)
    //{
    //    if (i % 6 == 0)
    //    {
    //        K[i] = 1;
    //        cout << endl;
    //    }
    //    else
    //        K[i] = 0;
    //    cout << K[i] << " ";
    //}
    //cout << endl;
    //int* tmpp = f(R, K);
    //for (int i = 0; i < 32; i++)
    //{
    //    if (i % 4 == 0)
    //        cout << endl;
    //    cout << tmpp[i] << " ";
    //}
    //验证P置换
    //int* temp = new int[48];
    //for (int i = 0; i < 48; i++)
    //    temp[i] = i + 1;
    //int* tmpp = new int[32];
    //for (int i = 0; i < 32; i++)
    //{
    //    tmpp[i] = temp[P_table[i] - 1];
    //}
    //for (int i = 0; i < 32; i++)
    //{
    //    if (i % 4 == 0)
    //        cout << endl;
    //    cout << tmpp[i] << " ";
    //}

    int key0[64], txt0[64], out0[64];//保存第0组数据，用于后续雪崩检验
    cout << "num" << "\tmode" << endl;
    for (int i = 0; i < 20; i++)
    {
        int k = 0;
        int* key = new int[64];
        int* txt = new int[64];
        int* output = new int[64];
        int* out = new int[64];

        
		//将密钥和明文转换成2进制，共64位，存储在长位64的int型数组里面
		for (int j = 0; j < 8; j++)
		{
			DEC2BIN((int)cases[i].key[j], key, k);
			DEC2BIN((int)cases[i].txt[j], txt, k);
			DEC2BIN((int)cases[i].out[j], out, k);
			k += 8;
		}
		//cout << "key" << i << ": ";
		//for (int i = 0; i < 64; i++)
		//{
		//	if (i % 8 == 0)
		//		cout << endl;
		//	cout << key[i] << " ";
		//}
		//cout << endl;
		//cout << "txt" << i << ": ";
		//for (int i = 0; i < 64; i++)
		//{
		//	if (i % 8 == 0)
		//		cout << endl;
		//	cout << txt[i] << " ";
		//}
		//cout << endl;
  //      cout << "out" << i << ": ";
  //      for (int i = 0; i < 64; i++)
  //      {
  //          if (i % 8 == 0)
  //              cout << endl;
  //          cout << out[i] << " ";
  //      }
  //      cout << endl;
        if (i == 0)
        {
            for (int i = 0; i < 64; i++)
            {
                //if (i % 8 == 0)
                //    cout << endl;
                //cout << txt[i] << " ";
                key0[i] = key[i];
                txt0[i] = txt[i];
            }
        }
        //cout << endl;
		int* temp = PC_1_replace(key);//压缩置换1
		for (int i = 0; i < 16; i++)
		{
			LS(temp, i);//循环左移
			child_key[i] = PC_2_replace(temp);//压缩置换2
		}
		txt = IP_replace(txt);
		int* L = &txt[0];
		int* R = &txt[32];
        int j;
        if (cases[i].mode)
        {
            j = 0;
        }
        else
            j = 15;
        for (int k = 0; k < 16; k++)
        {
            int* tmpp;
            if (cases[i].mode)
            {
				tmpp = f(R, child_key[j++]);//加密，子密钥正序使用0-15
            }
            else
				tmpp = f(R, child_key[j--]);//解密，子密钥逆序使用15-0
            for (int i = 0; i < 32; i++)
            {
                if (tmpp[i] == L[i])//Ri=Li-1+f(Ri-1,Ki)
                    L[i] = 0;
                else
                    L[i] = 1;
            }
            int* temp = L;
            L = R;
            R = temp;
        }
		for (int i = 0; i < 32; i++)//左右交换
		{
			swap(L[i], R[i]);
		}
		output = IP_1_replace(txt);
        if (i == 0)
        {
            for (int i = 0; i < 64; i++)
            {
                //if (i % 8 == 0)
                //	cout << endl;
                //cout << output[i] << " ";
                out0[i] = output[i];
            }
        }
        //cout << "output" << i << ": ";
        //for (int i = 0; i < 64; i++)
        //{
        //    if (i % 8 == 0)
        //    	cout << endl;
        //    cout << output[i] << " ";
        //}
        //cout << endl;
        bool t = true;
        for (int k = 0; k < 64; k++)
        {
            if (out[k] != output[k])
            {
                t = false;
                break;
            }
        }
        if (t)
            cout << cases[i].num << " \t" << cases[i].mode << "  \t成功" << endl;
        else
            cout << cases[i].num << " \t" << cases[i].mode << "  \t失败" << endl;
    }

    //测试雪崩效应，选取第一组数据
    //cout << "key: ";
    //for (int i = 0; i < 64; i++)
    //{
    //    if (i % 8 == 0)
    //        cout << endl;
    //    cout << key0[i] << " ";
    //}
    //cout << endl;
    int num = 0;
    for (int i = 0; i < 16; i++)
    {
        if (i % 8 == 0)
            num = 0;
        int* testkey = new int[64];
        int* testtxt = new int[64];
        int* testout = new int[64];
        //if (i == 8)
        //{
        //    cout << "txt: ";
        //    for (int i = 0; i < 64; i++)
        //    {
        //        if (i % 8 == 0)
        //            cout << endl;
        //        cout << txt0[i] << " ";
        //    }
        //    cout << endl;
        //}
        if (i < 8)
        {
            for (int j = 0; j < 64; j++)
            {
                if (j == i * 8)
                {
                    testkey[j] = (key0[j] + 1) % 2;
                }
                else
                {
                    testkey[j] = key0[j];
                }
                testtxt[j] = txt0[j];
            }
        }
        else
        {
            for (int j = 0; j < 64; j++)
            {
                if (j == i * 4)
                {
                    testtxt[j] = (txt0[j] + 1) % 2;
                }
                else
                {
                    testtxt[j] = txt0[j];
                }
                testkey[j] = key0[j];
            }
        }
  //      cout << "key" << i << ": ";
		//for (int i = 0; i < 64; i++)
		//{
		//	if (i % 8 == 0)
		//		cout << endl;
		//	cout << testkey[i] << " ";
		//}
		//cout << endl;
  //      cout << "txt" << i << ": ";
		//for (int i = 0; i < 64; i++)
		//{
		//	if (i % 8 == 0)
		//		cout << endl;
		//	cout << testtxt[i] << " ";
		//}
		//cout << endl;
        int* temp = PC_1_replace(testkey);//压缩置换1
        for (int i = 0; i < 16; i++)
        {
            LS(temp, i);//循环左移
            child_key[i] = PC_2_replace(temp);//压缩置换2
        }
        testtxt = IP_replace(testtxt);
        int* L = &testtxt[0];
        int* R = &testtxt[32];
        for (int k = 0; k < 16; k++)
        {
            int* tmpp;
			tmpp = f(R, child_key[k++]);//加密，子密钥正序使用0-15
            for (int i = 0; i < 32; i++)
            {
                if (tmpp[i] == L[i])//Ri=Li-1+f(Ri-1,Ki)
                    L[i] = 0;
                else
                    L[i] = 1;
            }
            int* temp = L;
            L = R;
            R = temp;
        }
        for (int i = 0; i < 32; i++)//左右交换
        {
            swap(L[i], R[i]);
        }
        testout = IP_1_replace(testtxt);
        //cout << "out" << i << ": ";
        //for (int i = 0; i < 64; i++)
        //{
        //    if (i % 8 == 0)
        //        cout << endl;
        //    cout << testout[i] << " ";
        //}
        //cout << endl;
        for (int i = 0; i < 64; i++)
        {
            if (out0[i] != testout[i])
                num++;
        }
        //cout << "num: " << num << endl;
        if (i == 7)
            cout << "The average of out changed for changed 1bit of key is " << float(num / 8) << endl;
        if (i == 15)
            cout << "The average of out changed for changed 1bit of txt is " << float(num / 8) << endl;
    }
    
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              `
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
