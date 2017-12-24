#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleStage.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	const float speed = 0.3f;
	acceleration = initialAcceleration;
	accelerationCondition = initialAccelerationCondition;
	position.x = 177;
	position.y = 176;
	lastFramePosition = position;
	right = true;
	repeater = 0;
	bounce = false;
	collision = false;
	bounceRecoil = 0;
	movementsDone.assign(32, 0);
	moduleCollision = new ModuleCollision();

	// turn animation
	turn.frames.push_back({ 35, 12, 16, 9 });
	turn.frames.push_back({ 11, 12, 15, 9 });
	turn.frames.push_back({ 739, 11, 16, 10 });
	turn.frames.push_back({ 715, 10, 15, 11 });
	turn.frames.push_back({ 691, 9, 14, 12 });
	turn.frames.push_back({ 667, 9, 13, 12 });
	turn.frames.push_back({ 643, 9, 10, 12 });
	turn.frames.push_back({ 627, 8, 9, 13 });
	turn.frames.push_back({ 603, 8, 10, 13 });
	turn.frames.push_back({ 579, 8, 12, 13 });
	turn.frames.push_back({ 555, 8, 13, 13 });
	turn.frames.push_back({ 531, 8, 13, 13 });
	turn.frames.push_back({ 507, 8, 15, 13 });
	turn.frames.push_back({ 483, 9, 15, 12 });
	turn.frames.push_back({ 459, 10, 15, 11 });
	turn.frames.push_back({ 435, 10, 14, 11 });
	turn.frames.push_back({ 411, 11, 15, 10 });
	turn.frames.push_back({ 387, 12, 15, 9 });
	turn.frames.push_back({ 363, 12, 15, 9 });
	turn.frames.push_back({ 339, 11, 15, 10 });
	turn.frames.push_back({ 315, 10, 14, 11 });
	turn.frames.push_back({ 291, 9, 12, 12 });
	turn.frames.push_back({ 267, 9, 11, 12 });
	turn.frames.push_back({ 251, 9, 9, 12 });
	turn.frames.push_back({ 227, 9, 10, 12 });
	turn.frames.push_back({ 203, 9, 12, 12 });
	turn.frames.push_back({ 179, 9, 14, 12 });
	turn.frames.push_back({ 155, 9, 14, 12 });
	turn.frames.push_back({ 131, 9, 15, 12 });
	turn.frames.push_back({ 107, 10, 16, 11 });
	turn.frames.push_back({ 83, 10, 16, 11 });
	turn.frames.push_back({ 59, 11, 16, 10 });
	turn.speed = speed;

	// fill standard shadows vector
	standardShadows.frames.push_back({ 35, 324, 15, 8 });
	standardShadows.frames.push_back({ 11, 324, 14, 8 });
	standardShadows.frames.push_back({ 739, 323, 16, 10 });
	standardShadows.frames.push_back({ 715, 322, 15, 11 });
	standardShadows.frames.push_back({ 691, 322, 14, 12 });
	standardShadows.frames.push_back({ 667, 321, 13, 12 });
	standardShadows.frames.push_back({ 643, 321, 10, 12 });
	standardShadows.frames.push_back({ 627, 320, 9, 13 });
	standardShadows.frames.push_back({ 603, 320, 10, 13 });
	standardShadows.frames.push_back({ 579, 320, 12, 13 });
	standardShadows.frames.push_back({ 555, 320, 13, 13 });
	standardShadows.frames.push_back({ 531, 320, 13, 13 });
	standardShadows.frames.push_back({ 507, 320, 15, 13 });
	standardShadows.frames.push_back({ 483, 321, 15, 12 });
	standardShadows.frames.push_back({ 459, 322, 15, 11 });
	standardShadows.frames.push_back({ 435, 322, 14, 11 });
	standardShadows.frames.push_back({ 411, 323, 15, 10 });
	standardShadows.frames.push_back({ 387, 324, 15, 9 });
	standardShadows.frames.push_back({ 363, 324, 15, 9 });
	standardShadows.frames.push_back({ 339, 323, 15, 10 });
	standardShadows.frames.push_back({ 315, 322, 14, 11 });
	standardShadows.frames.push_back({ 291, 321, 12, 12 });
	standardShadows.frames.push_back({ 267, 321, 11, 12 });
	standardShadows.frames.push_back({ 251, 321, 9, 12 });
	standardShadows.frames.push_back({ 227, 321, 10, 12 });
	standardShadows.frames.push_back({ 203, 321, 12, 12 });
	standardShadows.frames.push_back({ 179, 321, 14, 12 });
	standardShadows.frames.push_back({ 155, 321, 14, 12 });
	standardShadows.frames.push_back({ 131, 321, 15, 12 });
	standardShadows.frames.push_back({ 107, 322, 16, 11 });
	standardShadows.frames.push_back({ 83, 322, 16, 11 });
	standardShadows.frames.push_back({ 59, 323, 16, 10 });
	standardShadows.speed = speed;

	// define start rotation of the car
	turn.current_frame = 17.0f;
	standardShadows.current_frame = 17.0f;
	currentAnimation = &turn;
	currentShadowsAnimation = &standardShadows;
}

ModulePlayer::~ModulePlayer()
{
	delete moduleCollision;
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("general_sprites.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// PreUpdate
update_status ModulePlayer::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		right = true;
		still = false;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		right = false;
		still = false;
	}
	else
	{
		still = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (acceleration == accelerationCondition)
		{
			LOG("positionX: %d", position.x);
			LOG("positionY: %d", position.y);

			repeater++;
			SetDirection();
			MoveCar();

			acceleration = initialAcceleration;
			if (accelerationCondition > 1 && repeater % 2 == 0)
			{
				accelerationCondition--;
			}
		}

		acceleration++;
	}
	else
	{
		if (acceleration == accelerationCondition)
		{
			repeater--;
			SetDirection();
			MoveCar();

			acceleration = initialAcceleration;
			if (accelerationCondition < initialAccelerationCondition && repeater % 2 == 0)
			{
				accelerationCondition++;
			}
		}

		if (accelerationCondition < initialAccelerationCondition)
		{
			acceleration++;
		}
		else 
		{ 
			repeater = 0;
			bounce = false;
			bounceRecoil = 0;
		}
	}

	if (still)
	{
		App->renderer->Blit(graphics, position.x, position.y + shadowsOffset, &currentShadowsAnimation->GetCurrentStaticFrame());
		App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentStaticFrame());
	}
	else
	{
		if (right)
		{
			App->renderer->Blit(graphics, position.x, position.y + shadowsOffset, &currentShadowsAnimation->GetCurrentFrame());
			App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentFrame());
		}
		else
		{
			App->renderer->Blit(graphics, position.x, position.y + shadowsOffset, &currentShadowsAnimation->GetCurrentInverseFrame());
			App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentInverseFrame());
		}
	}
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::SetDirection()
{
	if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[0])
	{
		currentDirection = { 1, 0 };
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[1])
	{
		switch (movementsDone[1])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[1] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[1] = 2;
			break;
		case 2:
			currentDirection = { 1, 0 };
			movementsDone[1] = 3;
			break;

		case 3:
			currentDirection = { 1, 0 };
			movementsDone[1] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[2])
	{
		switch (movementsDone[2])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[2] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[2] = 2;
			break;
		case 2:
			currentDirection = { 1, 0 };
			movementsDone[2] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[3])
	{
		switch (movementsDone[3])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[3] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[3] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[4])
	{
		currentDirection = { 1, 1 };
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[5])
	{
		switch (movementsDone[5])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[5] = 1;
			break;

		case 1:
			currentDirection = { 1, 1 };
			movementsDone[5] = 2;
			break;

		case 2:
			currentDirection = { 0, 1 };
			movementsDone[5] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[6])
	{
		switch (movementsDone[6])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[6] = 1;
			break;

		case 1:
			currentDirection = { 0, 1 };
			movementsDone[6] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[7])
	{
		switch (movementsDone[7])
		{
		case 0:
			currentDirection = { 1, 1 };
			movementsDone[7] = 1;
			break;

		case 1:
			currentDirection = { 0, 1 };
			movementsDone[7] = 2;
			break;

		case 2:
			currentDirection = { 0, 1 };
			movementsDone[7] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[8])
	{
		switch (movementsDone[8])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[8] = 1;
			break;

		case 1:
			currentDirection = { 0, 1 };
			movementsDone[8] = 2;
			break;

		case 2:
			currentDirection = { 0, 1 };
			movementsDone[8] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[9])
	{
		switch (movementsDone[9])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[9] = 1;
			break;

		case 1:
			currentDirection = { 0, 1 };
			movementsDone[9] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[10])
	{
		switch (movementsDone[10])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[10] = 1;
			break;

		case 1:
			currentDirection = { -1, 1 };
			movementsDone[10] = 2;
			break;

		case 2:
			currentDirection = { 0, 1 };
			movementsDone[10] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[11])
	{
		currentDirection = { -1, 1 };
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[12])
	{
		switch (movementsDone[12])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[12] = 1;
			break;

		case 1:
			currentDirection = { -1, 1 };
			movementsDone[12] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[12] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[13])
	{
		switch (movementsDone[13])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[13] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[13] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[14])
	{
		switch (movementsDone[14])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[14] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[14] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[14] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[15])
	{
		switch (movementsDone[15])
		{
		case 0:
			currentDirection = { -1, 1 };
			movementsDone[15] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[15] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[15] = 3;
			break;

		case 3:
			currentDirection = { -1, 0 };
			movementsDone[15] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[16])
	{
		currentDirection = { -1, 0 };
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[17])
	{
		currentDirection = { -1, 0 };
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[18])
	{
		switch (movementsDone[18])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[18] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[18] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[18] = 3;
			break;

		case 3:
			currentDirection = { -1, 0 };
			movementsDone[18] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[19])
	{
		switch (movementsDone[19])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[19] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[19] = 2;
			break;

		case 2:
			currentDirection = { -1, 0 };
			movementsDone[19] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[20])
	{
		switch (movementsDone[20])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[20] = 1;
			break;

		case 1:
			currentDirection = { -1, 0 };
			movementsDone[20] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[21])
	{
		currentDirection = { -1, -1 };
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[22])
	{
		switch (movementsDone[22])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[22] = 1;
			break;

		case 1:
			currentDirection = { 0, -1 };
			movementsDone[22] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[23])
	{
		switch (movementsDone[23])
		{
		case 0:
			currentDirection = { -1, -1 };
			movementsDone[23] = 1;
			break;

		case 1:
			currentDirection = { 0, -1 };
			movementsDone[23] = 2;
			break;

		case 2:
			currentDirection = { 0, -1 };
			movementsDone[23] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[24])
	{
		switch (movementsDone[24])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[24] = 1;
			break;

		case 1:
			currentDirection = { 0, -1 };
			movementsDone[24] = 2;
			break;

		case 2:
			currentDirection = { 0, -1 };
			movementsDone[24] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[25])
	{
		switch (movementsDone[25])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[25] = 1;
			break;

		case 1:
			currentDirection = { 0, -1 };
			movementsDone[25] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[26])
	{
		currentDirection = { 1, -1 };
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[27])
	{
		currentDirection = { 1, -1 };
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[28])
	{
		switch (movementsDone[28])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[28] = 1;
			break;

		case 1:
			currentDirection = { 1, -1 };
			movementsDone[28] = 2;
			break;

		case 2:
			currentDirection = { 1, 0 };
			movementsDone[28] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[29])
	{
		switch (movementsDone[29])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[29] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[29] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[30])
	{
		switch (movementsDone[30])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[30] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[30] = 2;
			break;

		case 2:
			currentDirection = { 1, 0 };
			movementsDone[30] = 0;
			break;
		}
	}
	else if (&currentAnimation->GetCurrentStaticFrame() == &turn.frames[31])
	{
		switch (movementsDone[31])
		{
		case 0:
			currentDirection = { 1, -1 };
			movementsDone[31] = 1;
			break;

		case 1:
			currentDirection = { 1, 0 };
			movementsDone[31] = 2;
			break;

		case 2:
			currentDirection = { 1, 0 };
			movementsDone[31] = 3;
			break;

		case 3:
			currentDirection = { 1, 0 };
			movementsDone[31] = 0;
			break;
		}
	}
}

void ModulePlayer::MoveCar()
{
	collision = false;

	if (!DetectFences(position))
	{
		lastFramePosition = position;
	}

	if (!bounce && !collision)
	{
		position.x += currentDirection[0];
		position.y += currentDirection[1];
	}
	else if (collision && !bounce)
	{
		iPoint tempPos;
		tempPos.x = position.x + currentDirection[0];
		tempPos.y = position.y + currentDirection[1];

		if (!DetectFences(tempPos))
		{
			position = tempPos;
		}
	}
	else
	{
		ApplyBounceEffect();
		bounceRecoil++;

		if (bounceRecoil == 10)
		{
			bounce = false;
			bounceRecoil = 0;
			acceleration = initialAcceleration;
			accelerationCondition = initialAccelerationCondition;
			repeater = 0;
		}
	}
}

bool ModulePlayer::DetectFences(iPoint position)
{
	bool fenceDetected = false;

	for each (std::vector<std::vector<int>> fences in moduleCollision->fenceContainer)
	{
		for (int i = 0; i < fences.size(); i++)
		{
			if (position.x == fences[i][0] && position.y == fences[i][1])
			{
				float intersection_carLastFrame = sqrt(pow(position.x - lastFramePosition.x, 2) + pow(position.y - lastFramePosition.y, 2));
				float intersection_colliderOrigin = sqrt(pow(position.x - fences.front()[0], 2) + pow(position.y - fences.front()[1], 2));
				float carLastFrame_colliderOrigin = sqrt(pow(lastFramePosition.x - fences.front()[0], 2) + pow(lastFramePosition.y - fences.front()[1], 2));

				float radianAngle = acos((pow(intersection_carLastFrame, 2) + pow(intersection_colliderOrigin, 2) - pow(carLastFrame_colliderOrigin, 2)) / (2 * intersection_carLastFrame * intersection_colliderOrigin));
				float angle = radianAngle * 180 / M_PI;

				/*LOG("intersection_carLastFrame: %f", intersection_carLastFrame);
				LOG("intersection_colliderOrigin: %f", intersection_colliderOrigin);
				LOG("carLastFrame_colliderOrigin: %f", carLastFrame_colliderOrigin);
				LOG("angle: %f", angle);*/

				collision = true;

				if (angle >= 88 && angle <= 92)
				{
					bounce = true;
					SetBounceDirection(fences);
				}
				else if (angle >= 0 && angle < 88)
				{
					right = SetRotationDirection(fences);
				}
				else if (angle <= 180 && angle > 92)
				{
					right = !SetRotationDirection(fences);
				}

				fenceDetected = true;
				break;
			}
		}
	}

	return fenceDetected;
}

bool ModulePlayer::SetRotationDirection(std::vector<std::vector<int>> fences)
{
	bool rotationRight = true;

	if (fences == moduleCollision->fence1_1 ||
		fences == moduleCollision->fence2_1 ||
		fences == moduleCollision->fence2_3 ||
		fences == moduleCollision->fence3_1 ||
		fences == moduleCollision->fence3_4 ||
		fences == moduleCollision->fence4_1 ||
		fences == moduleCollision->fence4_2 ||
		fences == moduleCollision->fence4_3 ||
		fences == moduleCollision->fence5_2 ||
		fences == moduleCollision->fence5_4 ||
		fences == moduleCollision->fence5_6)
	{
		rotationRight = false;
	}

	still = false;

	return rotationRight;
}

void ModulePlayer::SetBounceDirection(std::vector<std::vector<int>> fences)
{
	if (fences == moduleCollision->fence1_1 ||
		fences == moduleCollision->fence2_1 ||
		fences == moduleCollision->fence3_1 ||
		fences == moduleCollision->fence4_1 ||
		fences == moduleCollision->fence5_2)
	{
		// position.y--
		bounceType = 0;
	}
	else if (fences == moduleCollision->fence1_2 ||
		fences == moduleCollision->fence1_4 ||
		fences == moduleCollision->fence2_2 ||
		fences == moduleCollision->fence3_2 ||
		fences == moduleCollision->fence5_1)
	{
		// position.x--
		bounceType = 1;
	}
	else if (fences == moduleCollision->fence3_3)
	{
		// position.x--
		// position.y++
		bounceType = 2;
	}
	else if (fences == moduleCollision->fence3_4 ||
		fences == moduleCollision->fence2_3 ||
		fences == moduleCollision->fence4_3 ||
		fences == moduleCollision->fence5_4 ||
		fences == moduleCollision->fence5_6)
	{
		// position.x++
		bounceType = 3;
	}
	else if (fences == moduleCollision->fence4_2)
	{
		// position.x++
		// position.y--
		bounceType = 4;
	}
	else if (fences == moduleCollision->fence1_3 ||
		fences == moduleCollision->fence4_4 ||
		fences == moduleCollision->fence5_3 ||
		fences == moduleCollision->fence5_5)
	{
		// position.y++
		bounceType = 5;
	}
}

void ModulePlayer::ApplyBounceEffect()
{
	switch (bounceType)
	{
		case 0:
			position.y--;
			break;

		case 1:
			position.x--;
			break;

		case 2:
			position.x--;
			position.y++;

		case 3:
			position.x++;

		case 4:
			position.x++;
			position.y--;

		case 5:
			position.y++;
	}
}