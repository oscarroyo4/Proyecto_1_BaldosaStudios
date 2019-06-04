#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
#include "ModuleHowardArena.h"
#include "ModulePlayer.h"
#include "ModuleJoe.h"
#include "ModuleInput.h"
#include "ModuleIntro.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleAndy.h"
#include "ModuleEnemy.h"
#include "ModuleHUD.h"
#include "ModuleFadeToBlack.h"
#include "SDL_image/include/SDL_image.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleHowardArena::ModuleHowardArena()
{
	HA_Sky.PushBack({ 0, 0, 461, 104 });
	HA_Sky.PushBack({ 0, 104, 461, 104 });
	HA_Sky.PushBack({ 0, 208, 461, 104 });
	HA_Sky.speed = 0.05f;

	HA_Ground.PushBack({ 0, 312, 608, 224 });
	HA_Tree.PushBack({ 0, 312, 608, 224 });
	HA_Tree.PushBack({ 0, 312, 608, 224 });
	HA_Tree.PushBack({ 0, 312, 608, 224 });

	rectShadowHA.x = 0;
	rectShadowHA.y = 12;
	rectShadowHA.w = 64;
	rectShadowHA.h = 12;
}

ModuleHowardArena::~ModuleHowardArena()
{}

// Load assets
bool ModuleHowardArena::Start()
{
	App->hud->Enable();
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/Sound Beach Tileset/Day/SoundBeach.png");
	graphics2 = App->textures->Load("Assets/Sprites/Sound Beach Tileset/Sunset/SoundBeach (sunset).png");
	ShadowHA = App->textures->Load("Assets/Sprites/Main/Shadow.png");

	if (JoeOnStage == true) {
		App->joe->Enable();
		App->joe->input = true;
		App->joe->win_timer = 0;
		App->joe->defeat_timer = 0;
		App->joe->Life = 100;
		App->joe->position.x = 230;
		App->joe->status = JOE_IDLE;
	}
	if (TerryOnStage == true) {
		App->player->Enable();
		App->player->input = true;
		App->player->Life = 100;
		App->player->win_timer = 0;
		App->player->defeat_timer = 0;
		App->player->status = PLAYER_IDLE;
		App->player->position.x = 230;
	}
	if (AndyOnStage == true) {
		App->andy->Enable();
		App->andy->input = true;
		App->andy->Life = 100;
		App->andy->win_timer = 0;
		App->andy->defeat_timer = 0;
		App->andy->status = ANDY_IDLE;
		App->andy->position.x = 230;
	}

	App->enemy->Enable();
	App->render->camera.x = -530;
	App->enemy->input = true;
	App->enemy->win_timer = 0;
	App->enemy->defeat_timer = 0;
	App->hud->Win = false;
	App->enemy->Life = 100;
	App->enemy->position.x = 375;
	App->enemy->status = ENEMY_IDLE;

	return ret;
}

// UnLoad assets
bool ModuleHowardArena::CleanUp()
{
	LOG("Unloading ken scene");

	if (!IsEnabled()) {
		SDL_DestroyTexture(graphics);
		SDL_DestroyTexture(graphics2);
		SDL_DestroyTexture(ShadowHA);
		if (TerryOnStage == true) App->player->Disable();
		if (JoeOnStage == true) App->joe->Disable();
		if (AndyOnStage == true) App->andy->Disable();
		App->enemy->Disable();
		App->hud->Disable();
		App->howardArena->Disable();
	}

	return true;
}

// Update: draw background
update_status ModuleHowardArena::Update()
{
	// Draw everything --------------------------------------

	/*
	if (App->player->IsEnabled()) App->render->camera.x = (App->enemy->position.x*-2) - (App->player->position.x * 2) + 700;
	if (App->andy->IsEnabled()) App->render->camera.x = (App->enemy->position.x*-2) - (App->andy->position.x * 2) + 700;
	if (App->joe->IsEnabled()) App->render->camera.x = (App->enemy->position.x*-2) - (App->joe->position.x * 2) + 700;

	if (round == 1)
	{
		App->render->Blit(graphics, 45, 0, &(soundBeachSky.GetCurrentFrame()), 0.45f);
		App->render->Blit(graphics, 0, 0, &(soundBeachGround.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 140, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 210, 107, &(backgroundPeople2.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 280, 107, &(backgroundPeople3.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 350, 107, &(backgroundPeople4.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 420, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
	}


	if (round == 2)
	{
		App->render->Blit(graphics2, 45, 0, &(soundBeachSky.GetCurrentFrame()), 0.45f);
		App->render->Blit(graphics2, 0, 0, &(soundBeachGround.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 140, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 210, 107, &(backgroundPeople2.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 280, 107, &(backgroundPeople3.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 350, 107, &(backgroundPeople4.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 420, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
	}



	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 2.5);
	}

	if (App->player->win_timer == 180 && PlayerVictories == 0)
	{
		App->fade->FadeToBlackVisualEffect(2.5);
	}

	if (App->enemy->win_timer == 180 && EnemyVictories == 0)
	{
		App->fade->FadeToBlackVisualEffect(2.5);
	}

	if (App->player->win_timer == 235 && PlayerVictories == 0)
	{
		PlayerVictories++;
		round = 2;
		App->render->camera.x = -530;
		App->enemy->input = true;
		App->player->input = true;
		App->player->win_timer = 0;
		App->player->defeat_timer = 0;
		App->enemy->win_timer = 0;
		App->enemy->defeat_timer = 0;
		App->hud->Win = false;
		App->player->Life = 100;
		App->enemy->Life = 100;
		App->player->position.x = 230;
		App->enemy->position.x = 375;
		App->player->win.Reset();
		App->enemy->defeat.Reset();
		App->player->status = PLAYER_IDLE;
		App->enemy->status = ENEMY_IDLE;
	}

	if (App->enemy->win_timer == 235 && EnemyVictories == 0)
	{
		EnemyVictories++;
		round = 2;
		App->render->camera.x = -530;
		App->enemy->input = true;
		App->player->input = true;
		App->player->win_timer = 0;
		App->player->defeat_timer = 0;
		App->enemy->win_timer = 0;
		App->enemy->defeat_timer = 0;
		App->hud->Win = false;
		App->player->Life = 100;
		App->enemy->Life = 100;
		App->player->position.x = 230;
		App->enemy->position.x = 375;
		App->player->defeat.Reset();
		App->enemy->win.Reset();
		App->player->status = PLAYER_IDLE;
		App->enemy->status = ENEMY_IDLE;

	}
	if (App->player->win_timer == 210 && PlayerVictories == 1)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 2.5);
	}

	if (App->enemy->win_timer == 210 && EnemyVictories == 1)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 2.5);
	}

	if (PlayerVictories == 0 && EnemyVictories == 0)
	{
		App->render->Blit(App->hud->round, 18, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 270, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 1 && EnemyVictories == 0)
	{
		App->render->Blit(App->hud->round, 18, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 270, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 0 && EnemyVictories == 1)
	{
		App->render->Blit(App->hud->round, 18, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 270, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 1 && EnemyVictories == 1)
	{
		App->render->Blit(App->hud->round, 18, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 270, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->round, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (App->player->IsEnabled()) { App->render->Blit(ShadowSB, App->player->position.x - 5, 210, &rectShadowSB); }
	if (App->enemy->IsEnabled()) { App->render->Blit(ShadowSB, App->enemy->position.x - 5, 210, &rectShadowSB); }
	if (App->andy->IsEnabled()) { App->render->Blit(ShadowSB, App->andy->position.x - 5, 210, &rectShadowSB); }
	if (App->joe->IsEnabled()) { App->render->Blit(ShadowSB, App->joe->position.x - 5, 210, &rectShadowSB); }
	*/

	return UPDATE_CONTINUE;
}