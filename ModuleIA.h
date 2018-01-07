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
	int GetRandomCheckpoint(int lot) const;
	void DetectCheckpoints(ModulePlayer* car) const;
	void OnCheckpointExit(ModulePlayer* car) const;

private:
	vector<SDL_Texture*> graphics;
	const int checkpoint1Lot = 4;
	const int checkpoint2Lot = 4;
	const int checkpoint3Lot = 4;
	const int checkpoint4Lot = 4;
	const int checkpoint5Lot = 4;
	const int checkpoint6Lot = 2;
	const int checkpoint7Lot = 6;
	const int checkpoint8Lot = 3;
	vector<vector<fPoint>> checkpointContainer1;
	vector<vector<fPoint>> checkpointContainer2;
	vector<vector<fPoint>> checkpointContainer3;
	vector<vector<fPoint>> checkpointContainer4;
	vector<vector<fPoint>> checkpointContainer5;
	vector<vector<fPoint>> checkpointContainer6;
	vector<vector<fPoint>> checkpointContainer7;
	vector<vector<fPoint>> checkpointContainer8;
};

#endif // __MODULEPLAYER_H__