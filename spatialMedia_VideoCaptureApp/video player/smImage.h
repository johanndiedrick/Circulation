
//  smImage.h
//  spatialMedia

#ifndef spatialMedia_smImage_h
#define spatialMedia_smImage_h

#include "poTexture.h"
#include "poTextBox.h"	

class smImage
{
public:
    // the image constructor
    smImage( const char* fileName, int W, int H );
    smImage( int W, int H );
    
    // draw image methods
    void    draw();
    void    fastDraw( float x, float y );
    
    // get and set pixel methods
    int     getPixel( int x, int y );
    void    setPixel( int x, int y, int grayValue );
    void    setAllPixels( int grayValue );
    void    copyImageFromMemory( unsigned char*  imageBuffer );
    
    // image data variables
    int             width, height;
    unsigned char*  imageData;

    // this poTexture is used for the fastDraw method
    poTexture*      imageAsTexture;
    
};


#endif
