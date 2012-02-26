/*	Created by Johann Diedrick on 2/22/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "poShape2D.h"


class CirculationApp : public poObject {
public:
	CirculationApp();
	virtual ~CirculationApp();
	
    virtual void update();
    
    virtual void draw();
	
    virtual void eventHandler(poEvent *event);
	
    virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
    
    poShape2D* A;
    poShape2D* B;
    poShape2D* C;
    poShape2D* D;
    
    int rotationValue;
    
    char lastKeyDown;
};

