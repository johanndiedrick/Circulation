//  Created by Joshua Fisher on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#pragma once
#include "poHelpers.h"


class poVideoCaptureImpl;

class poVideoCapture {
public:
	poVideoCapture();
	~poVideoCapture();
	
	void startCapture(poPoint size=poPoint(640,480), const std::string &deviceID="");
	void stopCapture();
	bool isCapturing();
	
	float getWidth();
	float getHeight();
	poPoint getSize();
	// it better be big enought to hold dataSize bytes
	uint8_t *getPixels();
	uint8_t *getGreyPixels();
    
    void listVideoDevices();
	
private:
	poVideoCaptureImpl *impl;
	uint8_t *greyPixels;
};


