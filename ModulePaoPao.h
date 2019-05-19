#ifndef __ModulePaoPao_H__
#define __ModulePaoPao_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Mix_Chunk;

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
	Mix_Chunk * music = nullptr;
	Animation paopao;
	int PlayerVictories = 0;
	int EnemyVictories = 0;
};

#endif
