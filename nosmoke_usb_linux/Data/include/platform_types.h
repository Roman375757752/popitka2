#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*
 * Типы и константы цвета для Linux/SDL-сборки (NOSMOKE_PLATFORM_SDL).
 * На PS2 используются gsKit/tamtypes.
 */
#include <stdint.h>

typedef uint64_t u64;

typedef struct GSTEXTURE
{
	void* impl; /* SDL_Texture* */
	int Width;
	int Height;
} GSTEXTURE;

/* Упаковка RGBA в u64 (достаточно для тинта и ClearScreen в SDL). */
#define GS_SETREG_RGBAQ(r, g, b, a, q)                                                      \
	((u64)(uint8_t)(r) | ((u64)(uint8_t)(g) << 8) | ((u64)(uint8_t)(b) << 16)               \
	 | ((u64)(uint8_t)(a) << 24) | ((u64)(uint8_t)(q) << 32))

/* Intro вызывает SetPrimAlpha(GS_SETREG_ALPHA(...)); на SDL достаточно заглушки. */
#define GS_SETREG_ALPHA(a0, a1, a2, a3, a4) ((u64)0)

#endif
