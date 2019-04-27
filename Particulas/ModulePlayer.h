#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

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
	Animation* current_animation = nullptr;
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
};

#endif