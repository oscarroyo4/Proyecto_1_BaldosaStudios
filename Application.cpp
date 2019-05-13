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


Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = paopao = new ModuleScenePaoPao();
	modules[5] = soundBeach = new ModuleSceneSoundBeach();
	modules[6] = scene_intro = new ModuleIntro();
	modules[7] = select = new ModulePlayerSelect();
	modules[8] = player = new ModulePlayer();
	modules[9] = enemy = new ModuleEnemy();
	modules[10] = particles = new ModuleParticles();
	modules[11] = fade = new ModuleFadeToBlack();
	modules[12] = sounds = new ModuleSounds();
	modules[13] = collision = new ModuleCollision();
	modules[14] = hud = new ModuleHUD();
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