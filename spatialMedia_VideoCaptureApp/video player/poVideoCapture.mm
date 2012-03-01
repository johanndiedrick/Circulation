//  Created by Joshua Fisher on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#include "poVideoCapture.h"

#include <QTKit/QTKit.h>
#include <boost/thread.hpp>

class poVideoCaptureImpl {
public:
	virtual void startCapture(poPoint size, const std::string &deviceID) = 0;
	virtual void stopCapture() = 0;
	virtual bool isCapturing() = 0;
	
	virtual poPoint getSize() = 0;
	virtual uint8_t *getPixels() = 0;
    
    virtual void listVideoDevices() = 0;
};

class osxVidCap;

@interface osxVidCapDelegate : NSObject {
	osxVidCap *capture;
}
-(id)initWithCap:(osxVidCap*)cap;
@end

class osxVidCap : public poVideoCaptureImpl {
public:
	osxVidCap() : buffer(NULL), pixels(NULL)
	{}
	
	virtual void startCapture(poPoint size, const std::string &s) {
        NSString *deviceID = [NSString stringWithUTF8String:s.c_str()];
		dispatch_async(dispatch_get_main_queue(), ^{
            QTCaptureDevice *videoDevice;
            if(!deviceID.length) {
                videoDevice = [QTCaptureDevice defaultInputDeviceWithMediaType:QTMediaTypeVideo];
            }
            else {
                videoDevice = [QTCaptureDevice deviceWithUniqueID:deviceID];
                if(!videoDevice) {
                    printf("'%s' is not a valid device id", [deviceID UTF8String]);
                    return;
                }
            }
			
            session = [[QTCaptureSession alloc] init];

			NSError *error = nil;
			BOOL success = [videoDevice open:&error];
			
			videoIn = [[QTCaptureDeviceInput alloc] initWithDevice:videoDevice];
			success = [session addInput:videoIn error:&error];
			
			NSDictionary *outputOpts = [NSDictionary dictionaryWithObjectsAndKeys:
										[NSNumber numberWithFloat:size.x], kCVPixelBufferWidthKey,
										[NSNumber numberWithFloat:size.y], kCVPixelBufferHeightKey,
										[NSNumber numberWithUnsignedInt:kCVPixelFormatType_24RGB], kCVPixelBufferPixelFormatTypeKey,
										nil];
			QTCaptureDecompressedVideoOutput *vout = [[QTCaptureDecompressedVideoOutput alloc] init];
			[vout setPixelBufferAttributes:outputOpts];
			[vout setDelegate:[[osxVidCapDelegate alloc] initWithCap:this]];
			
			videoOut = vout;
			success = [session addOutput:videoOut error:&error];
			
			[session startRunning];
		});
	}
	
	virtual void stopCapture() {
		[session stopRunning];
		[videoIn release];
		[session release];
		delete [] pixels;
		pixels = NULL;
	}
	
	virtual bool isCapturing() {
		return buffer != NULL;
	}
	
	void setPixelBuffer(CVPixelBufferRef pix) {
		if(buffer) {
			CVPixelBufferRelease(buffer);
			buffer = NULL;
		}
		
		if(pix) {
			buffer = pix;
			CVPixelBufferRetain(buffer);
			
			if(mutex.try_lock()) {
				size_t dataSize = CVPixelBufferGetDataSize(buffer);
				if(!pixels)
					pixels = new uint8_t[dataSize];
				
				CVPixelBufferLockBaseAddress(buffer, 0);
				memcpy(pixels, CVPixelBufferGetBaseAddress(buffer), dataSize);
				CVPixelBufferUnlockBaseAddress(buffer, 0);
				
				mutex.unlock();
			}
		}
	}
	
	virtual poPoint getSize() {
		return poPoint(CVPixelBufferGetWidth(buffer), CVPixelBufferGetHeight(buffer));
	}
	
	virtual uint8_t *getPixels() {
		boost::lock_guard<boost::mutex> lock(mutex);
		return pixels;
	}
    
    virtual void listVideoDevices() {
        printf("video devices:\n");
        int count = 0;
        NSArray *devices = [QTCaptureDevice inputDevicesWithMediaType:QTMediaTypeVideo];
        for(QTCaptureDevice *device in devices) {
            printf("\t%d: '%s' '%s' (%s)\n", ++count, [[device localizedDisplayName] UTF8String], [[device modelUniqueID] UTF8String], [[device uniqueID] UTF8String]);
        }
    }

	QTCaptureSession *session;
	QTCaptureInput *videoIn;
	QTCaptureOutput *videoOut;
	CVPixelBufferRef buffer;
	uint8_t *pixels;
	boost::mutex mutex;
};

@implementation osxVidCapDelegate 
-(id)initWithCap:(osxVidCap*)cap {
	if(self = [super init]) {
		capture = cap;
	}
	return self;
}
-(void)captureOutput:(QTCaptureOutput *)captureOutput didOutputVideoFrame:(CVImageBufferRef)videoFrame withSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection {
	capture->setPixelBuffer((CVPixelBufferRef)videoFrame);
}
@end





poVideoCapture::poVideoCapture()
:	impl(new osxVidCap()), greyPixels(NULL)
{}

poVideoCapture::~poVideoCapture() {
	if(impl) {
		impl->stopCapture();
		delete impl;
	}
	
	if(greyPixels)
		delete [] greyPixels;
}

void poVideoCapture::startCapture(poPoint size, const std::string &deviceID) {
    if(!impl->isCapturing())
        impl->startCapture(size, deviceID);
}

void poVideoCapture::stopCapture() {
    impl->stopCapture();
    delete impl;
    impl = NULL;
    
    if(greyPixels) {
        delete [] greyPixels;
        greyPixels = NULL;
    }
}
bool poVideoCapture::isCapturing() {
	return impl->isCapturing();
}

float poVideoCapture::getWidth() {return impl->getSize().x;}
float poVideoCapture::getHeight() {return impl->getSize().y;}
poPoint poVideoCapture::getSize() {return impl->getSize();}
uint8_t* poVideoCapture::getPixels() {return impl->getPixels();}
uint8_t* poVideoCapture::getGreyPixels() {
	if(impl->getPixels()) {
		int w = getWidth();
		int h = getHeight();
		
		if(!greyPixels)
			greyPixels = new uint8_t[w * h];

		for(int y=0; y<h; y++)
			for(int x=0; x<w; x++) {
				uint8_t *pixel = impl->getPixels() + (y*w+x)*3;
				float grey = (float)pixel[0] * 0.3f + (float)pixel[1] * 0.59f + (float)pixel[2] * 0.11f;
				greyPixels[y*w+x] = (uint8_t)grey;
			}
	}
	
	return greyPixels;
}

void poVideoCapture::listVideoDevices() {impl->listVideoDevices();}



