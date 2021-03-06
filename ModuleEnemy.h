#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"

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
	ENEMY_SPECIAL_PUNCH,
	ENEMY_KICK,
	ENEMY_SPECIAL,
	ENEMY_DAMAGE,
	ENEMY_IN_PUNCH_FINISH,
	ENEMY_IN_KICK_FINISH,
	ENEMY_CROUCH_PUNCH_FINISH,
	ENEMY_IN_JUMP_FINISH,
	ENEMY_DAMAGE_FINISH,
	ENEMY_IN_SPECIAL_FINISH,
	ENEMY_SPECIAL_PUNCH_FINISH
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
	bool crouchPunchEnable = true;
	bool specialpunchEnable = true;
	bool kickEnable = true;
	bool jumpEnable = true;
	bool specialEnable = true;
	bool input = true;
	SDL_Texture * graphicsTerry = nullptr;
	SDL_Texture* Shadow = nullptr;
	Animation* current_animation = &idle;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation jump;
	Animation specialAttack;
	Animation specialpunch;
	Animation specialAttackStatic;
	Animation crouch;
	Animation crouchPunch;
	Animation damage;
	Animation defeat;
	Animation win;
	iPoint position;
	Collider* colEnemy;
	Collider* colEnemyCrouch;
	Collider* punchCol;
	Collider* crouchPunchCol = nullptr;
	Collider* kickCol;
	int Life = 100;
	bool hit = false;
	bool punchHit = false;
	bool crouchPunchHit = false;
	bool kickHit = false;
	enemy_status status = ENEMY_IDLE;
	Uint32 punch_timer = 0;
	Uint32 crouch_punch_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 damage_timer = 0;
	Uint32 special_timer = 0;
	Uint32 special_punch_timer = 0;
	Uint32 groundFire_timer = 0;
	Uint32 defeat_timer = 0;
	Uint32 win_timer = 0;
	Mix_Chunk* punchfx1 = nullptr;
	Mix_Chunk* kickfx1 = nullptr;
	Mix_Chunk* jumpfx1 = nullptr;
	Mix_Chunk* specialfx1 = nullptr;
	Mix_Chunk* winfx1 = nullptr;
	Mix_Chunk* defeatfx1 = nullptr;
	SDL_Rect r;

};
#endif
