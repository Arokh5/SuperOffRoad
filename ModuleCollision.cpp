#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
	fence1_1 = FillCollider(88, 247, 180, 180);
}

// Destructor
ModuleCollision::~ModuleCollision()
{
}

vector<vector<int>> ModuleCollision::FillCollider(int minX, int maxX, int minY, int maxY)
{
	vector<vector<int>> collider;
	int difX = maxX - minX;
	int difY = maxY - minY;
	int split;

	if (difX >= difY)
	{
		if (difY == 0)
		{
			split = 1;
		}
		else
		{
			split = difX / difY;
		}

		for (int i = minX, j = minY; i <= maxX; i++)
		{
			if (i % split == 0 && j < maxY)
			{
				j++;
			}

			collider.push_back({ i, j });
		}
	}
	else
	{
		if (difX == 0)
		{
			split = 1;
		}
		else
		{
			split = difY / difX;
		}

		for (int i = minY, j = minX; i <= maxY; i++)
		{
			if (i % split == 0 && j < maxX)
			{
				j++;
			}

			collider.push_back({ j, i });
		}
	}

	return collider;
}