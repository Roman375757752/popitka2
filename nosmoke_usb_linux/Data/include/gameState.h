#ifndef GAME_STATE
#define GAME_STATE

#include "stateManager.h"
#include <stdbool.h>

void GameStart();
void GameUpdate();
void GameDraw(u64 colour);
void GameEnd();

extern StateManager GameState;

#endif
