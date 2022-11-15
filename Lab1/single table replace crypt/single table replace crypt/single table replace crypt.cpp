// single table replace crypt.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string.h>
using namespace std;

int* build_table(char* inputtext)
{
    int len = strlen(inputtext);
    if (len > 26)
    {
        inputtext[26] = '\0';
        len = 26;
    }
    int* temp = new int[26];
    int j = 0;
    temp[j] = -1;
    for (int i = 0; i < len; i++)
    {
        if (inputtext[i] >= 'A' && inputtext[i] <= 'Z')
        {
            inputtext[i] = inputtext[i] - 'A' + 'a';
        }
        if (inputtext[i] >= 'a' && inputtext[i] <= 'z')
        {
            bool t = true;
            int n = inputtext[i] - 'a';
            for (int k = 0; k <= j; k++)
            {
                if (temp[k] == n)
                {
                    t = false;
                    break;
                }
            }
            if (t)
            {
                temp[j] = n;
                j++;
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        bool t = true;
        for (int k = 0; k < j; k++)
        {
            if (temp[k] == i)
            {
                t = false;
                break;
            }
        }
        if (!t)
            continue;
        else
        {
            temp[j] = i;
            j++;
        }
    }
    //for (int i = 0; i < 26; i++)
    //{
    //    cout << temp[i] << " ";
    //}
    return temp;
}

int retnum(int* replacetable, int num)
{
    for (int i = 0; i < 26; i++)
    {
        if (replacetable[i] == num)
        {
            return i;
        }
    }
}

class table_replace_crypt
{
private:
    int* replacetable = new int[26];
public:
    table_replace_crypt()
    {
        for (int i = 0; i < 26; i++)
        {
            replacetable[i] = i;
        }
    }
    table_replace_crypt(char* input)
    {
        replacetable = build_table(input);
    }
    int* getreplacetable()
    {
        return replacetable;
    }
    char* table_replace_encrypt(char*plaintext)//加密
    {
        int len = strlen(plaintext);
        char* ciphertext = new char[len];
        for (int i = 0; i < len; i++)
        {
            if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            {
                int n = plaintext[i] - 'a';
                ciphertext[i] = plaintext[i] + replacetable[n] - n;
            }
            else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            {
                int n = plaintext[i] - 'A';
                ciphertext[i] = plaintext[i] + replacetable[n] - n;
            }
            else
                ciphertext[i] = plaintext[i];
        }
        ciphertext[len] = '\0';
        return ciphertext;
    }
    char* table_replace_decrypt(char* ciphertext)//解密
    {
        int len = strlen(ciphertext);
        char* plaintext = new char[len];
        for (int i = 0; i < len; i++)
        {
            if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
            {
                int n = retnum(replacetable, ciphertext[i] - 'a');
                plaintext[i] = 'a' + n;
            }
            else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
            {
                int n = retnum(replacetable, ciphertext[i] - 'A');
                plaintext[i] = 'A' + n;
            }
            else
                plaintext[i] = ciphertext[i];
        }
        plaintext[len] = '\0';
        return plaintext;
    }
};
int main()
{

    cout << "请输入密钥：";
    char* input = new char[24];
    cin.getline(input, 20);
    
    table_replace_crypt pro = table_replace_crypt(input);
    cout << "置换表为：" << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << char('a' + i) << " ";
    }
    cout << endl;
    int* temp = pro.getreplacetable();
    for (int i = 0; i < 26; i++)
    {
		cout << char('a' + temp[i]) << " ";
    }
    cout << endl << endl;

    cout << "请输入要加密的明文：";
    char* plaintext = new char[24];
    char* temp1;
    cin.getline(plaintext, 20);
    temp1 = pro.table_replace_encrypt(plaintext);
    cout << "明文" << plaintext << "加密后的密文为：" << temp1 << endl << endl;

    cout << "请输入要解密的密文：";
    char* ciphertext = new char[24];
    char* temp2;
    cin.getline(ciphertext, 20);
    temp2 = pro.table_replace_decrypt(ciphertext);
    cout << "密文" << ciphertext << "解密后的明文为：" << temp2 << endl << endl;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
