#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleEnemy.h"
#include "ModuleJoe.h"
#include "ModuleAndy.h"
#include "ModulePlayer.h"
#include "ModuleHUD.h"
#include "SDL_image/include/SDL_image.h"

#define PUNCH_TIME 1000

ModuleEnemy::ModuleEnemy()
{
	position.x = 375;
	position.y = 220;

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
	jump.PushBack({ 268, 163, 52, 160 });
	jump.PushBack({ 328, 156, 65, 175 });
	jump.PushBack({ 393, 185, 59, 150 });
	jump.speed = 0.12f;

	//crouch animation
	crouch.PushBack({ 10, 808, 59, 98 });
	crouch.PushBack({ 133, 822, 63, 84 });
	crouch.PushBack({ 74, 812, 58, 95 });
	crouch.PushBack({ 200, 839, 57, 66 });
	crouch.speed = 0.25f;
	crouch.loop = false;

	//crouch punch animation
	crouchPunch.PushBack({ 260, 1880, 54, 65 });
	crouchPunch.PushBack({ 314, 1883, 81, 63 });
	crouchPunch.speed = 0.175f;
	crouchPunch.loop = false;

	//SpecialAttack animation
	specialAttack.PushBack({ 421, 693, 52, 106 });
	specialAttack.PushBack({ 362, 691, 55, 107 });
	specialAttack.PushBack({ 297, 702, 61, 96 });
	specialAttack.PushBack({ 214, 720, 80, 78 });
	specialAttack.PushBack({ 142, 721, 68, 77 });
	specialAttack.PushBack({ 75, 730, 66, 68 });
	specialAttack.PushBack({ 10, 717, 62, 81 });
	specialAttack.speed = 0.175f;
	specialAttackStatic.PushBack({ 142, 721, 68, 77 });

	//Special Punch animation
	specialpunch.PushBack({ 18, 1590, 88, 110 });
	specialpunch.PushBack({ 120, 1600, 58, 98 });
	specialpunch.PushBack({ 196, 1615, 62, 83 });
	specialpunch.PushBack({ 265, 1599, 116, 93 });
	specialpunch.PushBack({ 265, 1599, 116, 93 });
	specialpunch.PushBack({ 265, 1599, 116, 93 });
	specialpunch.PushBack({ 389, 1595 , 57, 94 });
	specialpunch.speed = 0.055f;

	// taking damage animation
	damage.PushBack({ 344, 342, 60, 100 });
	damage.PushBack({ 407, 336, 68, 106 });
	damage.PushBack({ 408, 346, 64, 96 });
	damage.PushBack({ 555, 355, 69, 87 });
	damage.speed = 0.15f;

	// defeat animation
	defeat.PushBack({ 10, 921, 64, 96 });
	defeat.PushBack({ 81, 930, 69, 87 });
	defeat.PushBack({ 159, 912, 84, 105 });
	defeat.PushBack({ 242, 934, 107, 71 });
	defeat.PushBack({ 356, 934, 87, 66 });
	defeat.PushBack({ 450, 935, 102, 64 });
	defeat.PushBack({ 559, 956, 112, 44 });
	defeat.PushBack({ 684, 969, 115, 31 });
	defeat.speed = 0.07f;
	defeat.loop = false;

	// win animation
	win.PushBack({ 272, 491, 62, 97 });
	win.PushBack({ 345, 488, 56, 100 });
	win.PushBack({ 412, 489, 59, 99 });
	win.PushBack({ 481, 452, 56, 136 });
	win.speed = 0.05f;
	win.loop = false;
}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading enemy");
	graphicsTerry = App->textures->Load("Assets/Sprites/Terry Bogard (Enemy Skin)/Terry Bogard (enemy).png");  //First Tery Bogard Sprite Sheet
	punchfx1 = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Punch.wav");
	kickfx1 = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Punch2.wav");
	jumpfx1 = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Landing.wav");
	specialfx1 = App->sounds->Load_effects("Assets/Audio/Fx/FX_SpecialAttack.wav");
	winfx1 = App->sounds->Load_effects("Assets/Audio/Fx/FX_WinScream.wav");
	defeatfx1 = App->sounds->Load_effects("Assets/Audio/Fx/FX_DefeatScream.wav");
	colEnemy = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_ENEMY);
	colEnemyCrouch = App->collision->AddCollider({ position.x, position.y - 46, 34, 60 }, COLLIDER_NONE);
	godMode = true;
	Life = 100;
	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemy");
	if (!IsEnabled()) {
		App->collision->Disable();
		SDL_DestroyTexture(graphicsTerry);
		//Audio
		App->sounds->Unload_effects(punchfx1);
		App->sounds->Unload_effects(kickfx1);
		App->sounds->Unload_effects(jumpfx1);
		App->sounds->Unload_effects(specialfx1);
		App->sounds->Unload_effects(winfx1);
		App->sounds->Unload_effects(defeatfx1);
		//Disable
		App->enemy->Disable();
	}

	return true;
}

update_status ModuleEnemy::Update()
{
	int speed = 2;
	if (input) {
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

		else if (App->input->GetKey(SDL_SCANCODE_RALT) == KEY_DOWN)
			status = ENEMY_SPECIAL;

		else if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
			status = ENEMY_SPECIAL_PUNCH;

		else {
			status = ENEMY_IDLE;
			crouch.Reset();
		}

		if (hit == true) {
			status = ENEMY_DAMAGE;
			hit = false;
		}

	}
	

	switch (status)
	{
	case ENEMY_IDLE:
		current_animation = &idle;
		position.y = 220;

		colEnemy->type = COLLIDER_ENEMY;
		colEnemyCrouch->type = COLLIDER_NONE;
		break;

	case ENEMY_BACKWARD:
		if (special_timer < 60 && special_timer > 0) { position.x += 0; }
		else
		{
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
				if (jumpEnable == true) {
					jumpEnable = false;
					jump.Reset();
					if (App->sounds->Play_chunk(jumpfx1))
					{
						LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
					}
					jump_timer = 1;
				}
			if (position.x < 10) { position.x -= 0; }
			else position.x -= speed;
			current_animation = &backward;
			colEnemy->type = COLLIDER_ENEMY;
			colEnemyCrouch->type = COLLIDER_NONE;
		}
		break;

	case ENEMY_FORWARD:
		if (special_timer < 60 && special_timer > 0) { position.x += 0; }
		else
		{
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
				if (jumpEnable == true) {
					jumpEnable = false;
					jump.Reset();
					if (App->sounds->Play_chunk(jumpfx1))
					{
						LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
					}
					jump_timer = 1;
				}
			if (position.x > 590) { position.x -= 0; }
			else position.x += speed;
			current_animation = &forward;
			colEnemy->type = COLLIDER_ENEMY;
			colEnemyCrouch->type = COLLIDER_NONE;
		}
		break;

	case ENEMY_JUMP:
		if (jumpEnable == true) {
			jumpEnable = false;
			jump.Reset();
			if (App->sounds->Play_chunk(jumpfx1))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			jump_timer = 1;
		}
		break;

	case ENEMY_CROUCH:
		if (jumpEnable == true && crouchPunchEnable == true) {

			colEnemy->type = COLLIDER_NONE;
			colEnemyCrouch->type = COLLIDER_ENEMY;

			if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
				crouchPunchEnable = false;
				crouchPunch.Reset();
				crouch_punch_timer = 1;
				if (App->sounds->Play_chunk(punchfx1))
				{
					LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
				}
				if (App->player->position.x < position.x) crouchPunchCol = App->collision->AddCollider({ position.x - 30, position.y - 55, 40, 18 }, COLLIDER_ENEMY_SHOT);
				else crouchPunchCol = App->collision->AddCollider({ position.x + 46, position.y - 55, 40, 18 }, COLLIDER_ENEMY_SHOT);

				crouchPunchHit = false;
			}
			else current_animation = &crouch;
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

	case ENEMY_CROUCH_PUNCH_FINISH:
		status = ENEMY_CROUCH;
		crouchPunch.Reset();
		break;

	case ENEMY_IN_KICK_FINISH:
		status = ENEMY_IDLE;
		kick.Reset();
		break;

	case ENEMY_DAMAGE_FINISH:
		status = ENEMY_IDLE;
		damage.Reset();
		break;

	case ENEMY_SPECIAL_PUNCH_FINISH:
		status = ENEMY_IDLE;
		specialpunch.Reset();
		break;

	case ENEMY_KICK:
		if (kickEnable == true) {
			kickEnable = false;
			kick.Reset();
			kick_timer = 1;
			if (App->sounds->Play_chunk(kickfx1))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			if (App->player->position.x < position.x) kickCol = App->collision->AddCollider({ position.x - 45, position.y - 58, 55, 18 }, COLLIDER_ENEMY_SHOT);
			else kickCol = App->collision->AddCollider({ position.x + 46, position.y - 58, 55, 18 }, COLLIDER_ENEMY_SHOT);
			kickHit = false;
		}
		break;

	case ENEMY_PUNCH:
		if (punchEnable == true) {
			punchEnable = false;
			punch.Reset();
			punch_timer = 1;
			if (App->sounds->Play_chunk(punchfx1))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			if (App->player->position.x < position.x) punchCol = App->collision->AddCollider({ position.x - 30, position.y - 90, 40, 20 }, COLLIDER_ENEMY_SHOT);
			else punchCol = App->collision->AddCollider({ position.x + 46, position.y - 90, 40, 20 }, COLLIDER_ENEMY_SHOT);

			punchHit = false;
		}
		break;

	case ENEMY_SPECIAL_PUNCH:
		if (specialpunchEnable == true) {
			specialpunchEnable = false;
			specialpunch.Reset();
			special_punch_timer = 1;
			if (App->sounds->Play_chunk(punchfx1))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			if (App->enemy->position.x > position.x) punchCol = App->collision->AddCollider({ position.x + 46, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			else punchCol = App->collision->AddCollider({ position.x - 30, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			punchHit = false;
		}
		break;

	case ENEMY_SPECIAL:
		if (specialEnable == true) {
			specialEnable = false;
			specialAttack.Reset();
			if (App->sounds->Play_chunk(specialfx1))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			groundFire_timer = 1;
			special_timer = 1;
		}
		break;
	

	case ENEMY_DAMAGE:
		damage.Reset();

		Life = Life - 10;
		if (Life <= 0) {
			Life = 0;
			if (defeat_timer == 0) {
				defeat_timer = 1;
				App->player->win_timer = 1;
				App->joe->win_timer = 1;
				App->andy->win_timer = 1;
			}
		}
		damage_timer = 1;
		break;
	}

	if (defeat_timer > 0)
	{
		input = false;
		defeat_timer = defeat_timer + 1;
		current_animation = &defeat;
		if (defeat_timer == 4)
		{
			if (App->sounds->Play_chunk(defeatfx1))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
		}
		else if (defeat_timer >= 210) {
			App->hud->Win = true;
			input = false;
		}
	}


	if (win_timer > 0)
	{
		input = false;
		win_timer = win_timer + 1;
		current_animation = &win;
		if (win_timer == 4)
		{
			if (App->sounds->Play_chunk(winfx1))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
		}
	}
	if (win_timer >= 210) {
		App->hud->Win = true; 
		input = false;
	}

	if (win_timer >= 400) { win_timer = 0; }
	if (defeat_timer >= 400) { defeat_timer = 0; }
	

	if (kick_timer > 0)
	{
		kick_timer = kick_timer + 1;
		current_animation = &kick;
		if (kickCol->CheckCollision(App->player->r) && kickHit == false) {
			App->player->hit = true;
			kickHit = true;
		}
		if (kick_timer > 37)
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
		if (punch_timer > 30)
		{
			punchEnable = true;
			status = ENEMY_IN_PUNCH_FINISH;
			punchCol->to_delete = true;
			punch_timer = 0;
		}
	}

	if (special_punch_timer > 0)
	{
		special_punch_timer = special_punch_timer + 1;
		current_animation = &specialpunch;
		if (punchCol->CheckCollision(App->enemy->r) && punchHit == false) {
			App->player->hit = true;
			punchHit = true;
		}
		if (special_punch_timer > 123)
		{
			specialpunchEnable = true;
			status = ENEMY_SPECIAL_PUNCH_FINISH;
			punchCol->to_delete = true;
			special_punch_timer = 0;
		}
	}

	if (special_punch_timer > 45 && special_punch_timer < 100 && position.x < App->player->position.x)
	{
		position.x = position.x + 3;
		punchCol->rect.x = punchCol->rect.x + 3;
	}
	else if (special_punch_timer > 45 && special_punch_timer < 100 && position.x >= App->player->position.x)
	{
		position.x = position.x - 3;
		punchCol->rect.x = punchCol->rect.x - 3;

	}

	if (crouch_punch_timer > 0)
	{
		crouch_punch_timer = crouch_punch_timer + 1;
		current_animation = &crouchPunch;
		if (crouchPunchCol->CheckCollision(App->player->r) && crouchPunchHit == false) {
			App->player->hit = true;
			crouchPunchHit = true;
		}
		if (crouch_punch_timer > 20)
		{
			crouchPunchEnable = true;
			status = ENEMY_CROUCH_PUNCH_FINISH;
			crouchPunchCol->to_delete = true;
			crouch_punch_timer = 0;
		}
	}

	if (jump_timer > 0)
	{
		jump_timer = jump_timer + 1;
		current_animation = &jump;
		if (jump_timer < 8) { colEnemy->SetPos(position.x + 12, position.y - 140); }
		else if (jump_timer < 29) { colEnemy->SetPos(position.x + 12, position.y - 180); }
		else if (jump_timer < 38) { colEnemy->SetPos(position.x + 12, position.y - 165); }

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

	if (special_timer > 0)
	{
		special_timer = special_timer + 1;
		current_animation = &specialAttack;

		if (special_timer > 30)
		{
			status = ENEMY_IN_SPECIAL_FINISH;
			special_timer = 0;
		}
	}

	if (groundFire_timer > 0)
	{
		groundFire_timer = groundFire_timer + 1;
		if (groundFire_timer > 30 && groundFire_timer < 60) current_animation = &specialAttackStatic;
		if (groundFire_timer == 56)
		{
			if (App->player->position.x < position.x) App->particles->AddParticle(App->particles->smallfire, position.x + 18, position.y, 0, 2800, -3, 0, 2);
			else App->particles->AddParticle(App->particles->smallfire, position.x + 26, position.y, 0, 2800, 3, 0, 2);

		}
		if (groundFire_timer == 50)
		{
			if (App->player->position.x < position.x) App->particles->AddParticle(App->particles->midfire, position.x + 18, position.y, 0, 2700, -3, 0, 2);
			else App->particles->AddParticle(App->particles->midfire, position.x + 26, position.y, 0, 2700, 3, 0, 2);
		}
		if (groundFire_timer == 44)
		{
			if (App->player->position.x < position.x) App->particles->AddParticle(App->particles->bigfire, position.x + 18, position.y, 0, 2600, -3, 0, 2);
			else App->particles->AddParticle(App->particles->bigfire, position.x + 26, position.y, 0, 2600, 3, 0, 2);
		}
		if (groundFire_timer == 38)
		{
			if (App->player->position.x < position.x)App->particles->AddParticle(App->particles->midfire, position.x + 18, position.y, 0, 2500, -3, 0, 2);
			else App->particles->AddParticle(App->particles->midfire, position.x + 26, position.y, 0, 2500, 3, 0, 2);
		}
		if (groundFire_timer == 32) 
		{
			if (App->player->position.x < position.x) App->particles->AddParticle(App->particles->smallfire, position.x + 18, position.y, 0, 2400, -3, 0, 2);
			else App->particles->AddParticle(App->particles->smallfire, position.x + 26, position.y, 0, 2400, 3, 0, 2);
		}
		if (groundFire_timer >= 60)
		{
			status = ENEMY_IDLE;
		}
		if (groundFire_timer >= 1000)
		{
			specialEnable = true;
			groundFire_timer = 0;
		}
	}

	if (jump_timer == 0) {
		//Normal collider position
		colEnemy->SetPos(position.x + 12, position.y - 107);
		//Crouched collider position
		colEnemyCrouch->SetPos(position.x + 12, position.y - 67);
	}

	// Draw everything --------------------------------------

	r = current_animation->GetCurrentFrame();

	if (App->player->IsEnabled())
	{
		if (App->player->position.x < position.x &&  defeat_timer == 0) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
		if (App->player->position.x > position.x) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r); }
	}

	if (App->andy->IsEnabled())
	{
		if (App->andy->position.x < position.x &&  defeat_timer == 0) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
		if (App->andy->position.x > position.x) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r); }
	}

	if (App->joe->IsEnabled())
	{
		if (App->joe->position.x < position.x &&  defeat_timer == 0) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
		if (App->joe->position.x > position.x) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r); }
	}

	r.x = position.x;
	r.y = position.y;

	return UPDATE_CONTINUE;
}