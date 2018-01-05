#ifndef __MODULETITLESCREEN_H__
#define __MODULETITLESCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleTitleScreen : public Module
{
public:
	ModuleTitleScreen(bool start_enabled = true);
	~ModuleTitleScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr;
	SDL_Rect title;
	bool keyPressed;
};

#endif // __MODULETITLESCREEN_H__