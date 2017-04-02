#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 12

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleBackground;
class ModuleBackground2;
class ModulePlayer;
class ModuleMusic;
class ModuleCollider;
class ModuleFadeToBlack;
class ModuleMenuScreen;
class ModuleParticles;
class Module;

class Application{
public:
	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleBackground* background;
	ModuleBackground2* background2;
	ModulePlayer* player;
	ModuleMusic* music;
	ModuleCollider* collider;
	ModuleFadeToBlack* fade;
	ModuleMenuScreen* menuScreen;
	ModuleParticles* particles;

public:
	
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif