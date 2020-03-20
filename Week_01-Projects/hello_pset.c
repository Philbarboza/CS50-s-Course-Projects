#include <stdio.h>
#include <cs50.h>

int main(void)
{ 
    // creating prompt, to ask users name
    string n = get_string("What's your name?\n");
    // code to print the final output with the input received by the prompt above
    printf("hello, %s\n", n);
}
