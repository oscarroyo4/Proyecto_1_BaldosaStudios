#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"
#include "SDL_image/include/SDL_image.h"


ModuleEnemy::ModuleEnemy()
{
	position.x = 375;
	position.y = 223;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 28, 208, 62, 105 });
	idle.PushBack({ 97, 208, 60, 106 });
	idle.PushBack({ 163, 208, 60, 105 });
	idle.speed = 0.1f;

	// taking damage animation
	damage.PushBack({ 344, 342, 60, 100 });
	damage.PushBack({ 407, 336, 68, 106 });
	damage.PushBack({ 408, 346, 64, 96 });
	damage.PushBack({ 555, 355, 69, 87 });
	damage.speed = 0.15f;
}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading player");
	graphicsTerry = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites.png");  //First Tery Bogard Sprite Sheet
	colEnemy = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_ENEMY);
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

	colEnemy->SetPos(position.x + 12, position.y - 107);

	if (hit == true) {
		current_animation = &damage;
		hit = false;
	}


	// Draw everything --------------------------------------

	r = current_animation->GetCurrentFrame();

	App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL);

	return UPDATE_CONTINUE;
}