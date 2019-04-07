#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 13

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleScenePaoPao;
class ModulePlayer;
class ModuleEnemy;
class ModuleIntro;
class ModulePlayerSelect;
class ModuleFadeToBlack;
class ModuleSounds;
class ModuleCollision;
class Module;

// TODO 1: Create an intro scene with rtype/intro.png that then fades to ModuleSpaceScene

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleScenePaoPao* paopao;
	ModuleIntro* scene_intro;
	ModulePlayer* player;
	ModuleEnemy* enemy;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModulePlayerSelect* select;
	ModuleSounds* sounds;
	ModuleCollision* collision;


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