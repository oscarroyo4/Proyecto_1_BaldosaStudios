#include "ModuleController.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"


ModuleGameControllers::ModuleGameControllers() :Module()
{}

ModuleGameControllers::~ModuleGameControllers()
{}

bool ModuleGameControllers::Init()
{
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	bool ret = true;

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
		LOG("Error", SDL_GetError());

	}
	return ret;
}

update_status  ModuleGameControllers::PreUpdate()
{

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {

		if (SDL_IsGameController(i)) {
			
			if (i == 0) {
				controller = SDL_GameControllerOpen(i);

				if (SDL_GameControllerGetAttached(controller)) {

					Controller_AxisX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
					Controller_AxisY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
  
					A_pressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
					B_pressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
					Y_pressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);
					Start_pressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);

					Controller_player1_Connected = true;
				}

				else {
					SDL_GameControllerClose(controller);
					controller = nullptr;
					Controller_player1_Connected = false;

				}
			}

		}
	}



	if (B_pressed == true) 
	{
		App->input->keyboard[SDL_SCANCODE_R] = KEY_STATE::KEY_DOWN;
	}

	if (A_pressed == true)
	{
		App->input->keyboard[SDL_SCANCODE_T] = KEY_STATE::KEY_DOWN;
	}

	if (Y_pressed == true)
	{
		App->input->keyboard[SDL_SCANCODE_Y] = KEY_STATE::KEY_DOWN;
	}

	if (Start_pressed == true)
	{
		App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_DOWN;
	}

	if (Controller_AxisX > 6400) 
	{
		App->input->keyboard[SDL_SCANCODE_D] = KEY_STATE::KEY_REPEAT;
	}
	if (Controller_AxisX < -15000) 
	{
		App->input->keyboard[SDL_SCANCODE_A] = KEY_STATE::KEY_REPEAT;
	}

	if (Controller_AxisY < -15000) 
	{
		App->input->keyboard[SDL_SCANCODE_W] = KEY_STATE::KEY_DOWN;
	}





	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool  ModuleGameControllers::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	SDL_GameControllerClose(controller);
	controller = nullptr;

	return true;
}