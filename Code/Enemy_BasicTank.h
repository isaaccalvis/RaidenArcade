#ifndef __Enemy_BasicTank_H__
#define __Enemy_BasicTank_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_BasicTank : public Enemy {
private:
	//int original_y = 0;
	Animation Enemy_BasicTank_Animation;

public:
	Enemy_BasicTank(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void Draw(/*SDL_Texture* sprites*/);
};
#endif