#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

// Ci = (Pi + key) % 26

// Aski A = 65; letter - 65 = Alphabetic index; A = 0

int converter(char aski, int k);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for (int e = 0, lenarg = strlen(argv[1]); e < lenarg; e++)
        {
            if ((isalpha(argv[1][e])) != 0)
            {
                printf ("./carsar key\n");
                exit(1);
            }
        }
        
        int key = atoi(argv[1]);
        //printf("%d",key);
        if (key > 0)
        {
            string aski_text = get_string("Write your text: ");

            printf ("ciphertext: ");

            for (int i = 0, len = strlen(aski_text); i < len; i++)
            {
                if (isalpha(aski_text[i]))
                {
                    if (islower(aski_text[i]))
                    {
                        //Transform lowercase into highercase (ASCII)
                        aski_text[i] -= 32;
                        aski_text[i] = converter(aski_text[i],key);
                        //Transform highercase into lowercase (ASCII)
                        aski_text[i] += 32;
                        printf("%c",aski_text[i]);
                    }
                    else
                    {
                        //Transformar aski em alpha
                        aski_text[i] = converter(aski_text[i],key);
                        printf("%c",aski_text[i]);
                    }
                }
                else
                {
                    printf("%c",aski_text[i]);
                }
            }
           printf("\n");
           return 0;
        }
    }
    printf ("./carsar key\n");
    return 1;
}

//Ascii to Alpha with cycle to Ascii
int converter(char aski, int k)
{
    char alpha_text = aski - 65;
    char encrip = (alpha_text + k) % 26;
    aski = encrip + 65;
    return aski;
}

