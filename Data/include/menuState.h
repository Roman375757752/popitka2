#ifndef MENU_STATE
#define MENU_STATE

#include "stateManager.h"

void MenuStart();
void MenuUpdate();
void MenuDraw(u64 colour);
void MenuEnd();

extern StateManager MenuState;

#endif
