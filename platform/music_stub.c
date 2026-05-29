#include "musicManager.h"

void initMusicFormat(void)
{
}

void LoadMusic(BGM* bgm)
{
	if (!bgm)
	{
		return;
	}
	bgm->wav = NULL;
	bgm->ret = 0;
	bgm->err = 0;
}

void PlayMusic(BGM* bgm)
{
	if (!bgm || !bgm->wav)
	{
		return;
	}
}

void UnloadMusic(BGM* bgm)
{
	if (!bgm)
	{
		return;
	}
	if (bgm->wav)
	{
		fclose(bgm->wav);
		bgm->wav = NULL;
	}
}

char* PickMusic(int BGMTrack)
{
	(void)BGMTrack;
	static char empty[] = "";
	return empty;
}
