#include <stdio.h>
#include <cs50.h>
#include <math.h>

int count(int cents);


int main()
{
    // Ask the ammount
    float dollars;
    do
    {
        dollars = get_float("How much dolars do you owe? ");
    }
    while (dollars <= 0);


    // Convert the ammount to cents
    int cents = round(dollars * 100);

    //Run count function
    count(cents);
}



int count(int cents)
{
    printf("%d\n", cents);
    int qcents,dcents,ncents,pcents,qcoins = 0,dcoins = 0,ncoins = 0,pcoins = 0;

    for (int quarter = 25;quarter <= cents;cents = cents - quarter)
    {
        qcoins++;
        //printf("%d\n",cents);
    }
    for (int dime = 10; dime <= cents;cents = cents - dime)
    {
        dcoins++;
        //printf("%d\n",cents);
    }
    for (int nickel = 5; nickel <= cents;cents = cents - nickel)
    {
        ncoins++;
        //printf("%d\n",cents);
    }
    for (int pennie = 1; pennie <= cents;cents = cents - pennie)
    {
        pcoins++;
        //printf("%d\n",cents);
    }
    int coin = qcoins + dcoins + ncoins + pcoins;
        // printf("%d Quarters\n", qcoins);
        // printf("%d Dimes\n", dcoins);
        // printf("%d Nickels\n", ncoins);
        // printf("%d Pennies\n", pcoins);
        printf("Coins: %d\n", coin);
    return 0;

}


    //   // Ask the ammount
    // float dollars;
    // do
    // {
    //     dollars = get_float("How much dolars do you owe? ");
    // }
    // while (dollars <= 0);


    // // Convert the ammount to cents    
    // int cents = round(dollars * 100);
    
    
    // int quarter = 25, dime = 10, nickel = 5, pennie = 1;
    // int nquarter = cents / quarter;
    // cents = cents - nquarter*quarter;
    // int ndime = cents / dime;
    // cents = cents - ndime*dime;
    // int nnickel = cents / nickel;
    // cents = cents - nnickel*nickel;
    // int npennie = cents / pennie;
    // pennie = cents - npennie*pennie;
    
    // int coin = nquarter + ndime + nnickel + npennie;
    
    // printf("%d",coin);
    
    
