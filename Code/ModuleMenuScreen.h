#ifndef __ModuleMenuScreen_H__
#define __ModuleMenuScreen_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

enum MenuScreenNames {
	StartScreen,
	GameOverScreen
};

class ModuleMenuScreen : public Module {
public:
	ModuleMenuScreen();
	~ModuleMenuScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool selectorScreen(MenuScreenNames name);
public:

	SDL_Texture* MenuScreenTexture = nullptr;
	SDL_Rect MenuScreenRect;
	Animation pantallaIniciAnimStatic;
	Animation pantallaIniciAnim;
};

#endif