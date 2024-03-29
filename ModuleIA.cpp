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
	cars.push_back(new ModulePlayer()); // blue car
	cars.push_back(new ModulePlayer()); // yellow car
	cars.push_back(new ModulePlayer()); // grey car

	// Add checkpoints to checkpoints containers
	/*1*/
	for (float i = 100; i < 116; i+=5)
	{
		vector<fPoint> tempCheckpoint;
		for (float j = 160; j < 179; j++)
		{
			tempCheckpoint.push_back({ i, j });
		}

		checkpointContainer1.push_back(tempCheckpoint);
	}
	/*2*/
	for (float i = 65; i < 81; i+=5)
	{
		vector<fPoint> tempCheckpoint;
		for (float j = 112; j < 177; j++)
		{
			tempCheckpoint.push_back({ j, i });
		}

		checkpointContainer2.push_back(tempCheckpoint);
	}
	/*3*/
	for (float i = 230; i < 246; i += 5)
	{
		vector<fPoint> tempCheckpoint;
		for (float j = 58; j < 81; j++)
		{
			tempCheckpoint.push_back({ i, j });
		}

		checkpointContainer3.push_back(tempCheckpoint);
	}
	/*4*/
	for (float i = 25; i < 41; i += 5)
	{
		vector<fPoint> tempCheckpoint;
		for (float j = 228; j < 268; j++)
		{
			tempCheckpoint.push_back({ j, i });
		}

		checkpointContainer4.push_back(tempCheckpoint);
	}
	/*5*/
	for (float i = 70; i < 86; i += 5)
	{
		vector<fPoint> tempCheckpoint;
		for (float j = 22; j < 44; j++)
		{
			tempCheckpoint.push_back({ i, j });
		}

		checkpointContainer5.push_back(tempCheckpoint);
	}
	/*6*/
	for (float i = 100; i < 106; i += 5)
	{
		vector<fPoint> tempCheckpoint;
		for (float j = 26; j < 66; j++)
		{
			tempCheckpoint.push_back({ j, i });
		}

		checkpointContainer6.push_back(tempCheckpoint);
	}
	/*7*/
	for (float i = 230; i < 256; i += 5)
	{
		vector<fPoint> tempCheckpoint;
		for (float j = 100; j < 130; j++)
		{
			tempCheckpoint.push_back({ i, j });
		}

		checkpointContainer7.push_back(tempCheckpoint);
	}
	/*8*/
	for (float i = 155; i < 166; i += 5)
	{
		vector<fPoint> tempCheckpoint;
		for (float j = 220; j < 253; j++)
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

	cars[0]->StartingInitials();
	cars[1]->StartingInitials();
	cars[2]->StartingInitials();

	// Define initial positions
	cars[0]->position.x = 177;
	cars[0]->position.y = 165;
	cars[1]->position.x = 195;
	cars[1]->position.y = 165;
	cars[2]->position.x = 195;
	cars[2]->position.y = 176;

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

	graphics.clear();

	return true;
}

// PreUpdate
update_status ModuleIA::PreUpdate()
{
	for (int i = 0; i < cars.size(); i++)
	{
		cars[i]->CalculateDeltatime();
		cars[i]->DetectBumps();
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

		if (cars[i]->DetectPool())
		{
			App->renderer->Blit(graphics[i], cars[i]->position.x, cars[i]->position.y + cars[i]->shadowsOffset, &cars[i]->currentSplashAnimation->GetCurrentFrame());
		}

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

		cars[i]->CheckIfLapCompleted();
		cars[i]->CheckIfWinner();
	}

	return UPDATE_CONTINUE;
}

int ModuleIA::GetRandomCheckpoint(int lot) const
{
	return rand() % lot + 0;
}

void ModuleIA::DetectCheckpoints(ModulePlayer* car) const
{
	for each (fPoint checkpoint in checkpointContainer1[GetRandomCheckpoint(checkpoint1Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= car->distanceOffset)
		{
			car->right = true;
			car->still = false;
			car->frameReference = 25;
			car->checkpoint[0] = true;
		}
	}

	for each (fPoint checkpoint in checkpointContainer2[GetRandomCheckpoint(checkpoint2Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= car->distanceOffset)
		{
			car->right = true;
			car->still = false;
			car->frameReference = 0;
			car->checkpoint[1] = true;
		}
	}

	for each (fPoint checkpoint in checkpointContainer3[GetRandomCheckpoint(checkpoint3Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= car->distanceOffset)
		{
			car->right = false;
			car->still = false;
			car->frameReference = 23;
			car->checkpoint[2] = true;
		}
	}

	for each (fPoint checkpoint in checkpointContainer4[GetRandomCheckpoint(checkpoint4Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= car->distanceOffset)
		{
			car->right = false;
			car->still = false;
			car->frameReference = 17;
			car->checkpoint[3] = true;
		}
	}

	for each (fPoint checkpoint in checkpointContainer5[GetRandomCheckpoint(checkpoint5Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= car->distanceOffset)
		{
			car->right = false;
			car->still = false;
			car->frameReference = 8;
			car->checkpoint[4] = true;
		}
	}

	for each (fPoint checkpoint in checkpointContainer6[GetRandomCheckpoint(checkpoint6Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= car->distanceOffset)
		{
			car->right = false;
			car->still = false;
			car->frameReference = 0;
			car->checkpoint[5] = true;
		}
	}

	for each (fPoint checkpoint in checkpointContainer7[GetRandomCheckpoint(checkpoint7Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= car->distanceOffset)
		{
			car->right = true;
			car->still = false;
			car->frameReference = 8;
			car->checkpoint[6] = true;
		}
	}

	for each (fPoint checkpoint in checkpointContainer8[GetRandomCheckpoint(checkpoint8Lot)])
	{
		if (car->position.DistanceTo(checkpoint) <= car->distanceOffset)
		{
			car->right = true;
			car->still = false;
			car->frameReference = 17;
			car->checkpoint[7] = true;
		}
	}
}

void ModuleIA::OnCheckpointExit(ModulePlayer* car) const
{
	if (((int)car->currentAnimation->current_frame) == car->frameReference)
	{
		car->still = true;
	}
	else
	{
		car->still = false;

		int cont1 = 0;
		for (int i = ((int)car->currentAnimation->current_frame); i != car->frameReference;)
		{
			i++;

			if (i == car->turn.frames.size())
			{
				i = 0;
			}

			cont1++;
		}

		int cont2 = 0;
		for (int i = ((int)car->currentAnimation->current_frame); i != car->frameReference;)
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