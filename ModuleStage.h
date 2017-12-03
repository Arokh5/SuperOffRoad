#ifndef __MODULESTAGE_H__
#define __MODULESTAGE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

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

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	SDL_Rect fence1_1;
	SDL_Rect fence1_2;
	SDL_Rect fence2_1;
	SDL_Rect fence2_2;
	SDL_Rect fence3;
	SDL_Rect fence4;
	SDL_Rect fence5_1;
	SDL_Rect fence5_2;
};

#endif // __MODULESTAGE_H__