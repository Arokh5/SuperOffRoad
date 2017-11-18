#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleStage.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 100;

	// turn right
	turnRight.frames.push_back({ 35, 12, 16, 9 });
	turnRight.frames.push_back({ 11, 12, 15, 9 });
	turnRight.frames.push_back({ 739, 11, 16, 10 });
	turnRight.frames.push_back({ 715, 10, 15, 11 });
	turnRight.frames.push_back({ 691, 9, 14, 12 });
	turnRight.frames.push_back({ 667, 9, 13, 12 });
	turnRight.frames.push_back({ 643, 9, 10, 12 });
	turnRight.frames.push_back({ 627, 8, 9, 13 });
	turnRight.frames.push_back({ 603, 8, 10, 13 });
	turnRight.frames.push_back({ 579, 8, 12, 13 });
	turnRight.frames.push_back({ 555, 8, 13, 13 });
	turnRight.frames.push_back({ 531, 8, 13, 13 });
	turnRight.frames.push_back({ 507, 8, 15, 13 });
	turnRight.frames.push_back({ 483, 9, 15, 12 });
	turnRight.frames.push_back({ 459, 10, 15, 11 });
	turnRight.frames.push_back({ 435, 10, 14, 11 });
	turnRight.frames.push_back({ 411, 11, 15, 10 });
	turnRight.frames.push_back({ 387, 12, 15, 9 });
	turnRight.frames.push_back({ 363, 12, 15, 9 });
	turnRight.frames.push_back({ 339, 11, 15, 10 });
	turnRight.frames.push_back({ 315, 10, 14, 11 });
	turnRight.frames.push_back({ 291, 9, 12, 12 });
	turnRight.frames.push_back({ 267, 9, 11, 12 });
	turnRight.frames.push_back({ 251, 9, 9, 12 });
	turnRight.frames.push_back({ 227, 9, 10, 12 });
	turnRight.frames.push_back({ 203, 9, 12, 12 });
	turnRight.frames.push_back({ 179, 9, 14, 12 });
	turnRight.frames.push_back({ 155, 9, 14, 12 });
	turnRight.frames.push_back({ 131, 9, 15, 12 });
	turnRight.frames.push_back({ 107, 10, 16, 11 });
	turnRight.frames.push_back({ 83, 10, 16, 11 });
	turnRight.frames.push_back({ 59, 11, 16, 10 });
	turnRight.speed = speed;

	// turn left
	for (vector<SDL_Rect>::const_reverse_iterator it = turnRight.frames.crbegin(); it != turnRight.frames.crend(); ++it)
	{
		turnLeft.frames.push_back(*it);
	}
	turnLeft.speed = speed;

	int cont = 0;

	// fill animation idles with each turn animation frame
	for (vector<SDL_Rect>::iterator it = turnRight.frames.begin(); it != turnRight.frames.end(); ++it)
	{
		tempAnim = new Animation();
		tempAnim->frames.push_back(*it);
		idles.insert(pair<Animation*, vector<int>>(tempAnim, SetDirection(cont)));
		cont++;
	}

	// first animation that we will show
	currentAnimation = tempAnim;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
	delete tempAnim;
	tempAnim = nullptr;
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
	int x, y;

	for (map<Animation*, vector<int>>::iterator it = idles.begin(); it != idles.end(); ++it)
	{
		if (SDL_RectEquals(&it->first->frames[0], &currentAnimation->GetCurrentFrame()))
		{
			currentAnimation = it->first;
			x = it->second[0];
			y = it->second[1];
			break;
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		currentAnimation = &turnRight;
		turnLeft.current_frame = turnRight.frames.size() - 1 - turnRight.current_frame;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		currentAnimation = &turnLeft;
		turnRight.current_frame = turnLeft.frames.size() - 1 - turnLeft.current_frame;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		for (map<Animation*, vector<int>>::iterator it = idles.begin(); it != idles.end(); ++it)
		{
			if (SDL_RectEquals(&it->first->frames[0], &currentAnimation->GetCurrentFrame()))
			{
				currentAnimation = it->first;
				x = it->second[0];
				y = it->second[1];
				position.x += x;
				position.y += y;
				break;
			}
		}
	}
	
	App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentFrame(), 0.0f);

	return UPDATE_CONTINUE;
}

vector<int> ModulePlayer::SetDirection(int cont)
{
	vector<int> direction;

	switch (cont)
	{
		case 0:
		case 1:
		case 2:
			direction = { 1, 0 };
			break;

		case 3:
			direction = { 2, 1 };
			break;

		case 4:
		case 5:
			direction = { 1, 1 };
			break;

		case 6:
			direction = { 1, 2 };
			break;

		case 7:
			direction = { 0, 1 };
			break;

		case 8:
		case 9:
		case 10:
			direction = { -1, 2 };
			break;
		
		case 11:
		case 12:
		case 13:
			direction = { -1, 1 };
			break;

		case 14:
		case 15:
			direction = { -2, 1 };
			break;

		case 16:
		case 17:
		case 18:
			direction = { -1, 0 };
			break;

		case 19:
			direction = { -2, -1 };
			break;

		case 20:
		case 21:
			direction = { -1, -1 };
			break;

		case 22:
			direction = { -1, -2 };
			break;

		case 23:
		case 24:
			direction = { 0, -1 };
			break;

		case 25:
		case 26:
		case 27:
			direction = { 1, -2 };
			break;

		case 28:
		case 29:
			direction = { 1, -1 };
			break;

		case 30:
		case 31:
			direction = { 2, -1 };
			break;
	}

	return direction;
}