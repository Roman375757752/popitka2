#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

#include <SDL2/SDL.h>

#include "introState.h"
#include "menuState.h"
#include "gameState.h"
#include "overState.h"
#include "pad.h"
#include "renderCompat.h"
#include "stateManager.h"

char relativePath[512];

int GameRunning;

StateMachine GameMachineState;

static char* dirname_portable(char* path)
{
	static char buffer[512];
	size_t len;
	if (path == NULL)
	{
		strcpy(buffer, ".");
		return buffer;
	}
	len = strlen(path);
	assert(len < sizeof(buffer));
	if (len != 0 && (path[len - 1] == '/' || path[len - 1] == '\\'))
	{
		--len;
	}
	while (len != 0 && path[len - 1] != '/' && path[len - 1] != '\\')
	{
		--len;
	}
	if (len == 0)
	{
		strcpy(buffer, ".");
	}
	else if (len == 1)
	{
		if (path[0] == '/' || path[0] == '\\')
		{
			strcpy(buffer, "/");
		}
		else
		{
			strcpy(buffer, ".");
		}
	}
	else
	{
		memcpy(buffer, path, len - 1);
		buffer[len - 1] = '\0';
	}
	return buffer;
}

int main(int argc, char* argv[])
{
	(void)argc;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
	    "nosmoke",
	    SDL_WINDOWPOS_CENTERED,
	    SDL_WINDOWPOS_CENTERED,
	    640,
	    448,
	    0);
	if (!window)
	{
		fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
		if (!renderer)
		{
			fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
			SDL_DestroyWindow(window);
			SDL_Quit();
			return 1;
		}
	}

	RenderBackendInit(renderer);

	/* Ресурсы ищем от текущей рабочей папки (откуда запустили в терминале), не от каталога exe. */
#ifdef _WIN32
	if (_getcwd(relativePath, (int)sizeof(relativePath)) == NULL)
#else
	if (getcwd(relativePath, sizeof(relativePath)) == NULL)
#endif
	{
		strncpy(relativePath, dirname_portable(argv[0]), sizeof(relativePath) - 1);
		relativePath[sizeof(relativePath) - 1] = '\0';
	}

	fprintf(stderr, "[nosmoke] cwd/resource root: %s\n", relativePath);
	fprintf(stderr, "[nosmoke] ожидаются папки вроде Graphics/, Audio/ рядом с этим путём\n");

	PadInitialize();

	u64 black = GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0xFF, 0x00);
	u64 texCol = GS_SETREG_RGBAQ(0x80, 0x80, 0x80, 0x80, 0x00);

	ClearScreen(black);
	GameRunning = 1;
	StateMachineStart(&GameMachineState, &IntroState);

	while (GameRunning)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				GameRunning = 0;
			}
		}

		UpdatePad();
		StateMachineUpdate(&GameMachineState);
		StateMachineDraw(&GameMachineState, texCol);
		SDL_RenderPresent(renderer);
	}

	RenderBackendShutdown();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
