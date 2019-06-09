#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "SDL_image\include\SDL_image.h"
#include "RectSprites.h"


struct SDL_Renderer;
struct SDL_Texture;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f, SDL_RendererFlip flip_texture = SDL_FLIP_NONE);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);
	void StartCameraShake(int duration, float magnitude);
	void UpdateCameraShake();
	void CameraFollowingPlayers(int, int);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;

	bool shaking = false;
	float shake_duration = 0.0f;
	float shake_timer = 0.0f;
	float shake_magnitude = 0.0f;
	float cameraX;
	SDL_Point camera_offset;
};

#endif //__ModuleRenderer_H__