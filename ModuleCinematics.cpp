#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleCinematics.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
#include "ModuleSounds.h"
#include "ModulePlayerSelect.h"
#include "ModuleFadeToBlack.h"


ModuleCinematics::ModuleCinematics()
{
	BetweenPaoPaoAndBeachAnimation.PushBack({ 0, 0, 304, 224 });
	BetweenPaoPaoAndBeachAnimation.PushBack({ 0, 224, 304, 224 });
	BetweenPaoPaoAndBeachAnimation.speed = 0.007f;
	BetweenPaoPaoAndBeachAnimation.loop = false;

	GameIntroCinematicBackground.PushBack({ 0, 0, 350, 237 });
	GameIntroCinematicTerry.PushBack({ 0, 237, 150, 144 });
	GameIntroCinematicTerry.PushBack({ 151, 237, 150, 144 });
	GameIntroCinematicTerry.speed = 0.1;
	GameIntroCinematicWords.PushBack({ 0, 0, 561, 63 });
	insertcoins.PushBack({ 0, 0, 174, 64 });
	insertcoins.PushBack({ 0, 64, 174, 64 });
	insertcoins.speed = 0.04;
}

ModuleCinematics::~ModuleCinematics()
{}

bool ModuleCinematics::Start()
{
	LOG("Loading intro scene");
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	background = App->textures->Load("Assets/Sprites/Main/DevilMan1.png");
	fatalfuryintro = App->textures->Load("Assets/Sprites/Main/FatalFuryIntro.png");
	fatalfuryintrowords = App->textures->Load("Assets/Sprites/Main/FatalFuryIntro_words.png");
	inscoins = App->textures->Load("Assets/Sprites/Main/InsertCoin.png");

	return true;
}

// UnLoad assets
bool ModuleCinematics::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(background);
	App->textures->Unload(fatalfuryintro);
	App->textures->Unload(fatalfuryintrowords);
	App->textures->Unload(inscoins);

	return true;
}

// Update: draw background
update_status ModuleCinematics::Update()
{
	// Draw everything --------------------------------------
	
	if (GameIntroCinematic_timer < 380) 
	{
		GameIntroCinematic_timer++;
		App->render->camera.x--;
		App->render->Blit(fatalfuryintro, 0, -6, &(GameIntroCinematicBackground.GetCurrentFrame()), 0.17f);
		App->render->Blit(fatalfuryintrowords, 350, 52, &(GameIntroCinematicWords.GetCurrentFrame()), 6);
		App->render->Blit(fatalfuryintro, -35, 70, &(GameIntroCinematicTerry.GetCurrentFrame()), -0.28f);
		App->render->Blit(inscoins, 125, 160, &(insertcoins.GetCurrentFrame()), 0);
	}


	if (GameIntroCinematic_timer == 280)
	{
		App->fade->FadeToBlack(this, App->scene_intro, 4);
	}
	

	if (finalpaopao == true) 
	{
		App->render->Blit(background, 10, 0, &(BetweenPaoPaoAndBeachAnimation.GetCurrentFrame()), 0.75f);
		finalpaopao_timer++;
	}
	
	if (finalpaopao_timer >= 210) 
	{	
		App->fade->FadeToBlack(this, App->soundBeach, 2.5);
		finalpaopao_timer = 0;
	}

	return UPDATE_CONTINUE;
}