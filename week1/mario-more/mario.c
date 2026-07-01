#include <cs50.h>
#include <stdio.h>

void print_left_pyr(int n, int m)
{
    for (int j = 0; j < (m - n); j++)
    {
        printf(" ");
    }
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

void print_right_pyr(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}

int main()
{
    int gap = 2;
    int height;
    do
    {
        height = get_int("Choose the height for pyramid:");
    }
    while (height < 1);

    for (int i = 0; i < height; i++)
    {
        print_left_pyr(i + 1, height);
        for (int j = 0; j < gap; j++)
            printf(" ");
        print_right_pyr(i + 1);
    }
}
