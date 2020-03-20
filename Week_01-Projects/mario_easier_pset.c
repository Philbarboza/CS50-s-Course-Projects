#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    // prompt user, so that he types in the height and assign answer to variable h
    {
        h = get_int("Height: "); 
    }
    // re-prompt user as long as his or her answer is not between 1 and 8 inclusively
    while (h < 1 || h > 8);   

    // for loop to get to the next row or line
    for (int i = 0; i < h; i++)
    {
        // creating spaces (previously dots) along a row and this as long as d < (h-i)
        for (int d = 1; d < (h - i); d++)
        {
            printf(" ");
        }
        // creating # along a row, as long as x <= i    
        for (int x = 0; x <= i; x++)
        {
            printf("#");
        }
        printf("\n");
    }
}
