#ifndef PAD_MANAGER
#define PAD_MANAGER

#include <stdbool.h>
#include <stdio.h>

#ifdef NOSMOKE_PLATFORM_SDL

typedef struct
{
	bool UP_KEY_TAP;
	bool DOWN_KEY_TAP;
	bool LEFT_KEY_TAP;
	bool RIGHT_KEY_TAP;
	bool SELECT_KEY_TAP;
	bool START_KEY_TAP;
	bool BUTTON_X_KEY_TAP;
	bool BUTTON_O_KEY_TAP;
	bool BUTTON_T_KEY_TAP;
	bool BUTTON_S_KEY_TAP;
	bool BUTTON_L1_KEY_TAP;
	bool BUTTON_L2_KEY_TAP;
	bool BUTTON_R1_KEY_TAP;
	bool BUTTON_R2_KEY_TAP;
	bool UP_KEY_DOWN;
	bool DOWN_KEY_DOWN;
	bool LEFT_KEY_DOWN;
	bool RIGHT_KEY_DOWN;
	bool BUTTON_X_KEY_DOWN;
	bool BUTTON_O_KEY_DOWN;
	bool BUTTON_T_KEY_DOWN;
	bool BUTTON_S_KEY_DOWN;
	bool BUTTON_L1_KEY_DOWN;
	bool BUTTON_L2_KEY_DOWN;
	bool BUTTON_R1_KEY_DOWN;
	bool BUTTON_R2_KEY_DOWN;
	bool HAPTIC_MOTOR;
} Controller;

void PadInitialize(void);
void UpdatePad(void);

#else

#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <libpad.h>

typedef struct
{
	bool UP_KEY_TAP;
	bool DOWN_KEY_TAP;
	bool LEFT_KEY_TAP;
	bool RIGHT_KEY_TAP;
	bool SELECT_KEY_TAP;
	bool START_KEY_TAP;
	bool BUTTON_X_KEY_TAP;
	bool BUTTON_O_KEY_TAP;
	bool BUTTON_T_KEY_TAP;
	bool BUTTON_S_KEY_TAP;
	bool BUTTON_L1_KEY_TAP;
	bool BUTTON_L2_KEY_TAP;
	bool BUTTON_R1_KEY_TAP;
	bool BUTTON_R2_KEY_TAP;
	bool UP_KEY_DOWN;
	bool DOWN_KEY_DOWN;
	bool LEFT_KEY_DOWN;
	bool RIGHT_KEY_DOWN;
	bool BUTTON_X_KEY_DOWN;
	bool BUTTON_O_KEY_DOWN;
	bool BUTTON_T_KEY_DOWN;
	bool BUTTON_S_KEY_DOWN;
	bool BUTTON_L1_KEY_DOWN;
	bool BUTTON_L2_KEY_DOWN;
	bool BUTTON_R1_KEY_DOWN;
	bool BUTTON_R2_KEY_DOWN;
	bool HAPTIC_MOTOR;
} Controller;

static void loadModules(void);
static int waitPadReady(int port, int slot);
static int initializePad(int port, int slot);
void PadInitialize();
void UpdatePad();

#endif

#endif
