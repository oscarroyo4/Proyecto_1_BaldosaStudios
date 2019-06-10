#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleInput.h"
#include "ModuleHUD.h"
#include "ModuleAndy.h"
#include "ModuleJoe.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"
#include "ModulePaoPao.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"


ModuleHUD::ModuleHUD()
{
	lifebar.x = 0;
	lifebar.y = 0;
	lifebar.w = 154;
	lifebar.h = 32;

	lifebar2.x = 1;
	lifebar2.y = 175;
	lifebar2.w = 119;
	lifebar2.h = 16;

	rectPlayer.w = 100;
	rectPlayer.h = 6;
	rectEnemy.w = 100;
	rectEnemy.h = 6;

	win.x = 0;
	win.y = 0;
	win.w = 304;
	win.h = 224;



	fight.x = 0;
	fight.y = 102;
	fight.w = 172;
	fight.h = 38;

	round1.x = 0;
	round1.y = 140;
	round1.w = 106;
	round1.h = 15;

	round2.x = 0;
	round2.y = 155;
	round2.w = 106;
	round2.h = 15;

	r.x = 0;
	r.y = 0;
	r.w = 16;
	r.y = 16;

	roundCircle.PushBack({ 88, 51, 16, 16 });
	roundCircleWon.PushBack({ 104, 51, 16, 16 });
	roundCircleWon.PushBack({ 88, 67, 16, 16 });
	roundCircleWon.speed = 0.08;     
}


ModuleHUD::~ModuleHUD()
{}

bool ModuleHUD::Start()
{
	Win = false;
	Lose = false;
	hud = App->textures->Load("Assets/Sprites/Main/UI-HUD spritesheet.png");
	Wwin = App->textures->Load("Assets/Sprites/Main/win.png");
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

	App->textures->Unload(hud);
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

	App->render->Blit(hud, App->render->camera.x + 22 , App->render->camera.y + 8, &lifebar, - 1);
	App->render->Blit(hud, App->render->camera.x + 180, App->render->camera.y + 16, &lifebar2, -1);


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

	rectPlayer.x = 39 + App->render->camera.x * -1 ;
	rectPlayer.y = 25 + App->render->camera.y;
	if(App->player->IsEnabled())rectPlayer.w = App->player->Life;
	if (App->joe->IsEnabled())rectPlayer.w = App->joe->Life;
	if (App->andy->IsEnabled())rectPlayer.w = App->andy->Life;
	App->render->DrawQuad(rectPlayer, 250, 230, 30, 255, true);

	rectEnemy.x = 182 + App->render->camera.x * -1 ;
	rectEnemy.y = 25 + App->render->camera.y;
	rectEnemy.w = App->enemy->Life;
	App->render->DrawQuad(rectEnemy, 250, 230, 30, 255, true);

	if (Win) { App->render->Blit(hud, App->render->camera.x, App->render->camera.y, &win, -3); timer = 60; }
	if (Lose) { App->render->Blit(hud, App->render->camera.x, App->render->camera.y, &lose, -3); timer = 60; }

	return UPDATE_CONTINUE;
}

