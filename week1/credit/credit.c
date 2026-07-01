#include <cs50.h>
#include <stdio.h>

int count_digits(long n)
{
    int counter = 0;
    while (n > 0)
    {
        counter++;
        n /= 10;
    }
    return counter;
}

string check_card(long n)
{
    char res = '\0';
    int total = 0;
    int total_temp1 = 0;
    int total_temp2 = 0;
    int count = count_digits(n);
    long first_two = n;
    long first_one = n;

    for (int i = 0; i < count; i++)
    {

        int card_digit = n % 10;

        if ((i % 2) == 0)
        {

            total_temp1 += card_digit;
        }
        else
        {

            card_digit *= 2;
            if (card_digit > 9)
            {
                card_digit -= 9;
            }
            total_temp2 += card_digit;
        }
        n /= 10;
    }

    total = total_temp1 + total_temp2;

    if ((total % 10) == 0)
    {
        res = 'y';
    }
    else
    {
        res = 'n';
    }

    if (res == 'y')
    {
        for (int i = 0; i < count - 2; i++)
        {
            first_two /= 10;
        }

        for (int i = 0; i < count - 1; i++)
        {
            first_one /= 10;
        }

        if ((first_two == 34 || first_two == 37) && (count == 15))
        {
            return "AMEX";
        }
        else if ((first_two >= 51 && first_two <= 55) && (count == 16))
        {
            return "MASTERCARD";
        }
        else if ((first_one == 4) && ((count == 13) || (count == 16)))
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
    return " ";
}

int main()
{
    long number;
    number = get_long("Card number: ");

    string result = check_card(number);
    printf("%s\n", result);
}
