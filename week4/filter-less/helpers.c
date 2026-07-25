#include "helpers.h"
#include "math.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int temp=0;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            temp = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = temp;
            image[i][j].rgbtRed = temp;
            image[i][j].rgbtGreen = temp;

        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue;
    int sepiaRed, sepiaGreen, sepiaBlue;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // Update pixel with sepia values

            if(sepiaBlue > 255){
               image[i][j].rgbtBlue = 255;
            } else{
            image[i][j].rgbtBlue = sepiaBlue;
            }
            if(sepiaRed > 255){
               image[i][j].rgbtRed = 255;
            } else{
            image[i][j].rgbtRed = sepiaRed;
            }
            if(sepiaGreen > 255){
               image[i][j].rgbtGreen = 255;
            } else{
            image[i][j].rgbtGreen = sepiaGreen;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        //cutting in half bc thats all we need
        for (int j = 0; j < width/2; j++)
        {
            int temp[3];
            temp[0] = image[i][j].rgbtRed;
            temp[1] = image[i][j].rgbtBlue;
            temp[2] = image[i][j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][width-1-j].rgbtRed =  temp[0];
            image[i][width-1-j].rgbtGreen = temp[2];
            image[i][width-1-j].rgbtBlue = temp[1];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Red = 0, Green = 0, Blue = 0;
            float count = 0;
            //searching neighbours
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int n_i = x + i;
                    int n_j = y + j;

                    if ((n_i >= 0 && n_i < height) && (n_j >= 0 && n_j < width))
                    {
                        Red += copy[n_i][n_j].rgbtRed;
                        Green += copy[n_i][n_j].rgbtGreen;
                        Blue += copy[n_i][n_j].rgbtBlue;
                        count++;
                    }
                }
            }
            //update the image pixels with copy ones
            image[i][j].rgbtRed = round(Red / count);
            image[i][j].rgbtGreen = round(Green / count);
            image[i][j].rgbtBlue = round(Blue / count);
        }
    }
}
