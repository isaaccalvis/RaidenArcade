#ifndef __DiamondPlane_H__
#define __DiamondPlane_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class DiamondPlane : public Enemy {
private:
	Animation DiamondPlane_Animation;
	int current_time;
	bool dispara;
	int move;
public:
	DiamondPlane(int x, int y);
	~DiamondPlane(){}
	void Move();
	void OnCollision(Collider* collider);
	void DrawUp();
	float rectaY;
	float rectaX;
};
#endif