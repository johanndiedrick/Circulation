//  Created by Joshua Fisher on 2/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#pragma once

#include "poObject.h"
#include "poHelpers.h"

class poVideoPlayerImpl;

class poVideoPlayer : public poObject {
public:
	poVideoPlayer();
	~poVideoPlayer();
	
	void openFile(const fs::path &url);
	
	void setPlaying(bool b);
	bool isPlaying();
	void rewind();
	void seek(float time);
	
	void setVolume(float vol);
	float getVolume();
	void setMuted(bool m);
	bool isMuted();
	
	void update();
	void draw();
	
private:
	poVideoPlayerImpl *impl;
	bool playing, muted;
	float volume;
};