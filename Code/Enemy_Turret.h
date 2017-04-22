#ifndef __Enemy_Turret_H__
#define __Enemy_Turret_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_Turret : public Enemy {
private:
	Animation Enemy_Turret_Animation;

public:
	Enemy_Turret(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void Draw(/*SDL_Texture* sprites*/);
	float deltaY;
	float deltaX;
};
#endif