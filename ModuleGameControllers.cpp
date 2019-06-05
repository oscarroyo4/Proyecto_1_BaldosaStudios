#include "ModuleGameControllers.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"


ModuleGameControllers::ModuleGameControllers() :Module()
{}

ModuleGameControllers::~ModuleGameControllers()
{}

bool ModuleGameControllers::Start()
{
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	bool ret = true;

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
		LOG("Error", SDL_GetError());
		ret = false;
	}
	return ret;
}

update_status  ModuleGameControllers::PreUpdate()
{
	if (SDL_NumJoysticks() > 0) {
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

				else if (i < 1) {

					Controller_player2_Connected = false;
					SDL_GameControllerClose(controller2);
					controller2 = nullptr;

				}

				else if (i == 1 || i == 0 && Controller_player1_Connected == false) {

					controller2 = SDL_GameControllerOpen(i);
					if (SDL_GameControllerGetAttached(controller2)) {

						Controller2_AxisX = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_LEFTX);
						Controller2_AxisY = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_LEFTY);

						A_pressed2 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_A);
						B_pressed2 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_B);
						Y_pressed2 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_Y);
						Start_pressed2 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_START);

						Controller_player2_Connected = true;
						break;

					}
					else {

						SDL_GameControllerClose(controller2);
						controller2 = nullptr;
					}		controller2 = false;
				}
			}
		}
	
		//PLAYER 1 (player)

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
			if (!Up_pressed) {
				App->input->keyboard[SDL_SCANCODE_W] = KEY_STATE::KEY_DOWN;
				Up_pressed = true;
			}
		}
		else Up_pressed = false;

		if (Controller_AxisY > 6400)
		{
				App->input->keyboard[SDL_SCANCODE_S] = KEY_STATE::KEY_DOWN;
		}

		//PLAYER 2 (enemy)

		if (B_pressed2 == true)
		{
			App->input->keyboard[SDL_SCANCODE_RETURN] = KEY_STATE::KEY_DOWN;
		}

		if (A_pressed2 == true)
		{
			App->input->keyboard[SDL_SCANCODE_RSHIFT] = KEY_STATE::KEY_DOWN;
		}

		if (Y_pressed2 == true)
		{
			App->input->keyboard[SDL_SCANCODE_RALT] = KEY_STATE::KEY_DOWN;
		}

		if (Controller2_AxisX > 6400)
		{
			App->input->keyboard[SDL_SCANCODE_RIGHT] = KEY_STATE::KEY_REPEAT;
		}
		if (Controller2_AxisX < -15000)
		{
			App->input->keyboard[SDL_SCANCODE_LEFT] = KEY_STATE::KEY_REPEAT;
		}

		if (Controller2_AxisY < -15000)
		{
			if (!Up_pressed) {
				App->input->keyboard[SDL_SCANCODE_UP] = KEY_STATE::KEY_DOWN;
				Up_pressed = true;
			}
		}
		else Up_pressed2 = false;

		if (Controller2_AxisY > 6400)
		{
			App->input->keyboard[SDL_SCANCODE_DOWN] = KEY_STATE::KEY_DOWN;
		}
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