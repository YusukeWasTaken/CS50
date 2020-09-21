#include <stdio.h>
#include <cs50.h>

int main()
{
    int height;
    do
    {
        //Ask the height
        height = get_int("Height:");
    }
    while (height < 1 || height > 8);


    int i, j, k, l;
    //Make the height
    for (i = 0; i < height; i++)
    {
        //Make the spaces
        for (k = height - 1; k > i; k--)
        {
            printf(" ");
        }
        //Make the width-left
        for (j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("#  #");
        //Make the width-right
        for (l = 0; l < i; l++)
        {
            printf("#");
        }
        printf("\n");
    }


   // printf("\n");
}