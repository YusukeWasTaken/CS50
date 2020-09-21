#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float gscale = (image[y][x].rgbtRed + image[y][x].rgbtBlue + image[y][x].rgbtGreen) / 3.0;
            image[y][x].rgbtRed = round(gscale);
            image[y][x].rgbtBlue = round(gscale);
            image[y][x].rgbtGreen = round(gscale);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            temp = image[y][x];
            image[y][x] = image[y][width - 1 - x];
            image[y][width - 1 - x] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int PixelCount = 0;
            float Red = 0, Green = 0, Blue = 0;
            for (int Ty = -1; Ty < 2; Ty++)
            {
                for (int Tx = -1; Tx < 2; Tx++)
                {
                    if (Ty + y >= 0 && Ty + y < height && Tx + x >= 0 && Tx + x < width)
                    {
                        PixelCount++;
                        Red += image[Ty + y][Tx + x].rgbtRed;
                        Blue += image[Ty + y][Tx + x].rgbtBlue;
                        Green += image[Ty + y][Tx + x].rgbtGreen;
                    }
                }
            }
            temp[y][x].rgbtRed = round(Red / PixelCount);
            temp[y][x].rgbtBlue = round(Blue / PixelCount);
            temp[y][x].rgbtGreen = round(Green / PixelCount);
        }
    }

    for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                image[y][x].rgbtRed = temp[y][x].rgbtRed;
                image[y][x].rgbtGreen = temp[y][x].rgbtGreen;
                image[y][x].rgbtBlue = temp[y][x].rgbtBlue;
            }
        }
    return;
}

int limit(int x);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Equation [y][x]
    int Gx[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};
    RGBTRIPLE temp[height][width];
    //Select Collumn
    for (int y = 0; y < height; y++)
    {
        //Select Pixel in the collum
        for (int x = 0; x < width; x++)
        {
            float RedX = 0.0, BlueX = 0.0, GreenX = 0.0, RedY = 0.0, BlueY = 0.0, GreenY = 0.0;
            //Make a 3 by 3 and give black to the pixels out of the image
            for (int Ty = -1; Ty < 2; Ty++)
            {
                for (int Tx = -1; Tx < 2; Tx++)
                {
                    //Only select the pixels of the image
                    if (Ty + y >= 0 && Ty + y < height && Tx + x >= 0 && Tx + x < width)
                    {
                        //Select the Gx and multiply the value with the colour
                        int mX = Gx[Ty + 1][Tx + 1];
                        RedX += image[Ty + y][Tx + x].rgbtRed * mX;
                        BlueX += image[Ty + y][Tx + x].rgbtBlue * mX;
                        GreenX += image[Ty + y][Tx + x].rgbtGreen * mX;
                        //Select the Gy and multiply the value with the colour
                        int mY = Gy[Ty + 1][Tx + 1];
                        RedY += image[Ty + y][Tx + x].rgbtRed * mY;
                        BlueY += image[Ty + y][Tx + x].rgbtBlue * mY;
                        GreenY += image[Ty + y][Tx + x].rgbtGreen *mY;

                    }
                    //If it is out of the picture, you can ignore it, since 0 * x = 0
                }
            }
            //Paint with a new colour
            temp[y][x].rgbtRed = limit(round(sqrt(RedX*RedX + RedY*RedY)));
            temp[y][x].rgbtBlue = limit(round(sqrt(BlueX*BlueX + BlueY*BlueY)));
            temp[y][x].rgbtGreen = limit(round(sqrt(GreenX*GreenX + GreenY*GreenY)));
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //Replace the colour
            image[y][x].rgbtRed = temp[y][x].rgbtRed;
            image[y][x].rgbtGreen = temp[y][x].rgbtGreen;
            image[y][x].rgbtBlue = temp[y][x].rgbtBlue;
        }
    }
    return;
}

int limit(int x)
{
    if (x > 255)
    {
        return 255;
    }
    else
    {
        return x;
    }
}
