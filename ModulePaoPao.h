#ifndef __ModulePaoPao_H__
#define __ModulePaoPao_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleSounds.h"


struct SDL_Texture;

class ModuleScenePaoPao : public Module
{
public:
	ModuleScenePaoPao();
	~ModuleScenePaoPao();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	Mix_Music* music = nullptr;
	Animation paopao;
	int PlayerVictories = 0;
	int AndyVictories = 0;
	int JoeVictories = 0;
	int EnemyVictories = 0;
	bool JoeOnStage = false;
	bool TerryOnStage = false;
	bool AndyOnStage = false;
};

#endif
