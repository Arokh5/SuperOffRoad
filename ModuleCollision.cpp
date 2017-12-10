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

			if (i % split == 0 && j != finalY)
			{
				int extraX = initialX > finalX ? i - 1 : i + 1;
				collider.push_back({ extraX, j });
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

			if (i % split == 0 && j != finalX)
			{
				int extraY = initialY > finalY ? i - 1 : i + 1;
				collider.push_back({ j, extraY });
				initialX > finalX ? j-- : j++;
			}
		}
	}

	return collider;
}