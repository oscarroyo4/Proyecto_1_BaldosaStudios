#include "Application.h"
#include "Enemy_BrownCookies.h"
#include "ModuleCollision.h"

Enemy_BrownCookies::Enemy_BrownCookies(int x, int y) : Enemy(x, y)
{
	fly->PushBack({ 4, 39, 24, 24 });
	fly->PushBack({ 35, 39, 24, 24 });
	fly->PushBack({ 68, 39, 24, 24 });
	fly->PushBack({ 102, 39, 24, 24 });
	fly->PushBack({ 134, 39, 24, 24 });
	fly->PushBack({ 167, 39, 24, 24 });
	fly->PushBack({ 201, 39, 24, 24 });
	fly->PushBack({ 235, 39, 24, 24 });
	fly->PushBack({ 4, 72, 24, 24 });
	fly->PushBack({ 35, 72, 24, 24 });
	fly->PushBack({ 68, 72, 24, 24 });
	fly->PushBack({ 102, 72, 24, 24 });
	fly->PushBack({ 134, 72, 24, 24 });
	fly->PushBack({ 167, 72, 24, 24 });
	fly->PushBack({ 201, 72, 24, 24 });
	fly->PushBack({ 235, 72, 24, 24 });

	fly->speed = 0.2f;

	animation = fly;

	collider = App->collision->AddCollider({0, 0, 24, 24}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_BrownCookies::Move()
{
	/*
	if(going_up)
	{
		if(wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if(wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}*/
	if (going_up) {
		path->PushBack({ 0.2f, 0.2f }, 8, &fly);
	}
	else {
		path->PushBack({ 0.2f, -0.2f }, 8, &fly);
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;
	original_pos = position;
	position = original_pos + path->GetCurrentPosition();
}
