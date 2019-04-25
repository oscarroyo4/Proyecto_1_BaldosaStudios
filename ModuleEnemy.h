#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

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
	Animation* current_animation = nullptr;
	Animation idle;
	Animation damage;
	iPoint position;
	Collider* colEnemy;
	SDL_Rect r;
	int Life = 100;
	bool hit = false;
};
#endif
