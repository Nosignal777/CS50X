#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int sum1 = 0, sum2 = 0, sum;
    int t;
    long num, n;
    do
    {
        num = get_long("Number: ");
    }
    while (num <= 0);

    n = num;
    while (n > 0)
    {
        t = n % 10;
        n = n / 100;
        sum1 += t;
    }
    n = num;
    while (n > 0)
    {
        t = (n / 10) % 10;
        n = n / 100;
        int x = t * 2;
        sum2 += x / 10 + x % 10;
    }
    sum = sum1 + sum2;

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    int len = 0;
    n = num;
    while (n > 0)
    {
        n = n / 10;
        len++;
    }

    n = num;
    while (n >= 10)
    {
        n = n / 10;
    }
    if (n == 4 && (len == 13 || len == 16))
    {
        printf("VISA\n");
        return 0;
    }

    n = num;
    while (n >= 100)
    {
        n = n / 10;
    }
    if ((n == 34 || n == 37) && len == 15)
    {
        printf("AMEX\n");
        return 0;
    }

    if (n >= 51 && n <= 55 && len == 16)
    {
        printf("MASTERCARD\n");
        return 0;
    }

    printf("INVALID\n");
}
