#include <stdio.h>
#include <cs50.h>
#include <math.h>

int checksum(long ccn);
int cccheck(long ccn);


int main()
{
    long ccn;
    do
    {
        ccn = get_long("Type your credit card number ");
    }
    while (ccn <= 0);

    int sumf = checksum(ccn);
    if (sumf == 0)
        cccheck(ccn);
    else
        printf("INVALID\n");
}

int cccheck(long ccn)
{
    if ((ccn >= 340000000000000 && ccn < 350000000000000) || (ccn >= 370000000000000 && ccn < 380000000000000))
        printf("AMEX\n");
    else if (ccn >= 5100000000000000 && ccn < 5600000000000000)
        printf("MASTERCARD\n");
    else if ((ccn >= 4000000000000 && ccn < 5000000000000) || (ccn >= 4000000000000000 && ccn < 5000000000000000))
        printf("VISA\n");
    else
        printf("INVALID\n");
        return 0;
}





int checksum(long ccn)
{
    long n=1;
    int dig = 1;
    int sumtraco = 0;
    int sumntraco = 0;
    
    for(int count = 2;ccn / n > 0 ; n = n*10)
    {
        if (count % 2 != 0)
        {
            dig = (ccn / n) % 10;
            dig = dig * 2;
            if (dig >= 10)
                dig = (dig % 10) + (dig / 10);
            sumtraco = sumtraco + dig;
        }
        else
        {
            dig = (ccn / n) % 10;
            sumntraco = sumntraco + dig;
        }
        count++;
    }
    int sum = sumntraco + sumtraco;
    
    int sumf = sum % 10;
    
    printf("%d\n",sum);
    return sumf;
}


