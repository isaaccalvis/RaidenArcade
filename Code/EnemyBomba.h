#ifndef __Enemy_Bomba_H__
#define __Enemy_Bomba_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_Bomb : public Enemy {
private:
	Animation Enemy_Enemy_Bomb_Animation;

public:
	Enemy_Bomb(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void DrawUp();
};
#endif