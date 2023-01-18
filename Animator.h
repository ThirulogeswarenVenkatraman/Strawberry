#ifndef _ANIMATOR_H
#define _ANIMATOR_H

#include "Timer.h"
#include <string>
#include <map>

typedef struct sheet_properties {
	int totalFrames;
	float animation_speed;
}sheet_properties;

class Animator {
	bool isPaused;
	std::string CurrentSheetID;
	std::map<std::string, sheet_properties> spritesheets;
private:
	int in_totalframe;
	int CurrentColumnX;
	float in_animationspeed;
	strad::Timer _timer;
public:
	Animator();
	~Animator();

	int getColumnX() { return this->CurrentColumnX; }
	std::string getStateID() { return this->CurrentSheetID; }

	void pauseAnimation() { isPaused = true; }
	void unpauseAnimation() { isPaused = false; }

	/* sprite-sheet for single state <row> */
	void loadState(std::string filename, std::string state_id, sheet_properties properties);
	void setState(std::string state_id);

	void update_animation();
};


#endif 
