#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include <map>

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	vector<int> SetDirection(int cont);

public:
	SDL_Texture* graphics = nullptr;
	map<Animation*, vector<int>> idles;
	Animation turnRight;
	Animation* tempAnim;
	Animation turnLeft;
	iPoint position;
	Animation* currentAnimation;
	const float speed = 0.05f;
};

#endif // __MODULEPLAYER_H__