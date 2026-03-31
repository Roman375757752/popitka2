#include "renderCompat.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

static SDL_Renderer* g_renderer;

void RenderBackendInit(struct SDL_Renderer* renderer)
{
	g_renderer = renderer;
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, "SDL_image: %s\n", IMG_GetError());
	}
}

void RenderBackendShutdown(void)
{
	IMG_Quit();
	g_renderer = NULL;
}

void TextureLoadPng(GSTEXTURE* texture, const char* path)
{
	if (!g_renderer || !texture)
	{
		return;
	}
	if (texture->impl)
	{
		SDL_DestroyTexture((SDL_Texture*)texture->impl);
		texture->impl = NULL;
	}

	SDL_Texture* t = IMG_LoadTexture(g_renderer, path);
	if (!t)
	{
		fprintf(stderr, "TextureLoadPng %s: %s\n", path, IMG_GetError());
		texture->Width = 0;
		texture->Height = 0;
		return;
	}

	int w = 0;
	int h = 0;
	SDL_QueryTexture(t, NULL, NULL, &w, &h);
	texture->Width = w;
	texture->Height = h;
	texture->impl = t;
}

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
                       u64 colour)
{
	(void)z;
	if (!g_renderer || !texture || !texture->impl)
	{
		return;
	}

	SDL_Texture* t = (SDL_Texture*)texture->impl;

	SDL_Rect src;
	src.x = (int)u1;
	src.y = (int)v1;
	src.w = u2 - src.x;
	src.h = v2 - src.y;
	if (src.w <= 0 || src.h <= 0)
	{
		src.x = 0;
		src.y = 0;
		src.w = texture->Width;
		src.h = texture->Height;
	}

	SDL_Rect dst;
	dst.x = x1;
	dst.y = y1;
	dst.w = x2 - x1;
	dst.h = y2 - y1;

	{
		uint8_t r = (uint8_t)(colour & 0xFFu);
		uint8_t g = (uint8_t)((colour >> 8) & 0xFFu);
		uint8_t b = (uint8_t)((colour >> 16) & 0xFFu);
		uint8_t a = (uint8_t)((colour >> 24) & 0xFFu);
		SDL_SetTextureColorMod(t, r, g, b);
		SDL_SetTextureAlphaMod(t, a);
		SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	}

	SDL_RenderCopy(g_renderer, t, &src, &dst);
	SDL_SetTextureColorMod(t, 255, 255, 255);
	SDL_SetTextureAlphaMod(t, 255);
}

void SetPrimAlpha(u64 alpha, int perPixel)
{
	(void)alpha;
	(void)perPixel;
}

void ClearScreen(u64 colour)
{
	if (!g_renderer)
	{
		return;
	}
	uint8_t r = (uint8_t)(colour & 0xFFu);
	uint8_t g = (uint8_t)((colour >> 8) & 0xFFu);
	uint8_t b = (uint8_t)((colour >> 16) & 0xFFu);
	uint8_t a = (uint8_t)((colour >> 24) & 0xFFu);
	SDL_SetRenderDrawColor(g_renderer, r, g, b, a);
	SDL_RenderClear(g_renderer);
}

void VramClear(void)
{
	/* На PS2 очищает VRAM; на SDL текстуры освобождаются при повторной загрузке. */
}
