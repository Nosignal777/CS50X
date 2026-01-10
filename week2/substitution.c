#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int seen[26] = {0};
    string key = argv[1];
    int len = strlen(key);

    if (len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < len; i++)
    {
        char c = key[i];

        if (isalpha(c))
        {
            c = toupper(c);
        }
        else
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        if (seen[c - 'A'] == 0)
        {
            seen[c - 'A'] = 1;
        }
        else
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, len2 = strlen(plaintext); i < len2; i++)
    {
        if (!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
        else
        {
            char ch = plaintext[i];
            int pos = toupper(ch) - 'A';
            char sb = key[pos];
            if (isupper(ch))
            {
                printf("%c", toupper(sb));
            }
            else
            {
                printf("%c", tolower(sb));
            }
        }
    }
    printf("\n");
    return 0;
}
