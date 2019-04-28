#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"



struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

enum player_status
{
	PLAYER_IDLE,
	PLAYER_FORWARD,
	PLAYER_BACKWARD,
	PLAYER_JUMP,
	PLAYER_CROUCH,
	PLAYER_PUNCH,
	PLAYER_KICK,
	PLAYER_SPECIAL,
	PLAYER_DAMAGE,
	PLAYER_IN_PUNCH_FINISH,
	PLAYER_IN_KICK_FINISH,
	PLAYER_IN_JUMP_FINISH,
	PLAYER_DAMAGE_FINISH,
	IN_SPECIAL_FINISH
};


class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	bool godMode;
	bool punchEnable = true;
	bool kickEnable = true;
	bool jumpEnable = true;
	bool specialEnable = true;
	SDL_Texture * graphicsTerry = nullptr;
	SDL_Texture* graphicsTerry2 = nullptr;
	Mix_Chunk* winfx = nullptr;
	Mix_Chunk* defeatfx = nullptr;
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
	Collider* colPlayer;
	Collider* punchCol;
	Collider* kickCol;
	int Life = 100;
	bool hit = false;
	bool punchHit = false;
	bool kickHit = false;
	player_status status = PLAYER_IDLE;
	Uint32 punch_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 damage_timer = 0;
	Uint32 special_timer = 0;
	Uint32 groundFire_timer = 0;
	Uint32 defeat_timer = 0;
	Uint32 win_timer = 0;
	SDL_Rect r;
};

#endif