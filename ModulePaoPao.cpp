#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModulePlayer.h"
#include "ModuleJoe.h"
#include "ModuleAndy.h"
#include "ModuleInput.h"
#include "ModuleIntro.h"
#include "ModuleCollision.h"
#include "ModuleSoundBeach.h"
#include "ModuleAudio.h"
#include "ModuleEnemy.h"
#include "ModuleHUD.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCinematics.h"
#include "SDL_image/include/SDL_image.h"


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
	music = App->sounds->Load_music("Assets/Audio/PaoPao.ogg");
	if (JoeOnStage == true) { App->joe->Enable(); }
	if (TerryOnStage == true) { App->player->Enable(); }
	if (AndyOnStage == true) { App->andy->Enable(); }
	App->enemy->Enable();
	App->render->camera.x = -530;
	//Play the music
	if (!App->sounds->Play_music(music))
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
	if (!IsEnabled()) {
		SDL_DestroyTexture(graphics);
		App->sounds->Unload_music(music);
		App->player->Disable();
		App->enemy->Disable();
		App->collision->Disable();
		App->sounds->Disable();
		App->hud->Disable();
		App->paopao->Disable();
	}

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
		App->fade->FadeToBlack(this, App->soundBeach, 2.5);
	}

	if (App->player->win_timer == 180 && PlayerVictories == 0)
	{
		App->fade->FadeToBlackVisualEffect(2.5);
	}

	if (App->joe->win_timer == 180 && PlayerVictories == 0)
	{
		App->fade->FadeToBlackVisualEffect(2.5);
	}

	if (App->andy->win_timer == 180 && PlayerVictories == 0)
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

	if (App->joe->win_timer == 235 && PlayerVictories == 0)
	{

		PlayerVictories++;
		App->render->camera.x = -530;
		App->enemy->input = true;
		App->joe->input = true;
		App->joe->win_timer = 0;
		App->joe->defeat_timer = 0;
		App->enemy->win_timer = 0;
		App->enemy->defeat_timer = 0;
		App->hud->Win = false;
		App->joe->Life = 100;
		App->enemy->Life = 100;
		App->joe->position.x = 230;
		App->enemy->position.x = 375;
		App->joe->win.Reset();
		App->enemy->defeat.Reset();
		App->joe->status = JOE_IDLE;
		App->enemy->status = ENEMY_IDLE;
	}
	
	if (App->andy->win_timer == 235 && PlayerVictories == 0)
	{

		PlayerVictories++;
		App->render->camera.x = -530;
		App->enemy->input = true;
		App->andy->input = true;
		App->andy->win_timer = 0;
		App->andy->defeat_timer = 0;
		App->enemy->win_timer = 0;
		App->enemy->defeat_timer = 0;
		App->hud->Win = false;
		App->andy->Life = 100;
		App->enemy->Life = 100;
		App->andy->position.x = 230;
		App->enemy->position.x = 375;
		App->andy->win.Reset();
		App->enemy->defeat.Reset();
		App->andy->status = ANDY_IDLE;
		App->enemy->status = ENEMY_IDLE;
	}

	if (App->enemy->win_timer == 235 && EnemyVictories == 0)
	{
		EnemyVictories++;
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
		App->fade->FadeToBlack(this, App->cinematics, 2.5);
		App->cinematics->finalpaopao = true;
	}

	if (App->joe->win_timer == 210 && PlayerVictories == 1)
	{
		App->fade->FadeToBlack(this, App->cinematics, 2.5);
		App->cinematics->finalpaopao = true;
	}

	if (App->andy->win_timer == 210 && PlayerVictories == 1)
	{
		App->fade->FadeToBlack(this, App->cinematics, 2.5);
		App->cinematics->finalpaopao = true;
	}

	if (App->enemy->win_timer == 210 && EnemyVictories == 1)
	{
		App->fade->FadeToBlack(this, App->soundBeach, 2.5);
	}

	if (PlayerVictories == 0 && EnemyVictories == 0)
	{
		App->render->Blit(App->hud->Round, 18, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 270, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 1 && EnemyVictories == 0)
	{
		App->render->Blit(App->hud->Round, 18, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 270, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 0 && EnemyVictories == 1)
	{
		App->render->Blit(App->hud->Round, 18, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 270, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 1 && EnemyVictories == 1)
	{
		App->render->Blit(App->hud->Round, 18, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 270, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->Round, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	return UPDATE_CONTINUE;
}