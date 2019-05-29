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
	SDL_Texture * life = nullptr;
	SDL_Texture * youWin = nullptr;
	SDL_Texture * youLose = nullptr;
	SDL_Texture * round = nullptr;
	SDL_Texture * newround = nullptr;
	SDL_Rect lifebar, rectPlayer, rectEnemy;
	SDL_Rect win, lose, r;
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

