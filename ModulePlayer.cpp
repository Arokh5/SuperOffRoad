#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleStage.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool start_enabled, const float speed) : speed(speed), Module(start_enabled)
{
	position.x = 177;
	position.y = 176;
	right = true;
	movementsDone.assign(32, 0);

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

	// define start rotation of the car
	turn.current_frame = 17.0f;
	currentAnimation = &turn;
}

ModulePlayer::~ModulePlayer()
{
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

// Update
update_status ModulePlayer::Update()
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

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		SetDirection();
		position.x += currentDirection[0];
		position.y += currentDirection[1];
	}

	if (still)
	{
		App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentStaticFrame());
	}
	else
	{
		if (right)
		{
			App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentFrame());
		}
		else
		{
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