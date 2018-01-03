#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	const float turnSpeed = 0.3f;
	const float jumpSpeed = 0.1f;
	position.x = 177;
	position.y = 176;
	acceleration = initialAcceleration;
	accelerationCondition = initialAccelerationCondition;
	lastFramePosition = position;
	right = true;
	repeater = 0;
	bounce = false;
	collision = false;
	still = true;
	bounceRecoil = 0;
	movementsDone.assign(32, 0);
	moduleCollision = new ModuleCollision();
	frameReference = 17;
	carCollision = false;

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
	turn.speed = turnSpeed;

	// little bump right side animation
	littleBumpRightSide.frames.push_back({ 11, 62, 14, 6 });
	littleBumpRightSide.frames.push_back({ 379, 299, 14, 9 });
	littleBumpRightSide.frames.push_back({ 35, 251, 14, 9 });
	littleBumpRightSide.frames.push_back({ 11, 249, 14, 11 });
	littleBumpRightSide.frames.push_back({ 347, 248, 14, 12 });
	littleBumpRightSide.frames.push_back({ 331, 271, 12, 13 });
	littleBumpRightSide.frames.push_back({ 331, 221, 10, 15 });
	littleBumpRightSide.frames.push_back({ 307, 221, 9, 15 });
	littleBumpRightSide.frames.push_back({ 283, 221, 10, 15 });
	littleBumpRightSide.frames.push_back({ 259, 221, 12, 15 });
	littleBumpRightSide.frames.push_back({ 659, 30, 12, 14 });
	littleBumpRightSide.frames.push_back({ 635, 31, 13, 13 });
	littleBumpRightSide.frames.push_back({ 611, 33, 13, 11 });
	littleBumpRightSide.frames.push_back({ 243, 105, 14, 11 });
	littleBumpRightSide.frames.push_back({ 587, 35, 13, 9 });
	littleBumpRightSide.frames.push_back({ 219, 108, 15, 8 });
	littleBumpRightSide.frames.push_back({ 619, 82, 15, 10 });
	littleBumpRightSide.frames.push_back({ 627, 132, 14, 8 });
	littleBumpRightSide.frames.push_back({ 603, 130, 14, 10 });
	littleBumpRightSide.frames.push_back({ 579, 128, 14, 12 });
	littleBumpRightSide.frames.push_back({ 555, 126, 14, 14 });
	littleBumpRightSide.frames.push_back({ 531, 125, 12, 15 });
	littleBumpRightSide.frames.push_back({ 515, 173, 11, 15 });
	littleBumpRightSide.frames.push_back({ 499, 102, 7, 14 });
	littleBumpRightSide.frames.push_back({ 475, 101, 12, 15 });
	littleBumpRightSide.frames.push_back({ 107, 55, 11, 13 });
	littleBumpRightSide.frames.push_back({ 83, 55, 13, 13 });
	littleBumpRightSide.frames.push_back({ 59, 56, 14, 12 });
	littleBumpRightSide.frames.push_back({ 107, 298, 9, 10 });
	littleBumpRightSide.frames.push_back({ 83, 299, 13, 9 });
	littleBumpRightSide.frames.push_back({ 59, 299, 14, 9 });
	littleBumpRightSide.frames.push_back({ 35, 300, 14, 8 });
	littleBumpRightSide.speed = turnSpeed;

	// little bump left side animation
	littleBumpLeftSide.frames.push_back({ 11, 83, 14, 9 });
	littleBumpLeftSide.frames.push_back({ 11, 132, 12, 8 });
	littleBumpLeftSide.frames.push_back({ 731, 85, 12, 7 });
	littleBumpLeftSide.frames.push_back({ 723, 107, 12, 9 });
	littleBumpLeftSide.frames.push_back({ 715, 247, 14, 13 });
	littleBumpLeftSide.frames.push_back({ 691, 246, 12, 14 });
	littleBumpLeftSide.frames.push_back({ 675, 246, 8, 14 });
	littleBumpLeftSide.frames.push_back({ 683, 270, 8, 14 });
	littleBumpLeftSide.frames.push_back({ 643, 197, 9, 15 });
	littleBumpLeftSide.frames.push_back({ 619, 198, 10, 14 });
	littleBumpLeftSide.frames.push_back({ 595, 197, 11, 15 });
	littleBumpLeftSide.frames.push_back({ 571, 198, 11, 14 });
	littleBumpLeftSide.frames.push_back({ 603, 247, 12, 13 });
	littleBumpLeftSide.frames.push_back({ 579, 246, 12, 14 });
	littleBumpLeftSide.frames.push_back({ 555, 199, 8, 13 });
	littleBumpLeftSide.frames.push_back({ 555, 249, 12, 11 });
	littleBumpLeftSide.frames.push_back({ 563, 275, 11, 9 });
	littleBumpLeftSide.frames.push_back({ 531, 253, 11, 7 });
	littleBumpLeftSide.frames.push_back({ 539, 276, 9, 8 });
	littleBumpLeftSide.frames.push_back({ 539, 34, 11, 10 });
	littleBumpLeftSide.frames.push_back({ 507, 253, 9, 7 });
	littleBumpLeftSide.frames.push_back({ 523, 59, 11, 9 });
	littleBumpLeftSide.frames.push_back({ 131, 32, 8, 12 });
	littleBumpLeftSide.frames.push_back({ 483, 77, 8, 15 });
	littleBumpLeftSide.frames.push_back({ 107, 33, 10, 11 });
	littleBumpLeftSide.frames.push_back({ 483, 55, 11, 13 });
	littleBumpLeftSide.frames.push_back({ 83, 34, 12, 10 });
	littleBumpLeftSide.frames.push_back({ 59, 79, 13, 13 });
	littleBumpLeftSide.frames.push_back({ 459, 55, 14, 13 });
	littleBumpLeftSide.frames.push_back({ 435, 57, 15, 11 });
	littleBumpLeftSide.frames.push_back({ 59, 35, 15, 9 });
	littleBumpLeftSide.frames.push_back({ 35, 37, 15, 7 });
	littleBumpLeftSide.speed = turnSpeed;

	// little bump bottom side animation
	littleBumpBottomSide.frames.push_back({ 403, 301, 14, 7 });
	littleBumpBottomSide.frames.push_back({ 11, 300, 14, 8 });
	littleBumpBottomSide.frames.push_back({ 731, 296, 14, 12 });
	littleBumpBottomSide.frames.push_back({ 355, 297, 15, 11 });
	littleBumpBottomSide.frames.push_back({ 715, 224, 15, 12 });
	littleBumpBottomSide.frames.push_back({ 691, 223, 14, 13 });
	littleBumpBottomSide.frames.push_back({ 683, 198, 10, 14 });
	littleBumpBottomSide.frames.push_back({ 667, 197, 8, 15 });
	littleBumpBottomSide.frames.push_back({ 643, 197, 9, 15 });
	littleBumpBottomSide.frames.push_back({ 619, 198, 10, 14 });
	littleBumpBottomSide.frames.push_back({ 659, 269, 11, 15 });
	littleBumpBottomSide.frames.push_back({ 635, 270, 14, 14 });
	littleBumpBottomSide.frames.push_back({ 611, 271, 15, 13 });
	littleBumpBottomSide.frames.push_back({ 587, 274, 14, 10 });
	littleBumpBottomSide.frames.push_back({ 587, 35, 13, 9 });
	littleBumpBottomSide.frames.push_back({ 219, 108, 15, 8 });
	littleBumpBottomSide.frames.push_back({ 595, 84, 15, 8 });
	littleBumpBottomSide.frames.push_back({ 563, 38, 13, 6 });
	littleBumpBottomSide.frames.push_back({ 571, 84, 14, 8 });
	littleBumpBottomSide.frames.push_back({ 571, 154, 14, 10 });
	littleBumpBottomSide.frames.push_back({ 547, 154, 15, 10 });
	littleBumpBottomSide.frames.push_back({ 523, 151, 13, 13 });
	littleBumpBottomSide.frames.push_back({ 507, 125, 10, 15 });
	littleBumpBottomSide.frames.push_back({ 499, 174, 8, 14 });
	littleBumpBottomSide.frames.push_back({ 483, 125, 9, 15 });
	littleBumpBottomSide.frames.push_back({ 475, 174, 9, 14 });
	littleBumpBottomSide.frames.push_back({ 451, 174, 11, 14 });
	littleBumpBottomSide.frames.push_back({ 451, 102, 13, 14 });
	littleBumpBottomSide.frames.push_back({ 427, 103, 14, 13 });
	littleBumpBottomSide.frames.push_back({ 403, 106, 14, 10 });
	littleBumpBottomSide.frames.push_back({ 411, 59, 15, 9 });
	littleBumpBottomSide.frames.push_back({ 35, 300, 14, 8 });
	littleBumpBottomSide.speed = turnSpeed;

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
	standardShadows.speed = turnSpeed;

	// define car start rotation
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
	DetectBumps();
	if (carCollision) ApplyCarCollisionEffect();

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
	if (((int)currentAnimation->current_frame) == 0)
	{
		currentDirection = { 1, 0 };
	}
	else if (((int)currentAnimation->current_frame) == 1)
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
	else if (((int)currentAnimation->current_frame) == 2)
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
	else if (((int)currentAnimation->current_frame) == 3)
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
	else if (((int)currentAnimation->current_frame) == 4)
	{
		currentDirection = { 1, 1 };
	}
	else if (((int)currentAnimation->current_frame) == 5)
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
	else if (((int)currentAnimation->current_frame) == 6)
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
	else if (((int)currentAnimation->current_frame) == 7)
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
	else if (((int)currentAnimation->current_frame) == 8)
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
	else if (((int)currentAnimation->current_frame) == 9)
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
	else if (((int)currentAnimation->current_frame) == 10)
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
	else if (((int)currentAnimation->current_frame) == 11)
	{
		currentDirection = { -1, 1 };
	}
	else if (((int)currentAnimation->current_frame) == 12)
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
	else if (((int)currentAnimation->current_frame) == 13)
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
	else if (((int)currentAnimation->current_frame) == 14)
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
	else if (((int)currentAnimation->current_frame) == 15)
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
	else if (((int)currentAnimation->current_frame) == 16)
	{
		currentDirection = { -1, 0 };
	}
	else if (((int)currentAnimation->current_frame) == 17)
	{
		currentDirection = { -1, 0 };
	}
	else if (((int)currentAnimation->current_frame) == 18)
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
	else if (((int)currentAnimation->current_frame) == 19)
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
	else if (((int)currentAnimation->current_frame) == 20)
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
	else if (((int)currentAnimation->current_frame) == 21)
	{
		currentDirection = { -1, -1 };
	}
	else if (((int)currentAnimation->current_frame) == 22)
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
	else if (((int)currentAnimation->current_frame) == 23)
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
	else if (((int)currentAnimation->current_frame) == 24)
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
	else if (((int)currentAnimation->current_frame) == 25)
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
	else if (((int)currentAnimation->current_frame) == 26)
	{
		currentDirection = { 1, -1 };
	}
	else if (((int)currentAnimation->current_frame) == 27)
	{
		currentDirection = { 1, -1 };
	}
	else if (((int)currentAnimation->current_frame) == 28)
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
	else if (((int)currentAnimation->current_frame) == 29)
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
	else if (((int)currentAnimation->current_frame) == 30)
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
	else if (((int)currentAnimation->current_frame) == 31)
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
			/* Debug fences */
			//SDL_RenderDrawPoint(App->renderer->renderer, fences[i][0], fences[i][1]);

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

void ModulePlayer::ApplyCarCollisionEffect()
{
	iPoint tempPos;

	switch (carCollisionType)
	{
		case 1:
			tempPos.x = position.x;
			tempPos.y = position.y + 1;
			break;

		case 2:
			tempPos.x = position.x - 1;
			tempPos.y = position.y + 1;
			break;

		case 3:
			tempPos.x = position.x - 1;
			tempPos.y = position.y;
			break;

		case 4:
			tempPos.x = position.x - 1;
			tempPos.y = position.y - 1;
			break;

		case 5:
			tempPos.x = position.x;
			tempPos.y = position.y - 1;
			break;

		case 6:
			tempPos.x = position.x + 1;
			tempPos.y = position.y - 1;
			break;

		case 7:
			tempPos.x = position.x + 1;
			tempPos.y = position.y;
			break;

		case 8:
			tempPos.x = position.x + 1;
			tempPos.y = position.y + 1;
			break;
	}

	bool fenceDetected = false;

	for each (std::vector<std::vector<int>> fences in moduleCollision->fenceContainer)
	{
		for (int i = 0; i < fences.size(); i++)
		{
			if (tempPos.x == fences[i][0] && tempPos.y == fences[i][1])
			{
				fenceDetected = true;
				break;
			}
		}
	}

	if (!fenceDetected)
	{
		position = tempPos;
	}

	carCollision = false;
}

void ModulePlayer::DetectBumps()
{
	bool littleBumpRightSideDetected = false;
	bool littleBumpLeftSideDetected = false;
	bool littleBumpBottomSideDetected = false;

	SDL_Rect playerCar;
	playerCar.x = position.x;
	playerCar.y = position.y;
	playerCar.w = 15;
	playerCar.h = 11;

	for each (SDL_Rect bump in moduleCollision->littleBumpRightSideContainer)
	{
		App->renderer->DrawQuad(bump, 255, 0, 0, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			littleBumpRightSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->littleBumpLeftSideContainer)
	{
		App->renderer->DrawQuad(bump, 0, 255, 0, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			littleBumpLeftSideDetected = true;
			break;
		}
	}

	for each (SDL_Rect bump in moduleCollision->littleBumpBottomSideContainer)
	{
		App->renderer->DrawQuad(bump, 0, 0, 255, 80);

		if (SDL_HasIntersection(&playerCar, &bump))
		{
			littleBumpBottomSideDetected = true;
			break;
		}
	}

	if (littleBumpRightSideDetected)
	{
		littleBumpRightSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &littleBumpRightSide;
	}
	if (littleBumpLeftSideDetected)
	{
		littleBumpLeftSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &littleBumpLeftSide;
	}
	if (littleBumpBottomSideDetected)
	{
		littleBumpBottomSide.current_frame = currentAnimation->current_frame;
		currentAnimation = &littleBumpBottomSide;
	}
	if (!littleBumpRightSideDetected && !littleBumpLeftSideDetected && !littleBumpBottomSideDetected)
	{
		turn.current_frame = currentAnimation->current_frame;
		currentAnimation = &turn;
	}
}