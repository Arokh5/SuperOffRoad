#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "ModuleIA.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

ModuleIA::ModuleIA(bool start_enabled) : Module(start_enabled)
{
	cars.push_back(new ModulePlayer());
	cars.push_back(new ModulePlayer());
	cars.push_back(new ModulePlayer());

	cars[0]->position.x = 177;
	cars[0]->position.y = 165;

	cars[1]->position.x = 185;
	cars[1]->position.y = 165;

	cars[2]->position.x = 185;
	cars[2]->position.y = 176;
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
	for each (ModulePlayer* car in cars)
	{
		if (car->acceleration == car->accelerationCondition)
		{
			car->repeater++;
			car->SetDirection();
			car->MoveCar();

			car->acceleration = car->initialAcceleration;
			if (car->accelerationCondition > 1 && car->repeater % 2 == 0)
			{
				car->accelerationCondition--;
			}
		}

		car->acceleration++;

		App->renderer->Blit(graphics, car->position.x, car->position.y + car->shadowsOffset, &car->currentShadowsAnimation->GetCurrentStaticFrame());
		App->renderer->Blit(graphics, car->position.x, car->position.y, &car->currentAnimation->GetCurrentStaticFrame());
	}

	return UPDATE_CONTINUE;
}