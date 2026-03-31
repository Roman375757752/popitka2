#ifndef TEXTTOGRAPHICS
#define TEXTTOGRAPHICS

#ifdef NOSMOKE_PLATFORM_SDL
#include <stdlib.h>
#include "platform_types.h"
#else
#include <unistd.h>
#include <malloc.h>

#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>
#include <iopcontrol.h>
#include <sbv_patches.h>
#endif

typedef struct
{
	int x;
	int y;
	int width;
	int height;
} Font;

Font setUpFontStruct(int x, int y, int width, int height);

void SetUpFont();

void DrawText(int xpos, int ypos, char* Text, int scale, u64 colour, int selected);

void DrawAnimatedText(int xpos, int ypos, char* Text, int type);

void textSelfDestruct();

#endif
