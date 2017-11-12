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
	update_status Update();
	bool CleanUp();

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
};

#endif // __MODULESTAGE_H__