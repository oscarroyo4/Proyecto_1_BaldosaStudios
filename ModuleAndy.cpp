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
	jump.PushBack({ 377, 123, 60, 101 });
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

	//SpecialAttack animation
	specialAttack.PushBack({ 25, 361, 65, 95 });
	specialAttack.PushBack({ 95, 364, 49, 92 });
	specialAttack.PushBack({ 156, 368, 49, 88 });
	specialAttackStatic.PushBack({ 218, 367, 99, 89 });
	specialAttack.speed = 0.175f;

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
	LOG("Loading player");

	App->collision->Enable();
	graphicsAndy = App->textures->Load("Assets/Sprites/Andy Bogard/Sprites_Andy_Bogard.png"); //First Andy Bogard Sprite Sheet
																						  //graphicsAndy2 = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites 2.png"); //Second Tery Bogard Sprite Sheet
	punchfx = App->sounds->Load("Assets/Audio/Fx/SFX_Punch.ogg");
	kickfx = App->sounds->Load("Assets/Audio/Fx/SFX_Punch2.ogg");
	jumpfx = App->sounds->Load("Assets/Audio/Fx/SFX_Landing.ogg");
	specialfx = App->sounds->Load("Assets/Audio/Fx/FX_Hishoken.ogg");
	winfx = App->sounds->Load("Assets/Audio/Fx/FX_WinScream.ogg");
	//defeatfx = App->sounds->Load("Assets/Audio/Fx/FX_DefeatScream.ogg"); Not working
	godMode = true;
	colPlayer = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_PLAYER);
	Life = 100;

	return true;
}

// Unload assets
bool ModuleAndy::CleanUp()
{
	LOG("Unloading player");
	if (App->player->IsEnabled()) {
		App->collision->Disable();
		SDL_DestroyTexture(graphicsAndy);
		App->player->Disable();
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

		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			status = ANDY_CROUCH;

		else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			status = ANDY_PUNCH;

		else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			status = ANDY_KICK;

		else if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
			status = ANDY_SPECIAL;

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
		if (specialEnable == false) { position.x += 0; }
		else
		{
			if (position.x < 10) { position.x -= 0; }
			else position.x -= speed;
			current_animation = &backward;
		}
		break;

	case ANDY_FORWARD:

		if (specialEnable == false) { position.x += 0; }
		else
		{
			position.x += speed;
			current_animation = &forward;
		}
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
		current_animation = &crouch;
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


	case ANDY_SPECIAL:
		if (specialEnable == true) {
			specialAttack.Reset();
			if (Mix_PlayChannel(-1, specialfx, 0) == -1)
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			groundFire_timer = 1;
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


	if (jump_timer > 0)
	{
		jump_timer = jump_timer + 1;
		current_animation = &jump;
		if (jump_timer < 12)colPlayer->SetPos(position.x + 12, position.y - 130);
		else if (jump_timer < 29)colPlayer->SetPos(position.x + 12, position.y - 140);
		else if (jump_timer < 38)colPlayer->SetPos(position.x + 12, position.y - 130);

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

	if (groundFire_timer > 0)
	{
		groundFire_timer = groundFire_timer + 1;
		if (groundFire_timer > 30) { current_animation = &specialAttackStatic; }
		if (groundFire_timer == 69)
		{
			App->particles->AddParticle(App->particles->smallfire, position.x + 26, position.y - 45, 0, 2800, 1.5, 0, 1);

		}
		if (groundFire_timer == 55)
		{
			App->particles->AddParticle(App->particles->midfire, position.x + 28, position.y - 72, 0, 2700, 1.5, 0, 1);

		}
		if (groundFire_timer == 41)
		{
			App->particles->AddParticle(App->particles->bigfire, position.x + 29, position.y - 100, 0, 2600, 1.5, 0, 1);

		}
		if (groundFire_timer == 27)
		{
			App->particles->AddParticle(App->particles->midfire, position.x + 31, position.y - 72, 0, 2500, 1.5, 0, 1);

		}
		if (groundFire_timer == 13)
		{
			App->particles->AddParticle(App->particles->smallfire, position.x + 33, position.y - 45, 0, 2400, 1.5, 0, 1);

		}
		if (groundFire_timer >= 120)
		{
			status = ANDY_IDLE;
		}
		if (groundFire_timer >= 180)
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