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

	//Punch animation
	punch.PushBack({ 481, 610, 64, 102 });
	punch.PushBack({ 553, 616, 63, 96 });
	punch.PushBack({ 627, 616, 97, 96 });
	punch.PushBack({ 553, 616, 63, 96 });
	punch.PushBack({ 481, 610, 64, 102 });
	punch.speed = 0.14f;

	//Kick animation 
	kick.PushBack({ 417, 163, 60, 84, });
	kick.PushBack({ 495, 185, 52, 62 });
	kick.PushBack({ 562, 153, 44, 94 });
	kick.PushBack({ 631, 139, 110, 106 });
	kick.speed = 0.14f;

	//Jump animation *
	jump.PushBack({ 21, 1639, 54, 90 });
	jump.PushBack({ 87, 1565, 39, 164 });
	jump.PushBack({ 145, 1559, 49, 171 });
	jump.PushBack({ 203, 1590, 56, 141 });
	jump.speed = 0.1f;

	//crouch animation
	crouch.PushBack({ 26, 288, 59, 69 });
	crouch.speed = 0.25f;
	crouch.loop = false;

	//SpecialAttack animation 
	specialAttack.PushBack({ 12, 1078, 54, 102 });
	specialAttack.PushBack({ 91, 1117, 80, 63 });
	specialAttack.PushBack({ 197, 1096, 50, 84 });
	specialAttack.PushBack({ 272, 1039, 47, 141 });
	specialAttackStatic.PushBack({ 272, 1039, 47, 141 });
	specialAttack.speed = 0.12f;

	//Special Kick animation
	specialkick.PushBack({ 5, 1439, 49, 89 });
	specialkick.PushBack({ 63, 1442, 50, 80 });
	specialkick.PushBack({ 125, 1435, 72, 93 });
	specialkick.PushBack({ 205, 1433, 92, 93 });
	specialkick.PushBack({ 305, 1429, 107, 93 });
	specialkick.PushBack({ 305, 1429, 107, 93 });
	specialkick.speed = 0.065f;

	// taking damage animation *
	damage.PushBack({ 344, 342, 60, 100 });
	damage.PushBack({ 407, 336, 68, 106 });
	damage.PushBack({ 408, 346, 64, 96 });
	damage.PushBack({ 555, 355, 69, 87 });
	damage.speed = 0.15f;

	//crouch punch animation
	crouchPunch.PushBack({ 97, 286, 55, 71 });
	crouchPunch.PushBack({ 159, 288, 76, 70 });
	crouchPunch.PushBack({ 238, 288, 55, 71 });
	crouchPunch.speed = 0.175f;
	crouchPunch.loop = false;

	// defeat animation *
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

	// win animation *
	win.PushBack({ 272, 491, 62, 97 });
	win.PushBack({ 345, 488, 56, 100 });
	win.PushBack({ 412, 489, 59, 99 });
	win.PushBack({ 481, 452, 56, 136 });
	win.speed = 0.05f;
	win.loop = false;

}

ModuleJoe::~ModuleJoe()
{}

// Load assets
bool ModuleJoe::Start()
{
	LOG("Loading JOE");

	App->collision->Enable();
	graphicsJoe = App->textures->Load("Assets/Sprites/Joe Higashi/Sprites joe higashi.png"); //Joe Higashi Sprite Sheet																				 
	punchfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Punch.wav");
	kickfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Punch2.wav");
	jumpfx = App->sounds->Load_effects("Assets/Audio/Fx/SFX_Landing.wav");
	specialfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_Hishoken.wav");
	winfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_WinScream.wav");
	defeatfx = App->sounds->Load_effects("Assets/Audio/Fx/FX_DefeatScream.wav");
	godMode = true;
	colPlayer = App->collision->AddCollider({ position.x, position.y, 38, 104 }, COLLIDER_PLAYER);
	colPlayerCrouch = App->collision->AddCollider({ position.x, position.y - 46, 38, 65 }, COLLIDER_NONE);
	Life = 100;

	return true;
}

// Unload assets
bool ModuleJoe::CleanUp()
{
	LOG("Unloading player");
	if (!IsEnabled()) {
		App->collision->Disable();
		SDL_DestroyTexture(graphicsJoe);
		//Audio
		App->sounds->Unload_effects(punchfx);
		App->sounds->Unload_effects(kickfx);
		App->sounds->Unload_effects(specialfx);
		App->sounds->Unload_effects(jumpfx);
		App->sounds->Unload_effects(winfx);
		App->sounds->Unload_effects(defeatfx);
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

		else if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			status = JOE_SPECIAL_KICK;

		else {
			status = JOE_IDLE;
			crouch.Reset();
		}

		if (hit == true) {
			status = JOE_DAMAGE;
			hit = false;
		}
	}

	switch (status)
	{
	case JOE_IDLE:
		current_animation = &idle;
		position.y = 220;

		colPlayer->type = COLLIDER_PLAYER;
		colPlayerCrouch->type = COLLIDER_NONE;
		break;

	case JOE_BACKWARD:
		if (special_timer < 50 && special_timer > 0) { position.x += 0; }
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

	case JOE_FORWARD:

		if (special_timer <= 50 && special_timer > 0) { position.x += 0; }
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

	case JOE_JUMP:
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

	case JOE_CROUCH:
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


	case JOE_IN_JUMP_FINISH:
		status = JOE_IDLE;
		jump.Reset();
		break;

	case JOE_CROUCH_PUNCH_FINISH:
		status = JOE_CROUCH;
		crouchPunch.Reset();
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
			if (App->sounds->Play_chunk(kickfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			
			if (App->enemy->position.x > position.x) kickCol = App->collision->AddCollider({ position.x + 46, position.y - 85, 55, 18 }, COLLIDER_PLAYER_SHOT);
			else kickCol = App->collision->AddCollider({ position.x - 45, position.y - 85, 55, 18 }, COLLIDER_PLAYER_SHOT);
			kickHit = false;
		}
		break;

	case JOE_SPECIAL_KICK:
		if (specialkickEnable == true) {
			specialkickEnable = false;
			specialkick.Reset();
			special_kick_timer = 1;
			if (App->sounds->Play_chunk(kickfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}

			if (App->enemy->position.x > position.x) speciakickCol = App->collision->AddCollider({ position.x + 46, position.y - 65, 45, 30 }, COLLIDER_PLAYER_SHOT);
			else speciakickCol = App->collision->AddCollider({ position.x - 45, position.y - 65, 45, 30 }, COLLIDER_PLAYER_SHOT);
			kickHit = false;
		}
		break;

	case JOE_PUNCH:
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


	case JOE_SPECIAL:
		if (specialEnable == true) {
			specialEnable = false;
			specialAttack.Reset();
			if (App->sounds->Play_chunk(specialfx))
			{
				LOG("Could not play select sound. Mix_PlayChannel: %s", Mix_GetError());
			}
			tornado_timer = 1;
			special_timer = 1;
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
			if (App->sounds->Play_chunk(defeatfx))
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
			if (App->sounds->Play_chunk(winfx))
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

	if (special_kick_timer > 0)
	{
		special_kick_timer = special_kick_timer + 1;
		current_animation = &specialkick;
		if (speciakickCol->CheckCollision(App->enemy->r) && kickHit == false) {
			App->enemy->hit = true;
			kickHit = true;
		}
		if (special_kick_timer > 95)
		{
			specialkickEnable = true;
			status = JOE_IN_SPECIAL_KICK_FINISH;
			speciakickCol->to_delete = true;
			special_kick_timer = 0;
		}
	}

	if (special_kick_timer > 40 && special_kick_timer < 82 && position.x < App->enemy->position.x)
	{
		position.x = position.x + 3;
		speciakickCol->rect.x = speciakickCol->rect.x + 3;
	}
	else if (special_kick_timer > 40 && special_kick_timer < 82 && position.x >= App->enemy->position.x)
	{
		position.x = position.x - 3;
		speciakickCol->rect.x = speciakickCol->rect.x - 3;

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
			status = JOE_CROUCH_PUNCH_FINISH;
			crouchPunchCol->to_delete = true;
			crouch_punch_timer = 0;
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
		if (jump_timer < 12)colPlayer->SetPos(position.x, position.y - 140);
		else if (jump_timer < 29)colPlayer->SetPos(position.x, position.y - 155);
		else if (jump_timer < 38)colPlayer->SetPos(position.x, position.y - 140);

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

		if (special_timer > 40)
		{
			status = JOE_IN_SPECIAL_FINISH;
			special_timer = 0;
		}
	}

	if (tornado_timer > 0)
	{
		tornado_timer = tornado_timer + 1;
		if (tornado_timer > 30 && tornado_timer < 50) { current_animation = &specialAttackStatic; }
		if (tornado_timer == 25)
		{
			if (App->enemy->position.x > position.x) App->particles->AddParticle(App->particles->tornado, position.x + 26, position.y, 0, 1100, 2.2, 0, 1);
			else App->particles->AddParticle(App->particles->tornado, position.x - 5, position.y, 0, 1100, -2.2, 0, 1);

		}
		if (tornado_timer >= 50)
		{
			status = JOE_IDLE;
		}
		if (tornado_timer >= 1000)
		{
			specialEnable = true;
			tornado_timer = 0;
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

		colPlayer->SetPos(position.x, position.y - 107);
		colPlayerCrouch->SetPos(position.x, position.y - 67);

	}
	// Draw everything --------------------------------------

	r = current_animation->GetCurrentFrame();


	if (App->enemy->position.x <= position.x) { App->render->Blit(graphicsJoe, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }
	if (App->enemy->position.x > position.x &&  defeat_timer == 0) { App->render->Blit(graphicsJoe, position.x, position.y - r.h, &r); }
	if (defeat_timer > 0) { App->render->Blit(graphicsJoe, position.x, position.y - r.h, &r, 1, SDL_FLIP_HORIZONTAL); }

	r.x = position.x;
	r.y = position.y;

	return UPDATE_CONTINUE;
}