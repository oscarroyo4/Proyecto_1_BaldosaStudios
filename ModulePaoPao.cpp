#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModulePlayer.h"
#include "ModuleJoe.h"
#include "ModuleInput.h"
#include "ModuleIntro.h"
#include "ModuleCollision.h"
#include "ModuleSoundBeach.h"
#include "ModuleSounds.h"
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
	music = App->sounds->Load("Assets/Audio/PaoPao.ogg");
	if (JoeOnStage == true) { App->joe->Enable(); }
	if (TerryOnStage == true) { App->player->Enable(); }
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
	App->sounds->Unload();
	App->player->Disable();
	App->enemy->Disable();
	App->collision->Disable();
	App->sounds->Disable();
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
		App->fade->FadeToBlack(this, App->soundBeach, 2.5);
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