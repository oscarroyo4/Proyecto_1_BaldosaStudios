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
	lifebar_p.x = 0;
	lifebar_p.y = 0;
	lifebar_p.w = 158;
	lifebar_p.h = 32;

	lifebar_e.x = 0;
	lifebar_e.y = 174;
	lifebar_e.w = 120;
	lifebar_e.h = 18;

	rectPlayer.w = 100;
	rectPlayer.h = 6;
	rectEnemy.w = 100;
	rectEnemy.h = 6;

	win.x = 124;
	win.y = 62;
	win.w = 122;
	win.h = 15;

	lose.x = 0;
	lose.y = 0;
	lose.w = 320;
	lose.h = 224;

	r.x = 0;
	r.y = 0;
	r.w = 16;
	r.y = 16;

	roundCircle.PushBack({ 88, 51, 16, 16 });
	roundCircleWon.PushBack({ 104, 51, 16, 16 });
	roundCircleWon.PushBack({ 88, 67, 16, 16 });
	roundCircleWon.speed = 0.1;     
}


ModuleHUD::~ModuleHUD()
{}

bool ModuleHUD::Start()
{
	Win = false;
	Lose = false;
	Hud = App->textures->Load("Assets/Sprites/Main/UI-HUD spritesheet.png");

	return true;
}

// UnLoad assets
bool ModuleHUD::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(Hud);

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

	App->render->Blit(Hud, App->render->camera.x + 22, App->render->camera.y + 8, &lifebar_p, -3);
	App->render->Blit(Hud, App->render->camera.x + 178, App->render->camera.y + 15, &lifebar_e, -3);

	rectPlayer.x = 39 + App->render->camera.x * -1 / 3;
	rectPlayer.y = 25 + App->render->camera.y;
	rectPlayer.w = App->player->Life;
	App->render->DrawQuad(rectPlayer, 250, 230, 30, 255, true);

	rectEnemy.x = 181 + App->render->camera.x * -1 / 3;
	rectEnemy.y = 25 + App->render->camera.y;
	rectEnemy.w = App->enemy->Life;
	App->render->DrawQuad(rectEnemy, 250, 230, 30, 255, true);

	if (Win) { App->render->Blit(Hud, App->render->camera.x + 89, App->render->camera.y + 72, &win, -3); }
	if (Lose) { App->render->Blit(Hud, App->render->camera.x, App->render->camera.y, &lose, -3); }

	return UPDATE_CONTINUE;
}

