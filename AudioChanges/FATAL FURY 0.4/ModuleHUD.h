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
	SDL_Rect lifebar, rectPlayer, rectEnemy;
	SDL_Rect win, lose;
	bool Win, Lose;
};

#endif // __MODULEHUD_H__

