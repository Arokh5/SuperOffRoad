#ifndef __MODULESTAGE_H__
#define __MODULESTAGE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "time.h"

struct SDL_Texture;

class ModuleStage : public Module
{
public:
	ModuleStage(bool start_enabled = true);
	~ModuleStage();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	SDL_Rect scoreboard;
	vector<SDL_Rect> playerCarNumbers;
	vector<SDL_Rect> blueCarNumbers;
	vector<SDL_Rect> yellowCarNumbers;
	vector<SDL_Rect> greyCarNumbers;
	SDL_Rect fence1_1;
	SDL_Rect fence1_2;
	SDL_Rect fence2_1;
	SDL_Rect fence2_2;
	SDL_Rect fence3;
	SDL_Rect fence4;
	SDL_Rect fence5_1;
	SDL_Rect fence5_2;
	bool titleScreen;
	clock_t seconds;
	clock_t tenthOfSecond;
	int tens;
	int units;
	int dsUnits;

	void GoTitleScreen();
	void RunTimer();
};

#endif // __MODULESTAGE_H__