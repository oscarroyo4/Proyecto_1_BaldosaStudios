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
	IN_PUNCH_FINISH_ENEMY,
	IN_KICK_FINISH_ENEMY,
	IN_JUMP_FINISH_ENEMY,
	DAMAGE_FINISH_ENEMY
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
	iPoint position;
	Collider* colEnemy;
	SDL_Rect r;	
	Collider* punchCol;
	Collider* kickCol;
	int Life = 100;
	bool hit = false;
	bool godMode;
	bool punchEnable = true;
	bool kickEnable = true;
	bool jumpEnable = true;
	bool punchHit = false;
	bool kickHit = false;
	enemy_status status = ENEMY_IDLE;
	Uint32 punch_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 damage_timer = 0;

};
#endif
