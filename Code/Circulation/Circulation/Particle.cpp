//
//  Particle.cpp
//  Circulation
//
//  Created by Johann Diedrick on 2/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Particle.h"
#include "poTextBox.h"

Particle::Particle() {
	
    positiveQuadrant = 1;
    bounded = 1;
	float defaultScale = poRand(0.4, 1);
    
    letter[0] = 'A';
    letter[0] = 'A' + rand()%26;
    letter[1] = 0;
    
    float posX = 0;
	float posY = 0;
    
    float hypotenuse=0;
    
    //	position.set(posX, posY, 0);
	
	float velX = poRand(-0.6, 0.6);
	float velY = poRand(-0.6, 0.6);
	
	velocity.set(velX, velY, 0);
	
	if(velocity.getLength() < 0.2) {
		velocity *= (0.2 / velocity.getLength());
	}
	
	rotationSpeed = poRand( -1.0, 1.0 );
}

void Particle::draw()
{
    poColor lavender;
    lavender.set("#BF5FFF");
    po::setColor(lavender);
    po::drawString( letter, poGetFont("Helvetica", "Regular") , poPoint(0,0), 12.0 ); 
    
   // po::setColor(poColor(1.0, 0.0, 0.0));
   // po::drawStrokedRect(150,150,100,100); //fun accident...
    //po::drawFilledRect(600,300,10,10);
}

void Particle::update() {
	
	
	
//	if( position.x > 300 || position.x < 0 ) velocity.x *= -1;
//	if( position.y > 0 || position.y < -300 ) velocity.y *= -1;
    
    //if( (position.x > 300 || position.x < 0) || (position.x < -300 || position.x > 0) ) velocity.x *= -1;//doesnt work :/
	//if( (position.y > 0 || position.y < -300) || (position.y > 300 || position.y < 0) ) velocity.y *= -1;//doesnt work :/
    
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

void Particle::eventHandler(poEvent *event) {
		
}
