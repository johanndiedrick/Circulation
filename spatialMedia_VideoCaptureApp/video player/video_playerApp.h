/*	Created by Joshua Fisher on 2/15/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "poVideoPlayer.h"
#include "poVideoCapture.h"
#include "smImage.h"

class video_playerApp : public poObject {
public:
	video_playerApp();
	virtual ~video_playerApp();
	
    virtual void update();
    virtual void draw();
    virtual void eventHandler(poEvent *event);
    virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	poVideoPlayer   *player;
	poVideoCapture  *capture;
    
    smImage*        frameImage;
};

