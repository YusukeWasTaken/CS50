#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    
    //Counter that is going to help naming the files
    int counter = 0;

    //Check number of arguments
    if (argc != 2)
    {
        printf("./recover (filename)");
        return 1;
    }

    //Open File
    FILE *file = fopen(argv[1], "r");
    
    //Create a newimage without an adress
    FILE *newimage = NULL;
    
    unsigned char buffer[512];

    //If the file doesn't exist
    if (file == NULL)
    {
        printf("The file couldn't be opened");
        return 1;
    }

    // 0xx.jpg
    char newfile[8];

    //While it can read 512 item of size 1
    while (fread(buffer, 1, 512, file) == 512)
    {
        //Check if the bytes are 0xff 0xd8 0xff
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter != 0)
            {
                fclose(newimage);
            }
            //Create a new name according to the counter
            sprintf(newfile, "%03i.jpg", counter);
            counter++;
            //Create a new file
            newimage = fopen(newfile, "w");
            fwrite(buffer, 1, 512, newimage);
        }
        else if (newimage != NULL)
        {
            fwrite(buffer, 1, 512, newimage);
        }
    }
    fclose(file);
    
    if (counter > 0)
    {
        fclose(newimage);
    }
}
