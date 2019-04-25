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

#define PUNCH_TIME 1000

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
	punch.speed = 0.12f;

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

	App->collision->Enable();
	graphicsTerry = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites.png"); //First Tery Bogard Sprite Sheet
	godMode = true;																	  //graphicsTerry2 = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites 2.png"); //Second Tery Bogard Sprite Sheet
	colPlayer = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_PLAYER);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->collision->Disable();
	App->player->Disable();
	SDL_DestroyTexture(graphicsTerry);
	SDL_DestroyTexture(graphicsTerry2);

	return true;
}

update_status ModulePlayer::Update()
{	
	int speed = 1;
	/*

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &jump;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &crouch;
	}

	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &specialAttack;
		//App->particles->AddParticle(App->particles->special, position.x + 85, position.y - 70, 1, 1000, 1, 0);
	}*/


	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		status = PLAYER_BACKWARD;

	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		status = PLAYER_FORWARD;

	else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		status = PLAYER_JUMP;

	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		status = PLAYER_CROUCH;

	else if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		status = PLAYER_PUNCH;

	else if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
		status = PLAYER_KICK;

	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		status = PLAYER_SPECIAL;
	else
		status = PLAYER_IDLE;

	switch (status)
	{
	case PLAYER_IDLE:
		current_animation = &idle;
		break;

	case PLAYER_BACKWARD:
		if (position.x < 10) { position.x -= 0; }
		else position.x -= speed;
		current_animation = &backward;
		if (App->render->camera.x > 0) { App->render->camera.x -= 0; }
		else App->render->camera.x += 3;
		break;

	case PLAYER_FORWARD:
		position.x += speed;
		current_animation = &forward;
		App->render->camera.x -= 3;
		break;

	case PLAYER_JUMP:
		jump_timer = 1;

		break;

	case IN_JUMP_FINISH:
		status = PLAYER_IDLE;
		jump.Reset();
		break;

	case IN_PUNCH_FINISH:
		status = PLAYER_IDLE;
		punch.Reset();
		break;

	case IN_KICK_FINISH:
		status = PLAYER_IDLE;
		kick.Reset();
		break;

	case PLAYER_KICK: {
		kick.Reset();
		kick_timer = 1;
		current_animation = &kick;
		Collider* kickCol = App->collision->AddCollider({ position.x + 45, position.y - 90, 30, 20 }, COLLIDER_PLAYER_SHOT);
		if (kickCol->CheckCollision(App->enemy->r)) {
			App->enemy->hit = true;
		}
		kickCol->to_delete = true;
		break;
	}
	

	case PLAYER_PUNCH:
		punch.Reset();
		punch_timer = 1;
		Collider* punchCol = App->collision->AddCollider({ position.x + 45, position.y - 90, 30, 20 }, COLLIDER_PLAYER_SHOT);
		if (punchCol->CheckCollision(App->enemy->r)) {
			App->enemy->hit = true;
		}
		punchCol->to_delete = true;
		break;
    }

	colPlayer->SetPos(position.x + 12, position.y - 107);

	if (punch_timer > 0)
	{
		punch_timer = punch_timer + 1;
		current_animation = &punch;
		if (punch_timer > 28)
		{
			status = IN_PUNCH_FINISH;
			punch_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		kick_timer = kick_timer + 1;
		current_animation = &kick;
		if (kick_timer > 40)
		{
			status = IN_KICK_FINISH;
			kick_timer = 0;
		}
	}

	if (jump_timer > 0)
	{
		jump_timer = jump_timer + 1;
		current_animation = &jump;
		if (jump_timer > 30)
		{
			status = IN_JUMP_FINISH;
			jump_timer = 0;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN)
	{
		if (godMode) {
			colPlayer->to_delete = true;
			colPlayer = App->collision->AddCollider({ position.x + 12, position.y - 107, 34, 106 }, COLLIDER_NONE);
			godMode = false;
		}
		else {
			colPlayer->to_delete = true;
			colPlayer = App->collision->AddCollider({ position.x + 12, position.y - 107, 34, 106 }, COLLIDER_PLAYER);
			godMode = true;
		}
	}
	// Draw everything --------------------------------------

	SDL_Rect r = current_animation->GetCurrentFrame();

	  
	if (App->enemy->position.x < position.x) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
	else { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r); }
	//if (App->enemy->position.x > position.x) { App->render->Blit(graphicsTerry2, position.x, position.y - r.h, &r); }
	//if (App->enemy->position.x < position.x) { App->render->Blit(graphicsTerry2, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
	return UPDATE_CONTINUE;
}