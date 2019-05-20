#ifndef __MODULEINTRO_H__
#define __MODULEINTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Mix_Chunk;

class ModuleIntro : public Module
{
public:
	ModuleIntro();
	~ModuleIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * background = nullptr;
	Mix_Chunk * musicIntro = nullptr;
	Animation intr;
};

#endif // __MODULEINTRO_H__
