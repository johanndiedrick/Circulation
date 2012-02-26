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
//constructor, nothing goes here    
}

Title::Title(std::string _text){
    
    std::string text = _text;
    
    titleText = new poTextBox(100,100);
    titleText->setText( text );						// Set the text based on the value of the node
    titleText->setFont( poGetFont("Helvetica", "Regular") );
    titleText->setTextSize(13);
    titleText->textColor = poColor::white;
    titleText->doLayout();
    titleText->position.set(150, -150, 0);
    addChild(titleText);

}


void Title::update(){
    //code to make titles move around, change rotation speed etc.
}

void Title::eventHandler(poEvent *event){
    //code to make titles change color or do something on an event
    
}