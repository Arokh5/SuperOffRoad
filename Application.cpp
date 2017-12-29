#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleIA.h"
#include "ModuleStage.h"
#include "ModuleTitleScreen.h"

using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());

	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());

	// Game Modules
	modules.push_back(titleScreen = new ModuleTitleScreen(false));
	modules.push_back(stage = new ModuleStage(false));
	modules.push_back(player = new ModulePlayer(false));
	modules.push_back(IA = new ModuleIA(false));

	// Modules to draw on top of game logic
	modules.push_back(fade = new ModuleFadeToBlack());
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	// Start first scene
	fade->FadeToBlack(titleScreen, nullptr, 2.0f);

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PreUpdate();

	DetectCollisions();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

void Application::DetectCollisions()
{
	SDL_Rect playerCar;
	playerCar.x = player->position.x;
	playerCar.y = player->position.y;
	playerCar.w = player->currentAnimation->GetCurrentStaticFrame().w;
	playerCar.h = player->currentAnimation->GetCurrentStaticFrame().h;

	vector<SDL_Rect> carsIA;

	for each (ModulePlayer* car in IA->cars)
	{
		SDL_Rect carIA;
		carIA.x = car->position.x;
		carIA.y = car->position.y;
		carIA.w = car->currentAnimation->GetCurrentStaticFrame().w;
		carIA.h = car->currentAnimation->GetCurrentStaticFrame().h;

		carsIA.push_back(carIA);

		/*App->renderer->DrawQuad(playerCar, 0, 0, 255, 80);
		App->renderer->DrawQuad(carIA, 0, 255, 0, 80);*/

		if (SDL_HasIntersection(&playerCar, &carIA))
		{
			if (car->position.x == player->position.x && car->position.y < player->position.y)
			{
				player->carCollisionType = 1;
			}
			else if (car->position.x > player->position.x && car->position.y < player->position.y)
			{
				player->carCollisionType = 2;
			}
			else if (car->position.x > player->position.x && car->position.y == player->position.y)
			{
				player->carCollisionType = 3;
			}
			else if (car->position.x > player->position.x && car->position.y > player->position.y)
			{
				player->carCollisionType = 4;
			}
			else if (car->position.x == player->position.x && car->position.y > player->position.y)
			{
				player->carCollisionType = 5;
			}
			else if (car->position.x < player->position.x && car->position.y > player->position.y)
			{
				player->carCollisionType = 6;
			}
			else if (car->position.x < player->position.x && car->position.y == player->position.y)
			{
				player->carCollisionType = 7;
			}
			else if (car->position.x < player->position.x && car->position.y < player->position.y)
			{
				player->carCollisionType = 8;
			}

			player->carCollision = true;
			car->carCollision = true;
		}
	}

	if (SDL_HasIntersection(&carsIA[0], &carsIA[1]))
	{
		IA->cars[0]->carCollision = true;
		IA->cars[1]->carCollision = true;
	}
	if (SDL_HasIntersection(&carsIA[0], &carsIA[2]))
	{
		IA->cars[0]->carCollision = true;
		IA->cars[2]->carCollision = true;
	}
	if (SDL_HasIntersection(&carsIA[1], &carsIA[2]))
	{
		IA->cars[1]->carCollision = true;
		IA->cars[2]->carCollision = true;
	}
}