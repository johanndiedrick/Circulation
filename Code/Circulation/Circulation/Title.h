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

class Title : public poObject{
public:
    Title();
    
    virtual void update();
    virtual void eventHandler(poEvent* event);
    
    poTextBox* titleText;
    
    //things for movement
    poPoint velocity;
    float rotationSpeed;
    
    
};



#endif
