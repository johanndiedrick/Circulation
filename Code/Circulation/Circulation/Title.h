//
//  Title.h
//  Circulation
//
//  Created by Johann Diedrick on 2/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Circulation_Title_h
#define Circulation_Title_h

#include "poObject.h"
#include "poTextBox.h"
#include <iostream>

class Title : public poObject{
public:
    Title();
    Title(std::string _text);

    virtual void draw();
    virtual void update();
    virtual void eventHandler(poEvent* event);
    
    poTextBox* titleText;
    
    //things for movement
    poPoint velocity;
    float rotationSpeed;
    
    int positiveQuadrant;
    int bounded; 
    
};



#endif
