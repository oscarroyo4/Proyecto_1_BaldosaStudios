#ifndef __MODULEINTRO_H__
#define __MODULEINTRO_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleAudio.h"
#include "ModuleCinematics.h"

struct SDL_Texture;

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
	Animation intr;
};

#endif // __MODULEINTRO_H__
