#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleInput.h"
#include "ModulePaoPao.h"
#include "ModuleSounds.h"
#include "ModulePlayerSelect.h"
#include "ModuleFadeToBlack.h"


ModuleIntro::ModuleIntro()
{
	intr.PushBack({ 0, 0, 384, 224 });
	intr.PushBack({ 0, 224, 384, 224 });
	intr.PushBack({ 0, 448, 384, 224 });
	intr.PushBack({ 0, 224, 384, 224 });
	intr.speed = 0.05f;
}

ModuleIntro::~ModuleIntro()
{}

bool ModuleIntro::Start()
{
	LOG("Loading intro scene");
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	background = App->textures->Load("Assets/Sprites/Main/welcome.png");
	music = App->sounds->Load("Assets/Audio/Menu.ogg");
	if (Mix_PlayChannel(-1, music, 0) == -1)
	{
		LOG("Could not play music. Mix_PlayChannel: %s", Mix_GetError());
		return false;
	}

	return true;
}

// UnLoad assets
bool ModuleIntro::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(background);
	App->sounds->Unload(music);

	return true;
}

// Update: draw background
update_status ModuleIntro::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(background, -25, 0, &(intr.GetCurrentFrame()), 0.75f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_intro, App->select, 0.5);
	}

	return UPDATE_CONTINUE;
}