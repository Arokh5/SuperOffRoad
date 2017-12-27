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

	vector<ModulePlayer*> cars;

private:
	int GetRandomCheckpoint();
	void DetectCheckpoints(ModulePlayer* car);

private:
	SDL_Texture* graphics = nullptr;
	vector<vector<iPoint>> checkpointContainer1;
};

#endif // __MODULEPLAYER_H__