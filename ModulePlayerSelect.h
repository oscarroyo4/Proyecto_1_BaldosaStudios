#ifndef __ModulePlayerSelect_H__
#define __ModulePlayerSelect_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModulePlayerSelect : public Module
{
public:
	ModulePlayerSelect();
	~ModulePlayerSelect();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	bool posT, posJ, posA;
	Animation selectT;
	Animation selectA;
	Animation selectJ;
	Animation* current_animation = nullptr;
	Mix_Chunk* selectHover = nullptr;
	Mix_Chunk* chooseSelection = nullptr;
};

#endif

