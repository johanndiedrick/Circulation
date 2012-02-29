/*	Created by Johann Diedrick and Ann Chen on 2/22/12.
 *	Copyright 2012 __Circulation__. All rights reserved.
 */

#include "CirculationApp.h"
#include "poApplication.h"
#include "poCamera.h"
#include "poSimpleDrawing.h"
#include "poShapeBasics2D.h"
#include "poTextBox.h"
#include "Title.h"
#include "Particle.h"

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
using namespace boost;


// APP CONSTRUCTOR. Create all objects here.
CirculationApp::CirculationApp() {
	addModifier(new poCamera2D(poColor::white));
    
    addEvent(PO_KEY_DOWN_EVENT, this);
    addEvent(PO_KEY_UP_EVENT, this);

    
    lastKeyDown = 'x';
    
    //load xml document
    poXMLDocument doc = poXMLDocument("test.xml");
    
    //get root node
    poXMLNode rootNode = doc.getRootNode();
   
    int numChildrenOfRoot = rootNode.getNumChildren(); // number of rows (which is number of titles
    
    
    //add four poShape objects for our circle
    
    int radius = 300;
    A = new poShape2D(); // top right
    A->addPoint(0,0);
    for (int i = 0; i<91; i++){
        float x = radius*cos_deg(i);
        float y = -radius*sin_deg(i);
        
        poPoint P = poPoint(x, y);
        A->addPoint(P);
    }
    
    //set color
    poColor seafoam;
    seafoam.set("#BDFCC9");
    A->fillColor = seafoam;
   
    A->position.set(getWindowWidth()/2, getWindowHeight()/2, 0);
    A->rotation =  0;
    addChild(A);
    
    // bottom right
    B = new poShape2D();
    B->addPoint(0,0);
    for (int i = 0; i<91; i++){
        float x = radius*cos_deg(i);
        float y = radius*sin_deg(i);
        
        poPoint P = poPoint(x, y);
        B->addPoint(P);
    }
    
    B->fillColor = poColor::white; 
    B->position.set(getWindowWidth()/2, getWindowHeight()/2, 0);
    B->rotation =  0;
    addChild(B);
    
    //bottom left
    C = new poShape2D();
    C->addPoint(0,0);
    for (int i = 0; i<91; i++){
        float x = -radius*cos_deg(i);
        float y = radius*sin_deg(i);
        
        poPoint P = poPoint(x, y);
        C->addPoint(P);
    }
    
    //set color
    
    C->fillColor = seafoam;
    
    C->position.set(getWindowWidth()/2, getWindowHeight()/2, 0);
    C->rotation =  0;
    addChild(C);
    
    
    //top left
    D = new poShape2D();
    D->addPoint(0,0);
    for (int i = 0; i<91; i++){
        float x = -radius*cos_deg(i);
        float y = -radius*sin_deg(i);
        
        poPoint P = poPoint(x, y);
        D->addPoint(P);
    }   
    
    D->fillColor = poColor::white;
    D->position.set(getWindowWidth()/2, getWindowHeight()/2, 0);
    D->rotation =  0;
    addChild(D);
    
    //lets add some titles, based on the number of title entries we have in the xml file!
   for (int i=0; i<rootNode.getNumChildren(); i++){
        poXMLNode node_Row = rootNode.getChild(i);     //get first child of root, which should be a row
    poXMLNode node_Title = node_Row.getChild("title");
        
    std::string xml_Title = node_Title.getInnerString();
   // printf("%s\n", xml_Title.c_str());
        Title* newTitle = new Title(xml_Title);
       float posX = poRand(0,200);
       float posY = poRand(-200,0);
       newTitle->position.set(posX, posY, 0);
        A->addChild(newTitle); // add titles to upper right
}
    
    
    for (int i=0; i<rootNode.getNumChildren(); i++){
        poXMLNode node_Row = rootNode.getChild(i);     //get first child of root, which should be a row
        poXMLNode node_Title = node_Row.getChild("title");
        
        std::string xml_Title = node_Title.getInnerString();
        // printf("%s\n", xml_Title.c_str());
        Title* newTitle = new Title(xml_Title);
        float posX = poRand(-200,0);
        float posY = poRand(0,200);
        newTitle->position.set(posX, posY, 0);
        C->addChild(newTitle); //add titles to bottom left
    }

    
    
    int rotationValue = 0;
    
    //printf("%i", numChildrenOfRow);
    //printf("%i", numChildrenOfRoot);
    
    if(A->pointInside(poPoint(100,100), true) == true){
        printf("true!");
    }else
        printf("false :(");
    
    //lets add some alphabet particles!
    for(int i=0; i < 200; i++) {
		Particle* P = new Particle();
        float posX = poRand(0, 300);
        float posY = poRand(-300, 0);
        
        P->position.set(posX, posY, 0);
		A->addChild(P);
	}
    
    //lets add some alphabet particles!
    for(int i=0; i < 200; i++) {
		Particle* P = new Particle();
        float posX = poRand(-300, 0);
        float posY = poRand(0, 300);
        
        P->position.set(posX, posY, 0);
		C->addChild(P);
	}
    
  


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
        
  
    
    //rotate circle
    if(lastKeyDown=='p'){
       // printf("Rotating Clockwise...\n");
        rotationValue++;
    }
    
    if(lastKeyDown=='o'){
      //  printf("Rotating Counterclockwise...\n");
        rotationValue--;
    }
    
    
	A->rotation =  rotationValue;
    B->rotation =  rotationValue;
    C->rotation =  rotationValue;
    D->rotation =  rotationValue;
   


    
}

// DRAW. Called once per frame. Draw objects here.
void CirculationApp::draw() {

}

// EVENT HANDLER. Called when events happen. Respond to events here.
void CirculationApp::eventHandler(poEvent *event) {
    
    if(event->type==PO_KEY_DOWN_EVENT){
        
        lastKeyDown = event->keyChar;
        
    }
    
   if(event->type==PO_KEY_UP_EVENT){
        lastKeyDown = 'x';
    }
	
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void CirculationApp::messageHandler(const std::string &msg, const poDictionary& dict) {
	
}
