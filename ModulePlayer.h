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
	ModulePlayer(bool start_enabled = true, const float speed = 0.3f);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	void SetDirection();

private:
	SDL_Texture* graphics = nullptr;
	Animation turn;
	iPoint position;
	const float speed;
	Animation* currentAnimation;
	bool still;
	bool right;
	vector<int> currentDirection { 0, 0 };
	vector<int> movementsDone;
};

#endif // __MODULEPLAYER_H__