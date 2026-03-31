#ifndef RENDER_COMPAT
#define RENDER_COMPAT

#ifdef NOSMOKE_PLATFORM_SDL

#include "platform_types.h"

struct SDL_Renderer;

void RenderBackendInit(struct SDL_Renderer* renderer);
void RenderBackendShutdown(void);

void TextureLoadPng(GSTEXTURE* texture, const char* path);
void DrawSpriteTexture(GSTEXTURE* texture,
                       int x1,
                       int y1,
                       float u1,
                       float v1,
                       int x2,
                       int y2,
                       int u2,
                       int v2,
                       int z,
                       u64 colour);
void SetPrimAlpha(u64 alpha, int perPixel);
void ClearScreen(u64 colour);
void VramClear(void);

#else

#include <gsKit.h>
#include <gsToolkit.h>

static inline void TextureLoadPng(GSTEXTURE* texture, const char* path)
{
	gsKit_texture_png(gsGlobal, texture, (char*)path);
}

static inline void DrawSpriteTexture(GSTEXTURE* texture,
                                     int x1,
                                     int y1,
                                     float u1,
                                     float v1,
                                     int x2,
                                     int y2,
                                     int u2,
                                     int v2,
                                     int z,
                                     u64 colour)
{
	gsKit_prim_sprite_texture(gsGlobal, texture, x1, y1, u1, v1, x2, y2, u2, v2, z, colour);
}

static inline void SetPrimAlpha(u64 alpha, int perPixel)
{
	gsKit_set_primalpha(gsGlobal, alpha, perPixel);
}

static inline void ClearScreen(u64 colour)
{
	gsKit_clear(gsGlobal, colour);
}

static inline void VramClear(void)
{
	gsKit_vram_clear(gsGlobal);
}

#endif

#endif
