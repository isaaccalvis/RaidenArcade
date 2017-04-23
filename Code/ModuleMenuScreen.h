#ifndef __ModuleMenuScreen_H__
#define __ModuleMenuScreen_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

enum MenuScreenNames {
	Start_Screen,
	Players_Screen,
	Game_Over_Screen
};

class ModuleMenuScreen : public Module {
public:
	ModuleMenuScreen();
	~ModuleMenuScreen();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool selectorScreen(MenuScreenNames name);
	bool CridaMenu();

public:
	SDL_Texture* MenuScreenTexture = nullptr;
	SDL_Texture* MenuScreenGameOver= nullptr;
	Animation* 	current_animation;// &pantallaIniciAnim;
	SDL_Rect MenuScreenRect;
	Animation MainMenu;
	Animation Transition;
	Animation GameOver;
	int Menu_Actual_Fase;
	uint current_time;

	SDL_Texture* raiden_sprite;
	SDL_Texture* loading_sprite;
	SDL_Texture* player_sprite;
	SDL_Texture* gameOver_sprite;
};

#endif