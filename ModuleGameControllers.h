#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"

#define MAX_BUTTONS 150

class ModuleGameControllers :public Module
{
public:
	ModuleGameControllers();
	~ModuleGameControllers();


	bool Start();
	update_status PreUpdate();
	bool CleanUp();

public:

	SDL_Event event_;
	SDL_GameController *controller = nullptr;

	bool Controller_player1_Connected = false; 
	bool A_pressed = false;
	bool Y_pressed = false;
	bool B_pressed = false;
	bool Start_pressed = false;


	int Controller_AxisX = 0;
	int Controller_AxisY = 0;

};


