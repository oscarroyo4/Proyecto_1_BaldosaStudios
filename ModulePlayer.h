#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"

struct SDL_Texture;
struct Collider;

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
	IN_PUNCH_FINISH,
	IN_KICK_FINISH,
	IN_JUMP_FINISH
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
	iPoint position;
	Collider* colPlayer;
	player_status status = PLAYER_IDLE;
	Uint32 punch_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 kick_timer = 0;
};

#endif