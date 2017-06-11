#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleBackground.h"
#include "SDL/include/SDL.h"
#include "SDL\include\SDL_gamecontroller.h"

ModuleInput::ModuleInput() : Module(){
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}
ModuleInput::~ModuleInput(){}
bool ModuleInput::Init(){
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	if (SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) < 0){
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			if (i == 0) {
				controller = SDL_GameControllerOpen(i);
				joy = SDL_GameControllerGetJoystick(controller);
			}
			if (i == 1) {
				controller2 = SDL_GameControllerOpen(i);
				joy2 = SDL_GameControllerGetJoystick(controller2);
			}
			LOG("Index \'%i\' is a compatible controller, named \'%s\'\n", i, SDL_GameControllerNameForIndex(i));
		}
		else {
			LOG("Index \'%i\' is not a compatible controller.\n", i);
		}
	}
	return ret;
}

update_status ModuleInput::PreUpdate(){
	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	Sint16 x_joy, y_joy;
	Sint16 x_joy2, y_joy2;
	x_joy = SDL_JoystickGetAxis(joy, 0);
	y_joy = SDL_JoystickGetAxis(joy, 1);
	x_joy2 = SDL_JoystickGetAxis(joy2, 0);
	y_joy2 = SDL_JoystickGetAxis(joy2, 1);
	for (int i = 0; i < MAX_KEYS; ++i){
		if (keys[i] == 1){
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}


	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) == 1) {
		if (buttonA == KEY_IDLE)
			buttonA = KEY_DOWN;
		else
			buttonA = KEY_REPEAT;
	}
	else{
		if (buttonA == KEY_REPEAT || buttonA == KEY_DOWN)
			buttonA = KEY_UP;
		else
			buttonA = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START) == 1) {
		if (buttonStart == KEY_IDLE)
			buttonStart = KEY_DOWN;
		else
			buttonStart = KEY_REPEAT;
	}
	else{
		if (buttonStart == KEY_REPEAT || buttonStart == KEY_DOWN)
			buttonStart = KEY_UP;
		else
			buttonStart = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) == 1) {
		if (buttonB == KEY_IDLE)
			buttonB = KEY_DOWN;
		else
			buttonB = KEY_REPEAT;
	}
	else{
		if (buttonB == KEY_REPEAT || buttonB == KEY_DOWN)
			buttonB = KEY_UP;
		else
			buttonB = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1) {
		if (dpadUp == KEY_IDLE)
			dpadUp = KEY_DOWN;
		else
			dpadUp = KEY_REPEAT;
	}
	else{
		if (dpadUp == KEY_REPEAT || dpadUp == KEY_DOWN)
			dpadUp = KEY_UP;
		else
			dpadUp = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1) {
		if (dpadDown == KEY_IDLE)
			dpadDown = KEY_DOWN;
		else
			dpadDown = KEY_REPEAT;
	}
	else{
		if (dpadDown == KEY_REPEAT || dpadDown == KEY_DOWN)
			dpadDown = KEY_UP;
		else
			dpadDown = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1) {
		if (dpadLeft == KEY_IDLE)
			dpadLeft = KEY_DOWN;
		else
			dpadLeft = KEY_REPEAT;
	}
	else{
		if (dpadLeft == KEY_REPEAT || dpadLeft == KEY_DOWN)
			dpadLeft = KEY_UP;
		else
			dpadLeft = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1) {
		if (dpadRight == KEY_IDLE)
			dpadRight = KEY_DOWN;
		else
			dpadRight = KEY_REPEAT;
	}
	else{
		if (dpadRight == KEY_REPEAT || dpadRight == KEY_DOWN)
			dpadRight = KEY_UP;
		else
			dpadRight = KEY_IDLE;
	}
	if (x_joy >= -33000 && x_joy < -10000) {
		if (joy_left == KEY_IDLE)
			joy_left = KEY_DOWN;
		else
			joy_left = KEY_REPEAT;
	}
	else{
		if (joy_left == KEY_REPEAT || joy_left == KEY_DOWN)
			joy_left = KEY_UP;
		else
			joy_left = KEY_IDLE;
	}
	if (x_joy >= 10000 && x_joy < 33000) {
		if (joy_right == KEY_IDLE)
			joy_right = KEY_DOWN;
		else
			joy_right = KEY_REPEAT;
	}
	else{
		if (joy_right == KEY_REPEAT || joy_right == KEY_DOWN)
			joy_right = KEY_UP;
		else
			joy_right = KEY_IDLE;
	}
	if (y_joy >= -33000 && y_joy < -10000) {
		if (joy_up == KEY_IDLE)
			joy_up = KEY_DOWN;
		else
			joy_up = KEY_REPEAT;
	}
	else{
		if (joy_up == KEY_REPEAT || joy_up == KEY_DOWN)
			joy_up = KEY_UP;
		else
			joy_up = KEY_IDLE;
	}
	if (y_joy >= 10000 && y_joy < 33000) {
		if (joy_down == KEY_IDLE)
			joy_down = KEY_DOWN;
		else
			joy_down = KEY_REPEAT;
	}
	else{
		if (joy_down == KEY_REPEAT || joy_down == KEY_DOWN)
			joy_down = KEY_UP;
		else
			joy_down = KEY_IDLE;
	}


	if (SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_A) == 1) {
		if (buttonA2 == KEY_IDLE)
			buttonA2 = KEY_DOWN;
		else
			buttonA2 = KEY_REPEAT;
	}
	else{
		if (buttonA2 == KEY_REPEAT || buttonA2 == KEY_DOWN)
			buttonA2 = KEY_UP;
		else
			buttonA2 = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_START) == 1) {
		if (buttonStart2 == KEY_IDLE)
			buttonStart2 = KEY_DOWN;
		else
			buttonStart2 = KEY_REPEAT;
	}
	else{
		if (buttonStart2 == KEY_REPEAT || buttonStart2 == KEY_DOWN)
			buttonStart2 = KEY_UP;
		else
			buttonStart2 = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_B) == 1) {
		if (buttonB2 == KEY_IDLE)
			buttonB2 = KEY_DOWN;
		else
			buttonB2 = KEY_REPEAT;
	}
	else{
		if (buttonB2 == KEY_REPEAT || buttonB2 == KEY_DOWN)
			buttonB2 = KEY_UP;
		else
			buttonB2 = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1) {
		if (dpadUp2 == KEY_IDLE)
			dpadUp2 = KEY_DOWN;
		else
			dpadUp2 = KEY_REPEAT;
	}
	else{
		if (dpadUp2 == KEY_REPEAT || dpadUp2 == KEY_DOWN)
			dpadUp2 = KEY_UP;
		else
			dpadUp2 = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1) {
		if (dpadDown2 == KEY_IDLE)
			dpadDown2 = KEY_DOWN;
		else
			dpadDown2 = KEY_REPEAT;
	}
	else{
		if (dpadDown2 == KEY_REPEAT || dpadDown2 == KEY_DOWN)
			dpadDown2 = KEY_UP;
		else
			dpadDown2 = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1) {
		if (dpadLeft2 == KEY_IDLE)
			dpadLeft2 = KEY_DOWN;
		else
			dpadLeft2 = KEY_REPEAT;
	}
	else{
		if (dpadLeft2 == KEY_REPEAT || dpadLeft2 == KEY_DOWN)
			dpadLeft2 = KEY_UP;
		else
			dpadLeft2 = KEY_IDLE;
	}
	if (SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1) {
		if (dpadRight2 == KEY_IDLE)
			dpadRight2 = KEY_DOWN;
		else
			dpadRight2 = KEY_REPEAT;
	}
	else{
		if (dpadRight2 == KEY_REPEAT || dpadRight2 == KEY_DOWN)
			dpadRight2 = KEY_UP;
		else
			dpadRight2 = KEY_IDLE;
	}
	if (x_joy2 >= -33000 && x_joy2 < -10000) {
		if (joy_left2 == KEY_IDLE)
			joy_left2 = KEY_DOWN;
		else
			joy_left2 = KEY_REPEAT;
	}
	else{
		if (joy_left2 == KEY_REPEAT || joy_left2 == KEY_DOWN)
			joy_left2 = KEY_UP;
		else
			joy_left2 = KEY_IDLE;
	}
	if (x_joy2 >= 10000 && x_joy2 < 33000) {
		if (joy_right2 == KEY_IDLE)
			joy_right2 = KEY_DOWN;
		else
			joy_right2 = KEY_REPEAT;
	}
	else{
		if (joy_right2 == KEY_REPEAT || joy_right2 == KEY_DOWN)
			joy_right2 = KEY_UP;
		else
			joy_right2 = KEY_IDLE;
	}
	if (y_joy2 >= -33000 && y_joy2 < -10000) {
		if (joy_up2 == KEY_IDLE)
			joy_up2 = KEY_DOWN;
		else
			joy_up2 = KEY_REPEAT;
	}
	else{
		if (joy_up2 == KEY_REPEAT || joy_up2 == KEY_DOWN)
			joy_up2 = KEY_UP;
		else
			joy_up2 = KEY_IDLE;
	}
	if (y_joy2 >= 10000 && y_joy2 < 33000) {
		if (joy_down2 == KEY_IDLE)
			joy_down2 = KEY_DOWN;
		else
			joy_down2 = KEY_REPEAT;
	}
	else{
		if (joy_down2 == KEY_REPEAT || joy_down2 == KEY_DOWN)
			joy_down2 = KEY_UP;
		else
			joy_down2 = KEY_IDLE;
	}


	if (keyboard[SDL_SCANCODE_ESCAPE]) {
		App->CleanUp();
		return update_status::UPDATE_STOP;
	}
	return update_status::UPDATE_CONTINUE;
}
// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	if (controller != NULL) {
		SDL_GameControllerClose(controller);
	}
	controller = nullptr;
	return true;
}