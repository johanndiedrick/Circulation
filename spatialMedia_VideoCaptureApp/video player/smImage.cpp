//  smImage.cpp
//  spatialMedia


#include <iostream>
#include "smImage.h"
#include "poSimpleDrawing.h"
#include "poApplication.h"
#include "poTextBox.h"	   


using namespace po; 
using namespace std;

smImage::smImage( const char* fileName, int W, int H )
{  
    // set the image width and height
    width = W;
    height = H;
    
    // load in the image data from file
    FILE* F = fopen( fileName, "rb" );                  // open a file
    if ( F==NULL )
    {
        printf("ERROR: can't find file: %s\n", fileName );
        exit(0);
    }
    imageData = new unsigned char [ width*height*2 ];     // allocate memory for the image
    fread( imageData, 1, width*height, F );             // read file date into the memory
    fclose( F );                                        // close the file
    
    // used for fastDraw method
    imageAsTexture = new poTexture( width, height, imageData, poTextureConfig(GL_LUMINANCE) );
}

smImage::smImage( int W, int H )
{
    // set the image width and height
    width = W;
    height = H;
    
    // load in the image data from file
    imageData = new unsigned char [ width*height ];     // allocate memory for the image
    setAllPixels(0);
    
    // used for fastDraw method
    imageAsTexture = new poTexture( width, height, imageData, poTextureConfig(GL_LUMINANCE) );
}

int     smImage::getPixel( int x, int y )
{
    int index = x + y*width;                    // calculate the pixel index
    if ( index < 0 || index >= width*height )
    {
        printf("ERROR: getPixel out of bounds\n");
        return 0;
    }
    return imageData[index];                    // return the pixel
}

void    smImage::setPixel( int x, int y, int grayValue )
{
    int index = x + y*width;                    // calculate the pixel index
    if ( index < 0 || index >= width*height )
    {
        printf("ERROR: setPixel out of bounds\n");
        return 0;
    }
    imageData[index] = grayValue;               // set the pixel
}


void    smImage::setAllPixels( int grayValue )
{
    // set all pixels using the memset function
    memset( imageData, grayValue, width*height );
}


void    smImage::copyImageFromMemory( unsigned char*  imageBuffer )
{
    // copy pixel data from incoming imageBuffer into imageData
    memcpy( imageData, imageBuffer, width*height );
}


void    smImage::draw()
{
    // this is an inefficent, but simple mode of drawing an image
    // we draw one rectangle for every pixel
    // use the fastDraw() method if you want something faster
    for( int x=0; x<width; x++ )
    {
        for( int y=0; y<height; y++ )
        {
            float grayValue = getPixel(x,y);            // get the gray value
            grayValue = grayValue / 255;                // convert from 0-255 to 0.0-1.0
            po::setColor( poColor( grayValue, grayValue, grayValue) );  // set the color
            po::drawFilledRect( x*5,y*5, 5, 5 );        // draw the "pixel" rectangle
        }
    }
}

void    smImage::fastDraw( float x, float y )
{
    // set color to white, otherwise, image will be tinted
    po::setColor( poColor::white );
    // replace the image data int the texture
    imageAsTexture->replace( imageData );
    // draw the texture
    po::drawTexturedRect( imageAsTexture, poRect(x+0,y+height,width,-height) );
}












