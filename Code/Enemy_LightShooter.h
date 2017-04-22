#ifndef __ENEMY_LightShooter_H__
#define __ENEMY_LightShooter_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_LightShooter : public Enemy{
private:
	//int original_y = 0;
	Animation LightShooterAnim;
	Animation LightShooterHelix;

public:
	Enemy_LightShooter(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void Draw();
};
#endif