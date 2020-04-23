// Week 4 Challenge - Introduction to Computer Science Harvard

// Author: Philipp Pfister

// In this challenge the task is to implement a program that applies filters to BMPs.
// I was responsible to write the code chunks for each filter option.
// The included filters are: grayscale, sepia, horizontal reflection and blur.

#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // calculate average:
            float avg = round((round(image[j][i].rgbtBlue) + round(image[j][i].rgbtGreen) + round(image[j][i].rgbtRed)) / 3);

            // apply  in the same pixel the calculated greyscale colour to each colour element:
            image[j][i].rgbtBlue = avg;
            image[j][i].rgbtGreen = avg;
            image[j][i].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // calculate sepia blue, green and red values:
            float sepiaBlue = round(0.272 * image[j][i].rgbtRed + 0.534 * image[j][i].rgbtGreen + 0.131 * image[j][i].rgbtBlue);
            float *pB = &sepiaBlue;
            float sepiaGreen = round(0.349 * image[j][i].rgbtRed + 0.686 * image[j][i].rgbtGreen + 0.168 * image[j][i].rgbtBlue);
            float *pG = &sepiaGreen;
            float sepiaRed = round(0.393 * image[j][i].rgbtRed + 0.769 * image[j][i].rgbtGreen + 0.189 * image[j][i].rgbtBlue);
            float *pR = &sepiaRed;

            // go through all calculated sepia values and limit them at 255 if their value is above 255:
            float tmp_sepcol[3] = {*pB, *pG, *pR};
            for (int t = 0; t < 3; t++)
            {
                if (tmp_sepcol[t] > 255)
                {
                    tmp_sepcol[t] = 255;
                }
            }
            // pass new sepia values to pixel:
            image[j][i].rgbtBlue = tmp_sepcol[0];
            image[j][i].rgbtGreen = tmp_sepcol[1];
            image[j][i].rgbtRed = tmp_sepcol[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        if (width % 2 == 0) // check if width is even or not
        {
            for (int i = 0; i < width / 2; i++)
            {
                RGBTRIPLE tmp = image[j][i];
                image[j][i] = image[j][width - 1 - i];
                image[j][width - 1 - i] = tmp;
            }
        }
        else
        {
            for (int i = 0; i < (width - 1) / 2; i++) // when width is uneven this for loop is chosen
            {
                RGBTRIPLE tmp = image[j][i];
                image[j][i] = image[j][width - 1 - i];
                image[j][width - 1 - i] = tmp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy called image2 of the image picture grid, which will be used to always have the original setting
    RGBTRIPLE image2[height][width];
    for (int j = 0; j < height; j ++)
    {
        for (int i = 0; i < width; i++)
        {
            image2[j][i] = image[j][i];
        }
    }

    // starting Box Blur Algorithm
    int w = width - 1;
    int h = height - 1;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (j == 0 && i == 0)  // top left corner
            {
                float avgBlue = round((round(image2[j][i].rgbtBlue) + round(image2[j][i + 1].rgbtBlue) + round(image2[j + 1][i].rgbtBlue) + round(
                                        image2[j + 1][i + 1].rgbtBlue)) / 4);
                float *pB = &avgBlue;
                float avgGreen = round((round(image2[j][i].rgbtGreen) + round(image2[j][i + 1].rgbtGreen) + round(
                                            image2[j + 1][i].rgbtGreen) + round(
                                            image2[j + 1][i + 1].rgbtGreen)) / 4);
                float *pG = &avgGreen;
                float avgRed = round((round(image2[j][i].rgbtRed) + round(image2[j][i + 1].rgbtRed) + round(image2[j + 1][i].rgbtRed) + round(
                                            image2[j + 1][i + 1].rgbtRed)) / 4);
                float *pR = &avgRed;

                 // pass new values to pixel:
                float tmp_col[3] = {*pB, *pG, *pR};

  	    image[j][i].rgbtBlue = tmp_col[0];
 	    image[j][i].rgbtGreen = tmp_col[1];
  	    image[j][i].rgbtRed = tmp_col[2];

            }
            if (j == 0 && i > 0 && i < w) // top middle edge
            {
                float avgBlue = round((round(image2[j][i].rgbtBlue) + round(image2[j][i + 1].rgbtBlue) + round(image2[j][i - 1].rgbtBlue) + round(
                                            image2[j + 1][i].rgbtBlue) + round(image2[j + 1][i - 1].rgbtBlue) + round(image2[j + 1][i + 1].rgbtBlue)) / 6);
                float *pB = &avgBlue;
                float avgGreen = round((round(image2[j][i].rgbtGreen) + round(image2[j][i + 1].rgbtGreen) + round(
                                            image2[j][i - 1].rgbtGreen) + round(
                                            image2[j + 1][i].rgbtGreen) + round(image2[j + 1][i - 1].rgbtGreen) + round(image2[j + 1][i + 1].rgbtGreen)) / 6);
                float *pG = &avgGreen;
                float avgRed = round((round(image2[j][i].rgbtRed) + round(image2[j][i + 1].rgbtRed) + round(image2[j][i - 1].rgbtRed) + round(
                                            image2[j + 1][i].rgbtRed) + round(image2[j + 1][i - 1].rgbtRed) + round(image2[j + 1][i + 1].rgbtRed)) / 6);
                float *pR = &avgRed;

                 // pass new values to pixel:
                float tmp_col[3] = {*pB, *pG, *pR};

	    image[j][i].rgbtBlue = tmp_col[0];
	    image[j][i].rgbtGreen = tmp_col[1];
	    image[j][i].rgbtRed = tmp_col[2];

            }
            if (j == 0 && i == w) // top right corner
            {
                float avgBlue = round((round(image2[j][i].rgbtBlue) + round(image2[j][i - 1].rgbtBlue) + round(image2[j + 1][i].rgbtBlue) + round(
                                            image2[j + 1][i - 1].rgbtBlue)) / 4);
                float *pB = &avgBlue;
                float avgGreen = round((round(image2[j][i].rgbtGreen) + round(image2[j][i - 1].rgbtGreen) + round(
                                            image2[j + 1][i].rgbtGreen) + round(
                                            image2[j + 1][i - 1].rgbtGreen)) / 4);
                float *pG = &avgGreen;
                float avgRed = round((round(image2[j][i].rgbtRed) + round(image2[j][i - 1].rgbtRed) + round(image2[j + 1][i].rgbtRed) + round(
                                           image2[j + 1][i - 1].rgbtRed)) / 4);
                float *pR = &avgRed;

                 // pass new values to pixel:
                float tmp_col[3] = {*pB, *pG, *pR};

  	    image[j][i].rgbtBlue = tmp_col[0];
	    image[j][i].rgbtGreen = tmp_col[1];
 	    image[j][i].rgbtRed = tmp_col[2];

            }
            if (j > 0 && j < h && i == 0) // middle left edge
            {
                float avgBlue = round((round(image2[j][i].rgbtBlue) + round(image2[j][i + 1].rgbtBlue) + round(image2[j + 1][i].rgbtBlue) + round(
                                            image2[j - 1][i].rgbtBlue) + round(image2[j + 1][i + 1].rgbtBlue) + round(image2[j - 1][i + 1].rgbtBlue)) / 6);
                float *pB = &avgBlue;
                float avgGreen = round((round(image2[j][i].rgbtGreen) + round(image2[j][i + 1].rgbtGreen) + round(
                                            image2[j + 1][i].rgbtGreen) + round(
                                            image2[j - 1][i].rgbtGreen) + round(image2[j + 1][i + 1].rgbtGreen) + round(image2[j - 1][i + 1].rgbtGreen)) / 6);
                float *pG = &avgGreen;
                float avgRed = round((round(image2[j][i].rgbtRed) + round(image2[j][i + 1].rgbtRed) + round(image2[j + 1][i].rgbtRed) + round(
                                            image2[j - 1][i].rgbtRed) + round(image2[j + 1][i + 1].rgbtRed) + round(image2[j - 1][i + 1].rgbtRed)) / 6);
                float *pR = &avgRed;

                 // pass new values to pixel:
                float tmp_col[3] = {*pB, *pG, *pR};

  	    image[j][i].rgbtBlue = tmp_col[0];
  	    image[j][i].rgbtGreen = tmp_col[1];
  	    image[j][i].rgbtRed = tmp_col[2];

            }
            if (j > 0 && j < h && i > 0 && i < w) // central
            {
                float avgBlue = roundf((round(image2[j][i].rgbtBlue) + round(image2[j][i + 1].rgbtBlue) + round(image2[j + 1][i].rgbtBlue) + round(
                                            image2[j - 1][i].rgbtBlue) + round(image2[j][i - 1].rgbtBlue) + round(image2[j + 1][i + 1].rgbtBlue) + round(image2[j - 1][i + 1].rgbtBlue) + round(image2[j + 1][i - 1].rgbtBlue) + round(image2[j - 1][i - 1].rgbtBlue)) / 9);
                float *pB = &avgBlue;
                float avgGreen = roundf((round(image2[j][i].rgbtGreen) + round(image2[j][i + 1].rgbtGreen) + round(image2[j + 1][i].rgbtGreen) + round(
                                            image2[j - 1][i].rgbtGreen) + round(image2[j][i - 1].rgbtGreen) + round(image2[j + 1][i + 1].rgbtGreen) + round(image2[j - 1][i + 1].rgbtGreen) + round(image2[j + 1][i - 1].rgbtGreen) + round(image2[j - 1][i - 1].rgbtGreen)) / 9);
                float *pG = &avgGreen;
                float avgRed = roundf((round(image2[j][i].rgbtRed) + round(image2[j][i + 1].rgbtRed) + round(image2[j + 1][i].rgbtRed) + round(
                                            image2[j - 1][i].rgbtRed) + round(image2[j][i - 1].rgbtRed) + round(image2[j + 1][i + 1].rgbtRed) + round(image2[j - 1][i + 1].rgbtRed) + round(image2[j + 1][i - 1].rgbtRed) + round(image2[j - 1][i - 1].rgbtRed)) / 9);
                float *pR = &avgRed;

                 // pass new values to pixel:
                float tmp_col[3] = {*pB, *pG, *pR};

  	    image[j][i].rgbtBlue = tmp_col[0];
   	    image[j][i].rgbtGreen = tmp_col[1];
	    image[j][i].rgbtRed = tmp_col[2];

            }
            if (j > 0 && j < h && i == w) // middle right edge
            {
                float avgBlue = round((round(image2[j][i].rgbtBlue) + round(image2[j][i - 1].rgbtBlue) + round(image2[j + 1][i].rgbtBlue) + round(
                                            image2[j - 1][i].rgbtBlue) + round(image2[j + 1][i - 1].rgbtBlue) + round(image2[j - 1][i - 1].rgbtBlue)) / 6);
                float *pB = &avgBlue;
                float avgGreen = round((round(image2[j][i].rgbtGreen) + round(image2[j][i - 1].rgbtGreen) + round(image2[j + 1][i].rgbtGreen) + round(
                                            image2[j - 1][i].rgbtGreen) + round(image2[j + 1][i - 1].rgbtGreen) + round(image2[j - 1][i - 1].rgbtGreen)) / 6);
                float *pG = &avgGreen;
                float avgRed = round((round(image2[j][i].rgbtRed) + round(image2[j][i - 1].rgbtRed) + round(image2[j + 1][i].rgbtRed) + round(
                                            image2[j - 1][i].rgbtRed) + round(image2[j + 1][i - 1].rgbtRed) + round(image2[j - 1][i - 1].rgbtRed)) / 6);
                float *pR = &avgRed;

                 // pass new values to pixel:
                float tmp_col[3] = {*pB, *pG, *pR};

	    image[j][i].rgbtBlue = tmp_col[0];
	    image[j][i].rgbtGreen = tmp_col[1];
	    image[j][i].rgbtRed = tmp_col[2];


            }
            if (j == h && i == 0) // bottom left corner
            {
                float avgBlue = round((round(image2[j][i].rgbtBlue) + round(image2[j][i + 1].rgbtBlue) + round(image2[j - 1][i].rgbtBlue) + round(
                                            image2[j - 1][i + 1].rgbtBlue)) / 4);
                float *pB = &avgBlue;
                float avgGreen = round((round(image2[j][i].rgbtGreen) + round(image2[j][i + 1].rgbtGreen) + round(image2[j - 1][i].rgbtGreen) + round(
                                            image2[j - 1][i + 1].rgbtGreen)) / 4);
                float *pG = &avgGreen;
                float avgRed = round((round(image2[j][i].rgbtRed) + round(image2[j][i + 1].rgbtRed) + round(image2[j - 1][i].rgbtRed) + round(
                                            image2[j - 1][i + 1].rgbtRed)) / 4);
                float *pR = &avgRed;

                 // pass new values to pixel:
                float tmp_col[3] = {*pB, *pG, *pR};

	    image[j][i].rgbtBlue = tmp_col[0];
	    image[j][i].rgbtGreen = tmp_col[1];
	    image[j][i].rgbtRed = tmp_col[2];


            }
            if (j == h && i > 0 && i < w) // bottom middle edge
            {
                long avgBlue = round((round(image2[j][i].rgbtBlue) + round(image2[j][i + 1].rgbtBlue) + round(image2[j][i - 1].rgbtBlue) + round(
                                            image2[j - 1][i].rgbtBlue) + round(image2[j - 1][i - 1].rgbtBlue) + round(image2[j - 1][i + 1].rgbtBlue)) / 6);
                long *pB = &avgBlue;
                long avgGreen = round((round(image2[j][i].rgbtGreen) + round(image2[j][i + 1].rgbtGreen) + round(
                                            image2[j][i - 1].rgbtGreen) + round(
                                            image2[j - 1][i].rgbtGreen) + round(image2[j - 1][i - 1].rgbtGreen) + round(image2[j - 1][i + 1].rgbtGreen)) / 6);
                long *pG = &avgGreen;
                long avgRed = round((round(image2[j][i].rgbtRed) + round(image2[j][i + 1].rgbtRed) + round(image2[j][i - 1].rgbtRed) + round(
                                            image2[j - 1][i].rgbtRed) + round(image2[j - 1][i - 1].rgbtRed) + round(image2[j - 1][i + 1].rgbtRed)) / 6);
                long *pR = &avgRed;

                 // pass new values to pixel:
                long tmp_col[3] = {*pB, *pG, *pR};

	    image[j][i].rgbtBlue = tmp_col[0];
	    image[j][i].rgbtGreen = tmp_col[1];
	    image[j][i].rgbtRed = tmp_col[2];


            }
            if (j == h && i == w) // bottom right corner
            {
                float avgBlue = round((round(image2[j][i].rgbtBlue) + round(image2[j][i - 1].rgbtBlue) + round(
                                           image2[j - 1][i].rgbtBlue) + round(image2[j - 1][i - 1].rgbtBlue)) / 4);
                float *pB = &avgBlue;
                float avgGreen = round((round(image2[j][i].rgbtGreen) + round(image2[j][i - 1].rgbtGreen) + round(
                                            image2[j - 1][i].rgbtGreen) + round(image2[j - 1][i - 1].rgbtGreen)) / 4);
                float *pG = &avgGreen;
                float avgRed = round((round(image2[j][i].rgbtRed) + round(image2[j][i - 1].rgbtRed) + round(
                                          image2[j - 1][i].rgbtRed) + round(image2[j - 1][i - 1].rgbtRed)) / 4);
                float *pR = &avgRed;

                // pass new values to pixel:
                float tmp_col[3] = {*pB, *pG, *pR};

        image[j][i].rgbtBlue = tmp_col[0];
        image[j][i].rgbtGreen = tmp_col[1];
        image[j][i].rgbtRed = tmp_col[2];

            }
        }
    }
    return;
}








