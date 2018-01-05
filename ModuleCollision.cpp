#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
	// Fill fences collider
	fence1_1 = FillCollider(83, 247, 178, 178);
	fence1_2 = FillCollider(283, 220, 96, 180);
	fence1_3 = FillCollider(174, 284, 98, 98);
	fence1_4 = FillCollider(178, 174, 80, 98);
	fence2_1 = FillCollider(178, 255, 80, 80);
	fence2_2 = FillCollider(280, 245, 21, 83);
	fence2_3 = FillCollider(102, 77, 124, 182);
	fence3_1 = FillCollider(140, 226, 130, 130);
	fence3_2 = FillCollider(140, 130, 130, 158);
	fence3_3 = FillCollider(131, 218, 158, 158);
	fence3_4 = FillCollider(226, 214, 130, 158);
	fence4_1 = FillCollider(30, 102, 124, 124);
	fence4_2 = FillCollider(20, 42, 100, 125);
	fence4_3 = FillCollider(63, 17, 20, 106);
	fence4_4 = FillCollider(63, 286, 20, 20);
	fence5_1 = FillCollider(84, 61, 46, 106);
	fence5_2 = FillCollider(85, 226, 43, 43);
	fence5_3 = FillCollider(65, 104, 106, 106);
	fence5_4 = FillCollider(126, 100, 58, 106);
	fence5_5 = FillCollider(124, 229, 58, 58);
	fence5_6 = FillCollider(226, 226, 43, 58);
	fenceDiagonalReinforcement1 = FillCollider(86, 88, 168, 179);
	fenceDiagonalReinforcement2 = FillCollider(275, 279, 97, 110);
	fenceDiagonalReinforcement3 = FillCollider(275, 278, 19, 31);
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
	fenceContainer.push_back(fenceDiagonalReinforcement1);
	fenceContainer.push_back(fenceDiagonalReinforcement2);
	fenceContainer.push_back(fenceDiagonalReinforcement3);

	// Fill little bump right side collider container
	littleBumpRightSideContainer.push_back({ 234, 37, 15, 18 });
	littleBumpRightSideContainer.push_back({ 181, 37, 15, 18 });
	littleBumpRightSideContainer.push_back({ 214, 20, 17, 15 });
	littleBumpRightSideContainer.push_back({ 162, 18, 15, 18 });
	littleBumpRightSideContainer.push_back({ 133, 37, 15, 18 });
	littleBumpRightSideContainer.push_back({ 110, 18, 15, 18 });
	littleBumpRightSideContainer.push_back({ 175, 97, 25, 40 });
	littleBumpRightSideContainer.push_back({ 165, 115, 10, 25 });
	littleBumpRightSideContainer.push_back({ 170, 105, 5, 10 });
	littleBumpRightSideContainer.push_back({ 160, 127, 5, 10 });
	littleBumpRightSideContainer.push_back({ 105, 97, 20, 25 });
	littleBumpRightSideContainer.push_back({ 100, 115, 10, 15 });

	// Fill little bump left side collider container
	littleBumpLeftSideContainer.push_back({ 222, 37, 12, 18 });
	littleBumpLeftSideContainer.push_back({ 169, 37, 12, 18 });
	littleBumpLeftSideContainer.push_back({ 204, 20, 10, 15 });
	littleBumpLeftSideContainer.push_back({ 152, 18, 10, 18 });
	littleBumpLeftSideContainer.push_back({ 123, 37, 10, 15 });
	littleBumpLeftSideContainer.push_back({ 100, 18, 10, 18 });
	littleBumpLeftSideContainer.push_back({ 154, 105, 12, 20 });
	littleBumpLeftSideContainer.push_back({ 166, 105, 4, 10 });
	littleBumpLeftSideContainer.push_back({ 78, 105, 20, 25 });
	littleBumpLeftSideContainer.push_back({ 98, 105, 5, 15 });

	// Fill little bump bottom side collider container
	littleBumpBottomSideContainer.push_back({ 104, 128, 45, 18 });
	littleBumpBottomSideContainer.push_back({ 149, 128, 10, 10 });
	littleBumpBottomSideContainer.push_back({ 115, 95, 60, 13 });

	// Fill little bump top side collider container
	littleBumpTopSideContainer.push_back({ 110, 122, 45, 7 });
	littleBumpTopSideContainer.push_back({ 116, 88, 65, 7 });

	// Fill big bump right side collider container
	bigBumpRightSideContainer.push_back({ 255, 147, 10, 20 });
	bigBumpRightSideContainer.push_back({ 70, 91, 10, 20 });
	bigBumpRightSideContainer.push_back({ 63, 59, 10, 20 });
	bigBumpRightSideContainer.push_back({ 102, 43, 10, 20 });

	// Fill big bump left side collider container
	bigBumpLeftSideContainer.push_back({ 235, 147, 10, 20 });
	bigBumpLeftSideContainer.push_back({ 50, 91, 10, 20 });
	bigBumpLeftSideContainer.push_back({ 43, 59, 10, 20 });
	bigBumpLeftSideContainer.push_back({ 82, 43, 10, 20 });

	// Fill big bump bottom side collider container
	bigBumpBottomSideContainer.push_back({ 245, 147, 10, 20 });
	bigBumpBottomSideContainer.push_back({ 60, 91, 10, 20 });
	bigBumpBottomSideContainer.push_back({ 53, 59, 10, 20 });
	bigBumpBottomSideContainer.push_back({ 92, 43, 10, 20 });

	// Fill big bump top side collider container
	bigBumpTopSideContainer.push_back({ 240, 139, 20, 8 });
	bigBumpTopSideContainer.push_back({ 55, 83, 20, 8 });
	bigBumpTopSideContainer.push_back({ 48, 51, 20, 8 });
	bigBumpTopSideContainer.push_back({ 87, 35, 20, 8 });

	// Define pool collider
	poolCollider = { 121, 108, 35, 15 };

	// Define finish line
	finishLine = FillCollider(163, 152, 160, 178);
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