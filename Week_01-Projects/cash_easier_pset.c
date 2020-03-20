# include <stdio.h>
# include <cs50.h>
# include <math.h>

int main(void)
{
    // defining variable c which asks the cashier how much money need to be returned
    float c;
    // configuring the actual prompt, including a loop till valid number is inputted
    do
    {
        c = get_float("Change owed: ");
    }
    // reprompt user till his input is a positive number
    while (c < 0);

    // convert the dollar input to cents
    int cents = round(c * 100);

    // doing a loop as long as cents is bigger or equal 25 (= 25 pennies || 1 quarter) and if false going to the next smaller coin value
    int coinsCount;
    for (coinsCount = 0; cents >= 25; coinsCount++) 
    {
        cents = cents - 25;
    }
    for (; cents >= 10; coinsCount++)
    {
        cents = cents - 10;            
    }    
    for (; cents >= 5; coinsCount++)
    {
        cents = cents - 5;
    }
    for (; cents >= 1; coinsCount++)
    {
        cents = cents - 1;
    }    
    printf("%i\n", coinsCount);   
}
