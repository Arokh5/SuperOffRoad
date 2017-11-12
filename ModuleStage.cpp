#include "Globals.h"
#include "Application.h"
#include "ModuleStage.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
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

	return true;
}

// Update: draw background
update_status ModuleStage::Update()
{
	App->renderer->Blit(graphics, 0, 0, &background, 0.0f);
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