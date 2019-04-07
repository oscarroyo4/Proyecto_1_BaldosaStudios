#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "SDL_image/include/SDL_image.h"


ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 28, 208, 62, 105 });
	idle.PushBack({ 97, 208, 60, 106 });
	idle.PushBack({ 163, 208, 60, 105 });
	idle.speed = 0.1f;


	//forward
	forward.PushBack({ 15, 337, 60, 106 });
	forward.PushBack({ 90, 337, 70, 107 });
	forward.PushBack({ 170, 337, 62, 108 });
	forward.PushBack({ 247, 337, 60, 107 });
	forward.speed = 0.125f;

	//backwards
	backward.PushBack({ 16, 460, 58, 107 });
	backward.PushBack({ 96, 457, 62, 107 });
	backward.PushBack({ 179, 457, 62, 107 });
	backward.speed = 0.125f;

	//Punch animation
	punch.PushBack({ 14, 585, 72, 100 });
	punch.PushBack({ 87, 585, 62, 100 });
	punch.PushBack({ 155, 585, 96, 100 });
	punch.speed = 0.15f;

	//Kick animation
	kick.PushBack({ 40, 56, 50, 95, });
	kick.PushBack({ 93, 30, 58, 110 });
	kick.PushBack({ 164, 39, 53, 108 });
	kick.PushBack({ 218, 41, 121, 100 });
	kick.PushBack({ 341, 37, 65, 112 });
	kick.speed = 0.12f;

	//Jump animation
	jump.PushBack({ 15, 337, 60, 106 });
	jump.PushBack({ 268, 183, 52, 140 });
	jump.PushBack({ 328, 176, 65, 145 });
	jump.PushBack({ 393, 205, 59, 130 });
	jump.speed = 0.12f;

	//crouch animation
	crouch.PushBack({ 10, 808, 59, 98 });
	crouch.PushBack({ 133, 822, 63, 84 });
	crouch.PushBack({ 74, 812, 58, 95 });
	crouch.PushBack({ 200, 839, 57, 66 });
	crouch.speed = 0.175f;
	crouch.loop = false;

	//SpecialAttack animation
	specialAttack.PushBack({ 421, 693, 52, 106 });
	specialAttack.PushBack({ 362, 691, 55, 107 });
	specialAttack.PushBack({ 297, 702, 61, 96 });
	specialAttack.PushBack({ 214, 720, 80, 78 });
	specialAttack.PushBack({ 142, 721, 68, 77 });
	specialAttack.PushBack({ 75, 730, 66, 68 });
	specialAttack.PushBack({ 10, 717, 62, 81 });
	specialAttack.speed = 0.175f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphicsTerry = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites.png");  //First Tery Bogard Sprite Sheet
	//graphicsTerry2 = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites 2.png");  //Second Tery Bogard Sprite Sheet
	colPlayer = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_PLAYER);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	SDL_DestroyTexture(graphicsTerry);
	SDL_DestroyTexture(graphicsTerry2);
	App->player->Disable();

	return true;
}

update_status ModulePlayer::Update()
{
	current_animation = &idle;
	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x < 10) { position.x -= 0; }
		else position.x -= speed;
			current_animation = &backward;
		if (App->render->camera.x > 0) { App->render->camera.x -= 0; }
		else App->render->camera.x += 3;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		 position.x += speed;
		 current_animation = &forward;
         App->render->camera.x -= 3; 
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &jump;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &crouch;
	}

	if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &punch;
		Collider* punch = App->collision->AddCollider({position.x + 45, position.y - 90, 40, 20}, COLLIDER_PLAYER_SHOT);
		if (punch->CheckCollision(App->enemy->r)) {
			App->enemy->hit = true;
		}
		punch->to_delete = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &kick;
	}


	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_REPEAT)
	{
	current_animation = &specialAttack;
	//App->particles->AddParticle(App->particles->special, position.x + 85, position.y - 70, 1, 1000, 1, 0);
	}

	colPlayer->SetPos(position.x + 12, position.y - 107);
	// Draw everything --------------------------------------

	SDL_Rect r = current_animation->GetCurrentFrame();
    
	App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r);
	App->render->Blit(graphicsTerry2, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}