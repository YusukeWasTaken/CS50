#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask input for name
    string name = get_string("What's your name?\n");
    
    //Print name
    printf("Hello, %s\n", name);
}