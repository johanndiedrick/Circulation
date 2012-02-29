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
	
	float defaultScale = poRand(0.4, 1);
    
    letter[0] = 'A';
    letter[0] = 'A' + rand()%26;
    letter[1] = 0;
    
    //    std::string alphabet;
    //    
    //    for (int i = 0; i < letter.length; i++) {
    //        letters[i] = 0;
    //    }
    
    
    
    /*A = new poTextBox(10, 10);
     A->setText("A");
     A->setFont( poGetFont("Helvetica", "Regular") );
     A->setTextSize(12);
     A->textColor = poColor::grey;
     A->doLayout();
     A->drawBounds = false;
     addChild( A );*/
    
	
    //	shape = new poStarShape( 50, 50, 5, 10 );
    //	shape->fillColor = poColor::orange;
    //	shape->alpha = 0.75;
    //	shape->setAlignment(PO_ALIGN_CENTER_CENTER);
    //	shape->scale.set(defaultScale, defaultScale, 1);
    //	shape->scaleTween.setTweenFunction(PO_TWEEN_QUAD_OUT_FUNC);
    //	shape->scaleTween.setRepeat(PO_TWEEN_REPEAT_PINGPONG, 1);
    //	shape->scaleTween.setDuration(1);
    //	shape->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this, "particle_clicked");
    //	addChild(shape);
	
	float posX = poRand(100, 700);
	float posY = poRand(200, 500);
	
	position.set(posX, posY, 0);
	
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
    po::setColor( poColor::white );
    po::drawString( letter, poGetFont("Helvetica", "Regular") , poPoint(0,0), 12.0 ); 
}

void Particle::update() {
	
	position += velocity;
	
	if( position.x > 750 || position.x < 50 ) velocity.x *= -1;
	if( position.y > 550 || position.y < 150 ) velocity.y *= -1;
	
	rotation += rotationSpeed;
}

void Particle::eventHandler(poEvent *event) {
	
	if( event->message == "particle_clicked" ) {
		
		if( shape->scaleTween.isRunning() )
			return;
		
		shape->scaleTween.set( poPoint(2, 2, 1) );
		shape->scaleTween.start();
	}
	
}
