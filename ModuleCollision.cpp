#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
	fence1_1 = FillCollider(88, 247, 178, 178);
	fence1_2 = FillCollider(283, 220, 96, 180);
	fence2_1 = FillCollider(178, 255, 80, 80);
	fence2_2 = FillCollider(280, 245, 21, 83);
	fence3_1 = FillCollider(140, 226, 130, 130);
	fence3_2 = FillCollider(140, 130, 130, 158);
	fence3_3 = FillCollider(130, 218, 158, 158);
	fence3_4 = FillCollider(226, 214, 130, 158);
	fenceContainer.push_back(fence1_1);
	fenceContainer.push_back(fence1_2);
	fenceContainer.push_back(fence2_1);
	fenceContainer.push_back(fence2_2);
	fenceContainer.push_back(fence3_1);
	fenceContainer.push_back(fence3_2);
	fenceContainer.push_back(fence3_3);
	fenceContainer.push_back(fence3_4);
}

// Destructor
ModuleCollision::~ModuleCollision()
{
}

vector<vector<int>> ModuleCollision::FillCollider(int initialX, int finalX, int initialY, int finalY)
{
	vector<vector<int>> collider;
	int difX = abs(finalX - initialX);
	int difY = abs(finalY - initialY);
	int split;

	if (difX >= difY)
	{
		if (difY == 0)
		{
			split = 1;
		}
		else
		{
			split = (int)round(difX / difY + 0.5f);
		}

		for (int i = initialX, j = initialY; i != finalX; initialX > finalX ? i-- : i++)
		{
			collider.push_back({ i, j });
			collider.push_back({ i, j + 1 });
			collider.push_back({ i, j + 2 });

			if (i % split == 0 && j != finalY)
			{
				initialY > finalY ? j-- : j++;
			}
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
			split = (int)round(difY / difX + 0.5f);
		}

		for (int i = initialY, j = initialX; i <= finalY; initialY > finalY ? i-- : i++)
		{
			collider.push_back({ j, i });
			collider.push_back({ j + 1, i });
			collider.push_back({ j + 2, i });

			if (i % split == 0 && j != finalX)
			{
				initialX > finalX ? j-- : j++;
			}
		}
	}

	return collider;
}