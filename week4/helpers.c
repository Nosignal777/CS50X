#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            int avg = round((red + green + blue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumR += copy[ni][nj].rgbtRed;
                        sumG += copy[ni][nj].rgbtGreen;
                        sumB += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumR / (float) count);
            image[i][j].rgbtGreen = round(sumG / (float) count);
            image[i][j].rgbtBlue = round(sumB / (float) count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxR = 0, gxG = 0, gxB = 0;
            int gyR = 0, gyG = 0, gyB = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        int ki = di + 1;
                        int kj = dj + 1;
                        int wx = gx[ki][kj];
                        int wy = gy[ki][kj];
                        gxR += copy[ni][nj].rgbtRed * wx;
                        gxG += copy[ni][nj].rgbtGreen * wx;
                        gxB += copy[ni][nj].rgbtBlue * wx;
                        gyR += copy[ni][nj].rgbtRed * wy;
                        gyG += copy[ni][nj].rgbtGreen * wy;
                        gyB += copy[ni][nj].rgbtBlue * wy;
                    }
                }
            }
            int valueR = round(sqrt(gxR * gxR + gyR * gyR));
            if (valueR > 255)
            {
                valueR = 255;
            }
            image[i][j].rgbtRed = valueR;

            int valueG = round(sqrt(gxG * gxG + gyG * gyG));
            if (valueG > 255)
            {
                valueG = 255;
            }
            image[i][j].rgbtGreen = valueG;

            int valueB = round(sqrt(gxB * gxB + gyB * gyB));
            if (valueB > 255)
            {
                valueB = 255;
            }
            image[i][j].rgbtBlue = valueB;
        }
    }
    return;
}
