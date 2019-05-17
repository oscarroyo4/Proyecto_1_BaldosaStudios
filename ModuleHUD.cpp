#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleInput.h"
#include "ModuleHUD.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"
#include "ModulePaoPao.h"
#include "ModuleFadeToBlack.h"


ModuleHUD::ModuleHUD()
{
	lifebar.x = 0;
	lifebar.y = 0;
	lifebar.w = 320;
	lifebar.h = 224;

	rectPlayer.w = 100;
	rectPlayer.h = 6;
	rectEnemy.w = 100;
	rectEnemy.h = 6;

	win.x = 0;
	win.y = 0;
	win.w = 320;
	win.h = 224;

	lose.x = 0;
	lose.y = 0;
	lose.w = 320;
	lose.h = 224;

	r.x = 0;
	r.y = 0;
	r.w = 16;
	r.y = 16;

	roundCircle.PushBack({ 0, 0, 16, 16 });
	roundCircleWon.PushBack({ 16, 0, 16, 16 });
	roundCircleWon.PushBack({ 0, 16, 16, 16 });
	roundCircleWon.speed = 0.1;     
}


ModuleHUD::~ModuleHUD()
{}

bool ModuleHUD::Start()
{
	Win = false;
	Lose = false;
	life = App->textures->Load("Assets/Sprites/Main/life bar.png");
	youWin = App->textures->Load("Assets/Sprites/Main/win.png");
	youLose = App->textures->Load("Assets/Sprites/Main/gameover.png");
	Round = App->textures->Load("Assets/Sprites/Main/Round indicator.png");
	round = 1;

	return true;
}

// UnLoad assets
bool ModuleHUD::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(life);
	App->textures->Unload(youWin);
	App->textures->Unload(youLose);
	this->Disable();

	return true;
}

update_status ModuleHUD::Update()
{
	// Draw HUD --------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN)
	{
		Win = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN)
	{
		Lose = true;
	}

	App->render->Blit(life, App->render->camera.x , App->render->camera.y, &lifebar, - 3);

	if (round == 1) 
	{
	App->render->Blit(Round, 18, 42, &(roundCircle.GetCurrentFrame()), -1 / 3);
	App->render->Blit(Round, 34, 42, &(roundCircle.GetCurrentFrame()), -1 / 3);
	App->render->Blit(Round, 270, 42, &(roundCircle.GetCurrentFrame()), -1 / 3);
	App->render->Blit(Round, 286, 42, &(roundCircle.GetCurrentFrame()), -1 / 3);
	}

	if (round == 2 && App->player->PlayerVict == 1)
	{
		App->render->Blit(Round, 18, 42, &(roundCircleWon.GetCurrentFrame()), -1 / 3);
		App->render->Blit(Round, 34, 42, &(roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(Round, 270, 42, &(roundCircle.GetCurrentFrame()), -1 / 3);
		App->render->Blit(Round, 286, 42, &(roundCircle.GetCurrentFrame()), -1 / 3);
	}

	rectPlayer.x = 34 + App->render->camera.x * -1 / 3;
	rectPlayer.y = 25 + App->render->camera.y;
	rectPlayer.w = App->player->Life;
	App->render->DrawQuad(rectPlayer, 250, 230, 30, 255, true);

	rectEnemy.x = 186 + App->render->camera.x * -1 / 3;
	rectEnemy.y = 25 + App->render->camera.y;
	rectEnemy.w = App->enemy->Life;
	App->render->DrawQuad(rectEnemy, 250, 230, 30, 255, true);

	if (Win) { App->render->Blit(youWin, App->render->camera.x, App->render->camera.y, &win, -3); }
	if (Lose) { App->render->Blit(youLose, App->render->camera.x, App->render->camera.y, &lose, -3); }

	return UPDATE_CONTINUE;
}

