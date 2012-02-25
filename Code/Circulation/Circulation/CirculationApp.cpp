/*	Created by Johann Diedrick and Ann Chen on 2/22/12.
 *	Copyright 2012 __Circulation__. All rights reserved.
 */

#include "CirculationApp.h"
#include "poApplication.h"
#include "poCamera.h"
#include "poSimpleDrawing.h"
#include "poShapeBasics2D.h"
#include "poTextBox.h"

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
using namespace boost;


// APP CONSTRUCTOR. Create all objects here.
CirculationApp::CirculationApp() {
	addModifier(new poCamera2D(poColor::black));
    
    //load xml document
    poXMLDocument doc = poXMLDocument("library.xml");
    
    //get root node
    poXMLNode rootNode = doc.getRootNode();
    //get first child of root, which should be row
    poXMLNode nodeRow = rootNode.getFirstChild();
    poXMLNode nodeTitle = nodeRow.getFirstChild();
    std::string title = nodeTitle.getInnerString();
    
    printf("%s\n", title.c_str());
    
    
    //add four poShape objects for our circle
    
    int radius = 300;
    A = new poShape2D();
    A->addPoint(0,0);
    for (int i = 0; i<91; i++){
        float x = radius*cos_deg(i);
        float y = -radius*sin_deg(i);
        
        poPoint P = poPoint(x, y);
        A->addPoint(P);
    }

    A->fillColor = poColor::orange;
    A->position.set(getWindowWidth()/2, getWindowHeight()/2, 0);
    A->rotation =  0;
    addChild(A);
    
    B = new poShape2D();
    B->addPoint(0,0);
    for (int i = 0; i<91; i++){
        float x = radius*cos_deg(i);
        float y = radius*sin_deg(i);
        
        poPoint P = poPoint(x, y);
        B->addPoint(P);
    }
    
    B->fillColor = poColor::blue;
    B->position.set(getWindowWidth()/2, getWindowHeight()/2, 0);
    B->rotation =  0;
    addChild(B);
    
    C = new poShape2D();
    C->addPoint(0,0);
    for (int i = 0; i<91; i++){
        float x = -radius*cos_deg(i);
        float y = radius*sin_deg(i);
        
        poPoint P = poPoint(x, y);
        C->addPoint(P);
    }
    
    C->fillColor = poColor::green;
    C->position.set(getWindowWidth()/2, getWindowHeight()/2, 0);
    C->rotation =  0;
    addChild(C);
    
    D = new poShape2D();
    D->addPoint(0,0);
    for (int i = 0; i<91; i++){
        float x = -radius*cos_deg(i);
        float y = -radius*sin_deg(i);
        
        poPoint P = poPoint(x, y);
        D->addPoint(P);
    }
    
    D->fillColor = poColor::red;
    D->position.set(getWindowWidth()/2, getWindowHeight()/2, 0);
    D->rotation =  0;
    addChild(D);
  

}

// APP DESTRUCTOR. Delete all objects here.
CirculationApp::~CirculationApp() {
}

// UPDATE. Called once per frame. Animate objects here.
void CirculationApp::update() {
    
    if(A->rotation == 360){
        A->rotation = 0;
    }
    if(B->rotation == 360){
        B->rotation = 0;
    }
    if(C->rotation == 360){
        C->rotation = 0;
    }
    if(D->rotation == 360){
        D->rotation = 0;
    }
	A->rotation += 1.0;
    B->rotation += 1.0;
    C->rotation += 1.0;
    D->rotation += 1.0;

    
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
