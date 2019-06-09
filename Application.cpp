#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAndy.h"
#include "ModuleFadeToBlack.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
#include "ModuleHowardArena.h"
#include "ModuleParticles.h"
#include "ModuleIntro.h"
#include "ModuleEnemy.h"
#include "ModuleCollision.h"
#include "ModulePlayerSelect.h"
#include "ModuleSceneSelect.h"
#include "ModuleHUD.h"
#include "ModuleAudio.h"
#include "ModuleGameControllers.h"
#include "ModuleCinematics.h"
#include "ModuleJoe.h"
#include "ModuleVs.h"
#include "ModuleAndy.h"
#include "ModuleFonts.h"



Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = gamepad = new ModuleGameControllers();
	modules[4] = textures = new ModuleTextures();
	modules[5] = paopao = new ModuleScenePaoPao();
	modules[6] = soundBeach = new ModuleSceneSoundBeach();
	modules[7] = howardArena = new ModuleHowardArena();
	modules[8] = cinematics = new ModuleCinematics();
	modules[9] = scene_intro = new ModuleIntro();
	modules[10] = select = new ModulePlayerSelect();
	modules[11] = player = new ModulePlayer();
	modules[12] = enemy = new ModuleEnemy();
	modules[13] = particles = new ModuleParticles();
	modules[14] = fade = new ModuleFadeToBlack();
	modules[15] = sounds = new ModuleAudio();
	modules[16] = collision = new ModuleCollision();
	modules[17] = hud = new ModuleHUD();
	modules[18] = joe = new ModuleJoe();
	modules[19] = andy = new ModuleAndy();
	modules[20] = fonts = new ModuleFonts();
	modules[21] = selectScene = new ModuleSceneSelect();
	modules[22] = versus = new ModuleVsCinematic();

}

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Disable all stopped modules here
	scene_intro->Disable();
	player->Disable();
	joe->Disable();
	andy->Disable();
	enemy->Disable();
	select->Disable();
	selectScene->Disable();
	paopao->Disable();
	soundBeach->Disable();
	howardArena->Disable();
	hud->Disable();
	versus->Disable();

	// ---

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}