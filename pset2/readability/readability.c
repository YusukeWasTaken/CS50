#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int main()
{
    string text = get_string("Write the text you want to grade: ");

    int letter = 0;
    int words = 0;
    int sentence = 0;

    for (int i = 0, len = strlen(text); i <= len; i++)
    {   
        // See if it's an alphabetic letter
        if (isalpha(text[i]))
        {
            letter++;
        }
        // See if the character is a space and get a new word
        if (text[i] == ' ' || i == 0)
        {
            words++;
        }
        // See if the character is a sentence ending character and get a new sentence
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence++;
        }
    }

    float L = (float) letter * 100 / words;
    float S = (float) sentence * 100  / words;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int) round(index));
    }

}