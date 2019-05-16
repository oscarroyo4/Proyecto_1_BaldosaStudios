#ifndef __ModuleSoundBeach_H__
#define __ModuleSoundBeach_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Mix_Chunk;

class ModuleSceneSoundBeach : public Module
{
public:
	ModuleSceneSoundBeach();
	~ModuleSceneSoundBeach();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	SDL_Texture * graphicsAnim = nullptr;
	SDL_Texture * graphics2 = nullptr;
	SDL_Texture * graphicsAnim2 = nullptr;
	Mix_Chunk * music = nullptr;
	Animation soundBeachSky;
	Animation soundBeachGround;
	Animation backgroundPeople1;
	Animation backgroundPeople2;
	Animation backgroundPeople3;
	Animation backgroundPeople4;
};

#endif
