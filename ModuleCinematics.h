#ifndef __MODULECINEMATICS_H__
#define __MODULECINEMATICS_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Mix_Chunk;

class ModuleCinematics : public Module
{
public:
	ModuleCinematics();
	~ModuleCinematics();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * background = nullptr;
	SDL_Texture * fatalfuryintro = nullptr;
	SDL_Texture * fatalfuryintrowords = nullptr;
	SDL_Texture * inscoins = nullptr;
	Animation BetweenPaoPaoAndBeachAnimation;
	Animation GameIntroCinematicBackground;
	Animation GameIntroCinematicWords;
	Animation GameIntroCinematicTerry;
	Animation insertcoins;
	bool finalpaopao = false;
	int finalpaopao_timer = 0;
	int GameIntroCinematic_timer = 0;
};

#endif // __MODULEINTRO_H__
