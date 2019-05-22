#ifndef __ModuleAndy_H__
#define __ModuleAndy_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"
#include "ModuleSounds.h"

struct SDL_Texture;
struct Collider;

enum andy_status
{
	ANDY_IDLE,
	ANDY_FORWARD,
	ANDY_BACKWARD,
	ANDY_JUMP,
	ANDY_CROUCH,
	ANDY_PUNCH,
	ANDY_KICK,
	ANDY_SPECIAL,
	ANDY_DAMAGE,
	ANDY_IN_PUNCH_FINISH,
	ANDY_IN_KICK_FINISH,
	ANDY_IN_JUMP_FINISH,
	ANDY_DAMAGE_FINISH,
	ANDY_IN_SPECIAL_FINISH
};


class ModuleAndy : public Module
{
public:
	ModuleAndy();
	~ModuleAndy();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	bool godMode;
	bool punchEnable = true;
	bool kickEnable = true;
	bool jumpEnable = true;
	bool specialEnable = true;
	bool input = true;
	SDL_Event ev;
	SDL_Texture * graphicsAndy = nullptr;
	SDL_Texture* graphicsAndy2 = nullptr;
	Animation* current_animation = &idle;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation jump;
	Animation specialAttack;
	Animation specialAttackStatic;
	Animation crouch;
	Animation damage;
	Animation defeat;
	Animation win;
	iPoint position;
	Collider* colPlayer;
	Collider* punchCol;
	Collider* kickCol;
	Collider* specialCol1;
	Collider* specialCol2;
	Collider* specialCol3;
	int Life = 100;
	int PlayerVict = 0;
	bool hit = false;
	bool punchHit = false;
	bool kickHit = false;
	andy_status status = ANDY_IDLE;
	Uint32 punch_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 damage_timer = 0;
	Uint32 special_timer = 0;
	Uint32 groundFire_timer = 0;
	Uint32 defeat_timer = 0;
	Uint32 win_timer = 0;
	Mix_Chunk* punchfx = nullptr;
	Mix_Chunk* kickfx = nullptr;
	Mix_Chunk* jumpfx = nullptr;
	Mix_Chunk* specialfx = nullptr;
	Mix_Chunk* winfx = nullptr;
	Mix_Chunk* defeatfx = nullptr;
	SDL_Rect r;

};

#endif