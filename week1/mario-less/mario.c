#include <cs50.h>
#include <stdio.h>

void print_row(int n, int m)
{
    for (int j = 0; j < (m - n); j++)
    {
        printf(" ");
    }
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}

int main()
{
    int height;
    do
    {
        height = get_int("Choose the height for pyramid:");
    }
    while (height < 1);

    for (int i = 0; i < height; i++)
    {
        print_row(i + 1, height);
    }
}
