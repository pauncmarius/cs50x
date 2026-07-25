// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 27;

int counter=0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    if(word == NULL){
        return false;
    }

    int temp = hash(word);

    for(node *ptr = table[temp]; ptr != NULL; ptr=ptr->next){
        char *string = malloc(sizeof(char) * (LENGTH+1));
        strcpy(string, ptr->word);
        for(int i=0, leng=(strlen(string)); i<leng; i++){
            string[i]=tolower(string[i]);
        }
        if(strcmp(string, ptr->word)==0){
            free(string);
            return true;
        }

        free(string);
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if(isalpha(word[0])){
        return toupper(word[0]) - 'A';
    }
    return N-1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    counter=0;
    FILE *file_in = fopen(dictionary, "r");

    if(file_in == NULL){
        return false;
    }

    char s_buffer[LENGTH+1];
    while (fscanf(file_in, "%s", s_buffer) != EOF){
        counter++;
        node *n = malloc(sizeof(node));
        if(n == NULL){
            return 0;
        }

        strcpy(n->word, s_buffer);

        int temp_value = hash(n->word);
        n->next = table[temp_value];
        table[temp_value] = n;
    }

    fclose(file_in);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i=0; i<N; i++){
        node *temp= table[i];
        node *cursor = table[i];

        while(cursor != NULL){
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
