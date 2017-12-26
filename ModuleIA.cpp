#include "Globals.h"
#include "Application.h"
#include "ModuleIA.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

ModuleIA::ModuleIA(bool start_enabled) : Module(start_enabled)
{
	const float speed = 0.3f;

	// define cars start position
	position.push_back({ 177, 165 });
	position.push_back({ 195, 165 });
	position.push_back({ 195, 177 });

	// create temporal turn animation and assign it to turn vector
	Animation tempTurn;
	tempTurn.frames.push_back({ 35, 12, 16, 9 });
	tempTurn.frames.push_back({ 11, 12, 15, 9 });
	tempTurn.frames.push_back({ 739, 11, 16, 10 });
	tempTurn.frames.push_back({ 715, 10, 15, 11 });
	tempTurn.frames.push_back({ 691, 9, 14, 12 });
	tempTurn.frames.push_back({ 667, 9, 13, 12 });
	tempTurn.frames.push_back({ 643, 9, 10, 12 });
	tempTurn.frames.push_back({ 627, 8, 9, 13 });
	tempTurn.frames.push_back({ 603, 8, 10, 13 });
	tempTurn.frames.push_back({ 579, 8, 12, 13 });
	tempTurn.frames.push_back({ 555, 8, 13, 13 });
	tempTurn.frames.push_back({ 531, 8, 13, 13 });
	tempTurn.frames.push_back({ 507, 8, 15, 13 });
	tempTurn.frames.push_back({ 483, 9, 15, 12 });
	tempTurn.frames.push_back({ 459, 10, 15, 11 });
	tempTurn.frames.push_back({ 435, 10, 14, 11 });
	tempTurn.frames.push_back({ 411, 11, 15, 10 });
	tempTurn.frames.push_back({ 387, 12, 15, 9 });
	tempTurn.frames.push_back({ 363, 12, 15, 9 });
	tempTurn.frames.push_back({ 339, 11, 15, 10 });
	tempTurn.frames.push_back({ 315, 10, 14, 11 });
	tempTurn.frames.push_back({ 291, 9, 12, 12 });
	tempTurn.frames.push_back({ 267, 9, 11, 12 });
	tempTurn.frames.push_back({ 251, 9, 9, 12 });
	tempTurn.frames.push_back({ 227, 9, 10, 12 });
	tempTurn.frames.push_back({ 203, 9, 12, 12 });
	tempTurn.frames.push_back({ 179, 9, 14, 12 });
	tempTurn.frames.push_back({ 155, 9, 14, 12 });
	tempTurn.frames.push_back({ 131, 9, 15, 12 });
	tempTurn.frames.push_back({ 107, 10, 16, 11 });
	tempTurn.frames.push_back({ 83, 10, 16, 11 });
	tempTurn.frames.push_back({ 59, 11, 16, 10 });
	tempTurn.speed = speed;

	for (int i = 0; i < carsNumber; i++)
	{
		turn.push_back(tempTurn);
		turn[i].current_frame = 17.0f;
	}

	currentAnimation.push_back(&turn[0]);
	currentAnimation.push_back(&turn[1]);
	currentAnimation.push_back(&turn[2]);

	// same for shadows animation
	Animation tempShadows;
	tempShadows.frames.push_back({ 35, 324, 15, 8 });
	tempShadows.frames.push_back({ 11, 324, 14, 8 });
	tempShadows.frames.push_back({ 739, 323, 16, 10 });
	tempShadows.frames.push_back({ 715, 322, 15, 11 });
	tempShadows.frames.push_back({ 691, 322, 14, 12 });
	tempShadows.frames.push_back({ 667, 321, 13, 12 });
	tempShadows.frames.push_back({ 643, 321, 10, 12 });
	tempShadows.frames.push_back({ 627, 320, 9, 13 });
	tempShadows.frames.push_back({ 603, 320, 10, 13 });
	tempShadows.frames.push_back({ 579, 320, 12, 13 });
	tempShadows.frames.push_back({ 555, 320, 13, 13 });
	tempShadows.frames.push_back({ 531, 320, 13, 13 });
	tempShadows.frames.push_back({ 507, 320, 15, 13 });
	tempShadows.frames.push_back({ 483, 321, 15, 12 });
	tempShadows.frames.push_back({ 459, 322, 15, 11 });
	tempShadows.frames.push_back({ 435, 322, 14, 11 });
	tempShadows.frames.push_back({ 411, 323, 15, 10 });
	tempShadows.frames.push_back({ 387, 324, 15, 9 });
	tempShadows.frames.push_back({ 363, 324, 15, 9 });
	tempShadows.frames.push_back({ 339, 323, 15, 10 });
	tempShadows.frames.push_back({ 315, 322, 14, 11 });
	tempShadows.frames.push_back({ 291, 321, 12, 12 });
	tempShadows.frames.push_back({ 267, 321, 11, 12 });
	tempShadows.frames.push_back({ 251, 321, 9, 12 });
	tempShadows.frames.push_back({ 227, 321, 10, 12 });
	tempShadows.frames.push_back({ 203, 321, 12, 12 });
	tempShadows.frames.push_back({ 179, 321, 14, 12 });
	tempShadows.frames.push_back({ 155, 321, 14, 12 });
	tempShadows.frames.push_back({ 131, 321, 15, 12 });
	tempShadows.frames.push_back({ 107, 322, 16, 11 });
	tempShadows.frames.push_back({ 83, 322, 16, 11 });
	tempShadows.frames.push_back({ 59, 323, 16, 10 });
	tempShadows.speed = speed;

	for (int i = 0; i < carsNumber; i++)
	{
		standardShadows.push_back(tempShadows);
		standardShadows[i].current_frame = 17.0f;
	}

	currentShadowsAnimation.push_back(&standardShadows[0]);
	currentShadowsAnimation.push_back(&standardShadows[1]);
	currentShadowsAnimation.push_back(&standardShadows[2]);
}

ModuleIA::~ModuleIA()
{
}

// Load assets
bool ModuleIA::Start()
{
	LOG("Loading IA");

	graphics = App->textures->Load("general_sprites.png");

	return true;
}

// Unload assets
bool ModuleIA::CleanUp()
{
	LOG("Unloading IA");

	App->textures->Unload(graphics);

	return true;
}

// PreUpdate
update_status ModuleIA::PreUpdate()
{
	for (int i = 0; i < carsNumber; i++)
	{
		App->renderer->Blit(graphics, position[i].x, position[i].y + shadowsOffset, &currentShadowsAnimation[i]->GetCurrentStaticFrame());
		App->renderer->Blit(graphics, position[i].x, position[i].y, &currentAnimation[i]->GetCurrentStaticFrame());
	}

	return UPDATE_CONTINUE;
}