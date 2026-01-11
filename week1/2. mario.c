#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    int i, j, k;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        for (k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
