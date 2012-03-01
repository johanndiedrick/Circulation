/////////////////////////////////////////
//
// pocode application configuration
//
/////////////////////////////////////////


#include "poApplication.h"
#include "video_playerApp.h"

poObject *createObjectForID(uint uid) {
	return new video_playerApp();
}

void setupApplication() {
	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "video_player", 100, 100, 1024, 768);
}

void cleanupApplication() {
}