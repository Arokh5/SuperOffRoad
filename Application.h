#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCollision;
class ModulePlayer;
class ModuleIA;
class ModuleTitleScreen;
class ModuleStage;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModulePlayer* player = nullptr;
	ModuleIA* IA = nullptr;
	ModuleTitleScreen* titleScreen = nullptr;
	ModuleStage* stage = nullptr;

private:
	void DetectCollisions();
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__