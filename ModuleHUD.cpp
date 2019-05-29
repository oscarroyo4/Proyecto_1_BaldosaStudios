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
#include "ModuleFonts.h"


ModuleHUD::ModuleHUD()
{
	lifebar.x = 0;
	lifebar.y = 0;
	lifebar.w = 304;
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
	life = App->textures->Load("Assets/Sprites/Main/Life bar.png");
	youWin = App->textures->Load("Assets/Sprites/Main/win.png");
	youLose = App->textures->Load("Assets/Sprites/Main/gameover.png");
	round = App->textures->Load("Assets/Sprites/Main/Round indicator.png");
	newround = App->textures->Load("Assets/Sprites/Main/rounds.png");
	fontID = App->fonts->Load("Assets/Sprites/Fonts/NumberTimerFont.png", "0123456789", 1, 15, 21, 10);
	timer = 60;
	ticks1 = 0;
	ticks2 = SDL_GetTicks();
	ticks3 = ticks2;

	return true;
}

// UnLoad assets
bool ModuleHUD::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(life);
	App->textures->Unload(youWin);
	App->textures->Unload(youLose);
	App->textures->Unload(round);
	App->textures->Unload(newround);
	App->fonts->UnLoad(fontID);
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

	App->render->Blit(life, App->render->camera.x+8 , App->render->camera.y, &lifebar, - 3);
	if (ticks1 > 29000) {
		timer -= 1;
		ticks1 = 0;
		ticks3 = ticks2;
	}
	else {
		ticks1 += ticks2 - ticks3;
		ticks2 = SDL_GetTicks();
	}
	SDL_snprintf(time, 3, "%d", timer);
	App->fonts->BlitText(146, 18, fontID, time);
	if (timer <= 0) {
		ticks3 = 99999999;
		if (App->player->Life > App->enemy->Life) {
			Win = true;
		} 
		else if (App->enemy->Life > App->player->Life) {
			Lose = true;
		}
		else {
			//Empate
			Win = true; //CHANGE!!!!!!!
		}
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

