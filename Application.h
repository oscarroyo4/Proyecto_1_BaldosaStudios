#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleScenePaoPao;
class ModuleSceneSoundBeach;
class ModulePlayer;
class ModuleEnemy;
class ModuleIntro;
class ModulePlayerSelect;
class ModuleFadeToBlack;
class ModuleSounds;
class ModuleCollision;
class ModuleHUD;
class ModuleGameControllers;
class ModuleCinematics;

class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleScenePaoPao* paopao;
	ModuleSceneSoundBeach* soundBeach;
	ModuleIntro* scene_intro;
	ModulePlayer* player;
	ModuleEnemy* enemy;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModulePlayerSelect* select;
	ModuleSounds* sounds;
	ModuleCollision* collision;
	ModuleHUD* hud;
	ModuleGameControllers* gamepad;
	ModuleCinematics* cinematics;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__