//  Created by Joshua Fisher on 2/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#include "poVideoPlayer.h"
#include "poApplication.h"
#include "poOpenGLState.h"
#include "poBasicRenderer.h"

#include <QTKit/QTKit.h>
#include <CoreVideo/CoreVideo.h>
#include <Quicktime/Quicktime.h>

#include <boost/thread.hpp>

class poVideoPlayerImpl {
public:
	virtual void setPlaying(bool b) = 0;
	virtual void rewind() = 0;
	virtual void seek(float time) = 0;
	virtual void setVolume(float vol) = 0;
	virtual void setMuted(bool m) = 0;
	virtual void getTextureProperties(GLenum &target, GLuint &texID, poRect &coords) = 0;
	virtual poPoint getSize() = 0;
	virtual void update() = 0;
};

static CVReturn FrameRenderCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *inNow, const CVTimeStamp *inOutputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext);

class osxVidPlayer : public poVideoPlayerImpl {
public:
	osxVidPlayer(const fs::path &path)
	:	player(nil), context(nil), buffer(nil), dlink(nil)
	{
		CVDisplayLinkCreateWithCGDisplay(kCGDirectMainDisplay, &dlink);
		CVDisplayLinkSetOutputCallback(dlink, &FrameRenderCallback, this);
		
		NSString *url = [NSString stringWithUTF8String:path.c_str()];
		dispatch_async(dispatch_get_main_queue(), ^{
			NSDictionary *attribs = [NSDictionary dictionaryWithObjectsAndKeys:
									 url, QTMovieFileNameAttribute,
									 [NSNumber numberWithBool:YES], QTMovieOpenForPlaybackAttribute,
									 nil];
			
			NSError *error = nil;
			player = [[QTMovie alloc] initWithAttributes:attribs error:&error];
			[player detachFromCurrentThread];
		});
	}
	
	void setMuted(bool b) {
		[player setMuted:b];
	}
	
	void setVolume(float f) {
		[player setVolume:f];
	}
	
	void setPlaying(bool b) {
		if(b) {
			[player play];
			CVDisplayLinkStart(dlink);
		}
		else {
			[player stop];
			CVDisplayLinkStop(dlink);
		}
	}
	
	void rewind() {
		[player gotoBeginning];
	}
	
	void seek(float time) {
		QTTime timestamp = [player duration];
		timestamp.timeValue = time;
		[player setCurrentTime:timestamp];
	}
	
	void updateFrameForTime(const CVTimeStamp* timestamp) {
		NSAutoreleasePool *pool = [NSAutoreleasePool new];

		if(QTVisualContextIsNewImageAvailable(context, timestamp)) {
			if(buffer) {
				CVOpenGLTextureRelease(buffer);
				buffer = NULL;
			}
			
			OSStatus status = QTVisualContextCopyImageForTime(context, NULL, timestamp, &buffer);
			CVOpenGLTextureRetain(buffer);
		}
		
		[pool release];
	}

	void getTextureProperties(GLenum &target, GLuint &texID, poRect &coordinates) {
		target = CVOpenGLTextureGetTarget(buffer);
		texID = CVOpenGLTextureGetName(buffer);
		
		GLfloat coords[8];
		CVOpenGLTextureGetCleanTexCoords(buffer, coords, coords+2, coords+4, coords+6);

		coordinates.x = coords[6];
		coordinates.y = coords[7];
		coordinates.width = coords[2] - coordinates.x;
		coordinates.height = coords[3] - coordinates.y;
	}
	
	poPoint getSize() {
		NSSize movieSize;
		[[player attributeForKey:QTMovieNaturalSizeAttribute] getValue:&movieSize];
		return poPoint(movieSize.width, movieSize.height);
	}
	
	void update() {
		if(player && !context) {
			[QTMovie enterQTKitOnThread];
			[player attachToCurrentThread];
			
			CGLContextObj cglContext = CGLGetCurrentContext();
			CGLPixelFormatObj cglPixelFormat = CGLGetPixelFormat(cglContext);
			OSStatus err = QTOpenGLTextureContextCreate(NULL, cglContext, cglPixelFormat, NULL, &context);
			[player setVisualContext:context];
			
			if(CVDisplayLinkIsRunning(dlink))
				[player play];
		}
	}

	QTMovie *player;
	QTVisualContextRef context;
	CVOpenGLTextureRef buffer;
	CVDisplayLinkRef dlink;
};

static CVReturn FrameRenderCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *inNow, const CVTimeStamp *inOutputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext) {
	osxVidPlayer *player = (osxVidPlayer*)displayLinkContext;
	player->updateFrameForTime(inOutputTime);
	return kCVReturnSuccess;
}



poVideoPlayer::poVideoPlayer()
: impl(NULL), playing(false)
{}
poVideoPlayer::~poVideoPlayer() {
	if(impl) {
		impl->setPlaying(false);
		delete impl;
	}
}
void poVideoPlayer::openFile(const fs::path &url) {
	impl = new osxVidPlayer(url);
}
void poVideoPlayer::setPlaying(bool b) {impl->setPlaying(b); playing=b;}
bool poVideoPlayer::isPlaying() {return playing;}
void poVideoPlayer::rewind() {impl->rewind();}
void poVideoPlayer::seek(float time) {impl->seek(time);}
void poVideoPlayer::setVolume(float vol) {impl->setVolume(vol); volume=vol;}
float poVideoPlayer::getVolume() {return volume;}
void poVideoPlayer::setMuted(bool b) {impl->setMuted(b); muted=b;}
bool poVideoPlayer::isMuted() {return muted;}
void poVideoPlayer::update() {
	if(impl)
		impl->update();
}
void poVideoPlayer::draw() {
	if(impl) {
		GLint program;
		glGetIntegerv(GL_CURRENT_PROGRAM, &program);
		glUseProgram(0);

		GLenum target;
		GLuint texID;
		poRect coordinants;
		impl->getTextureProperties(target, texID, coordinants);
		poPoint size = impl->getSize();
		
		float verts[8] = {
			0,0,
			100,0,
			100,100,
			0,100
		};
		
		float coords[8] = {
			coordinants.x, coordinants.y,
			coordinants.x+coordinants.width, coordinants.y,
			coordinants.x+coordinants.width, coordinants.y+coordinants.height,
			coordinants.x, coordinants.y+coordinants.height
		};
		
		float w=getWindowWidth(), h=getWindowHeight();
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, w, 0, h, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(target);
		glBindTexture(target, texID);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verts);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, coords);
		glDrawArrays(GL_QUADS, 0, 4);
		glBindTexture(target, 0);
		glDisable(target);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glUseProgram(program);
	}
}

