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

	// Add checkpoints to checkpoints containers
	/*1*/
	for (int i = 120; i < 136; i+=5)
	{
		vector<iPoint> tempCheckpoint;
		for (int j = 160; j < 179; j++)
		{
			tempCheckpoint.push_back({ i, j });
		}

		checkpointContainer1.push_back(tempCheckpoint);
	}
	/*2*/
	for (int i = 75; i < 91; i+=5)
	{
		vector<iPoint> tempCheckpoint;
		for (int j = 112; j < 177; j++)
		{
			tempCheckpoint.push_back({ j, i });
		}

		checkpointContainer2.push_back(tempCheckpoint);
	}
	/*3*/
	for (int i = 220; i < 241; i += 5)
	{
		vector<iPoint> tempCheckpoint;
		for (int j = 58; j < 81; j++)
		{
			tempCheckpoint.push_back({ i, j });
		}

		checkpointContainer3.push_back(tempCheckpoint);
	}
	/*4*/
	for (int i = 35; i < 51; i += 5)
	{
		vector<iPoint> tempCheckpoint;
		for (int j = 228; j < 268; j++)
		{
			tempCheckpoint.push_back({ j, i });
		}

		checkpointContainer4.push_back(tempCheckpoint);
	}
	/*5*/
	for (int i = 80; i < 96; i += 5)
	{
		vector<iPoint> tempCheckpoint;
		for (int j = 22; j < 44; j++)
		{
			tempCheckpoint.push_back({ i, j });
		}

		checkpointContainer5.push_back(tempCheckpoint);
	}
	/*6*/
	for (int i = 95; i < 101; i += 5)
	{
		vector<iPoint> tempCheckpoint;
		for (int j = 26; j < 66; j++)
		{
			tempCheckpoint.push_back({ j, i });
		}

		checkpointContainer6.push_back(tempCheckpoint);
	}
	/*7*/
	for (int i = 220; i < 246; i += 5)
	{
		vector<iPoint> tempCheckpoint;
		for (int j = 100; j < 130; j++)
		{
			tempCheckpoint.push_back({ i, j });
		}

		checkpointContainer7.push_back(tempCheckpoint);
	}
	/*8*/
	for (int i = 150; i < 161; i += 5)
	{
		vector<iPoint> tempCheckpoint;
		for (int j = 220; j < 253; j++)
		{
			tempCheckpoint.push_back({ j, i });
		}

		checkpointContainer8.push_back(tempCheckpoint);
	}
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

	graphics.push_back(App->textures->Load("general_sprites_blue.png"));
	graphics.push_back(App->textures->Load("general_sprites_yellow.png"));
	graphics.push_back(App->textures->Load("general_sprites_grey.png"));

	return true;
}

// Unload assets
bool ModuleIA::CleanUp()
{
	LOG("Unloading IA");

	for each (SDL_Texture* graphic in graphics)
	{
		App->textures->Unload(graphic);
	}

	return true;
}

// PreUpdate
update_status ModuleIA::PreUpdate()
{
	for (int i = 0; i < cars.size(); i++)
	{
		if (cars[i]->carCollision) cars[i]->ApplyCarCollisionEffect();
		DetectCheckpoints(cars[i]);
		OnCheckpointExit(cars[i]);

		if (cars[i]->acceleration == cars[i]->accelerationCondition)
		{
			cars[i]->repeater++;
			cars[i]->SetDirection();
			cars[i]->MoveCar();

			cars[i]->acceleration = cars[i]->initialAcceleration;
			if (cars[i]->accelerationCondition > 1 && cars[i]->repeater % 2 == 0)
			{
				cars[i]->accelerationCondition--;
			}
		}

		cars[i]->acceleration++;

		if (cars[i]->still)
		{
			App->renderer->Blit(graphics[i], cars[i]->position.x, cars[i]->position.y + cars[i]->shadowsOffset, &cars[i]->currentShadowsAnimation->GetCurrentStaticFrame());
			App->renderer->Blit(graphics[i], cars[i]->position.x, cars[i]->position.y, &cars[i]->currentAnimation->GetCurrentStaticFrame());
		}
		else
		{
			if (cars[i]->right)
			{
				App->renderer->Blit(graphics[i], cars[i]->position.x, cars[i]->position.y + cars[i]->shadowsOffset, &cars[i]->currentShadowsAnimation->GetCurrentFrame());
				App->renderer->Blit(graphics[i], cars[i]->position.x, cars[i]->position.y, &cars[i]->currentAnimation->GetCurrentFrame());
			}
			else
			{
				App->renderer->Blit(graphics[i], cars[i]->position.x, cars[i]->position.y + cars[i]->shadowsOffset, &cars[i]->currentShadowsAnimation->GetCurrentInverseFrame());
				App->renderer->Blit(graphics[i], cars[i]->position.x, cars[i]->position.y, &cars[i]->currentAnimation->GetCurrentInverseFrame());
			}
		}
	}

	return UPDATE_CONTINUE;
}

int ModuleIA::GetRandomCheckpoint(int lot)
{
	return rand() % lot + 0;
}

void ModuleIA::DetectCheckpoints(ModulePlayer* car)
{
	for each (iPoint checkpoint in checkpointContainer1[GetRandomCheckpoint(checkpoint1Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= distanceOffset)
		{
			car->right = true;
			car->still = false;
			car->frameReference = 25;
		}
	}

	for each (iPoint checkpoint in checkpointContainer2[GetRandomCheckpoint(checkpoint2Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= distanceOffset)
		{
			car->right = true;
			car->still = false;
			car->frameReference = 0;
		}
	}

	for each (iPoint checkpoint in checkpointContainer3[GetRandomCheckpoint(checkpoint3Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= distanceOffset)
		{
			car->right = false;
			car->still = false;
			car->frameReference = 23;
		}
	}

	for each (iPoint checkpoint in checkpointContainer4[GetRandomCheckpoint(checkpoint4Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= distanceOffset)
		{
			car->right = false;
			car->still = false;
			car->frameReference = 17;
		}
	}

	for each (iPoint checkpoint in checkpointContainer5[GetRandomCheckpoint(checkpoint5Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= distanceOffset)
		{
			car->right = false;
			car->still = false;
			car->frameReference = 8;
		}
	}

	for each (iPoint checkpoint in checkpointContainer6[GetRandomCheckpoint(checkpoint6Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= distanceOffset)
		{
			car->right = false;
			car->still = false;
			car->frameReference = 0;
		}
	}

	for each (iPoint checkpoint in checkpointContainer7[GetRandomCheckpoint(checkpoint7Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= distanceOffset)
		{
			car->right = true;
			car->still = false;
			car->frameReference = 8;
		}
	}

	for each (iPoint checkpoint in checkpointContainer8[GetRandomCheckpoint(checkpoint8Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= distanceOffset)
		{
			car->right = true;
			car->still = false;
			car->frameReference = 17;
		}
	}
}

void ModuleIA::OnCheckpointExit(ModulePlayer* car)
{
	if (&car->currentAnimation->GetCurrentStaticFrame() == &car->turn.frames[car->frameReference])
	{
		car->still = true;
	}
	else
	{
		car->still = false;

		int cont1 = 0;
		for (int i = (int)car->currentAnimation->current_frame; i != car->frameReference;)
		{
			i++;

			if (i == car->turn.frames.size())
			{
				i = 0;
			}

			cont1++;
		}

		int cont2 = 0;
		for (int i = (int)car->currentAnimation->current_frame; i != car->frameReference;)
		{
			i--;

			if (i < 0)
			{
				i = car->turn.frames.size() - 1;
			}

			cont2++;
		}

		if (cont1 < cont2)
		{
			car->right = true;
		}
		else
		{
			car->right = false;
		}
	}
}