#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"
#include "ModuleAndy.h"
#include "ModuleHUD.h"
#include "SDL_image/include/SDL_image.h"

#define PUNCH_TIME 1000

ModuleAndy::ModuleAndy()
{
	position.x = 230;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 811, 343, 60, 101 });
	idle.PushBack({ 879, 345, 60, 99 });
	idle.PushBack({ 947, 348, 61, 96 });
	idle.speed = 0.1f;

	//forward
	forward.PushBack({ 746, 604, 63, 98 });
	forward.PushBack({ 821, 603, 56, 99 });
	forward.PushBack({ 878, 603, 64, 99 });
	forward.PushBack({ 944, 601, 61, 101 });
	forward.speed = 0.125f;


	//backwards
	backward.PushBack({ 746, 475, 50, 99 });
	backward.PushBack({ 802, 473, 49, 101 });
	backward.PushBack({ 867, 476, 54, 98 });
	backward.speed = 0.125f;

	//Punch animation
	punch.PushBack({ 17, 123, 60, 101 });
	punch.PushBack({ 90, 133, 50, 91 });
	punch.PushBack({ 156, 129, 49, 96 });
	punch.PushBack({ 221, 128, 94, 96 });
	punch.speed = 0.12f;

	//Kick animation
	kick.PushBack({ 313, 15, 45, 99 });
	kick.PushBack({ 380, 26, 57, 88 });
	kick.PushBack({ 450, 23, 53, 91 });
	kick.PushBack({ 516, 26, 114, 76 });
	kick.PushBack({ 643, 13, 84, 95 });
	kick.PushBack({ 749, 29, 54, 81 });
	kick.PushBack({ 834, 12, 60, 101 });
	kick.speed = 0.12f;

	//Jump animation
	jump.PushBack({ 442, 144, 54, 80 });
	jump.PushBack({ 516, 120, 43, 105 });
	jump.PushBack({ 578, 120, 50, 93 });
	jump.PushBack({ 649, 123, 49, 85 });
	jump.PushBack({ 709, 144, 54, 80 });
	jump.speed = 0.12f;

	//crouch animation
	crouch.PushBack({ 870, 123, 60, 101 });
	crouch.PushBack({ 946, 163, 49, 61 });
	crouch.speed = 0.175f;
	crouch.loop = false;

	//crouch punch animation
	crouchPunch.PushBack({ 881, 735, 49, 63 });
	crouchPunch.PushBack({ 942, 736, 78, 62 });
	crouchPunch.speed = 0.175f;
	crouchPunch.loop = false;

	//SpecialAttack animation
	specialAttack.PushBack({ 25, 361, 65, 95 });
	specialAttack.PushBack({ 95, 364, 49, 92 });
	specialAttack.PushBack({ 156, 368, 49, 88 });
	specialAttackStatic.PushBack({ 218, 367, 99, 89 });
	specialAttack.speed = 0.175f;

	//Special punch animation
	specialpunch.PushBack({ 339, 481, 75, 88 });
	specialpunch.PushBack({ 421, 481, 89, 88 });
	specialpunch.PushBack({ 517, 485, 87, 84 });
	specialpunch.speed = 0.03f;

	// taking damage animation
	damage.PushBack({ 864, 239, 60, 100 });
	damage.PushBack({ 932, 256, 68, 106 });
	damage.speed = 0.15f;

	// defeat animation
	defeat.PushBack({ 28, 934, 92, 80 });
	defeat.PushBack({ 128, 941, 99, 59 });
	defeat.PushBack({ 223, 941, 89, 55 });
	defeat.PushBack({ 317, 948, 99, 42 });
	defeat.PushBack({ 423, 953, 112, 37 });
	defeat.PushBack({ 522, 916, 109, 32 });
	defeat.speed = 0.07f;
	defeat.loop = false;

	// win animation
	win.PushBack({ 513, 807, 51, 97 });
	win.PushBack({ 575, 779, 56, 125 });
	win.speed = 0.05f;
	win.loop = false;

}

ModuleAndy::~ModuleAndy()
{}

// Load assets
bool ModuleAndy::Start()
{
	LOG("Loading andy");

	App->collision->Enable();
	graphicsAndy = App->textures->Load("Assets/Sprites/Andy Bogard/Sprites_Andy_Bogard.png"); //First Andy Bogard Sprite Sheet
	punchfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Punch.wav");
	kickfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Punch2.wav");
	jumpfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Landing.wav");
	specialfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_SpecialAttack.wav");
	winfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_WinScream.wav");
	defeatfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_DefeatScream.wav");
	godMode = true;
	colPlayer = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_PLAYER);
	Life = 100;

	return true;
}

// Unload assets
bool ModuleAndy::CleanUp()
{
	LOG("Unloading andy");
	if (!IsEnabled()) {
		App->collision->Disable();
		SDL_DestroyTexture(graphicsAndy);
		App->sounds->Unload_effects(punchfx);
		App->sounds->Unload_effects(kickfx);
		App->sounds->Unload_effects(specialfx);
		App->sounds->Unload_effects(jumpfx);
		App->sounds->Unload_effects(winfx);
		App->sounds->Unload_effects(defeatfx);
		App->andy->Disable();
	}

	//SDL_DestroyTexture(graphicsAndy2);

	return true;
}

update_status ModuleAndy::Update()
{
	float speed = 2;
	if (input) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			status = ANDY_BACKWARD;

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			status = ANDY_FORWARD;

		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
			status = ANDY_JUMP;

		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			status = ANDY_CROUCH;

		else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			status = ANDY_PUNCH;

		else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			status = ANDY_KICK;

		else if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
			status = ANDY_SPECIAL;

		else if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			status = ANDY_SPECIAL_PUNCH;

		else if (hit == true) {
			status = ANDY_DAMAGE;
			hit = false;
		}

		else {
			status = ANDY_IDLE;
			crouch.Reset();
		}
	}

	switch (status)
	{
	case ANDY_IDLE:
		current_animation = &idle;
		position.y = 220;
		break;

	case ANDY_BACKWARD:
		if (position.x < 10) { position.x -= 0; }
		else position.x -= speed;
		current_animation = &backward;
		break;

	case ANDY_FORWARD:

		position.x += speed;
		current_animation = &forward;

		break;

	case ANDY_JUMP:
		if (jumpEnable == true) {
			jumpEnable = false;
			jump.Reset();
			if (Mix_PlayChannel(-1, jumpfx, 0) == -1)
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			jump_timer = 1;
		}
		break;

	case ANDY_CROUCH:
		if (jumpEnable == true && crouchPunchEnable == true) {


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
				crouchpunchHit = false;
			}
			else current_animation = &crouch;
		}
		break;

	case ANDY_CROUCH_PUNCH_FINISH:
		status = ANDY_CROUCH;
		crouchPunch.Reset();
		break;

	case ANDY_IN_JUMP_FINISH:
		status = ANDY_IDLE;
		jump.Reset();
		break;

	case ANDY_IN_PUNCH_FINISH:
		status = ANDY_IDLE;
		punch.Reset();
		break;

	case ANDY_IN_KICK_FINISH:
		status = ANDY_IDLE;
		kick.Reset();
		break;

	case ANDY_DAMAGE_FINISH:
		status = ANDY_IDLE;
		damage.Reset();
		break;

	case ANDY_IN_SPECIAL_FINISH:
		status = ANDY_IDLE;
		specialAttack.Reset();
		break;

	case ANDY_SPECIAL_PUNCH_FINISH:
		status = ANDY_IDLE;
		specialpunch.Reset();
		break;

	case ANDY_KICK:
		if (kickEnable == true) {
			kickEnable = false;
			kick.Reset();
			kick_timer = 1;
			if (Mix_PlayChannel(-1, kickfx, 0) == -1)
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			kickCol = App->collision->AddCollider({ position.x + 46, position.y - 58, 55, 18 }, COLLIDER_PLAYER_SHOT);
			kickHit = false;
		}
		break;

	case ANDY_PUNCH:
		if (punchEnable == true) {
			punchEnable = false;
			punch.Reset();
			punch_timer = 1;
			if (Mix_PlayChannel(-1, punchfx, 0) == -1)
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			punchCol = App->collision->AddCollider({ position.x + 46, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			punchHit = false;
		}
		break;

	case ANDY_SPECIAL_PUNCH:
		if (specialpunchEnable == true) {
			specialpunchEnable = false;
			specialpunch.Reset();
			special_punch_timer = 1;
			if (Mix_PlayChannel(-1, punchfx, 0) == -1)
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			punchCol = App->collision->AddCollider({ position.x + 46, position.y - 90, 40, 20 }, COLLIDER_PLAYER_SHOT);
			punchHit = false;
		}
		break;


	case ANDY_SPECIAL:
		if (specialEnable == true) {
			specialAttack.Reset();
			if (Mix_PlayChannel(-1, specialfx, 0) == -1)
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			blast_timer = 1;
			special_timer = 1;
			specialEnable = false;
		}
		break;


	case ANDY_DAMAGE:
		damage.Reset();
		Life = Life - 10;
		if (Life <= 0) {
			Life = 0;
			defeat_timer = 1;
			App->enemy->win_timer = 1;
		}
		damage_timer = 1;
		break;
	}

	if (defeat_timer > 0)
	{
		input = false;

		defeat_timer = defeat_timer + 1;
		current_animation = &defeat;

		if (win_timer == 4)
		{
			if (Mix_PlayChannel(-1, defeatfx, 0) == -1)
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
		}
	}
	if (defeat_timer >= 210) { App->hud->Lose = true; }

	if (win_timer > 0)
	{
		input = false;

		win_timer = win_timer + 1;
		current_animation = &win;
		if (win_timer == 4)
		{
			PlayerVict = PlayerVict + 1;
			if (Mix_PlayChannel(-1, winfx, 0) == -1)
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
		}
	}
	if (win_timer >= 190) { App->hud->Win = true; }

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
			status = ANDY_IN_KICK_FINISH;
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
			status = ANDY_IN_PUNCH_FINISH;
			punchCol->to_delete = true;
			punch_timer = 0;
		}
	}

	if (crouch_punch_timer > 0)
	{
		crouch_punch_timer = crouch_punch_timer + 1;
		current_animation = &crouchPunch;
		if (crouchPunchCol->CheckCollision(App->enemy->r) && crouchpunchHit == false) {
			App->enemy->hit = true;
			crouchpunchHit = true;
		}
		if (crouch_punch_timer > 20)
		{
			crouchPunchEnable = true;
			status = ANDY_CROUCH_PUNCH_FINISH;
			crouchPunchCol->to_delete = true;
			crouch_punch_timer = 0;
		}
	}
	if (special_punch_timer > 0)
	{
		special_punch_timer = special_punch_timer + 1;
		current_animation = &specialpunch;
		if (punchCol->CheckCollision(App->enemy->r) && punchHit == false) {
			App->enemy->hit = true;
			punchHit = true;
		}
		if (special_punch_timer > 90)
		{
			specialpunchEnable = true;
			status = ANDY_SPECIAL_PUNCH_FINISH;
			punchCol->to_delete = true;
			special_punch_timer = 0;
		}
	}

	if (special_punch_timer > 25 && special_punch_timer < 80 && position.x < App->enemy->position.x)
	{
		position.x = position.x + 3;
		punchCol->rect.x = punchCol->rect.x + 3;
	}
	else if (special_punch_timer > 25 && special_punch_timer < 80 && position.x >= App->enemy->position.x)
	{
		position.x = position.x - 3;
		punchCol->rect.x = punchCol->rect.x - 3;

	}


	if (jump_timer > 0)
	{
		jump_timer = jump_timer + 1;
		current_animation = &jump;
		if (jump_timer < 8) { colPlayer->SetPos(position.x + 12, position.y - 140); }
		else if (jump_timer < 29) { colPlayer->SetPos(position.x + 12, position.y - 180); }
		else if (jump_timer < 38) { colPlayer->SetPos(position.x + 12, position.y - 165); }

		if (jump_timer > 38)
		{
			jumpEnable = true;
			status = ANDY_IN_JUMP_FINISH;
			jump_timer = 0;
		}
	}

	if (damage_timer > 0) {
		damage_timer = damage_timer + 1;
		current_animation = &damage;
		if (damage_timer > 30) {
			status = ANDY_DAMAGE_FINISH;
			damage_timer = 0;
		}
	}

	if (special_timer > 0)
	{
		special_timer = special_timer + 1;
		current_animation = &specialAttack;

		if (special_timer > 30)
		{
			status = ANDY_IN_SPECIAL_FINISH;
			special_timer = 0;
		}
	}

	if (blast_timer > 0)
	{
		blast_timer = blast_timer + 1;
		if (blast_timer > 30 && blast_timer < 50) { current_animation = &specialAttackStatic; }
		if (blast_timer == 25)
		{
			if (App->enemy->position.x > position.x) App->particles->AddParticle(App->particles->blast, position.x + 35, position.y-80, 0, 1100, 2.2, 0, 1);
			else App->particles->AddParticle(App->particles->blast, position.x - 5, position.y-80, 0, 1100, -2.2, 0, 1);

		}
		if (blast_timer >= 50)
		{
			status = ANDY_IDLE;
			input = true;
		}
		if (blast_timer >= 250)
		{
			specialEnable = true;
			blast_timer = 0;
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


	if (jump_timer == 0) { colPlayer->SetPos(position.x + 12, position.y - 107); }
	// Draw everything --------------------------------------

	r = current_animation->GetCurrentFrame();


	if (App->enemy->position.x < position.x) { App->render->Blit(graphicsAndy, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
	if (App->enemy->position.x > position.x &&  defeat_timer == 0) { App->render->Blit(graphicsAndy, position.x, position.y - r.h, &r); }
	if (defeat_timer > 0) { App->render->Blit(graphicsAndy, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }

	r.x = position.x;
	r.y = position.y;

	return UPDATE_CONTINUE;
}