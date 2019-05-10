#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleIntro.h"
#include "ModuleCollision.h"
#include "ModuleSounds.h"
#include "ModuleEnemy.h"
#include "ModuleHUD.h"
#include "ModuleFadeToBlack.h"
#include "SDL_image/include/SDL_image.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScenePaoPao::ModuleScenePaoPao()
{
	paopao.PushBack({ 0, 0, 619, 224 });
	paopao.PushBack({ 0, 224, 619, 224 });
	paopao.speed = 0.08f;


}

ModuleScenePaoPao::~ModuleScenePaoPao()
{}

// Load assets
bool ModuleScenePaoPao::Start()
{
	App->hud->Enable();
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/Pao Pao Cafe Tileset/Pao Pao Cafe Stage.png");
	music = App->sounds->Load("Assets/Audio/PaoPao.ogg");
	App->player->Enable();
	App->enemy->Enable();
	App->render->camera.x = -530;
	//Play the music
	if (Mix_PlayChannel(-1, music, 0) == -1)
	{
		LOG("Could not play music. Mix_PlayChannel: %s", Mix_GetError());
		ret = false;
	}
	return ret;
}

// UnLoad assets
bool ModuleScenePaoPao::CleanUp()
{
	LOG("Unloading ken scene");

	App->paopao->Disable();
	SDL_DestroyTexture(graphics);
	App->sounds->Unload(music);
	App->player->Disable();
	App->enemy->Disable();
	App->hud->Disable();

	return true;
}

// Update: draw background
update_status ModuleScenePaoPao::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &(paopao.GetCurrentFrame()), 0.75f);

	App->render->camera.x = App->player->position.x  * -2; 

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(this, App->scene_intro, 2.5);
	}

	return UPDATE_CONTINUE;
}