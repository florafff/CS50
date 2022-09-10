#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for(int i=0; i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
        average=(image[i][j].rgbtRed+image[i][j].rgbtBlue+image[i][j].rgbtGreen)/3.0;
            image[i][j].rgbtRed=(int)(average+0.5);
            image[i][j].rgbtBlue=(int)(average+0.5);
            image[i][j].rgbtGreen=(int)(average+0.5);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if(sepiaRed>255.0)
            {
                sepiaRed=255;
            }
            if(sepiaGreen>255.0)
            {
                sepiaGreen=255;
            }
            if(sepiaBlue>255.0)
            {
                sepiaBlue=255;
            }
            image[i][j].rgbtRed = (int)(sepiaRed+0.5);
            image[i][j].rgbtGreen = (int)(sepiaGreen+0.5);
            image[i][j].rgbtBlue = (int)(sepiaBlue+0.5);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for(int i=0;i<height;i++)
    {
       for(int j=0;j<width/2;j++)
        {
            temp=image[i][j];
            image[i][j]=image[i][width-1-j];
            image[i][width-1-j]=temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE juan[height+2][width+2];
    RGBTRIPLE zero;
    zero.rgbtRed=0;
    zero.rgbtGreen=0;
    zero.rgbtBlue=0;
    for(int i=0;i<height+2;i++)
    {
       for(int j=0;j<width+2;j++)
        {
            if(i==0||j==0||i==height+1||j==width+1)
            {
                juan[i][j]=zero;
            }
            else
            {
                juan[i][j]=image[i-1][j-1];  
            }
        }
    }


    float c=0,d=0,e=0;
    RGBTRIPLE average;
        for(int i=1;i<height+1;i++)
    {
        for(int j=1;j<width+1;j++)
        {
            for(int a=i-1;a<i+2;a++)
            {
                for(int b=j-1;b<j+2;b++)
                {
                    c+=juan[a][b].rgbtRed;
                    d+=juan[a][b].rgbtGreen;
                    e+=juan[a][b].rgbtBlue;
                }
            }
        if((i==1&&j==1)||(i==1&&j==width)||(i==height&&j==1)||(i==height&&j==width))
        {
            average.rgbtRed=(int)(c/4.0+0.5);
            average.rgbtGreen=(int)(d/4.0+0.5);
            average.rgbtBlue=(int)(e/4.0+0.5);
        }
        else if((i>1&&i<height)&&(j>1&&j<width))
        {
            average.rgbtRed=(int)(c/9.0+0.5);
            average.rgbtGreen=(int)(d/9.0+0.5);
            average.rgbtBlue=(int)(e/9.0+0.5);
        }
        else
        {
            average.rgbtRed=(int)(c/6.0+0.5);
            average.rgbtGreen=(int)(d/6.0+0.5);
            average.rgbtBlue=(int)(e/6.0+0.5);
        }
        image[i-1][j-1]=average;
        c=0,d=0,e=0;
        }
    }
    
    return;
}

