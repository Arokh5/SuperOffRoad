#include "Globals.h"
#include "Application.h"
#include "ModuleStage.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleIA.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleTitleScreen.h"
#include "SDL/include/SDL.h"

ModuleStage::ModuleStage(bool start_enabled) : Module(start_enabled)
{
	// Background
	background.x = 8;
	background.y = 208;
	background.w = 319;
	background.h = 191;

	// Scoreboard
	scoreboard.x = 8;
	scoreboard.y = 3210;
	scoreboard.w = 61;
	scoreboard.h = 30;

	// Player car numbers
	playerCarNumbers.push_back({ 80, 3232, 4, 7 });
	playerCarNumbers.push_back({ 88, 3232, 4, 7 });
	playerCarNumbers.push_back({ 96, 3232, 4, 7 });
	playerCarNumbers.push_back({ 104, 3232, 4, 7 });
	playerCarNumbers.push_back({ 112, 3232, 4, 7 });
	playerCarNumbers.push_back({ 120, 3232, 4, 7 });
	playerCarNumbers.push_back({ 128, 3232, 4, 7 });
	playerCarNumbers.push_back({ 136, 3232, 4, 7 });
	playerCarNumbers.push_back({ 144, 3232, 4, 7 });
	playerCarNumbers.push_back({ 152, 3232, 4, 7 });

	// Blue car numbers
	blueCarNumbers.push_back({ 80, 3223, 4, 7 });
	blueCarNumbers.push_back({ 88, 3223, 4, 7 });
	blueCarNumbers.push_back({ 96, 3223, 4, 7 });
	blueCarNumbers.push_back({ 104, 3223, 4, 7 });
	blueCarNumbers.push_back({ 112, 3223, 4, 7 });
	blueCarNumbers.push_back({ 120, 3223, 4, 7 });
	blueCarNumbers.push_back({ 128, 3223, 4, 7 });
	blueCarNumbers.push_back({ 136, 3223, 4, 7 });
	blueCarNumbers.push_back({ 144, 3223, 4, 7 });
	blueCarNumbers.push_back({ 152, 3223, 4, 7 });

	// Yellow car numbers
	yellowCarNumbers.push_back({ 80, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 88, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 96, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 104, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 112, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 120, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 128, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 136, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 144, 3214, 4, 7 });
	yellowCarNumbers.push_back({ 152, 3214, 4, 7 });

	// Grey car numbers
	greyCarNumbers.push_back({ 80, 3205, 4, 7 });
	greyCarNumbers.push_back({ 88, 3205, 4, 7 });
	greyCarNumbers.push_back({ 96, 3205, 4, 7 });
	greyCarNumbers.push_back({ 104, 3205, 4, 7 });
	greyCarNumbers.push_back({ 112, 3205, 4, 7 });
	greyCarNumbers.push_back({ 120, 3205, 4, 7 });
	greyCarNumbers.push_back({ 128, 3205, 4, 7 });
	greyCarNumbers.push_back({ 136, 3205, 4, 7 });
	greyCarNumbers.push_back({ 144, 3205, 4, 7 });
	greyCarNumbers.push_back({ 152, 3205, 4, 7 });

	// Fence 1
	fence1_1.x = 400;
	fence1_1.y = 388;
	fence1_1.w = 159;
	fence1_1.h = 11;
	fence1_2.x = 560;
	fence1_2.y = 304;
	fence1_2.w = 47;
	fence1_2.h = 92;

	// Fence 2
	fence2_1.x = 489;
	fence2_1.y = 296;
	fence2_1.w = 78;
	fence2_1.h = 7;
	fence2_2.x = 568;
	fence2_2.y = 228;
	fence2_2.w = 39;
	fence2_2.h = 73;

	// Fence 3
	fence3.x = 456;
	fence3.y = 344;
	fence3.w = 86;
	fence3.h = 15;

	// Fence 4
	fence4.x = 336;
	fence4.y = 316;
	fence4.w = 78;
	fence4.h = 27;

	// Fence 5
	fence5_1.x = 389;
	fence5_1.y = 261;
	fence5_1.w = 23;
	fence5_1.h = 42;
	fence5_2.x = 413;
	fence5_2.y = 260;
	fence5_2.w = 130;
	fence5_2.h = 5;
}

ModuleStage::~ModuleStage()
{
}

// Load assets
bool ModuleStage::Start()
{
	titleScreen = false;

	LOG("Loading Stage");

	graphics = App->textures->Load("stage.png");

	// Enable player and IA modules
	App->player->Enable();
	App->IA->Enable();

	// Trigger background music
	App->audio->PlayMusic("05_Fandango.ogg");

	return true;
}

// UnLoad assets
bool ModuleStage::CleanUp()
{
	LOG("Unloading stage");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->IA->Disable();

	return true;
}

update_status ModuleStage::PreUpdate()
{
	App->renderer->Blit(graphics, 0, 0, &background);
	App->renderer->Blit(graphics, 10, 150, &scoreboard);

	App->renderer->Blit(graphics, 27, 170, &playerCarNumbers[0]);
	App->renderer->Blit(graphics, 32, 170, &playerCarNumbers[0]);

	App->renderer->Blit(graphics, 38, 170, &blueCarNumbers[0]);
	App->renderer->Blit(graphics, 43, 170, &blueCarNumbers[0]);

	App->renderer->Blit(graphics, 49, 170, &yellowCarNumbers[0]);
	App->renderer->Blit(graphics, 54, 170, &yellowCarNumbers[0]);

	App->renderer->Blit(graphics, 60, 170, &greyCarNumbers[0]);
	App->renderer->Blit(graphics, 65, 170, &greyCarNumbers[0]);

	App->renderer->Blit(graphics, 31, 162, &playerCarNumbers[App->player->lap]);
	App->renderer->Blit(graphics, 42, 162, &blueCarNumbers[App->IA->cars[0]->lap]);
	App->renderer->Blit(graphics, 53, 162, &yellowCarNumbers[App->IA->cars[1]->lap]);
	App->renderer->Blit(graphics, 64, 162, &greyCarNumbers[App->IA->cars[2]->lap]);

	return UPDATE_CONTINUE;
}

// Update: draw fences
update_status ModuleStage::Update()
{
	App->renderer->Blit(graphics, 88, 180, &fence1_1);
	App->renderer->Blit(graphics, 247, 96, &fence1_2);
	App->renderer->Blit(graphics, 180, 88, &fence2_1);
	App->renderer->Blit(graphics, 256, 21, &fence2_2);
	App->renderer->Blit(graphics, 145, 137, &fence3);
	App->renderer->Blit(graphics, 25, 112, &fence4);
	App->renderer->Blit(graphics, 77, 51, &fence5_1);
	App->renderer->Blit(graphics, 100, 51, &fence5_2);

	GoTitleScreen();

	return UPDATE_CONTINUE;
}

void ModuleStage::GoTitleScreen()
{
	if (App->player->winner ||
		App->IA->cars[0]->winner ||
		App->IA->cars[1]->winner ||
		App->IA->cars[2]->winner)
	{
		if (!titleScreen)
		{
			titleScreen = true;
			App->fade->FadeToBlack(App->titleScreen, App->stage, 3.0f);
		}
	}
}