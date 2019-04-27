#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"
#include "ModuleHUD.h"
#include "SDL_image/include/SDL_image.h"

#define PUNCH_TIME 1000

ModuleEnemy::ModuleEnemy()
{
	position.x = 375;
	position.y = 223;

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
	LOG("Loading enemy");
	graphicsTerry = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites.png");  //First Tery Bogard Sprite Sheet
	colEnemy = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_ENEMY);
	godMode = true;
	
	Life = 100;
	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemy");

	SDL_DestroyTexture(graphicsTerry);
	App->enemy->Disable();

	return true;
}

update_status ModuleEnemy::Update()
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


	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		status = ENEMY_BACKWARD;

	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		status = ENEMY_FORWARD;

	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		status = ENEMY_JUMP;

	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		status = ENEMY_CROUCH;

	else if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		status = ENEMY_PUNCH;

	else if (App->input->GetKey(SDL_SCANCODE_RSHIFT) == KEY_DOWN)
		status = ENEMY_KICK;

	else if (App->input->GetKey(SDL_SCANCODE_MINUS) == KEY_DOWN)
		status = ENEMY_SPECIAL;

	else if (hit == true) {
		status = ENEMY_DAMAGE;
		hit = false;
	}

	else
		status = ENEMY_IDLE;

	switch (status)
	{
	case ENEMY_IDLE:
		current_animation = &idle;
		break;

	case ENEMY_BACKWARD:
		if (position.x < 10) { position.x -= 0; }
		else position.x -= speed;
		current_animation = &forward;
		break;

	case ENEMY_FORWARD:
		position.x += speed;
		current_animation = &backward;

		break;

	case ENEMY_JUMP:
		if (jumpEnable == true) {
			jumpEnable = false;
			jump.Reset();
			jump_timer = 1;
		}
		break;

	case ENEMY_IN_JUMP_FINISH:
		status = ENEMY_IDLE;
		jump.Reset();
		break;

	case ENEMY_IN_PUNCH_FINISH:
		status = ENEMY_IDLE;
		punch.Reset();
		break;

	case ENEMY_IN_KICK_FINISH:
		status = ENEMY_IDLE;
		kick.Reset();
		break;

	case ENEMY_DAMAGE_FINISH:
		status = ENEMY_IDLE;
		damage.Reset();
		break;

	case ENEMY_KICK:
		if (kickEnable == true) {
			kickEnable = false;
			kick.Reset();
			kick_timer = 1;
			kickCol = App->collision->AddCollider({ position.x - 45, position.y - 58, 55, 18 }, COLLIDER_ENEMY_SHOT);
			kickHit = false;
		}
		break;

	case ENEMY_PUNCH:
		if (punchEnable == true) {
			punchEnable = false;
			punch.Reset();
			punch_timer = 1;
			punchCol = App->collision->AddCollider({ position.x - 30, position.y - 90, 40, 20 }, COLLIDER_ENEMY_SHOT);
			punchHit = false;
		}
		break;
	

	case ENEMY_DAMAGE:
		damage.Reset();

		Life = Life - 15;
		if (Life <= 0) { Life = 0; App->hud->Lose = true; }

		damage_timer = 1;

		break;
	}
	

	if (kick_timer > 0)
	{
		kick_timer = kick_timer + 1;
		current_animation = &kick;
		if (kickCol->CheckCollision(App->player->r) && kickHit == false) {
			App->player->hit = true;
			kickHit = true;
		}
		if (kick_timer > 35)
		{
			kickEnable = true;
			status = ENEMY_IN_KICK_FINISH;
			kickCol->to_delete = true;
			kick_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		punch_timer = punch_timer + 1;
		current_animation = &punch;
		if (punchCol->CheckCollision(App->player->r) && punchHit == false) {
			App->player->hit = true;
			punchHit = true;
		}
		if (punch_timer > 28)
		{
			punchEnable = true;
			status = ENEMY_IN_PUNCH_FINISH;
			punchCol->to_delete = true;
			punch_timer = 0;
		}
	}

	if (jump_timer > 0)
	{
		jump_timer = jump_timer + 1;
		current_animation = &jump;

		if (jump_timer > 38)
		{
			jumpEnable = true;
			status = ENEMY_IN_JUMP_FINISH;
			jump_timer = 0;
		}
	}

	if (damage_timer > 0) {
		damage_timer = damage_timer + 1;
		current_animation = &damage;
		if (damage_timer > 30) {
			status = ENEMY_DAMAGE_FINISH;
			damage_timer = 0;
		}
	}

	colEnemy->SetPos(position.x + 12, position.y - 107);
	


	// Draw everything --------------------------------------

	r = current_animation->GetCurrentFrame();

	if (App->player->position.x < position.x) {App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
	if (App->player->position.x > position.x) {App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r);}

	r.x = position.x;
	r.y = position.y;

	return UPDATE_CONTINUE;
}