// Week 2 Challenge - Introduction to Computer Science Harvard

// Author: Philipp Pfister

// Implement a program that computes the approximate grade level needed to
// comprehend some text using the Coleman-Liau index of the text.

// Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
// L is average number of letters per 100 words
// S is average number of sentences per 100 words

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{

    // prompt user for text and save it in a variable txt
    string txt = get_string("Text: ");

    // Declare count variables:
    float count_l = 0;
    float count_w = 0;
    float count_s = 0;

    // Start string analysis:
    for (int i = 0; i <= strlen(txt); i++)
    {
        // Count Letters:
        if ((txt[i] >= 65 && txt[i] <= 90) || (txt[i] >= 97 && txt[i] <= 122)) // valid only for characters which are upper or lowercase letters
        {
            //printf("%c\n", txt[i]);
            count_l++;
        }
        // Count words (I’ll consider any sequence of characters separated by a space to be a word):
        if (txt[i] == 32)
        {
            count_w++;
        }
        // Count sentences (I'll consider any sequence of characters that ends with a . or a ! or a ? to be a sentence):
        if (txt[i] == 33 || txt[i] == 46 || txt[i] == 63)
        {
            count_s++;
        }
    }

    printf("%.0f letter(s)\n", count_l);

    count_w = count_w + 1; //here I add to the final result of count_w a one, since after the last word, there is no space to count and so without this "+1" I would count one word less!
    printf("%.0f words(s)\n", count_w);

    printf("%.0f sentence(s)\n", count_s);


    // Calculate Coleman-Liau index:
    float L = (count_l / (count_w)) * 100; // calculating L which is the average number of letters per 100 words
    //printf("%f\n", L);
    float S = (count_s / (count_w)) * 100; // calculating S which is average number of sentences per 100 words
    //printf("%f\n", S);

    float cole_index = 0.0588 * L - 0.296 * S - 15.8;
    cole_index = roundf(cole_index);

    printf("Coleman Index: %.3f\n", cole_index);

    // Create correct output regarding cole_index result:
    for (float g = 0; g < 16; g++)
    {
        if (cole_index < 1)
        {
            printf("Before Grade 1\n");
            return 0;
        }
        if (cole_index <= g)
        {
            printf("Grade %.0f\n", g);
            return 0;
        }
        if (cole_index >= 16)
        {
            printf("Grade 16+\n");
            return 0;
        }
    }
}


