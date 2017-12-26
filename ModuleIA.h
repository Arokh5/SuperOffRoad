#ifndef __MODULEIA_H__
#define __MODULEIA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModuleIA : public Module
{
public:
	ModuleIA(bool start_enabled = true);
	~ModuleIA();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();

private:
	const int carsNumber = 3;
	const int shadowsOffset = 2;
	SDL_Texture* graphics = nullptr;
	vector<Animation> turn;
	vector<Animation> standardShadows;
	vector<Animation*> currentAnimation;
	vector<Animation*> currentShadowsAnimation;
	vector<iPoint> position;
};

#endif // __MODULEPLAYER_H__