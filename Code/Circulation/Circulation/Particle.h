//
//  Particle.h
//  Circulation
//
//  Created by Johann Diedrick on 2/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Circulation_Particle_h
#define Circulation_Particle_h

#include "poObject.h"
#include "poShapeBasics2D.h"
#include "poTextBox.h"

class Particle : public poObject {
public:
	Particle();
	
    virtual void draw();
	virtual void update();
	virtual void eventHandler(poEvent* event);
	
	poPoint	velocity;
	float	rotationSpeed;
    
    poTextBox* A;
    
    char    letter[8];
    
    
};


#endif
