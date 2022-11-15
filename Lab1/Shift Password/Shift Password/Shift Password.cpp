// Shift Password.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

class shift_crypt
{
private:
    int offset;//移位
    char* ciphertext;//密文
public:
    shift_crypt()
    {
        offset = 0;
    }
    shift_crypt(int offset)
    {
        this->offset = offset;
    }
    char* get_ciphertext()
    {
        return this->ciphertext;
    }
    void shift_encrypt(char* plaintext) //加密
    {
        offset = offset % 26;
        //cout << "offset: " << offset << endl;
        int len = strlen(plaintext);
        //cout << "len: " << len << endl;
        this->ciphertext = new char[len];
        for (int i = 0; i < len; i++)
        {
            //cout << "plaintext[i]: " << plaintext[i] << endl;
            if (plaintext[i] >= 'a' && plaintext[i] <= 'z' || plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            {
				char temp = plaintext[i] + offset;
				//cout << "temp: " << temp << endl;
				if (temp > 'Z' && plaintext[i]<='Z' || temp > 'z')
					this->ciphertext[i] = temp - 26;
				else
					this->ciphertext[i] = temp;
			}
			else
			{
				this->ciphertext[i] = plaintext[i];
			}
			//cout << "ciphertext[i]: " << ciphertext[i] << endl;
		}
		this->ciphertext[len] = '\0';
	}
    char* shift_decrypt(char* ciphertext, int offset)//解密
	{
		int len = strlen(ciphertext);
		char* plaintext = new char[len];
		for (int i = 0; i < len; i++)
		{
			if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z' || ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
			{
				char temp = ciphertext[i] - offset;
				if (temp < 'a' && ciphertext[i] >= 'a' || temp < 'A')
					plaintext[i] = temp + 26;
				else
					plaintext[i] = temp;
			}
			else
				plaintext[i] = ciphertext[i];
		}
		plaintext[len] = '\0';
        return plaintext;
	}
    void exhaust_decrypt(char* ciphertext)//穷举
    {
        int offset;
        char* plaintext;
        for (offset = 0; offset <= 25; offset++)
        {
            plaintext = shift_decrypt(ciphertext, offset);
            cout << "移位为：" << offset << " 时明文为：" << plaintext << endl;
        }
    }
};
int main()
{
    char* plaintext = new char[1024];
    char* ciphertext = new char[1024];
    int offset;
    cout << "请输入移位：";
    cin >> offset;
    cout << "请输入要加密的明文：";
    cin >> plaintext;

    shift_crypt pro = shift_crypt(offset);
    pro.shift_encrypt(plaintext);
    char* temp1 = pro.get_ciphertext();
    cout << "移位加密后的密文为：" << temp1 << endl << endl;
    cout << "请输入要解密的密文：";
    cin >> ciphertext;
    char* temp2 = pro.shift_decrypt(ciphertext, offset);
    cout << ciphertext << "对应的明文为：" << temp2 << endl << endl;

    cout << "穷举攻击的密文为："<<temp1 << endl;
    pro.exhaust_decrypt(temp1);
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
