#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"

class Enemy_LightShooter : public Enemy{
private:
	float wave = -1.0f;
	bool going_down = true;
	bool going_up = false;
	int original_x = 0;
	Animation lightShooterAnim;

public:
	Enemy_LightShooter(int x, int y);
	void Move();
};
#endif