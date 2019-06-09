#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleInput.h"
#include "ModuleVs.h"
#include "ModulePaoPao.h"
#include "ModuleSoundBeach.h"
#include "ModuleHowardArena.h"
#include "ModuleSounds.h"
#include "ModulePlayerSelect.h"
#include "ModuleSceneSelect.h"
#include "ModuleFadeToBlack.h"


ModuleVsCinematic::ModuleVsCinematic()
{
	background.PushBack({ 0, 0, 304, 224 });
	terry.PushBack({ 0, 248, 96, 132 });
	enemyterry.PushBack({ 189, 248, 96, 132 });
	joe.PushBack({ 346, 248, 111, 129 });
	andy.PushBack({ 351, 44, 96, 129 });
	vs.PushBack({ 0, 408, 50, 41 });
}

ModuleVsCinematic::~ModuleVsCinematic()
{}

bool ModuleVsCinematic::Start()
{
	LOG("Loading intro scene");
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	graphics = App->textures->Load("Assets/Sprites/Main/vs spritesheet.png");

	return true;
}

// UnLoad assets
bool ModuleVsCinematic::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleVsCinematic::Update()
{
	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, 0, 0, &(background.GetCurrentFrame()), 0);
	
	if (timer >= 0 && timer < 34) { leftposX++; timer++; }
	if (timer >= 0 && timer < 34) { rightposX--; }


	if (App->select->posT) App->render->Blit(graphics, leftposX, 60, &(terry.GetCurrentFrame()), 0);
	if (App->select->posA) App->render->Blit(graphics, leftposX, 60, &(andy.GetCurrentFrame()), 0);
	if (App->select->posJ) App->render->Blit(graphics, leftposX, 60, &(joe.GetCurrentFrame()), 0);
	App->render->Blit(graphics, rightposX, 60, &(enemyterry.GetCurrentFrame()), 0);

	if (pp == true) { App->fade->FadeToBlack(this, App->paopao, 2.5); }
	if (bch == true) { App->fade->FadeToBlack(this, App->soundBeach, 2.5); }
	if (hwa == true) { App->fade->FadeToBlack(this, App->howardArena, 2.5); }

	return UPDATE_CONTINUE;
}