#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleEnemy.h"
#include "SDL_image/include/SDL_image.h"


ModuleEnemy::ModuleEnemy()
{
	position.x = 375;
	position.y = 222;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 351, 341, 60, 105 });
	idle.PushBack({ 419, 341, 60, 106 });
	idle.PushBack({ 488, 339, 62, 105 });
	idle.speed = 0.1f;
}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading player");
	graphicsTerry = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites.png");  //First Tery Bogard Sprite Sheet
	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading player");

	SDL_DestroyTexture(graphicsTerry);
	App->enemy->Disable();

	return true;
}

update_status ModuleEnemy::Update()
{
	current_animation = &idle;

	// Draw everything --------------------------------------

	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}