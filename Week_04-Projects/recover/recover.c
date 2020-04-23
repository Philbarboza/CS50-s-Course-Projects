// Week 4 Challenge - Introduction to Computer Science Harvard

// Author: Philipp Pfister

// In this challenge the task is to implement a program that recovers JPEGs from a forensic image.
// This means that a file needs to be open, read, written to and closed. The file that needs to be 
// recoverd is "card.raw".

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // check if there is exactly one command-line argument, if not return 1
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open file and check if selected file opens correctly, if not return 1, if yes start operation
    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("File not readable.\n");
        return 1;
    }
    
    // creating a new type to store a byte of data
    typedef uint8_t BYTE;
    // creating buffer array
    BYTE buffer[512];
    // char array where new jpeg name is stored
    char filename[10];
    // counter for correct jpeg name
    int jpeg_num = 0;
    // set output file to initially 0
    FILE *img = NULL;

    while (fread(buffer, 512, 1, file) == 1)
    {
        // read first 512 bytes block and copy into a buffer array
        //fread(buffer, 512, 1, file);

        // Check first fourth bytes of buffer to see if its a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // make a new JPEG
            sprintf(filename, "%03i.jpg", jpeg_num);
            img = fopen(filename, "w");

            // writing new file
            fwrite(buffer, 512, 1, img);
            fclose(img);
            jpeg_num++;
        }
        else if (jpeg_num > 0)
        {
           img = fopen(filename, "a");
           fwrite(buffer, 512, 1, img);
           fclose(img);
        }
    }
    fclose(file);
    return 0;
}