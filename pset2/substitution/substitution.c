#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int argchecker(int argc, string argv[]);
int converter(string cipher_text, int i);

int main(int argc, string argv[])
{
    argchecker(argc, argv);


    string cipher_text = get_string("Write the text you want to encrypt: ");
    
    printf("ciphertext: ");

    for (int i = 0, len = strlen(cipher_text); i <= len; i++)
    {
        //Check if it is a letter
        if (isalpha(cipher_text[i]))
        {
            //Check if it is a lowercase letter
            if (islower(cipher_text[i]))
            {
                //Transform it into a highercase letter
                cipher_text[i] -= 32;
                int a = converter(cipher_text, i);
                //Print the lowercase letter
                if (islower(argv[1][a]))
                {
                    printf("%c", argv[1][a]);
                }
                //Transform the highercase letter into a lowercase
                else
                {
                    printf("%c", argv[1][a] + 32);
                }
            }
            else
            {
                int a = converter(cipher_text, i);
                if (islower(argv[1][a]))
                {
                    argv[1][a] -= 32;
                }
                printf("%c",argv[1][a]);
            }
        }
        //Preserves the original space and numbers
        else if (cipher_text[i] == ' ' || isdigit(cipher_text[i]))
        {
            printf("%c", cipher_text[i]);
        }
    }
    printf("\n");
}

//Encrypt the text
int converter(string cipher_text, int i)
{
    int a;
    string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //char alfabeto[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    //Run every letter in alfabeto to see the positions
    for (a = 0; a < 26 ; a++)
    {
        if (alfabeto[a] == cipher_text[i])
        {
            return a;
        }
    }
    exit(1);
}



int argchecker(int argc, string argv[])
{
    //If it has 2 arguments
    if (argc == 2)
    {
        int lenarg = strlen(argv[1]);

        if (lenarg == 26)
        {

            //Scan if the argument has numbers and if the length is 26
            for (int e = 0; e < lenarg; e++)
            {
                //Removes if it has letters
                if ((isalpha(argv[1][e])) == 0)
                {
                    printf("./substitution key\n");
                    exit(1);
                }
                //Scan if it has repeated number
                for (int k = 0; k < e; k++)
                {
                    if (argv[1][k] == argv[1][e])
                    {
                        printf("Key must not contain duplicate characterns\n");
                        exit(1);
                    }
                }
            }
        }
        else
        {
            printf("Key must contain 26 characters\n");
            exit(1);
        }
    }
    else
    {
        printf("./substitution key\n");
        exit(1);
    }
    return 0;
}
