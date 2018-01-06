#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	bool CleanUp();

public:
	void StartingInitials();
	void SetDirection();
	bool DetectFences(iPoint position);
	void DetectBumps();
	bool DetectPool();
	bool SetRotationDirection(std::vector<std::vector<int>> fences);
	void SetBounceDirection(std::vector<std::vector<int>> fences);
	void ApplyBounceEffect();
	void MoveCar();
	void ApplyCarCollisionEffect();
	bool CheckIfFinishLine();
	void CheckIfLapCompleted();
	void CheckIfWinner();

private:
	void DetectPlayerCheckPoints();

public:
	const int shadowsOffset = 2;
	const float distanceOffset = 2.0f;
	Animation turn;
	Animation standardShadows;
	Animation littleBumpRightSide;
	Animation littleBumpLeftSide;
	Animation littleBumpBottomSide;
	Animation littleBumpTopSide;
	Animation bigBumpRightSide;
	Animation bigBumpLeftSide;
	Animation bigBumpBottomSide;
	Animation bigBumpTopSide;
	Animation splash;
	Animation* currentAnimation = nullptr;
	Animation* currentShadowsAnimation = nullptr;
	Animation* currentSplashAnimation = nullptr;
	iPoint position;
	iPoint lastFramePosition;
	bool still;
	bool right;
	const int initialAcceleration = 0;
	int acceleration;
	const int initialAccelerationCondition = 6;
	int repeater;
	bool collision;
	bool bounce;
	int bounceRecoil;
	int accelerationCondition;
	vector<int> currentDirection;
	vector<int> movementsDone;
	ModuleCollision* moduleCollision = nullptr;
	int bounceType;
	int frameReference;
	bool carCollision;
	int carCollisionType;
	vector<bool> checkpoint;
	int lap;
	bool winner;

private:
	SDL_Texture* graphics = nullptr;
	vector<iPoint> checkpoint1;
	vector<iPoint> checkpoint2;
	vector<iPoint> checkpoint3;
	vector<iPoint> checkpoint4;
	vector<iPoint> checkpoint5;
	vector<iPoint> checkpoint6;
	vector<iPoint> checkpoint7;
	vector<iPoint> checkpoint8;
};

#endif // __MODULEPLAYER_H__