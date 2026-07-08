#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(int n, string s);
int count_words(int n, string s);
int count_sentences(int n, string s);

int main(void)
{
    float index;
    string text = get_string("Text: ");
    int n = strlen(text);

    int letters, words, sentences;
    letters = count_letters(n, text);
    // printf("Letters = %i\n", letters);
    words = count_words(n, text);
    // printf("Words = %i\n", words);
    sentences = count_sentences(n, text);
    // printf("Sentences = %i\n", sentences);

    float L, S;

    L = (letters / (float) words) * 100;
    S = (sentences / (float) words) * 100;

    index = (0.0588 * L) - (0.296 * S) - 15.8;
    // printf("Index = %f\n", index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) (round(index)));
    }
}

int count_letters(int n, string s)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(s[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(int n, string s)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if ((s[i] == ' ' || s[i] == '!' || s[i] == '.' || s[i] == '?') && (!(s[i + 1] == ' ')))
        {
            count++;
        }
    }
    return count;
}

int count_sentences(int n, string s)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '!' || s[i] == '.' || s[i] == '?')
        {
            count++;
        }
    }
    return count;
}
