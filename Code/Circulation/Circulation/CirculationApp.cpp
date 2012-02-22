/*	Created by Johann Diedrick and Ann Chen on 2/22/12.
 *	Copyright 2012 __Circulation__. All rights reserved.
 */

#include "CirculationApp.h"
#include "poApplication.h"
#include "poCamera.h"


// APP CONSTRUCTOR. Create all objects here.
CirculationApp::CirculationApp() {
	addModifier(new poCamera2D(poColor::black));
}

// APP DESTRUCTOR. Delete all objects here.
CirculationApp::~CirculationApp() {
}

// UPDATE. Called once per frame. Animate objects here.
void CirculationApp::update() {
	
}

// DRAW. Called once per frame. Draw objects here.
void CirculationApp::draw() {
	
}

// EVENT HANDLER. Called when events happen. Respond to events here.
void CirculationApp::eventHandler(poEvent *event) {
	
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void CirculationApp::messageHandler(const std::string &msg, const poDictionary& dict) {
	
}
