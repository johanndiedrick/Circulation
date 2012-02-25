/////////////////////////////////////////
//
// pocode application configuration
//
/////////////////////////////////////////


#include "poApplication.h"
#include "CirculationApp.h"

poObject *createObjectForID(uint uid) {
	return new CirculationApp();
}

void setupApplication() {
    lookUpAndSetPath("resources");
	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "Circulation", 100, 100, 1024, 768);
}

void cleanupApplication() {
}