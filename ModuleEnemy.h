#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

enum enemy_status
{
	ENEMY_IDLE,
	ENEMY_FORWARD,
	ENEMY_BACKWARD,
	ENEMY_JUMP,
	ENEMY_CROUCH,
	ENEMY_PUNCH,
	ENEMY_KICK,
	ENEMY_SPECIAL,
	ENEMY_DAMAGE,
	ENEMY_IN_PUNCH_FINISH,
	ENEMY_IN_KICK_FINISH,
	ENEMY_IN_JUMP_FINISH,
	ENEMY_DAMAGE_FINISH
};

class ModuleEnemy : public Module
{
public:
	ModuleEnemy();
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	bool godMode;
	bool punchEnable = true;
	bool kickEnable = true;
	bool jumpEnable = true;
	SDL_Texture * graphicsTerry = nullptr;	
	SDL_Texture* graphicsTerry2 = nullptr;
	Animation* current_animation = &idle;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation jump;
	Animation specialAttack;
	Animation crouch;
	Animation damage;
	Animation defeat;
	Animation win;
	iPoint position;
	Collider* colEnemy;
	Collider* punchCol;
	Collider* kickCol;
	int Life = 100;
	bool hit = false;
	bool punchHit = false;
	bool kickHit = false;
	enemy_status status = ENEMY_IDLE;
	Uint32 punch_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 damage_timer = 0;
	Uint32 defeat_timer = 0;
	Uint32 win_timer = 0;
	SDL_Rect r;

};
#endif
