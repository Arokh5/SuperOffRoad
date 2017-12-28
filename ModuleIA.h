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
	int GetRandomCheckpoint(int lot);
	void DetectCheckpoints(ModulePlayer* car);
	void OnCheckpointExit(ModulePlayer* car);

private:
	vector<SDL_Texture*> graphics;
	const float distanceOffset = 2.0f;
	const int checkpoint1Lot = 5;
	const int checkpoint2Lot = 4;
	const int checkpoint3Lot = 5;
	const int checkpoint4Lot = 4;
	const int checkpoint5Lot = 4;
	const int checkpoint6Lot = 2;
	const int checkpoint7Lot = 6;
	const int checkpoint8Lot = 3;
	vector<vector<iPoint>> checkpointContainer1;
	vector<vector<iPoint>> checkpointContainer2;
	vector<vector<iPoint>> checkpointContainer3;
	vector<vector<iPoint>> checkpointContainer4;
	vector<vector<iPoint>> checkpointContainer5;
	vector<vector<iPoint>> checkpointContainer6;
	vector<vector<iPoint>> checkpointContainer7;
	vector<vector<iPoint>> checkpointContainer8;
};

#endif // __MODULEPLAYER_H__