#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleEnemy.h"
#include "ModuleJoe.h"
#include "ModuleHUD.h"
#include "SDL_image/include/SDL_image.h"

#define PUNCH_TIME 1000

ModuleJoe::ModuleJoe()
{
	position.x = 230;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 37, 16, 63, 108 });
	idle.PushBack({ 117, 18, 61, 106 });
	idle.PushBack({ 195, 20, 62, 104 });
	idle.speed = 0.1f;

	//forward
	forward.PushBack({ 597, 19, 75, 105 });
	forward.PushBack({ 686, 11, 65, 113 });
	forward.PushBack({ 758, 5, 62, 119 });
	forward.PushBack({ 825, 16, 63, 108 });
	forward.speed = 0.125f;

	//backwards
	backward.PushBack({ 33, 144, 60, 102 });
	backward.PushBack({ 111, 141, 55, 105 });
	backward.PushBack({ 176, 136, 55, 110 });
	backward.PushBack({ 241, 140, 56, 106 });
	backward.PushBack({ 315, 144, 60, 102 });
	backward.speed = 0.125f;
	/*
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
	specialAttackStatic.PushBack({ 142, 721, 68, 77 });
	specialAttack.PushBack({ 75, 730, 66, 68 });
	specialAttack.PushBack({ 10, 717, 62, 81 });
	specialAttack.speed = 0.175f;

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
	*/
}

ModuleJoe::~ModuleJoe()
{}

// Load assets
bool ModuleJoe::Start()
{
	LOG("Loading player");

	App->collision->Enable();
	graphicsJoe = App->textures->Load("Assets/Sprites/Joe Higashi/Sprites joe higashi.png"); //First Tery Bogard Sprite Sheet																				  //graphicsTerry2 = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites 2.png"); //Second Tery Bogard Sprite Sheet
	punchfx = App->sounds->Load("Assets/Audio/Fx/SFX_Punch.ogg");
	kickfx = App->sounds->Load("Assets/Audio/Fx/SFX_Punch2.ogg");
	jumpfx = App->sounds->Load("Assets/Audio/Fx/SFX_Landing.ogg");
	specialfx = App->sounds->Load("Assets/Audio/Fx/FX_SpecialAttack.ogg");
	winfx = App->sounds->Load("Assets/Audio/Fx/FX_WinScream.ogg");
	//defeatfx = App->sounds->Load("Assets/Audio/Fx/FX_DefeatScream.ogg"); Not working
	godMode = true;
	colPlayer = App->collision->AddCollider({ position.x, position.y, 34, 106 }, COLLIDER_PLAYER);
	Life = 100;

	return true;
}

// Unload assets
bool ModuleJoe::CleanUp()
{
	LOG("Unloading player");
	if (App->joe->IsEnabled()) {
		App->collision->Disable();
		SDL_DestroyTexture(graphicsJoe);
		App->joe->Disable();
	}

	//SDL_DestroyTexture(graphicsTerry2);

	return true;
}

update_status ModuleJoe::Update()
{
	float speed = 2;
	if (input) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			status = JOE_BACKWARD;

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			status = JOE_FORWARD;

		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
			status = JOE_JUMP;

		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			status = JOE_CROUCH;

		else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			status = JOE_PUNCH;

		else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			status = JOE_KICK;

		else if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
			status = JOE_SPECIAL;

		else if (hit == true) {
			status = JOE_DAMAGE;
			hit = false;
		}

		else {
			status = JOE_IDLE;
			crouch.Reset();
		}
	}

	switch (status)
	{
	case JOE_IDLE:
		current_animation = &idle;
		position.y = 220;
		break;

	case JOE_BACKWARD:
		if (specialEnable == false) { position.x += 0; }
		else
		{
			if (position.x < 10) { position.x -= 0; }
			else position.x -= speed;
			current_animation = &backward;
		}
		break;

	case JOE_FORWARD:

		if (specialEnable == false) { position.x += 0; }
		else
		{
			position.x += speed;
			current_animation = &forward;
		}
		break;

	case JOE_JUMP:
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

	case JOE_CROUCH:
		current_animation = &crouch;
		break;

	case JOE_IN_JUMP_FINISH:
		status = JOE_IDLE;
		jump.Reset();
		break;

	case JOE_IN_PUNCH_FINISH:
		status = JOE_IDLE;
		punch.Reset();
		break;

	case JOE_IN_KICK_FINISH:
		status = JOE_IDLE;
		kick.Reset();
		break;

	case JOE_DAMAGE_FINISH:
		status = JOE_IDLE;
		damage.Reset();
		break;

	case JOE_IN_SPECIAL_FINISH:
		status = JOE_IDLE;
		specialAttack.Reset();
		break;

	case JOE_KICK:
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

	case JOE_PUNCH:
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


	case JOE_SPECIAL:
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


	case JOE_DAMAGE:
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
			status = JOE_IN_KICK_FINISH;
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
			status = JOE_IN_PUNCH_FINISH;
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
			status = JOE_IN_JUMP_FINISH;
			jump_timer = 0;
		}
	}

	if (damage_timer > 0) {
		damage_timer = damage_timer + 1;
		current_animation = &damage;
		if (damage_timer > 30) {
			status = JOE_DAMAGE_FINISH;
			damage_timer = 0;
		}
	}

	if (special_timer > 0)
	{
		special_timer = special_timer + 1;
		current_animation = &specialAttack;

		if (special_timer > 30)
		{
			status = JOE_IN_SPECIAL_FINISH;
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
			status = JOE_IDLE;
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


	if (App->enemy->position.x < position.x) { App->render->Blit(graphicsJoe, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
	if (App->enemy->position.x > position.x &&  defeat_timer == 0) { App->render->Blit(graphicsJoe, position.x, position.y - r.h, &r); }
	if (defeat_timer > 0) { App->render->Blit(graphicsJoe, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }

	r.x = position.x;
	r.y = position.y;

	return UPDATE_CONTINUE;
}