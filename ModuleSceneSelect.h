#ifndef __ModuleSceneSelect_H__
#define __ModuleSceneSelect_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Mix_Chunk;

class ModuleSceneSelect : public Module
{
public:
	ModuleSceneSelect();
	~ModuleSceneSelect();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	bool posPaoPao, posSoundBeach;
	bool played = false;
	bool changed = false;
	int changedTime = 0;
	Animation selectPP;
	Animation selectSB;
	Animation Background;
	Animation* current_animation = nullptr;
};

#endif