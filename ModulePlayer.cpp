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

ModulePlayer::ModulePlayer()
{
	position.x = 230;
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

	// taking damage animation
	damage.PushBack({ 344, 342, 60, 100 });
	damage.PushBack({ 407, 336, 68, 106 });
	damage.PushBack({ 408, 346, 64, 96 });
	damage.PushBack({ 555, 355, 69, 87 });
	damage.speed = 0.15f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	App->collision->Enable();
	graphicsTerry = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites.png"); //First Tery Bogard Sprite Sheet
	//graphicsTerry2 = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites 2.png"); //Second Tery Bogard Sprite Sheet
	godMode = true;
	colPlayer = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_PLAYER);
	Life = 100;
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

	else if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
		status = PLAYER_SPECIAL;

	else if (hit == true) {
		status = PLAYER_DAMAGE;
		hit = false;
	}

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
		break;

	case PLAYER_FORWARD:
		position.x += speed;
		current_animation = &forward;
		break;

	case PLAYER_JUMP:
		if (jumpEnable == true) {
			jumpEnable = false;
			jump.Reset();
			jump_timer = 1;
		}
		break;

	case PLAYER_IN_JUMP_FINISH:
		status = PLAYER_IDLE;
		jump.Reset();
		break;

	case PLAYER_IN_PUNCH_FINISH:
		status = PLAYER_IDLE;
		punch.Reset();
		break;

	case PLAYER_IN_KICK_FINISH:
		status = PLAYER_IDLE;
		kick.Reset();
		break;

	case PLAYER_DAMAGE_FINISH:
		status = PLAYER_IDLE;
		damage.Reset();
		break;

	case IN_SPECIAL_FINISH:
		status = PLAYER_IDLE;
		specialAttack.Reset();
		break;

	case PLAYER_KICK:
		if (kickEnable == true) {
			kickEnable = false;
			kick.Reset();
			kick_timer = 1;
			kickCol = App->collision->AddCollider({ position.x + 46, position.y - 58, 55, 18 }, COLLIDER_PLAYER_SHOT);
			kickHit = false;
		}
		break;

	case PLAYER_PUNCH:
		if (punchEnable == true) {
			punchEnable = false;
			punch.Reset();
			punch_timer = 1;
			punchCol = App->collision->AddCollider({ position.x + 46, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			punchHit = false;
		}
		break;


	case PLAYER_SPECIAL:
		if (specialEnable == true) {
			specialEnable = false;
			specialAttack.Reset();
			groundFire_timer = 1;
			special_timer = 1;
		}
		break;
	

	case PLAYER_DAMAGE:
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
		if (kickCol->CheckCollision(App->enemy->r) && kickHit == false) {
			App->enemy->hit = true;
			kickHit = true;
		}
		if (kick_timer > 35)
		{
			kickEnable = true;
			status = PLAYER_IN_KICK_FINISH;
			kickCol->to_delete = true;
			kick_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		punch_timer = punch_timer + 1;
		current_animation = &punch;
		if (punchCol->CheckCollision(App->enemy->r) && punchHit == false) {
			App->enemy->hit = true;
			punchHit = true;
		}
		if (punch_timer > 28)
		{
			punchEnable = true;
			status = PLAYER_IN_PUNCH_FINISH;
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
			status = PLAYER_IN_JUMP_FINISH;
			jump_timer = 0;
		}
	}

	if (damage_timer > 0) {
		damage_timer = damage_timer + 1;
		current_animation = &damage;
		if (damage_timer > 30) {
			status = PLAYER_DAMAGE_FINISH;
			damage_timer = 0;
		}
	}

	if (special_timer > 0)
	{
		special_timer = special_timer + 1;
		current_animation = &specialAttack;

		if (special_timer > 30)
		{
			status = IN_SPECIAL_FINISH;
			special_timer = 0;
		}
	}

	if (groundFire_timer > 0)
	{
		groundFire_timer = groundFire_timer + 1;

		if (groundFire_timer == 69)
		{
			App->particles->AddParticle(App->particles->smallfire, position.x + 26, position.y - 45, 0, 2800, 1, 0);
		}
		if (groundFire_timer == 55)
		{
			App->particles->AddParticle(App->particles->midfire, position.x + 28, position.y - 72, 0, 2700, 1, 0);
		}
		if (groundFire_timer == 41)
		{
			App->particles->AddParticle(App->particles->bigfire, position.x + 29, position.y - 100, 0, 2600, 1, 0);
		}
		if (groundFire_timer == 27)
		{
			App->particles->AddParticle(App->particles->midfire, position.x + 31, position.y - 72, 0, 2500, 1, 0);
		}
		if (groundFire_timer == 13)
		{
			App->particles->AddParticle(App->particles->smallfire, position.x + 33, position.y - 45, 0, 2400, 1, 0);
		}
		if (groundFire_timer == 180)
		{
			specialEnable = true;
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

	colPlayer->SetPos(position.x + 12, position.y - 107);
	// Draw everything --------------------------------------

	r = current_animation->GetCurrentFrame();

	  
	if (App->enemy->position.x < position.x) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
	if (App->enemy->position.x > position.x) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r); }

	r.x = position.x;
	r.y = position.y;

	return UPDATE_CONTINUE;
}