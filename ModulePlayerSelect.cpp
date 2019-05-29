#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
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
	musicPlSel = App->sounds->Load_music("Assets/Audio/CharacterSelection.ogg");
	selectHover = App->sounds->Load_effects("Assets/Audio/Fx/FX_SelectHover.wav");
	chooseSelection = App->sounds->Load_effects("Assets/Audio/Fx/FX_ChooseSelection.wav");
	if (!App->sounds->Play_music(musicPlSel))
	{
		LOG("Could not play music. Mix_PlayChannel: %s", Mix_GetError());
		ret = false;
	}
	posA = false;
	posT = true;
	posJ = false;
	return ret;
}

// UnLoad assets
bool ModulePlayerSelect::CleanUp()
{
	LOG("Unloading ken scene");
	if (!IsEnabled()) {
		SDL_DestroyTexture(graphics);
		//Audio
		App->sounds->Unload_music(musicPlSel);
		App->sounds->Unload_effects(selectHover);
		App->sounds->Unload_effects(chooseSelection);
		App->paopao->Enable();
	}
	return true;
}

// Update: draw background
update_status ModulePlayerSelect::Update()
{
	// Draw everything --------------------------------------

	if (posT == true) { App->render->Blit(graphics, 7, 0, &(selectT.GetCurrentFrame()), 0.75f); }
	if (posJ == true) { App->render->Blit(graphics, 7, 0, &(selectJ.GetCurrentFrame()), 0.75f); }
	if (posA == true) { App->render->Blit(graphics, 7, 0, &(selectA.GetCurrentFrame()), 0.75f); }


	if (App->input->GetKey(SDL_SCANCODE_A) && posT == true && changed == false)
	{
		current_animation = &selectJ;
		posJ = true;
		posT = false;
		posA = false;
		if (App->sounds->Play_chunk(selectHover))
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
		changed = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_D) && posT == true && changed == false)
	{
		current_animation = &selectA;
		posA = true;
		posJ = false;
		posT = false;
		if (App->sounds->Play_chunk(selectHover))
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
		changed = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_A) && posA == true && changed == false)
	{
		current_animation = &selectT;
		posA = false;
		posJ = false;
		posT = true;
		if (App->sounds->Play_chunk(selectHover))
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
		changed = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_D) && posJ == true && changed == false)
	{
		current_animation = &selectT;
		posA = false;
		posJ = false;
		posT = true;
		if (App->sounds->Play_chunk(selectHover))
		{
			LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
		}
		changed = true;
	}


	else if (App->input->GetKey(SDL_SCANCODE_T))
	{
		if (played == false) {
			if (App->sounds->Play_chunk(chooseSelection))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			else played = true;
		}
	
		App->fade->FadeToBlack(this, App->paopao, 0.5);
		if (posJ == true) { 
			App->paopao->JoeOnStage = true; 
			App->soundBeach->JoeOnStage = true; 
		}
		if (posT == true) { 
			App->paopao->TerryOnStage = true; 
			App->soundBeach->TerryOnStage = true;
		}
		if (posA == true) {
			App->paopao->AndyOnStage = true; 
			App->soundBeach->AndyOnStage = true;
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