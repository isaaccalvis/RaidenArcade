#ifndef __Enemy_BasicTank_H__
#define __Enemy_BasicTank_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_BasicTank : public Enemy {
private:
	int original_y = 0;
	Animation Enemy_BasicTank_Animation1;
	Animation Enemy_BasicTank_Animation2;
	Animation Enemy_BasicTank_Animation3;
	Animation Enemy_BasicTank_Animation4;
	Animation Enemy_BasicTank_Animation5;
	Animation Enemy_BasicTank_Animation6;
	Animation Enemy_BasicTank_Animation7;
	Animation Enemy_BasicTank_Animation8;
	Animation Enemy_BasicTank_Animation9;
	Animation Enemy_BasicTank_Animation10;
	Animation Enemy_BasicTank_Animation11;
	Animation Enemy_BasicTank_Animation12;
	Animation Enemy_BasicTank_Animation13;
	Animation Enemy_BasicTank_Animation14;
	Animation Enemy_BasicTank_Animation15;
	Animation Enemy_BasicTank_Animation16;
	Animation Enemy_BasicTank_Death;

public:
	Enemy_BasicTank(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown(/*SDL_Texture* sprites*/);
	float rectaY;
	float rectaX;
	int current_time;
	bool dispara;
	int piun;
	int estat;
};
#endif