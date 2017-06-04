#ifndef __vTank_H__
#define __vTank_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class vTank : public Enemy {
private:
	Animation vTank_Animation1;
	Animation vTank_Animation2;

	int current_time;
	int piun;
	bool dispara;
	int state;
	fPoint original_pos;
public:
	vTank(int x, int y);
	~vTank() {}
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
};
#endif