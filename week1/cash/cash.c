#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents)
{
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents -= 25;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    int dimes = 0;
    while (cents >= 10)
    {
        dimes++;
        cents -= 10;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    int nickels = 0;
    while (cents >= 5)
    {
        nickels++;
        cents -= 5;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    int pennies = 0;
    while (cents >= 1)
    {
        pennies++;
        cents -= 1;
    }
    return pennies;
}

int main(void)
{
    int cents;
    int coins_for_change = 0;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int quarters = 0, dimes = 0, nickels = 0, pennies = 0;

    quarters = calculate_quarters(cents);
    cents -= (quarters * 25);
    printf("cents remained after checking qts:%i\n", cents);
    dimes = calculate_dimes(cents);
    cents -= (dimes * 10);
    printf("cents remained after checking dms:%i\n", cents);
    nickels = calculate_nickels(cents);
    cents -= (nickels * 5);
    printf("cents remained after checking ncs:%i\n", cents);
    pennies = calculate_pennies(cents);
    cents -= (pennies * 1);
    printf("cents remained after checking pns:%i\n", cents);
    printf("total coins for change: %i\n", quarters + dimes + nickels + pennies);
}
