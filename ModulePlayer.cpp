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
	jump.PushBack({ 468, 163, 52, 170 });
	jump.PushBack({ 528, 156, 65, 185 });
	jump.PushBack({ 593, 185, 59, 158 });
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

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	App->collision->Enable();
	graphicsTerry = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites.png"); //First Tery Bogard Sprite Sheet
	punchfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Punch.wav");
	kickfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Punch2.wav");
	jumpfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Landing.wav");
	specialfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_SpecialAttack.wav");
	winfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_WinScream.wav");
	defeatfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_DefeatScream.wav");
	colPlayer = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_PLAYER);
	colPlayerCrouch = App->collision->AddCollider({ position.x, position.y - 46, 34, 60 }, COLLIDER_NONE);
	godMode = true;
	Life = 100;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	if (!IsEnabled()) {
		App->collision->Disable();
		SDL_DestroyTexture(graphicsTerry);
		//Audio
		App->sounds->Unload_effects(punchfx);
		App->sounds->Unload_effects(kickfx);
		App->sounds->Unload_effects(jumpfx);
		App->sounds->Unload_effects(specialfx);
		App->sounds->Unload_effects(winfx);
		App->sounds->Unload_effects(defeatfx);
		//Disable
		App->player->Disable();
	}

	return true;
}

update_status ModulePlayer::Update()
{
	float speed = 2;
	if (input) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			status = PLAYER_BACKWARD;

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			status = PLAYER_FORWARD;

		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
			status = PLAYER_JUMP;

		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			status = PLAYER_CROUCH;

		else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			status = PLAYER_PUNCH;

		else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			status = PLAYER_KICK;

		else if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
			status = PLAYER_SPECIAL;

		else if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			status = PLAYER_SPECIAL_PUNCH;

		else {
			status = PLAYER_IDLE;
			crouch.Reset();
		}

		if (hit == true) {
			status = PLAYER_DAMAGE;
			hit = false;
		}
	}

	switch (status)
	{
	case PLAYER_IDLE:
		current_animation = &idle;
		position.y = 220;

		colPlayer->type = COLLIDER_PLAYER;
		colPlayerCrouch->type = COLLIDER_NONE;

		break;

	case PLAYER_BACKWARD:
		if (special_timer < 60 && special_timer > 0) { position.x += 0; }
		else
		{
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				if (jumpEnable == true) {
					jumpEnable = false;
					jump.Reset();
					if (App->sounds->Play_chunk(jumpfx))
					{
						LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
					}
					jump_timer = 1;
				}
			if (position.x < 10) { position.x -= 0; }
			else position.x -= speed;
			current_animation = &backward;
			colPlayer->type = COLLIDER_PLAYER;
			colPlayerCrouch->type = COLLIDER_NONE;
		}
		break;

	case PLAYER_FORWARD:

		if (special_timer < 60 && special_timer > 0) {position.x += 0;}
		else
		{
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				if (jumpEnable == true) {
					jumpEnable = false;
					jump.Reset();
					if (App->sounds->Play_chunk(jumpfx))
					{
						LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
					}
					jump_timer = 1;
				}
			if (position.x > 590) { position.x -= 0; }
			else position.x += speed;
			current_animation = &forward;
			colPlayer->type = COLLIDER_PLAYER;
			colPlayerCrouch->type = COLLIDER_NONE;
		}
		break;

	case PLAYER_JUMP:
		if (jumpEnable == true) {
			jumpEnable = false;
			jump.Reset();
			if (App->sounds->Play_chunk(jumpfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			jump_timer = 1;
		}
		break;

	case PLAYER_CROUCH:
		if (jumpEnable == true && crouchPunchEnable == true) {

			colPlayer->type = COLLIDER_NONE;
			colPlayerCrouch->type = COLLIDER_PLAYER;

			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
				crouchPunchEnable = false;
				crouchPunch.Reset();
				crouch_punch_timer = 1;
				if (App->sounds->Play_chunk(punchfx))
				{
					LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
				}

				if (App->enemy->position.x > position.x) crouchPunchCol = App->collision->AddCollider({ position.x + 46, position.y - 55, 40, 18 }, COLLIDER_PLAYER_SHOT);
				else crouchPunchCol = App->collision->AddCollider({ position.x - 30, position.y - 55, 40, 18 }, COLLIDER_PLAYER_SHOT);


				crouchPunchHit = false;
			}
			else current_animation = &crouch;
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

	case PLAYER_CROUCH_PUNCH_FINISH:
		status = PLAYER_CROUCH;
		crouchPunch.Reset();
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

	case IN_SPECIAL_PUNCH_FINISH:
		status = PLAYER_IDLE;
		specialpunch.Reset();
		break;

	case PLAYER_KICK:
		if (kickEnable == true) {
			kickEnable = false;
			kick.Reset();
			kick_timer = 1;
			if (App->sounds->Play_chunk(kickfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			if (App->enemy->position.x > position.x) kickCol = App->collision->AddCollider({ position.x + 46, position.y - 58, 55, 18 }, COLLIDER_PLAYER_SHOT);
			else kickCol = App->collision->AddCollider({ position.x - 45, position.y - 58, 55, 18 }, COLLIDER_PLAYER_SHOT);
			kickHit = false;
		}
		break;

	case PLAYER_PUNCH:
		if (punchEnable == true) {
			punchEnable = false;
			punch.Reset();
			punch_timer = 1;
			if (App->sounds->Play_chunk(punchfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			if (App->enemy->position.x > position.x) punchCol = App->collision->AddCollider({ position.x + 46, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			else punchCol = App->collision->AddCollider({ position.x - 30, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			punchHit = false;
		}
		break;

	case PLAYER_SPECIAL_PUNCH:
		if (specialpunchEnable == true) {
			specialpunchEnable = false;
			specialpunch.Reset();
			special_punch_timer = 1;
			if (App->sounds->Play_chunk(punchfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			if (App->enemy->position.x > position.x) punchCol = App->collision->AddCollider({ position.x + 46, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			else punchCol = App->collision->AddCollider({ position.x - 30, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			punchHit = false;
		}
		break;


	case PLAYER_SPECIAL:
		if (specialEnable == true) {
			specialEnable = false;
			specialAttack.Reset();
			if (App->sounds->Play_chunk(specialfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			groundFire_timer = 1;
			special_timer = 1;
		}
		break;


	case PLAYER_DAMAGE:
		damage.Reset();

		Life = Life - 10;
		if (Life <= 0) {
			Life = 0;
			if(defeat_timer == 0){
				defeat_timer = 1;
				App->enemy->win_timer = 1;
			}
		}
		damage_timer = 1;
		break;
	}

	if (defeat_timer > 0)
	{

		defeat_timer = defeat_timer + 1;
		current_animation = &defeat;

		if (defeat_timer == 4)
		{
			if (App->sounds->Play_chunk(defeatfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
		}
	}

	if(defeat_timer > 80) input = false;

	if (win_timer > 0)
	{
		input = false;

		win_timer = win_timer + 1;
		current_animation = &win;
		if (win_timer == 4)
		{
			PlayerVict = PlayerVict + 1;
			if (App->sounds->Play_chunk(winfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
		}
	}
	if (win_timer >= 210) { App->hud->Win = true; }

	if (win_timer >= 400) { win_timer = 0; }
	if (defeat_timer >= 400) { defeat_timer = 0; }

	if (kick_timer > 0)
	{
		kick_timer = kick_timer + 1;
		current_animation = &kick;
		if (kickCol->CheckCollision(App->enemy->r) && kickHit == false) {
			App->enemy->hit = true;
			kickHit = true;
		}
		if (kick_timer > 37)
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
		if (punch_timer > 30)
		{
			punchEnable = true;
			status = PLAYER_IN_PUNCH_FINISH;
			punchCol->to_delete = true;
			punch_timer = 0;
		}
	}

	if (special_punch_timer > 0)
	{
		input = false;
		special_punch_timer = special_punch_timer + 1;
		current_animation = &specialpunch;
		if (punchCol->CheckCollision(App->enemy->r) && punchHit == false) {
			App->enemy->hit = true;
			punchHit = true;
		}
		if (special_punch_timer > 123)
		{
			specialpunchEnable = true;
			status = IN_SPECIAL_PUNCH_FINISH;
			punchCol->to_delete = true;
			special_punch_timer = 0;
			input = true;
		}
	}

	if (special_punch_timer > 45 && special_punch_timer < 100 && position.x < App->enemy->position.x)
	{ 
		position.x = position.x + 3; 
		punchCol->rect.x = punchCol->rect.x + 3;
	}
	else if (special_punch_timer > 45 && special_punch_timer < 100 && position.x >= App->enemy->position.x) 
	{ 
		position.x = position.x - 3; 
		punchCol->rect.x = punchCol->rect.x - 3;

	}
	
	if (crouch_punch_timer > 0)
	{
		crouch_punch_timer = crouch_punch_timer + 1;
		current_animation = &crouchPunch;
		if (crouchPunchCol->CheckCollision(App->enemy->r) && crouchPunchHit == false) {
			App->enemy->hit = true;
			crouchPunchHit = true;
		}
		if (crouch_punch_timer > 20)
		{
			crouchPunchEnable = true;
			status = PLAYER_CROUCH_PUNCH_FINISH;
			crouchPunchCol->to_delete = true;
			crouch_punch_timer = 0;
		}
	}
	   
	if (jump_timer > 0)
	{
		jump_timer = jump_timer + 1;
		current_animation = &jump;
		if (jump_timer < 8) { colPlayer->SetPos(position.x + 12, position.y - 140);}
		else if (jump_timer < 29) { colPlayer->SetPos(position.x + 12, position.y - 180);}
		else if (jump_timer < 38) { colPlayer->SetPos(position.x + 12, position.y - 165);}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) { position.x--; }
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) { position.x++; }

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

		if (special_timer > 60)
		{
			status = IN_SPECIAL_FINISH;
			special_timer = 0;
		}
	}

	if (groundFire_timer > 0)
	{
		groundFire_timer = groundFire_timer + 1;
		if (groundFire_timer > 30 && groundFire_timer < 60) current_animation = &specialAttackStatic;
		if (groundFire_timer == 64)
		{
			if (App->enemy->position.x > position.x) App->particles->AddParticle(App->particles->smallfire, position.x + 26, position.y, 0, 2800, 2, 0, 1);
			else App->particles->AddParticle(App->particles->smallfire, position.x + 18, position.y, 0, 2800, -3, 0, 1);
		}
		if (groundFire_timer == 56)
		{
			if (App->enemy->position.x > position.x) App->particles->AddParticle(App->particles->midfire, position.x + 26, position.y, 0, 2700, 2, 0, 1);
			else App->particles->AddParticle(App->particles->midfire, position.x + 18, position.y, 0, 2700, -3, 0, 1);
		}
		if (groundFire_timer == 48)
		{
			if (App->enemy->position.x > position.x) App->particles->AddParticle(App->particles->bigfire, position.x + 26, position.y, 0, 2600, 2, 0, 1);
			else App->particles->AddParticle(App->particles->bigfire, position.x + 18, position.y, 0, 2600, -3, 0, 1);
		}
		if (groundFire_timer == 40)
		{
			if (App->enemy->position.x > position.x) App->particles->AddParticle(App->particles->midfire, position.x + 26, position.y, 0, 2500, 2, 0, 1);
			else App->particles->AddParticle(App->particles->midfire, position.x + 18, position.y, 0, 2500, -3, 0, 1);
		}
		if (groundFire_timer == 32)
		{
			if (App->enemy->position.x > position.x) App->particles->AddParticle(App->particles->smallfire, position.x + 26, position.y, 0, 2400, 2, 0, 1);
			else App->particles->AddParticle(App->particles->smallfire, position.x + 18, position.y, 0, 2400, -3, 0, 1);
		}
		if (groundFire_timer >= 60)
		{
			status = PLAYER_IDLE;
		}
		if (groundFire_timer >= 600)
		{
			specialEnable = true;
			groundFire_timer = 0;
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


	if (jump_timer == 0) {
		//Normal collider position
		colPlayer->SetPos(position.x + 12, position.y - 107);
		//Crouched collider position
		colPlayerCrouch->SetPos(position.x + 12, position.y - 67);
	}


	//COMBOS

	/*if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
		ComboFireCounter++;
	}

	if (ComboFireCounter < 40) {
		status = PLAYER_SPECIAL;
	}
	else if (ComboFireCounter >= 40) {
		ComboFireCounter = 0;
	}*/


	// Draw everything --------------------------------------

	r = current_animation->GetCurrentFrame();
	
	if (App->enemy->position.x < position.x) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
	if (App->enemy->position.x > position.x &&  defeat_timer == 0) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r); }
	if (defeat_timer > 0) { App->render->Blit(graphicsTerry, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }


	r.x = position.x;
	r.y = position.y;

	return UPDATE_CONTINUE;
}