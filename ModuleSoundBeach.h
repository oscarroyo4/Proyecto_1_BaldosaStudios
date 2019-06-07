#ifndef __ModuleSoundBeach_H__
#define __ModuleSoundBeach_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

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
	SDL_Texture * graphics3 = nullptr;
	SDL_Texture * graphicsAnim3 = nullptr;
	SDL_Texture * ShadowSB = nullptr;
	Mix_Music * music = nullptr;
	Animation soundBeachSky;
	Animation soundBeachGround;
	Animation backgroundPeople1;
	Animation backgroundPeople2;
	Animation backgroundPeople3;
	Animation backgroundPeople4;
	int PlayerVictories = 0;
	int EnemyVictories = 0;
	bool JoeOnStage = false;
	bool TerryOnStage = false;
	bool AndyOnStage = false;
	int round = 1;
	SDL_Rect rectShadowSB;
};

#endif
