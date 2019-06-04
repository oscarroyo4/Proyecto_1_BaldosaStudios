#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
#include "ModuleHowardArena.h"
#include "ModuleInput.h"
#include "ModuleSounds.h"
#include "ModulePlayerSelect.h"
#include "ModuleSceneSelect.h"
#include "ModuleFadeToBlack.h"
#include "SDL_image/include/SDL_image.h"


ModuleSceneSelect::ModuleSceneSelect()
{
	selectPP.PushBack({ 0, 224, 96, 64 });
	selectPP.PushBack({ 0, 288, 96, 64 });
	selectPP.speed = 0.1f;

	selectSB.PushBack({ 96, 224, 96, 64 });
	selectSB.PushBack({ 96, 288, 96, 64 });
	selectSB.speed = 0.1f;

	selectHA.PushBack({ 192, 224, 96, 64 });
	selectHA.PushBack({ 192, 288, 96, 64 });
	selectHA.speed = 0.1f;

	Background.PushBack({ 0, 0, 304, 224 });
	current_animation = &selectPP;
	posPaoPao = true;
	posSoundBeach = false;

}

ModuleSceneSelect::~ModuleSceneSelect()
{}

// Load assets
bool ModuleSceneSelect::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/Main/SelectMap.png");

	posPaoPao = true;
	posSoundBeach = false;
	return ret;
}

// UnLoad assets
bool ModuleSceneSelect::CleanUp()
{
	LOG("Unloading ken scene");
	if (!IsEnabled()) {
		SDL_DestroyTexture(graphics);
		//Audio

	}
	return true;
}


update_status ModuleSceneSelect::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &(Background.GetCurrentFrame()), 0.75f);
	if (posPaoPao == true) { App->render->Blit(graphics, 56, 80, &(selectPP.GetCurrentFrame()), 0.75f); }
	if (posSoundBeach == true) { App->render->Blit(graphics, 152, 80, &(selectSB.GetCurrentFrame()), 0.75f); }
	if (posHowardArena == true) { App->render->Blit(graphics, 152, 144, &(selectHA.GetCurrentFrame()), 0.75f); }

	if (App->input->GetKey(SDL_SCANCODE_D) && posPaoPao == true && changed == false)
	{
		current_animation = &selectPP;
		posPaoPao= false;
		posSoundBeach = true;
		posHowardArena = false;
		changed = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_A) && posSoundBeach == true && changed == false)
	{
		current_animation = &selectSB;
		posPaoPao = true;
		posSoundBeach = false;
		posHowardArena = false;
		changed = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_S) && posSoundBeach == true && changed == false)
	{
		current_animation = &selectHA;
		posPaoPao = false;
		posSoundBeach = false;
		posHowardArena = true;
		changed = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_W) && posHowardArena == true && changed == false)
	{
		current_animation = &selectSB;
		posPaoPao = false;
		posSoundBeach = true;
		posHowardArena = false;
		changed = true;
	}


	else if (App->input->GetKey(SDL_SCANCODE_T))
	{
		if (posPaoPao == true) {
			App->fade->FadeToBlack(this, App->paopao, 1.5);
		}
		if (posSoundBeach == true) {
			App->fade->FadeToBlack(this, App->soundBeach, 1.5);
		}
		if (posHowardArena == true) {
			App->fade->FadeToBlack(this, App->howardArena, 1.5);
		}
	}
	else {
		if (changedTime > 25) {
			changed = false;
			changedTime = 0;
		}
		else {
			changedTime += 1;
		}
	}

	return UPDATE_CONTINUE;
}