#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModuleInput.h"
#include "ModuleIntro.h"
#include "ModuleSounds.h"
#include "ModulePlayerSelect.h"
#include "ModuleFadeToBlack.h"
#include "SDL_image/include/SDL_image.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayerSelect::ModulePlayerSelect()
{
	selectT.PushBack({ 0, 0, 304, 224 });
	selectT.PushBack({ 304, 0, 304, 224 });
	selectT.speed = 0.1f;

	selectJ.PushBack({ 0, 224, 304, 224 });
	selectJ.PushBack({ 304, 224, 304, 224 });
	selectJ.speed = 0.1f;

	selectA.PushBack({ 0, 448, 304, 224 });
	selectA.PushBack({ 304, 448, 304, 224 });
	selectA.speed = 0.1f;

	current_animation = &selectT;
	posT = true;
	posJ = false;
	posA = false;
}

ModulePlayerSelect::~ModulePlayerSelect()
{}

// Load assets
bool ModulePlayerSelect::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/Main/PlayerSelect.png");
	App->scene_intro->Disable();
	selectHover = App->sounds->Load("Assets/Audio/Fx/FX_SelectHover.wav");
	chooseSelection = App->sounds->Load("Assets/Audio/Fx/FX_ChooseSelection.wav");
	return ret;
}

// UnLoad assets
bool ModulePlayerSelect::CleanUp()
{
	LOG("Unloading ken scene");

	SDL_DestroyTexture(graphics);
	App->paopao->Enable();

	return true;
}

// Update: draw background
update_status ModulePlayerSelect::Update()
{
	// Draw everything --------------------------------------

	if (posT == true) { App->render->Blit(graphics, 7, 0, &(selectT.GetCurrentFrame()), 0.75f); }
	if (posJ == true) { App->render->Blit(graphics, 7, 0, &(selectJ.GetCurrentFrame()), 0.75f); }
	if (posA == true) { App->render->Blit(graphics, 7, 0, &(selectA.GetCurrentFrame()), 0.75f); }


	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN && posT == true)
	{
		current_animation = &selectJ;
		posJ = true;
		posT = false;
		posA = false;
		if (Mix_PlayChannel(-1, selectHover, 0) == -1)
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN && posT == true)
	{
		current_animation = &selectA;
		posA = true;
		posJ = false;
		posT = false;
		if (Mix_PlayChannel(-1, selectHover, 0) == -1)
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN && posA == true)
	{
		current_animation = &selectT;
		posA = false;
		posJ = false;
		posT = true;
		if (Mix_PlayChannel(-1, selectHover, 0) == -1)
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN && posJ == true)
	{
		current_animation = &selectT;
		posA = false;
		posJ = false;
		posT = true;
		if (Mix_PlayChannel(-1, selectHover, 0) == -1)
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
	}




	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		if (Mix_PlayChannel(-1, chooseSelection, 0) == -1)
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
		App->fade->FadeToBlack(this, App->paopao, 0.5);
	}

	return UPDATE_CONTINUE;
}