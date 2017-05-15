#ifndef __HeavyOrangeAirship_H__
#define __HeavyOrangeAirship_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class HeavyOrangeAirship : public Enemy {
private:
	Animation HeavyOrangeAirship_Animation;
	int current_time;
	bool dispara;
public:
	HeavyOrangeAirship(int x, int y);
	~HeavyOrangeAirship(){}
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
};
#endif