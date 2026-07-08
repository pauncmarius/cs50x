#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_score(int n, string s);
int calculate_points(char c);

int main()
{
    string word1 = get_string("Player1: ");
    string word2 = get_string("Player2: ");

    int count_w1 = strlen(word1);
    int count_w2 = strlen(word2);

    printf("P1:%i\n", count_w1);
    printf("P2:%i\n", count_w2);

    int score1 = 0, score2 = 0;
    string final_winner;

    score1 = check_score(count_w1, word1);
    score2 = check_score(count_w2, word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int check_score(int n, string s)
{
    int score = 0;
    for (int i = 0; i < n; i++)
    {
        if (islower(s[i]))
        {
            s[i] = toupper(s[i]);
        }
        int score_temp = calculate_points(s[i]);
        score += score_temp;
    }
    return score;
}

int calculate_points(char c)
{
    if (c == 'Q' || c == 'Z')
    {
        return (int) 10;
    }
    else if (c == 'X' || c == 'J')
    {
        return (int) 8;
    }
    else if (c == 'K')
    {
        return (int) 5;
    }
    else if (c == 'Y' || c == 'W' || c == 'V' || c == 'H' || c == 'F')
    {
        return (int) 4;
    }
    else if (c == 'P' || c == 'M' || c == 'C' || c == 'B')
    {
        return (int) 3;
    }
    else if (c == 'D' || c == 'G')
    {
        return (int) 2;
    }
    else if (c == 'A' || c == 'E' || c == 'I' || c == 'L' || c == 'N' || c == 'O' || c == 'R' ||
             c == 'S' || c == 'T' || c == 'U')
    {
        return (int) 1;
    }
    else
    {
        return (int) 0;
    }
}
