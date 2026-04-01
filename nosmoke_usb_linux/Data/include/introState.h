#ifndef INTRO_STATE
#define INTRO_STATE

#include "stateManager.h"
#include <stdbool.h>

void IntroStart();
void IntroUpdate();
void IntroDraw(u64 colour);
void IntroEnd();

extern StateManager IntroState;

#endif
