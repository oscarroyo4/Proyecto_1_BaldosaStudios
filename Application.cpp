#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
#include "ModuleParticles.h"
#include "ModuleIntro.h"
#include "ModuleEnemy.h"
#include "ModuleCollision.h"
#include "ModulePlayerSelect.h"
#include "ModuleHUD.h"
#include "ModuleSounds.h"
#include "ModuleGameControllers.h"
#include "ModuleCinematics.h"


Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = gamepad = new ModuleGameControllers();
	modules[4] = textures = new ModuleTextures();
	modules[5] = paopao = new ModuleScenePaoPao();
	modules[6] = soundBeach = new ModuleSceneSoundBeach();
	modules[7] = cinematics = new ModuleCinematics();
	modules[8] = scene_intro = new ModuleIntro();
	modules[9] = select = new ModulePlayerSelect();
	modules[10] = player = new ModulePlayer();
	modules[11] = enemy = new ModuleEnemy();
	modules[12] = particles = new ModuleParticles();
	modules[13] = fade = new ModuleFadeToBlack();
	modules[14] = sounds = new ModuleSounds();
	modules[15] = collision = new ModuleCollision();
	modules[16] = hud = new ModuleHUD();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Disable all stopped modules here
	scene_intro->Disable();
	player->Disable();
	enemy->Disable();
	select->Disable();
	paopao->Disable();
	soundBeach->Disable();
	hud->Disable();

	// ---

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}