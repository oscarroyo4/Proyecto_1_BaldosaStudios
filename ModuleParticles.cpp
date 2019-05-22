#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Sprites/Terry Bogard/Terry Sprites.png");

	smallfire.anim.PushBack({ 517, 755, 22, 44 });
	midfire.anim.PushBack({ 483, 728, 27, 72 });
	bigfire.anim.PushBack({ 550, 700, 18, 100 });
	midfire.anim.PushBack({ 483, 728, 27, 72 });
	smallfire.anim.PushBack({ 517, 755, 22, 44 });

	smallfire.anim.speed = 0.01f;
	midfire.anim.speed = 0.01f;
	bigfire.anim.speed = 0.01f;

	//SDL_DestroyTexture(graphics);

	//graphics2 = App->textures->Load("Assets/Sprites/Joe Higashi/Sprites joe higashi.png");

	//tornado.anim.PushBack({378,1122,42,58});
	//tornado.anim.PushBack({434,1092,51,88});
	//tornado.anim.PushBack({497,1068,61,112});
	//tornado.anim.PushBack({563,1068,58,112});
	//tornado.anim.PushBack({630,1068,63,112});
	//tornado.anim.PushBack({718,1068,64,112});

	//tornado.anim.speed = 0.04f;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			p->col->to_delete = true;
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay, Uint32 lifeVar, float speedX, float speedY, int PlEnVar)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	p->life = lifeVar;
	
	p->speed.x = speedX;
	p->speed.y = speedY;
	if (PlEnVar == 1) {
		p->col = App->collision->AddCollider({ p->position.x - 3, p->position.y, p->anim.GetCurrentFrame().w,  p->anim.GetCurrentFrame().h }, COLLIDER_PLAYER_SHOT);
		p->PlEn = 1;
	}
	else if (PlEnVar == 2) {
		p->col = App->collision->AddCollider({ p->position.x - 3, p->position.y, p->anim.GetCurrentFrame().w,  p->anim.GetCurrentFrame().h }, COLLIDER_ENEMY_SHOT);
		p->PlEn = 2;
	}

	active[last_particle++] = p;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;
	
	col->SetPos(position.x, position.y);
	if (col->CheckCollision(App->enemy->r) && PlEn == 1) {
		App->enemy->hit = true;
		col->to_delete = true;
		ret = false;
	}
	else if (col->CheckCollision(App->player->r) && PlEn == 2) {
		App->player->hit = true;
		col->to_delete = true;
		ret = false;
	}

	return ret;
}