#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
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

ModuleSceneSoundBeach::ModuleSceneSoundBeach()
{
	soundBeachSky.PushBack({ 0, 0, 461, 104 });
	soundBeachSky.PushBack({ 0, 104, 461, 104 });
	soundBeachSky.PushBack({ 0, 208, 461, 104 });
	soundBeachSky.speed = 0.05f;

	soundBeachGround.PushBack({ 0, 312, 608, 224 });
	soundBeachGround.PushBack({ 0, 536, 608, 224 });
	soundBeachGround.PushBack({ 0, 760, 608, 224 });
	soundBeachGround.PushBack({ 0, 984, 608, 224 });
	soundBeachGround.speed = 0.05f;

	backgroundPeople1.PushBack({ 0, 0, 63, 94 });
	backgroundPeople1.PushBack({ 63, 0, 63, 94 });
	backgroundPeople1.speed = 0.035f;

	backgroundPeople2.PushBack({ 126, 0, 64, 91 });
	backgroundPeople2.PushBack({ 189, 0, 64, 91 });
	backgroundPeople2.speed = 0.07f;

	backgroundPeople3.PushBack({ 0, 94, 62, 96 });
	backgroundPeople3.PushBack({ 62, 99, 61, 96 });
	backgroundPeople3.speed = 0.07f;

	backgroundPeople4.PushBack({ 123, 97, 59, 93 });
	backgroundPeople4.PushBack({ 182, 103, 60, 93 });
	backgroundPeople4.speed = 0.07f;
}

ModuleSceneSoundBeach::~ModuleSceneSoundBeach()
{}

// Load assets
bool ModuleSceneSoundBeach::Start()
{
	App->hud->Enable();
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/Sound Beach Tileset/Day/SoundBeach.png");
	graphicsAnim = App->textures->Load("Assets/Sprites/Sound Beach Tileset/Day/SoundBeach_PeopleAnim.png");
	graphics2 = App->textures->Load("Assets/Sprites/Sound Beach Tileset/Sunset/SoundBeach (sunset).png");
	graphicsAnim2 = App->textures->Load("Assets/Sprites/Sound Beach Tileset/Sunset/PeopleAnimation_(sunset).png");
	App->player->Enable();
	App->enemy->Enable();
	App->render->camera.x = -530;

	return ret;
}

// UnLoad assets
bool ModuleSceneSoundBeach::CleanUp()
{
	LOG("Unloading ken scene");

	App->soundBeach->Disable();
	SDL_DestroyTexture(graphics);
	App->player->Disable();
	App->enemy->Disable();
	App->hud->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneSoundBeach::Update()
{
	// Draw everything --------------------------------------
	

	if ((App->player->Life == 0 || App->enemy->Life == 0) && App->player->win_timer == 360 || App->enemy->win_timer == 360 || App->enemy->defeat_timer == 360)
	{
		App->fade->FadeToBlack(this, this, 1.3);
	}


	if ((App->player->Life == 0 || App->enemy->Life == 0) && App->player->win_timer == 400 || App->enemy->win_timer == 400 || App->enemy->defeat_timer == 400)
	{
		//Reseting things for the new round
		App->hud->round = 2;
		App->player->win_timer = 0;
		App->player->defeat_timer = 0;
		App->enemy->win_timer = 0;
		App->enemy->defeat_timer = 0;
		App->hud->Win = false;
		App->player->Life = 100;
		App->enemy->Life = 100;
		App->player->position.x = 230;
		App->enemy->position.x = 375;
		App->player->status = PLAYER_IDLE;
		App->enemy->status = ENEMY_IDLE;
	}

	if (App->hud->round == 1)
	{
		App->player->input = true;
		App->enemy->input = true;
		App->render->Blit(graphics, 45, 0, &(soundBeachSky.GetCurrentFrame()), 0.45f);
		App->render->Blit(graphics, 0, 0, &(soundBeachGround.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 140, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 210, 107, &(backgroundPeople2.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 280, 107, &(backgroundPeople3.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 350, 107, &(backgroundPeople4.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 420, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
	}

	if (App->hud->round == 2)
	{
		App->player->input = true;
		App->enemy->input = true;
		App->render->Blit(graphics2, 45, 0, &(soundBeachSky.GetCurrentFrame()), 0.45f);
		App->render->Blit(graphics2, 0, 0, &(soundBeachGround.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 140, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 210, 107, &(backgroundPeople2.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 280, 107, &(backgroundPeople3.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 350, 107, &(backgroundPeople4.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 420, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
	}

	App->render->camera.x = App->player->position.x  * -2;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 2.5);
	}

	return UPDATE_CONTINUE;
}