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
	SDL_Texture * Hud = nullptr;
	SDL_Rect lifebar_p, lifebar_e, rectPlayer, rectEnemy;
	SDL_Rect win, lose, r;
	Animation roundCircle;
	Animation roundCircleWon;
	bool Win, Lose;
};

#endif // __MODULEHUD_H__

