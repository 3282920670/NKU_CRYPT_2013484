// table_replace_attack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<map>
#include"single_table_replace_crypt.h"
using namespace std;
int main()
{
    char* ciphertext = new char[1024];
    cin.getline(ciphertext, 1024);
    int len = strlen(ciphertext);

    //统计字母频率
    int num[26], total = 0;
    for (int i = 0; i < 26; i++)
        num[i] = 0;
    for (int i = 0; i < len; i++)
    {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
        {
            int n = ciphertext[i] - 'a';
            num[n]++;
            total++;
        }
        else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
        {
            int n = ciphertext[i] - 'A';
            num[n]++;
            total++;
        }
    }

    int n[26][2];
    for (int i = 0; i < 26; i++)
    {
        n[i][0] = i;
        cout << char('a' + i) << "的频率为：" << float(num[i]) / total << endl;
    }

    //将字母按频率排序
    for (int i = 0; i < 26; i++)
    {
        for (int j = i; j < 26; j++)
        {
            if (num[i] < num[j])
            {
                swap(num[i], num[j]);
                int temp = n[i][0];
                n[i][0] = n[j][0];
                n[j][0] = temp;
            }
        }
    }
    //for (int i = 0; i < 26; i++)
    //{
    //    //cout << num[i] << endl;
    //    cout << char(n[i][0] + 'a') << endl;
    //}

    //创建n[26][2]二维数组，将排好序的字母与近似字母频率一一对应起来
    //其中n[i][0]储存排好序的字母，n[i][1]储存对应的近似字母
    //然后创建temp[26]创建置换表，将字母按顺序排好
    string str = "etoiansrhlducmpyfgwbvkxjqz";
    for (int i = 0; i < 26; i++)
    {
        n[i][1] = int(str[i] - 'a');
        //cout << n[i][1] << endl;
    }
    int temp[26];
    for (int i = 0; i < 26; i++)
    {
        temp[n[i][0]] = n[i][1];
    }

    //校正
    swap(temp['n' - 'a'], temp['j' - 'a']);
    swap(temp['y' - 'a'], temp['f' - 'a']);
    swap(temp['d' - 'a'], temp['x' - 'a']);
    swap(temp['m' - 'a'], temp['j' - 'a']);
    swap(temp['p' - 'a'], temp['r' - 'a']);
    swap(temp['q' - 'a'], temp['h' - 'a']);
    swap(temp['z' - 'a'], temp['a' - 'a']);
    swap(temp['e' - 'a'], temp['g' - 'a']);
    swap(temp['h' - 'a'], temp['x' - 'a']);
    swap(temp['a' - 'a'], temp['e' - 'a']);
    swap(temp['o' - 'a'], temp['k' - 'a']);
    
    cout << "置换表为：" << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << char(i + 'a') << " ";
    }
    cout << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << char(temp[i] + 'a') << " ";
    }
    cout << endl;

    for (int i = 0; i < len; i++)
    {
		if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z')
			ciphertext[i] = char(temp[ciphertext[i] - 'A'] + 'a');
		else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
			ciphertext[i] = char(temp[ciphertext[i] - 'a'] + 'a');
    }
    cout << ciphertext << endl;
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
