#include "pad.h"

#include <SDL2/SDL.h>
#include <string.h>

Controller PlaystationGamePad;

static Uint8 prev_keys[SDL_NUM_SCANCODES];

void PadInitialize(void)
{
	memset(prev_keys, 0, sizeof(prev_keys));
	memset(&PlaystationGamePad, 0, sizeof(PlaystationGamePad));
}

void UpdatePad(void)
{
	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);

#define TAP(scan) ((keys[(scan)] != 0) && (prev_keys[(scan)] == 0))

	PlaystationGamePad.UP_KEY_TAP = TAP(SDL_SCANCODE_UP);
	PlaystationGamePad.DOWN_KEY_TAP = TAP(SDL_SCANCODE_DOWN);
	PlaystationGamePad.LEFT_KEY_TAP = TAP(SDL_SCANCODE_LEFT);
	PlaystationGamePad.RIGHT_KEY_TAP = TAP(SDL_SCANCODE_RIGHT);
	PlaystationGamePad.START_KEY_TAP = TAP(SDL_SCANCODE_RETURN) || TAP(SDL_SCANCODE_SPACE);
	PlaystationGamePad.SELECT_KEY_TAP = TAP(SDL_SCANCODE_ESCAPE);
	PlaystationGamePad.BUTTON_X_KEY_TAP = TAP(SDL_SCANCODE_X);

	PlaystationGamePad.BUTTON_O_KEY_TAP = TAP(SDL_SCANCODE_Z);
	PlaystationGamePad.BUTTON_T_KEY_TAP = TAP(SDL_SCANCODE_W);
	PlaystationGamePad.BUTTON_S_KEY_TAP = TAP(SDL_SCANCODE_S);

	PlaystationGamePad.UP_KEY_DOWN = keys[SDL_SCANCODE_UP] != 0;
	PlaystationGamePad.DOWN_KEY_DOWN = keys[SDL_SCANCODE_DOWN] != 0;
	PlaystationGamePad.LEFT_KEY_DOWN = keys[SDL_SCANCODE_LEFT] != 0;
	PlaystationGamePad.RIGHT_KEY_DOWN = keys[SDL_SCANCODE_RIGHT] != 0;
	PlaystationGamePad.BUTTON_X_KEY_DOWN = keys[SDL_SCANCODE_X] != 0;

#undef TAP

	memcpy(prev_keys, keys, SDL_NUM_SCANCODES);
}
