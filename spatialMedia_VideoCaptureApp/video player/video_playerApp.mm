/*	Created by Joshua Fisher on 2/15/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "video_playerApp.h"

#include "poCamera.h"
#include "poHelpers.h"
#include "poApplication.h"
#include "poShapeBasics2D.h"


// APP CONSTRUCTOR. Create all objects here.
video_playerApp::video_playerApp() {
	addModifier(new poCamera2D(poColor::black));

	// make new video capture object
	capture = new poVideoCapture();
    
    // list video devices
    capture->listVideoDevices();
    
    // start video capture
    // to access an external camera, add camera ID (e.g. "0xfa20000005ac850a") as second input
	capture->startCapture(poPoint(320,240));    

    // make smImage to copy video imge into
    frameImage = new smImage(320,240);
}


// APP DESTRUCTOR. Delete all objects here.
video_playerApp::~video_playerApp() {
}


// UPDATE. Called once per frame. Animate objects here.
void video_playerApp::update() {
}


// DRAW. Called once per frame. Draw objects here.
void video_playerApp::draw() {
	
    if(capture->isCapturing()) 
    {
        // copy in video image into smImage
        frameImage->copyImageFromMemory( capture->getGreyPixels() );
        // and draw it
        frameImage->fastDraw(0,0);
	}
    
}

// EVENT HANDLER. Called when events happen. Respond to events here.
void video_playerApp::eventHandler(poEvent *event) {
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void video_playerApp::messageHandler(const std::string &msg, const poDictionary& dict) {
}


