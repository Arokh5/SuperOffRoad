#include "Globals.h"
#include "Application.h"
#include "ModuleTitleScreen.h"
#include "ModuleStage.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleTitleScreen::ModuleTitleScreen(bool start_enabled) : Module(start_enabled)
{
	title.x = 307;
	title.y = 397;
	title.w = 319;
	title.h = 199;
}

ModuleTitleScreen::~ModuleTitleScreen()
{
}

// Load assets
bool ModuleTitleScreen::Start()
{
	LOG("Loading Stage");

	graphics = App->textures->Load("general_sprites.png");

	// TODO 0: trigger background music
	//App->audio->PlayMusic("ken.ogg");

	return true;
}

// UnLoad assets
bool ModuleTitleScreen::CleanUp()
{
	LOG("Unloading stage");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw fences
update_status ModuleTitleScreen::Update()
{
	App->renderer->Blit(graphics, 0, 0, &title);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->stage, App->titleScreen, 2.0f);
	}

	return UPDATE_CONTINUE;
}