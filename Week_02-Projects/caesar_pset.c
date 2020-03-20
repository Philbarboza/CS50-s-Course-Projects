// Week 2 Challenge - Caesar - Introduction to Computer Science Harvard

// Author: Philipp Pfister

// Implement a program that encrypts messages using Caesar’s cipher.
// Caesar’s algorithm (i.e., cipher) encrypts messages by “rotating” each letter by k positions.
// So for example if the key is 1 and the inputted message is "HELLO", the program should give as
// output "IFMMP". So here, each letter of "HELLO" was shifted by 1 in their alphabetical order.

#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
int k, i, p, m, e, c, c_text[99999];

    // First, testing if number of arguments inputted into command-line are correct
if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Second, testing if the key argument is purly numeric
for (e = 0 ; e < strlen(argv[1]); e++)
    {
        if (isdigit(argv[1][e]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Now, valid inputted key will be transformed into an integer and saved in variable k for later use
    k = atoi(argv[1]);

    // prompting for plaintext and save in variable s
    string s = get_string("Plaintext: ");

    for (i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]) && isupper(s[i]))
        {
            p = (s[i] - 65 + k) % 26; // get correct position in the alphabetical index and save it in p
            //printf("%i\n", p);
            c = p + 65; // get equiviliant ASCII value by converting back
        }
        if (isalpha(s[i]) && islower(s[i])) // same procedure when alpha is lower letter
        {
            p = ((s[i] - 97) + k) % 26;
            c = p + 97;
        }
        if (!isalpha(s[i])) // if s[i] is not alphabetic, use original ASCII value
        {
            c = s[i];
        }
        c_text [i] = c; // array which stores all if results from above
    }

    // part of printing the final result:
    printf("ciphertext: ");

    for (m = 0; m < strlen(s); m++) // loop of printing out the whole array
    {
        printf("%c", c_text[m]);
    }
    printf("\n");
    return 0;
}