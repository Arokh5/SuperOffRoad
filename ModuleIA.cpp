#include "Globals.h"
#include "Application.h"
#include "ModuleIA.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

ModuleIA::ModuleIA(bool start_enabled) : ModulePlayer(start_enabled)
{
	const float speed = 0.3f;
	position.x = 177;
	position.y = 165;
	acceleration = initialAcceleration;
	accelerationCondition = initialAccelerationCondition;
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
	if (acceleration == accelerationCondition)
	{
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

	App->renderer->Blit(graphics, position.x, position.y + shadowsOffset, &currentShadowsAnimation->GetCurrentStaticFrame());
	App->renderer->Blit(graphics, position.x, position.y, &currentAnimation->GetCurrentStaticFrame());

	return UPDATE_CONTINUE;
}