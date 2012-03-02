//
//  Title.cpp
//  Circulation
//
//  Created by Johann Diedrick on 2/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "Title.h"
#include "CirculationApp.h"
#include <iostream>

Title::Title(){

   
    
}

Title::Title(std::string _text){
    
    positiveQuadrant = 1;
    bounded = 1;
    
    float velX = poRand(-0.6, 0.6);
	float velY = poRand(-0.6, 0.6);
	
	velocity.set(velX, velY, 0);
    
    if(velocity.getLength() < 0.2) {
		velocity *= (0.2 / velocity.getLength());
	}
	
	rotationSpeed = poRand( -1.0, 1.0 );
    
    
    
    std::string text = _text;
    
    poColor lavender;
    lavender.set("#2E0854");
    
    titleText = new poTextBox(100,100);
    titleText->setText( text );						// Set the text based on the value of the node
    titleText->setFont( poGetFont("Helvetica", "Regular") );
    titleText->setTextSize(13);
    titleText->textColor = lavender;
    titleText->doLayout();
    
    //give our text a random position
   
    addChild(titleText);

}



void Title::draw(){

}

void Title::update(){
    //code to make titles move around, change rotation speed etc.
    
	
    
    if(positiveQuadrant==1){
        if( position.x > 300 || position.x < 0 ) velocity.x *= -1;
        if( position.y > 0 || position.y < -300) velocity.y *= -1;
	}
    
    if(positiveQuadrant==0){
        if( position.x > 0 || position.x < -300 ) velocity.x *= -1;
        if( position.y > 300 || position.y < 0) velocity.y *= -1;
    }
	
    if(bounded==1){
        position += velocity;
    }
    
    if(bounded==0){
        //move radially
        position.x = position.x + position.x/(sqrt((position.x*position.x) + (position.y*position.y)));  
        position.y = position.y + position.y/(sqrt((position.x*position.x) + (position.y*position.y)));
        
    }
    
	rotation += rotationSpeed;

    
    
}

void Title::eventHandler(poEvent *event){
    //code to make titles change color or do something on an event
    
}