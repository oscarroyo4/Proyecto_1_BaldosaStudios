#ifndef __ModulePlayerSelect_H__
#define __ModulePlayerSelect_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Mix_Chunk;

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
	bool played = false;
	bool changed = false;
	int changedTime = 0;
	Animation selectT;
	Animation selectA;
	Animation selectJ;
	Animation* current_animation = nullptr;
	Mix_Chunk* selectHover = nullptr;
	Mix_Chunk* chooseSelection = nullptr;
	Mix_Music* musicPlSel = nullptr;
};

#endif

