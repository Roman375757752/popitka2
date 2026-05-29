#include "pad.h"

#include <SDL2/SDL.h>
#include <string.h>

Controller PlaystationGamePad;

static Uint8 prev_keys[SDL_NUM_SCANCODES];
static SDL_GameController* g_controller;
static Uint32 prev_gc_buttons;
static Sint16 prev_axis_y;
static Sint16 prev_axis_x;

static bool key_tap(const Uint8* keys, SDL_Scancode sc)
{
	return (keys[sc] != 0) && (prev_keys[sc] == 0);
}

static Uint32 read_controller_buttons(SDL_GameController* gc)
{
	Uint32 b = 0;
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		b |= 1u << 0;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		b |= 1u << 1;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		b |= 1u << 2;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		b |= 1u << 3;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_A))
	{
		b |= 1u << 4;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_B))
	{
		b |= 1u << 5;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_X))
	{
		b |= 1u << 6;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_Y))
	{
		b |= 1u << 7;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_START))
	{
		b |= 1u << 8;
	}
	if (SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_BACK))
	{
		b |= 1u << 9;
	}
	return b;
}

void PadInitialize(void)
{
	memset(prev_keys, 0, sizeof(prev_keys));
	memset(&PlaystationGamePad, 0, sizeof(PlaystationGamePad));
	prev_gc_buttons = 0;
	prev_axis_x = 0;
	prev_axis_y = 0;

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == 0)
	{
		SDL_GameControllerEventState(SDL_ENABLE);
		if (SDL_NumJoysticks() > 0 && SDL_IsGameController(0))
		{
			g_controller = SDL_GameControllerOpen(0);
			if (g_controller)
			{
				fprintf(stderr, "[nosmoke] геймпад: %s\n", SDL_GameControllerName(g_controller));
			}
		}
	}

	fprintf(stderr,
	        "[nosmoke] управление: стрелки или WASD — меню, Enter/Space/X/Z — выбор\n");
}

void UpdatePad(void)
{
	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	memset(&PlaystationGamePad, 0, sizeof(PlaystationGamePad));

	PlaystationGamePad.UP_KEY_TAP = key_tap(keys, SDL_SCANCODE_UP) || key_tap(keys, SDL_SCANCODE_W);
	PlaystationGamePad.DOWN_KEY_TAP = key_tap(keys, SDL_SCANCODE_DOWN) || key_tap(keys, SDL_SCANCODE_S);
	PlaystationGamePad.LEFT_KEY_TAP = key_tap(keys, SDL_SCANCODE_LEFT) || key_tap(keys, SDL_SCANCODE_A);
	PlaystationGamePad.RIGHT_KEY_TAP = key_tap(keys, SDL_SCANCODE_RIGHT) || key_tap(keys, SDL_SCANCODE_D);
	PlaystationGamePad.START_KEY_TAP = key_tap(keys, SDL_SCANCODE_RETURN) || key_tap(keys, SDL_SCANCODE_KP_ENTER) ||
	                                   key_tap(keys, SDL_SCANCODE_SPACE);
	PlaystationGamePad.SELECT_KEY_TAP = key_tap(keys, SDL_SCANCODE_ESCAPE);
	PlaystationGamePad.BUTTON_X_KEY_TAP = key_tap(keys, SDL_SCANCODE_X);
	PlaystationGamePad.BUTTON_O_KEY_TAP = key_tap(keys, SDL_SCANCODE_Z);
	PlaystationGamePad.BUTTON_T_KEY_TAP = key_tap(keys, SDL_SCANCODE_W);
	PlaystationGamePad.BUTTON_S_KEY_TAP = key_tap(keys, SDL_SCANCODE_S);

	PlaystationGamePad.UP_KEY_DOWN = keys[SDL_SCANCODE_UP] != 0 || keys[SDL_SCANCODE_W] != 0;
	PlaystationGamePad.DOWN_KEY_DOWN = keys[SDL_SCANCODE_DOWN] != 0 || keys[SDL_SCANCODE_S] != 0;
	PlaystationGamePad.LEFT_KEY_DOWN = keys[SDL_SCANCODE_LEFT] != 0 || keys[SDL_SCANCODE_A] != 0;
	PlaystationGamePad.RIGHT_KEY_DOWN = keys[SDL_SCANCODE_RIGHT] != 0 || keys[SDL_SCANCODE_D] != 0;
	PlaystationGamePad.BUTTON_X_KEY_DOWN = keys[SDL_SCANCODE_X] != 0;

	if (g_controller)
	{
		SDL_GameControllerUpdate(g_controller);
		const Uint32 cur = read_controller_buttons(g_controller);
		const Uint32 edge = cur & ~prev_gc_buttons;
		prev_gc_buttons = cur;

		if (edge & (1u << 0))
		{
			PlaystationGamePad.UP_KEY_TAP = true;
		}
		if (edge & (1u << 1))
		{
			PlaystationGamePad.DOWN_KEY_TAP = true;
		}
		if (edge & (1u << 2))
		{
			PlaystationGamePad.LEFT_KEY_TAP = true;
		}
		if (edge & (1u << 3))
		{
			PlaystationGamePad.RIGHT_KEY_TAP = true;
		}
		if (edge & (1u << 4) || edge & (1u << 6) || edge & (1u << 8))
		{
			PlaystationGamePad.START_KEY_TAP = true;
			PlaystationGamePad.BUTTON_X_KEY_TAP = true;
		}
		if (edge & (1u << 5))
		{
			PlaystationGamePad.BUTTON_O_KEY_TAP = true;
		}
		if (edge & (1u << 7))
		{
			PlaystationGamePad.BUTTON_T_KEY_TAP = true;
		}
		if (edge & (1u << 9))
		{
			PlaystationGamePad.SELECT_KEY_TAP = true;
		}

		const Sint16 axis_y = SDL_GameControllerGetAxis(g_controller, SDL_CONTROLLER_AXIS_LEFTY);
		const Sint16 axis_x = SDL_GameControllerGetAxis(g_controller, SDL_CONTROLLER_AXIS_LEFTX);
		if (axis_y < -16000 && prev_axis_y >= -16000)
		{
			PlaystationGamePad.UP_KEY_TAP = true;
		}
		if (axis_y > 16000 && prev_axis_y <= 16000)
		{
			PlaystationGamePad.DOWN_KEY_TAP = true;
		}
		if (axis_x < -16000 && prev_axis_x >= -16000)
		{
			PlaystationGamePad.LEFT_KEY_TAP = true;
		}
		if (axis_x > 16000 && prev_axis_x <= 16000)
		{
			PlaystationGamePad.RIGHT_KEY_TAP = true;
		}
		prev_axis_y = axis_y;
		prev_axis_x = axis_x;

		PlaystationGamePad.UP_KEY_DOWN = PlaystationGamePad.UP_KEY_DOWN || (cur & (1u << 0)) != 0 || axis_y < -8000;
		PlaystationGamePad.DOWN_KEY_DOWN = PlaystationGamePad.DOWN_KEY_DOWN || (cur & (1u << 1)) != 0 || axis_y > 8000;
		PlaystationGamePad.LEFT_KEY_DOWN = PlaystationGamePad.LEFT_KEY_DOWN || (cur & (1u << 2)) != 0 || axis_x < -8000;
		PlaystationGamePad.RIGHT_KEY_DOWN = PlaystationGamePad.RIGHT_KEY_DOWN || (cur & (1u << 3)) != 0 || axis_x > 8000;
	}

	memcpy(prev_keys, keys, SDL_NUM_SCANCODES);
}
