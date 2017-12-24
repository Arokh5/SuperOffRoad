#ifndef __MODULEIA_H__
#define __MODULEIA_H__

#include "ModulePlayer.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModuleIA : public ModulePlayer
{
public:
	ModuleIA(bool start_enabled = true);
	~ModuleIA();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();
};

#endif // __MODULEPLAYER_H__