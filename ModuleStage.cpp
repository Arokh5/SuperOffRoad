#include "Globals.h"
#include "Application.h"
#include "ModuleStage.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleIA.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleStage::ModuleStage(bool start_enabled) : Module(start_enabled)
{
	// Background
	background.x = 8;
	background.y = 208;
	background.w = 319;
	background.h = 191;

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
	LOG("Loading Stage");

	graphics = App->textures->Load("stage.png");

	// TODO 7: Enable the player module
	App->player->Enable();
	App->IA->Enable();

	// TODO 0: trigger background music
	//App->audio->PlayMusic("ken.ogg");

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

	//App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 2.0f); // flag animation
	//App->renderer->Blit(graphics, 0, AnimateShip(), &foreground, 2.0f);

	// TODO 6: Draw the girl. Make sure it follows the ship movement!
	//App->renderer->Blit(graphics, 193, 106 + actualY, &(girl.GetCurrentFrame()), 2.0f);
	//App->renderer->Blit(graphics, 0, 170, &ground);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module

	return UPDATE_CONTINUE;
}