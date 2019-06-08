#ifndef __ModuleJoe_H__
#define __ModuleJoe_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"

struct SDL_Texture;
struct Collider;

enum joe_status
{
	JOE_IDLE,
	JOE_FORWARD,
	JOE_BACKWARD,
	JOE_JUMP,
	JOE_CROUCH,
	JOE_PUNCH,
	JOE_KICK,
	JOE_SPECIAL,
	JOE_SPECIAL_KICK,
	JOE_DAMAGE,
	JOE_IN_PUNCH_FINISH,
	JOE_IN_KICK_FINISH,
	JOE_IN_JUMP_FINISH,
	JOE_DAMAGE_FINISH,
	JOE_IN_SPECIAL_FINISH,
	JOE_IN_SPECIAL_KICK_FINISH,
	JOE_CROUCH_PUNCH_FINISH
};


class ModuleJoe : public Module
{
public:
	ModuleJoe();
	~ModuleJoe();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	bool godMode;
	bool punchEnable = true;
	bool kickEnable = true;
	bool specialkickEnable = true;
	bool jumpEnable = true;
	bool specialEnable = true;
	bool crouchPunchEnable = true;
	bool input = true;
	SDL_Event ev;
	SDL_Texture * graphicsJoe = nullptr;
	Animation* current_animation = &idle;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation specialkick;
	Animation jump;
	Animation specialAttack;
	Animation specialAttackStatic;
	Animation crouch;
	Animation crouchPunch;
	Animation damage;
	Animation defeat;
	Animation win;
	iPoint position;
	Collider* colPlayer=nullptr;
	Collider* colPlayerCrouch = nullptr;
	Collider* punchCol=nullptr;
	Collider* kickCol=nullptr;
	Collider* crouchPunchCol=nullptr;
	Collider* specialCol;
	int Life = 100;
	int PlayerVict = 0;
	bool hit = false;
	bool punchHit = false;
	bool crouchPunchHit = false;
	bool kickHit = false;
	joe_status status = JOE_IDLE;
	Uint32 punch_timer = 0;
	Uint32 jump_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 damage_timer = 0;
	Uint32 crouch_punch_timer = 0;
	Uint32 special_timer = 0;
	Uint32 special_kick_timer = 0;
	Uint32 tornado_timer = 0;
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
