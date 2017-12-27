#include "Globals.h"
#include "Application.h"
#include "ModuleIA.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

ModuleIA::ModuleIA(bool start_enabled) : Module(start_enabled)
{
	// Create 3 rival IA cars
	cars.push_back(new ModulePlayer());
	cars.push_back(new ModulePlayer());
	cars.push_back(new ModulePlayer());

	// Define initial positions
	cars[0]->position.x = 177;
	cars[0]->position.y = 165;
	cars[1]->position.x = 195;
	cars[1]->position.y = 165;
	cars[2]->position.x = 195;
	cars[2]->position.y = 177;
}

ModuleIA::~ModuleIA()
{
	for each (ModulePlayer* car in cars)
	{
		delete car;
	}
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

		if (car->still)
		{
			App->renderer->Blit(graphics, car->position.x, car->position.y + car->shadowsOffset, &car->currentShadowsAnimation->GetCurrentStaticFrame());
			App->renderer->Blit(graphics, car->position.x, car->position.y, &car->currentAnimation->GetCurrentStaticFrame());
		}
		else
		{
			if (car->right)
			{
				App->renderer->Blit(graphics, car->position.x, car->position.y + car->shadowsOffset, &car->currentShadowsAnimation->GetCurrentFrame());
				App->renderer->Blit(graphics, car->position.x, car->position.y, &car->currentAnimation->GetCurrentFrame());
			}
			else
			{
				App->renderer->Blit(graphics, car->position.x, car->position.y + car->shadowsOffset, &car->currentShadowsAnimation->GetCurrentInverseFrame());
				App->renderer->Blit(graphics, car->position.x, car->position.y, &car->currentAnimation->GetCurrentInverseFrame());
			}
		}
	}

	return UPDATE_CONTINUE;
}