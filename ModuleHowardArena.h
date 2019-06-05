#ifndef __ModuleHowardArena_H__
#define __ModuleHowardArena_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleHowardArena : public Module
{
public:
	ModuleHowardArena();
	~ModuleHowardArena();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	SDL_Texture * graphics2 = nullptr;
	SDL_Texture * ShadowHA = nullptr;

	Animation HA_Sky;
	Animation HA_SkyLightning;
	Animation HA_Ground;
	Animation HA_Tree;

	Animation HA_Sky2;
	Animation HA_Ground2;
	Animation HA_Tree2;
	Animation HA_Rain;

	int Lightning_counter = 0;
	int PlayerVictories = 0;
	int EnemyVictories = 0;
	bool JoeOnStage = false;
	bool TerryOnStage = false;
	bool AndyOnStage = false;
	int round = 1;
	SDL_Rect rectShadowHA;
};

#endif
