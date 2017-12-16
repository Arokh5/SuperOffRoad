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
	std::vector<std::vector<int>> fence2_1;
	std::vector<std::vector<int>> fence2_2;
	std::vector<std::vector<int>> fence3_1;
	std::vector<std::vector<int>> fence3_2;
	std::vector<std::vector<int>> fence3_3;
	std::vector<std::vector<int>> fence3_4;

private:
	std::vector<std::vector<int>> FillCollider(int initialX, int finalX, int initialY, int finalY);
};

#endif // __ModuleCollision_H__