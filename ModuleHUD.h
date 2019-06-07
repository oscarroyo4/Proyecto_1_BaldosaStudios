#ifndef __MODULEHUD_H__
#define __MODULEHUD_H__

#include "Module.h"

struct SDL_Texture;

class ModuleHUD : public Module
{
public:
	ModuleHUD();
	~ModuleHUD();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Renderer *renderer;
	SDL_Texture *hud = nullptr;
	SDL_Rect lifebar, lifebar2, rectPlayer, rectEnemy;
	SDL_Rect win, lose, r, fight, round1, round2;
	Animation roundCircle;
	Animation roundCircleWon;
	bool Win, Lose;

	int fontID = -1;
	int timer = 0;

	int ticks1;
	int ticks2;
	int ticks3;
	char time[3];
};

#endif // __MODULEHUD_H__

