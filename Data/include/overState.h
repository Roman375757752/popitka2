#ifndef OVER_STATE
#define OVER_STATE

#include "stateManager.h"

void OverStart();
void OverUpdate();
void OverDraw(u64 colour);
void OverEnd();

extern StateManager OverState;

#endif
