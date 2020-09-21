// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

int counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5760;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    free(cursor);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int soma = 0;

    for (int x = 0, n = strlen(word); x < n; x++)
    {
        soma += (int)(tolower(word[x]));
    }
    return soma;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        return false;
    }
    //Read every line until the end of the file
    while (fscanf(file, "%s", word) != EOF)
    {
        //Allocate memory for new node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            free(n);
            return false;
        }

        //Copy the word to the new node
        strcpy(n->word, word);

        //Give a number to the node word
        unsigned int index = hash(word);

        //Assign the index number of the hash to the pointer
        n->next = table[index];

        //Point to the value
        table[index] = n;

        //Counter for the number of words in the dictionary
        counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            while (cursor != NULL)
            {
                node *temp = cursor;
                cursor = cursor->next;
                free(temp);
            }
            free(cursor);
        }
    }
    return true;
}
