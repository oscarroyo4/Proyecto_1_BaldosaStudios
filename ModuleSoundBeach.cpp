#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
#include "ModulePlayer.h"
#include "ModuleJoe.h"
#include "ModuleInput.h"
#include "ModuleHowardArena.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleAndy.h"
#include "ModuleEnemy.h"
#include "ModuleHUD.h"
#include "ModuleFadeToBlack.h"
#include "SDL_image/include/SDL_image.h"


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

	rectShadowSB.x = 0;
	rectShadowSB.y = 12;
	rectShadowSB.w = 64;
	rectShadowSB.h = 12;
}

ModuleSceneSoundBeach::~ModuleSceneSoundBeach()
{}

// Load assets
bool ModuleSceneSoundBeach::Start()
{
	App->hud->Enable();
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/Sound Beach Tileset/SoundBeach.png");
	graphicsAnim = App->textures->Load("Assets/Sprites/Sound Beach Tileset/SoundBeach_PeopleAnim.png");
	graphics2 = App->textures->Load("Assets/Sprites/Sound Beach Tileset/SoundBeach (sunset).png");
	graphicsAnim2 = App->textures->Load("Assets/Sprites/Sound Beach Tileset/PeopleAnimation_(sunset).png");
	graphics3 = App->textures->Load("Assets/Sprites/Sound Beach Tileset/SoundBeachNight.png");
	graphicsAnim3 = App->textures->Load("Assets/Sprites/Sound Beach Tileset/PeopleAnimation (night).png");
	ShadowSB = App->textures->Load("Assets/Sprites/Main/Shadow.png");
	music = App->sounds->Load_music("Assets/Fatal Fury King of Fighters - The Sea Knows (Michael Max Theme).ogg");

	App->player->Disable();
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
	if (App->sounds->Play_music(music) == false) {
		LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
	}
	return ret;
}

// UnLoad assets
bool ModuleSceneSoundBeach::CleanUp()
{
	LOG("Unloading ken scene");

	if (!IsEnabled()) {
		SDL_DestroyTexture(graphics);
		SDL_DestroyTexture(graphicsAnim);
		SDL_DestroyTexture(graphics2);
		SDL_DestroyTexture(graphicsAnim2);
		SDL_DestroyTexture(ShadowSB);
		if (TerryOnStage == true) App->player->Disable();
		if (JoeOnStage == true) App->joe->Disable();
		if (AndyOnStage == true) App->andy->Disable();
		App->enemy->Disable();
		App->hud->Disable();
		App->sounds->Unload_music(music);
		App->soundBeach->Disable();
	}

	return true;
}

// Update: draw background
update_status ModuleSceneSoundBeach::Update()
{
	// Draw everything --------------------------------------

	if (App->player->IsEnabled()) App->render->CameraFollowingPlayers(App->player->position.x, App->enemy->position.x);
	if (App->andy->IsEnabled()) App->render->CameraFollowingPlayers(App->andy->position.x, App->enemy->position.x);
	if (App->joe->IsEnabled()) App->render->CameraFollowingPlayers(App->joe->position.x, App->enemy->position.x);

	if (round == 1) 
	{
		App->render->Blit(graphics, 10, 0, &(soundBeachSky.GetCurrentFrame()), 0.40f);
		App->render->Blit(graphics, 0, 0, &(soundBeachGround.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 140, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 210, 107, &(backgroundPeople2.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 280, 107, &(backgroundPeople3.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 350, 107, &(backgroundPeople4.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim, 420, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
	}


	if (round == 2)
	{
		App->render->Blit(graphics2, 10, 0, &(soundBeachSky.GetCurrentFrame()), 0.40f);
		App->render->Blit(graphics2, 0, 0, &(soundBeachGround.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 140, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 210, 107, &(backgroundPeople2.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 280, 107, &(backgroundPeople3.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 350, 107, &(backgroundPeople4.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim2, 420, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
	}


	if (round == 3)
	{
		App->render->Blit(graphics3, 10, 0, &(soundBeachSky.GetCurrentFrame()), 0.40f);
		App->render->Blit(graphics3, 0, 0, &(soundBeachGround.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim3, 140, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim3, 210, 107, &(backgroundPeople2.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim3, 280, 107, &(backgroundPeople3.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim3, 350, 107, &(backgroundPeople4.GetCurrentFrame()), 0.75f);
		App->render->Blit(graphicsAnim3, 420, 107, &(backgroundPeople1.GetCurrentFrame()), 0.75f);
	}

	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->howardArena, 2.5);
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
		round++;
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
		round++;
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
		App->fade->FadeToBlack(this, App->howardArena, 2.5);
	}

	if (App->enemy->win_timer == 210 && EnemyVictories == 1)
	{
		App->fade->FadeToBlack(this, App->howardArena, 2.5);
	}

	if (PlayerVictories == 0 && EnemyVictories == 0)
	{
		App->render->Blit(App->hud->hud, 18, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 270, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 1 && EnemyVictories == 0)
	{
		App->render->Blit(App->hud->hud, 18, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 270, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 0 && EnemyVictories == 1)
	{
		App->render->Blit(App->hud->hud, 18, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 270, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (PlayerVictories == 1 && EnemyVictories == 1)
	{
		App->render->Blit(App->hud->hud, 18, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 34, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 270, 42, &(App->hud->roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(App->hud->hud, 286, 42, &(App->hud->roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (App->player->IsEnabled()) { App->render->Blit(ShadowSB, App->player->position.x - 5, 210, &rectShadowSB); }
	if (App->enemy->IsEnabled()) { App->render->Blit(ShadowSB, App->enemy->position.x - 5, 210, &rectShadowSB); }
	if (App->andy->IsEnabled()) { App->render->Blit(ShadowSB, App->andy->position.x - 5, 210, &rectShadowSB); }
	if (App->joe->IsEnabled()) { App->render->Blit(ShadowSB, App->joe->position.x - 5, 210, &rectShadowSB); }

	return UPDATE_CONTINUE;
}