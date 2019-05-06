#ifndef __ENEMY_BROWNCOOKIES_H__
#define __ENEMY_BROWNCOOKIES_H__

#include "Enemy.h"

class Enemy_BrownCookies : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	fPoint original_pos;
	Animation* fly;

public:

	Enemy_BrownCookies(int x, int y);

	void Move();
};

#endif // __ENEMY_BROWNCOOKIES_H__