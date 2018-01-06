#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include "Module.h"
#include <vector>

class ModuleCollision : public Module
{
public:
	ModuleCollision();
	~ModuleCollision();

	std::vector<std::vector<std::vector<int>>> fenceContainer;
	std::vector<std::vector<int>> fence1_1;
	std::vector<std::vector<int>> fence1_2;
	std::vector<std::vector<int>> fence1_3;
	std::vector<std::vector<int>> fence1_4;
	std::vector<std::vector<int>> fence2_1;
	std::vector<std::vector<int>> fence2_2;
	std::vector<std::vector<int>> fence2_3;
	std::vector<std::vector<int>> fence3_1;
	std::vector<std::vector<int>> fence3_2;
	std::vector<std::vector<int>> fence3_3;
	std::vector<std::vector<int>> fence3_4;
	std::vector<std::vector<int>> fence4_1;
	std::vector<std::vector<int>> fence4_2;
	std::vector<std::vector<int>> fence4_3;
	std::vector<std::vector<int>> fence4_4;
	std::vector<std::vector<int>> fence5_1;
	std::vector<std::vector<int>> fence5_2;
	std::vector<std::vector<int>> fence5_3;
	std::vector<std::vector<int>> fence5_4;
	std::vector<std::vector<int>> fence5_5;
	std::vector<std::vector<int>> fence5_6;
	std::vector<std::vector<int>> fenceDiagonalReinforcement1;
	std::vector<std::vector<int>> fenceDiagonalReinforcement2;
	std::vector<std::vector<int>> fenceDiagonalReinforcement3;

	std::vector<SDL_Rect> littleBumpRightSideContainer;
	std::vector<SDL_Rect> littleBumpLeftSideContainer;
	std::vector<SDL_Rect> littleBumpBottomSideContainer;
	std::vector<SDL_Rect> littleBumpTopSideContainer;

	std::vector<SDL_Rect> bigBumpRightSideContainer;
	std::vector<SDL_Rect> bigBumpLeftSideContainer;
	std::vector<SDL_Rect> bigBumpBottomSideContainer;
	std::vector<SDL_Rect> bigBumpTopSideContainer;

	SDL_Rect poolCollider;

	std::vector<std::vector<int>> finishLine;

	void DetectCarCollisions() const;

private:
	std::vector<std::vector<int>> FillCollider(int initialX, int finalX, int initialY, int finalY) const;

	void DefineCollisionType(ModulePlayer* car1, ModulePlayer* car2) const;
};

#endif // __ModuleCollision_H__