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
	turnRight.frames.push_back({ 736, 14, 15, 9 });
	turnRight.frames.push_back({ 712, 13, 14, 10 });
	turnRight.frames.push_back({ 688, 12, 13, 11 });
	turnRight.frames.push_back({ 664, 12, 12, 11 });
	turnRight.frames.push_back({ 640, 12, 9, 11 });
	turnRight.frames.push_back({ 624, 11, 8, 12 });
	turnRight.frames.push_back({ 600, 11, 9, 12 });
	turnRight.frames.push_back({ 576, 11, 11, 12 });
	turnRight.frames.push_back({ 552, 11, 12, 12 });
	turnRight.frames.push_back({ 528, 11, 12, 12 });
	turnRight.frames.push_back({ 504, 11, 14, 12 });
	turnRight.frames.push_back({ 480, 12, 14, 11 });
	turnRight.frames.push_back({ 456, 13, 14, 10 });
	turnRight.frames.push_back({ 432, 13, 13, 10 });
	turnRight.frames.push_back({ 408, 14, 14, 9 });
	turnRight.frames.push_back({ 384, 15, 14, 8 });
	turnRight.frames.push_back({ 360, 15, 14, 8 });
	turnRight.frames.push_back({ 336, 14, 14, 9 });
	turnRight.frames.push_back({ 312, 13, 13, 10 });
	turnRight.frames.push_back({ 288, 12, 11, 11 });
	turnRight.frames.push_back({ 264, 12, 10, 11 });
	turnRight.frames.push_back({ 248, 12, 8, 11 });
	turnRight.frames.push_back({ 224, 12, 9, 11 });
	turnRight.frames.push_back({ 200, 12, 11, 11 });
	turnRight.frames.push_back({ 176, 12, 13, 11 });
	turnRight.frames.push_back({ 152, 12, 13, 11 });
	turnRight.frames.push_back({ 128, 12, 14, 11 });
	turnRight.frames.push_back({ 104, 13, 15, 10 });
	turnRight.frames.push_back({ 80, 13, 15, 10 });
	turnRight.frames.push_back({ 56, 14, 15, 9 });
	turnRight.frames.push_back({ 32, 15, 15, 8 });
	turnRight.frames.push_back({ 8, 15, 14, 8 });
	turnRight.speed = speed;

	// turn left
	for (vector<SDL_Rect>::const_reverse_iterator it = turnRight.frames.crbegin(); it != turnRight.frames.crend(); ++it)
	{
		turnLeft.frames.push_back(*it);
	}
	turnLeft.speed = speed;

	int x = -1;
	int y = -1;

	// fill animation idles with each turn animation frame
	for (vector<SDL_Rect>::iterator it = turnRight.frames.begin(); it != turnRight.frames.end(); ++it)
	{
		tempAnim = new Animation();
		tempAnim->frames.push_back(*it);
		idles.insert(pair<Animation*, vector<int>>(tempAnim, { x, y }));
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
	
	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
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