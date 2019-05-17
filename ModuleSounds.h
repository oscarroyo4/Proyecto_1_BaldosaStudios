#ifndef __ModuleSounds_H__
#define __ModuleSounds_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_SOUNDS 100

class ModuleSounds : public Module
{
public:
	ModuleSounds();
	~ModuleSounds();

	bool Init();
	bool CleanUp();

	Mix_Chunk* const Load(const char* path);
	bool Unload();

public:
	Mix_Chunk* sounds[MAX_SOUNDS];
	uint last_sound = 0;
	uint soundsCount = 0;
};

#endif // __ModuleSounds_H__
