#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string rotate_with_k(string s, int k);

int main(int argc, string argv[])
{
    // 2 because is name of app + 1st arg
    if (argc != 2)
    {
        printf("You have to write exactly one arg! \n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]);
    string plaintext = get_string("plaintext:  ");
    string ciphertext = rotate_with_k(plaintext, k);
    printf("ciphertext: %s\n", ciphertext);
}

string rotate_with_k(string s, int k)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (isupper(s[i]))
        {
            s[i] = ((s[i] - 'A' + k) % 26) + 'A';
        }
        else if (islower(s[i]))
        {
            s[i] = ((s[i] - 'a' + k) % 26) + 'a';
        }
        else
        {
            // nothing to change
        }
    }
    return s;
}
