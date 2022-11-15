#pragma once
#include<iostream>

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
    table_replace_crypt(char* input)
    {
        replacetable = build_table(input);
    }
    int* getreplacetable()
    {
        return replacetable;
    }
    char* table_replace_encrypt(char* plaintext)
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
    char* table_replace_decrypt(char* ciphertext)
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