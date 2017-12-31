#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
	fence1_1 = FillCollider(83, 247, 178, 178);
	fence1_2 = FillCollider(283, 220, 96, 180);
	fence1_3 = FillCollider(178, 284, 98, 98);
	fence1_4 = FillCollider(178, 178, 80, 98);
	fence2_1 = FillCollider(178, 255, 80, 80);
	fence2_2 = FillCollider(280, 245, 21, 83);
	fence2_3 = FillCollider(102, 77, 124, 182);
	fence3_1 = FillCollider(140, 226, 130, 130);
	fence3_2 = FillCollider(140, 130, 130, 158);
	fence3_3 = FillCollider(130, 218, 158, 158);
	fence3_4 = FillCollider(226, 214, 130, 158);
	fence4_1 = FillCollider(30, 102, 124, 124);
	fence4_2 = FillCollider(20, 42, 100, 125);
	fence4_3 = FillCollider(63, 17, 20, 106);
	fence4_4 = FillCollider(63, 286, 20, 20);
	fence5_1 = FillCollider(84, 61, 46, 106);
	fence5_2 = FillCollider(84, 226, 43, 43);
	fence5_3 = FillCollider(65, 104, 106, 106);
	fence5_4 = FillCollider(126, 100, 58, 106);
	fence5_5 = FillCollider(124, 229, 58, 58);
	fence5_6 = FillCollider(226, 226, 43, 58);
	fenceContainer.push_back(fence1_1);
	fenceContainer.push_back(fence1_2);
	fenceContainer.push_back(fence1_3);
	fenceContainer.push_back(fence1_4);
	fenceContainer.push_back(fence2_1);
	fenceContainer.push_back(fence2_2);
	fenceContainer.push_back(fence2_3);
	fenceContainer.push_back(fence3_1);
	fenceContainer.push_back(fence3_2);
	fenceContainer.push_back(fence3_3);
	fenceContainer.push_back(fence3_4);
	fenceContainer.push_back(fence4_1);
	fenceContainer.push_back(fence4_2);
	fenceContainer.push_back(fence4_3);
	fenceContainer.push_back(fence4_4);
	fenceContainer.push_back(fence5_1);
	fenceContainer.push_back(fence5_2);
	fenceContainer.push_back(fence5_3);
	fenceContainer.push_back(fence5_4);
	fenceContainer.push_back(fence5_5);
	fenceContainer.push_back(fence5_6);

	littleBumpRightSideContainer.push_back({ 235, 37, 15, 18 });
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