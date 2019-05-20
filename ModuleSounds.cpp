#include "Globals.h"
#include "Application.h"
#include "ModuleSounds.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleSounds::ModuleSounds() : Module()
{
	for (uint i = 0; i < MAX_SOUNDS; ++i)
		sounds[i] = nullptr;
}

// Destructor
ModuleSounds::~ModuleSounds()
{}

// Called before sounds is available
bool ModuleSounds::Init()
{
	LOG("Init Sound library");
	bool ret = true;
	last_sound = 0;
	// load support for the mp3 and ogg audio format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}
	//Initialize SDL_mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

	return ret;
}

// Called before quitting
bool ModuleSounds::CleanUp()
{
	LOG("Freeing sounds and Mixer library");

	for (uint i = 0; i < last_sound; ++i)
		if (sounds[i] != nullptr)
			//Destroy sounds
			Mix_FreeChunk(sounds[i]);

	Mix_CloseAudio();
	Mix_Quit();
	return true;
}

// Load new sound from file path
Mix_Chunk* const ModuleSounds::Load(const char* path)
{
	sound = nullptr;

	//Load audio file
	sound = Mix_LoadWAV(path);
	//sound = Mix_LoadWAV_RW(SDL_RWFromFile(path, "rb"), 1);
	if (sound == nullptr) {
		LOG("Could not load sound with path: %s. Mix_LoadWAV: %s", path, Mix_GetError());
		return nullptr;
	}
	else {
		sounds[last_sound++] = sound;
		//soundsCount++;
	}
	
	return sound;
}

bool ModuleSounds::Unload()
{
	bool ret = true;

	for (int i = 0; i < last_sound; i++)
	{
		//Destroy sound
		Mix_FreeChunk(sounds[i]);
		sounds[i] = nullptr;
		if (sounds[i] != nullptr) ret = false;
	}
	last_sound = 0;
	return ret;
}

