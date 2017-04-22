
#ifndef Enemy_BonusPlane_H
#define Enemy_BonusPlane_H

#include "Enemy.h"
#include "ModuleEnemies.h"
#include "Path.h"

class Enemy_BonusPlane : public Enemy {
private:
	Animation Enemy_BonusPlane_Animation;

	Path path;
	fPoint original_pos;

public:
	Enemy_BonusPlane(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void Draw();
};
#endif