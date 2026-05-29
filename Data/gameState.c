/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2					             */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                              */
/*                                                                           */
/*  Содержимое файла	: Стадия игровой детельности                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: gameState.c	                                     */
/*                                                                           */
/*****************************************************************************/

#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"
#include "include/textToGraphics.h"
#include "include/renderCompat.h"

#include <stdio.h>
#include <string.h>

extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/gameState.def"

GSTEXTURE GameBG;
GSTEXTURE TextBG;
GSTEXTURE CharacterLeft;
GSTEXTURE CharacterRight;
BGM MikuSong;

int VNSTEP;
char* VNTextName;
char* VNText;

static char game_music_path[4096];
static char game_path_a[4096];
static char game_path_b[4096];
static char game_path_c[4096];
static char game_path_d[4096];
static int game_input_grace_frames;

static void game_join_path(char* out, size_t outsz, const char* suffix)
{
	strncpy(out, relativePath, outsz - 1);
	out[outsz - 1] = '\0';
	strncat(out, suffix, outsz - strlen(out) - 1);
}

static void GameLoadOpeningScene(void)
{
	game_join_path(game_path_c, sizeof(game_path_c), NON);
	TextureLoadPng(&CharacterLeft, game_path_c);
	if (!CharacterLeft.impl)
	{
		fprintf(stderr, "[nosmoke] нет файла: %s\n", game_path_c);
	}

	game_join_path(game_path_b, sizeof(game_path_b), TEXTBC);
	TextureLoadPng(&TextBG, game_path_b);
	if (!TextBG.impl)
	{
		fprintf(stderr, "[nosmoke] нет файла: %s\n", game_path_b);
	}

	game_join_path(game_path_a, sizeof(game_path_a), GIRLBGIMAGE);
	TextureLoadPng(&GameBG, game_path_a);
	if (!GameBG.impl)
	{
		fprintf(stderr, "[nosmoke] нет файла: %s\n", game_path_a);
	}

	SetUpFontIfNeeded();
	VNTextName = "RNJ NJ";
	VNText = "RV RV[";
}

void GameStart()
{
	fprintf(stderr, "[nosmoke] GameStart (cwd=%s)\n", relativePath);
	fflush(stderr);

	strcpy(game_music_path, relativePath);
	strcat(game_music_path, PickMusic(1));
	MikuSong.fileName = game_music_path;
	MikuSong.wav = NULL;
	LoadMusic(&MikuSong);

	VNTextName = "";
	VNText = "";

	fprintf(stderr, "[nosmoke] GameStart: loading scene...\n");
	fflush(stderr);
	GameLoadOpeningScene();

	VNSTEP = 1;
	game_input_grace_frames = 3;

	fprintf(stderr, "[nosmoke] GameStart OK (bg %dx%d)\n", GameBG.Width, GameBG.Height);
	fflush(stderr);
}

void GameUpdate()
{
	PlayMusic(&MikuSong);

	strcpy(game_path_a, relativePath);
	strcpy(game_path_b, relativePath);
	strcpy(game_path_c, relativePath);
	strcpy(game_path_d, relativePath);

	if (game_input_grace_frames > 0)
	{
		game_input_grace_frames--;
	}
	else if (VNSTEP > 0
	         && (PlaystationGamePad.BUTTON_X_KEY_TAP || PlaystationGamePad.START_KEY_TAP
	             || PlaystationGamePad.BUTTON_O_KEY_TAP))
	{
		VNSTEP++;
	}

	switch (VNSTEP)
	{
			case 0:
			GameLoadOpeningScene();
			VNSTEP = 1;
			break;

			case 1:
			break;
			
			case 2:
			VNTextName = "";
			VNText = "DTCM FKMYSQ PFK GHBNB";
			break;
			
			case 3:
			VNTextName = "RNJ NJ";
			VNText = "BNFR";
			break;
			
			case 4: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, KING);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "RJHJKM";
			VNText = "PHFDCNDEQNT LHEPMZ!";
			break;
			
			case 5:
			VNText = "CTUJLYZ WTHTVJYBZ RJHJYFWBB";
			break;
			
			case 6:
			VNText = "CTUJLYZ WTHTVJYBZ RJHJYFWBB";
			break;
			
			case 7:
			VNText = "B Z JXE GHTLCNFDBNM DFV";
			break;
			
			case 8:
			VNText = "CDJTUJ CSYF";
			break;
			
			case 9: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng(&CharacterLeft,game_path_d);
			break;
			
			case 10:
			VNTextName = "GHBYW";
			VNText = "TTVVV[[[ PLHFDCNDEQNT[[[";
			break;
			
			case 11:
			VNText = "Z KEYYSQ GHBYW[[[";
			break;
			
			case 12:
			VramClear();
			
			strcat(game_path_c, NON);
			TextureLoadPng(&CharacterLeft, game_path_c);

			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG, game_path_b);

			strcat(game_path_a, GIRLBGIMAGE);
			TextureLoadPng(&GameBG, game_path_a);
			
			SetUpFontIfNeeded();
			VNSTEP++;
			break;
			
			case 13:
			VNTextName = "";
			VNText = "NJKGF FGKJLBHETN";
			break;
			
			case 14: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, LADYGRAY);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "KTLB UHTQ";
			VNText = "J UJCGJLB JY NFRJQ RHFCFDXBR";
			break;
			
			case 15: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, LADYGREEN);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "KTLB GEHGEH";
			VNText = "KTLB UHTQ[ DFIT GJDTLTYBT JNCNJQ";
			break;
			
			case 16: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, LADYGRAY);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "KTLB UHTQ";
			VNText = "YJ DTLM GHFDLF";
			break;
			
			case 17: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, MAN);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "UHFA HTL";
			VNText = "LFVS ECGJRJQNTCM";
			break;
			
			case 18: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "GHBYW";
			VNText = "JNTW[[[";
			break;
			
			case 19:
			
			break;
			
			case 20: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, KING);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "RJHJKM";
			VNText = "LF";
			break;
			
			case 21:
			VNText = "CTQXFC Z DJPMVE RJHJYE[[[ B[[[";
			break;
			
			case 22:
			VNText = "CTREYLJXRE[[[";
			break;
			
			case 23:
			VNText = "CTREYLJXRB VFKJ[[[";
			break;
			
			case 24:
			VNText = "RJHJYF GHJGFKF";
			break;
			
			case 25: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, NON);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "";
			VNText = "PFK D IJRT";
			break;
			
			case 26: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng(&CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "";
			break;
			
			case 27:
			VNTextName = "GHBYW";
			VNText = "JNTW[[[";
			break;

			case 28:
			VNText = "XNJ NTGTHM LTKFNM [[[";
			break;
			
			case 29: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, KING);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "RJHJKM";
			VNText = "CSYJR";
			break;
			
			case 30:
			VNText = "NS JNGHFDBIMCZ BCRFNM RJHJYE";
			break;
			
			case 31: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, NON);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "";
			VNText = "DCT EIKB GJ RJVYFNFV";
			break;
			
			//СЦЕНА 2
			
			case 32:
			VramClear();
			
			strcat(game_path_c, NON);
			TextureLoadPng(&CharacterLeft,game_path_c);
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_a, HALLWAY1);
			TextureLoadPng(&GameBG,game_path_a);
			
			SetUpFontIfNeeded();
			VNSTEP++;
			
			VNTextName = "";
			VNText = "";
			break;
			
			case 33: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng(&CharacterLeft,game_path_d);
			break;
			
			case 34:
			VNTextName = "GHBYW";
			VNText = "UHJVRBQ NZU YJCJV";
			break;
			
			case 35:
			VNText = "BNFR[[[";
			break;
			
			case 36:
			VNText = "VYT YFLJ JGHJCBNM UJCNTQ[[[";
			break;
			
			case 37:
			VNText = "YTKJDRJ[[[";
			break;
			
			case 38:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, NON);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "";
			VNText = "NER NER";
			break;
			
			case 39: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, PRINCESS);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "GHBYWTCCF";
			VNText = "RNJ NFV";
			break;
			
			case 40:
			VNText = "PLHFDCNDEQNT GHBYW";
			break;
			
			case 41: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng(&CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "";
			break;
			
			case 42:
			VNTextName = "GHBYW";
			VNText = "PLHFDNCDEQ CTDTHYFZ GHBYWTCCF";
			break;
			
			case 43: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, PRINCESS);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "GHBYWTCCF";
			VNText = "XTV Z VJUE DFV GJVJXM";
			break;
			
			case 44: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng(&CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "";
			break;
			
			case 45:
			VNTextName = "GHBYW";
			VNText = "VJZ RJHJYF ERHFLTYF[[[";
			break;
			
			case 46:
			VNText = "Z TT BOE[[[";
			break;
			
			case 47: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(&TextBG,game_path_b);
			
			strcat(game_path_d, PRINCESS);
			TextureLoadPng(&CharacterLeft,game_path_d);
			
			VNTextName = "GHBYWTCCF";
			VNText = "GTXFKMYFZ YJDJCNM";
			break;
			
			case 48:
			VNText = "YJ[[[";
			break;
			
			case 49:
			VNText = "YT LEVFQ XNJ CVJUE DFV GJVJXM";
			break;
			
			/*case 50:
			VNText = "JLYFRJ[[[";
			break;*/
			
			case 50:
			VNText = "Z DBLTKF JLYE CNHFYYJCNM";
			break;
			
			case 51: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "GHBYWTCCF[[[ UJDJHB VYT[[[";
			break;
			
			case 52: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCESS);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "GHBYWTCCF";
			VNText = "Z DBLTKF XTKJDTRF D VFCRT";
			break;
			
			case 53:
			VNText = "YT LEVFNM JY YT BP NDJTUJ PFDVRF";
			break;
			
			case 54: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "JQ JQ";
			break;
			
			case 55:
			VNText = "BYAJHVFWBZ YT ENTIFTN";
			break;
			
			case 56:
			VNText = "KFLYJ CGC GHBYWTCCF";
			break;
			
			case 57:
			VNText = "CRJRB YJRB";
			break;
			
			case 58: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCESS);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "GHBYWTCCF";
			VNText = "CGJRB YJRB GHBYW";
			break;
			
			case 59: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "[[[";
			break;
			
			case 60:
			VNText = "VYT UHECNYJ";
			break;
			
			case 61:
			VNText = "RJHJYE LTQCNDBNTKMYJ ERHFKB";
			break;
			
			case 62:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, NON);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "";
			VNText = "NER NER";
			break;
			
			case 63:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, LADYBLOND);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "KTLB DFQN";
			VNText = "GHBYW[[[";
			break;
			
			case 64: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "KTLB DFQN";
			break;
			
			case 65:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, LADYBLOND);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "KTLB DFQN";
			VNText = "CHFPE UJDJHBNM XNJ Z YBXTUJ YT DBLTKF";
			break;
			
			case 66: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "KFLYJ GJRF[[[";
			break;
			
			case 67:
			VNText = "GJQLE D LHEUJT RHSKJ[[[";
			break;
			
			//СЦЕНА 3
			
			case 68: 
			VramClear();
			
			strcat(game_path_c, NON);
			TextureLoadPng( &CharacterLeft,game_path_c);
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_a, HALLWAY2);
			TextureLoadPng( &GameBG,game_path_a);
			
			SetUpFontIfNeeded();
			VNSTEP++;
			
			VNTextName = "";
			VNText = "";
			break;
			
			case 69: 
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			VNTextName = "GHBYW";
			VNText = "XNJ I[[[";
			break;
			
			case 70:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, NON);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "";
			VNText = "NER NER";
			break;
			
			case 71:
			VNText = "VTYZ YTN";
			break;
			
			case 72:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "GHBYW";
			VNText = "KFLYJ[[[";
			break;
			
			case 73:
			VNText = "RNJ BLTN";
			break;
			
			case 74:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, CLOWN);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "IEN";
			VNText = "PLHFDCNDEQNT GHBYW";
			break;
			
			case 75:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "GHBYW";
			VNText = "GHBDTN IEN";
			break;
			
			case 76:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, CLOWN);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "IEN";
			VNText = "GJXTVE DS NFRJQ UHECNYSQ";
			break;
			
			case 77:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "GHBYW";
			VNText = "E VTYZ ERHFKB RJHJYE";
			break;
			
			case 78:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, CLOWN);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "IEN";
			VNText = "YFYFYFYFYFYYFYFYF";
			break;
			
			case 79:
			VNText = "YE YFCVTIBKB";
			break;
			
			case 80:
			VNText = "JYF YF UJKJDT RJHJKZ";
			break;
			
			case 81:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "GHBYW";
			VNText = "[[[";
			break;
			
			case 82:
			VNText = "NJXYJ[[[";
			break;
			
			case 83:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, KING);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "RJHJKM";
			VNText = "JQ[[[";
			break;
			
			//СЦЕНА 4
			
			case 84: 
			VramClear();
			
			strcat(game_path_c, NON);
			TextureLoadPng( &CharacterLeft,game_path_c);
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_a, HALL3);
			TextureLoadPng( &GameBG,game_path_a);
			
			SetUpFontIfNeeded();
			VNSTEP++;
			
			VNTextName = "";
			VNText = "";
			break;
			
			case 85:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, KING);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "RJHJKM";
			VNText = "BPDBYBNT VTYZ[[[";
			break;
			
			case 86:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, NON);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "DCT";
			VNText = "GHJOFTV";
			break;
			
			case 87:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, KING);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "RJHJKM";
			VNText = "GHBYW NTGTHM RJHJKM";
			break;
			
			case 88:
			VramClear();
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng( &TextBG,game_path_b);
			
			strcat(game_path_d, PRINCE);
			TextureLoadPng( &CharacterLeft,game_path_d);
			
			VNTextName = "GHBYW";
			VNText = "Z RJHJKM";
			break;
			
			/*
			case 86:
			VramClear(gsGlobal);
			
			strcat(game_path_b, TEXTBC);
			TextureLoadPng(gsGlobal, &TextBG,game_path_b);
			
			strcat(game_path_d, NON);
			TextureLoadPng(gsGlobal, &CharacterLeft,game_path_d);
			
			VNTextName = "";
			VNText = "RJYTW";
			break;
			
			//case 8:
			//VramClear(gsGlobal);
			//strcat(game_path_a, HALL2);
			//TextureLoadPng(gsGlobal, &GameBG,game_path_a);
			//SetUpFont(gsGlobal);
			//VNSTEP++;
			//break;
			
			//case 8:

			//break;
			
			//case 9:
			//VramClear(gsGlobal);
			//strcat(game_path_a, HALL3);
			//TextureLoadPng(gsGlobal, &GameBG,game_path_a);
			//SetUpFont(gsGlobal);
			//VNSTEP++;
			//break;
			
			//case 10:

			//break;
			
			//case 11:
			//VramClear(gsGlobal);
			//strcat(game_path_a, HALLWAY1);
			//TextureLoadPng(gsGlobal, &GameBG,game_path_a);
			//SetUpFont(gsGlobal);
			//VNSTEP++;
			//break;
			
			//case 12:
			//break;
			
			//case 13:
			//VramClear(gsGlobal);
			//strcat(game_path_a, HALLWAY2);
			//TextureLoadPng(gsGlobal, &GameBG,game_path_a);
			//SetUpFont(gsGlobal);
			//VNSTEP++;
			//break;*/
		
		}
		
}

void GameDraw( u64 colour)
{
	if (!GameBG.impl && !TextBG.impl)
	{
		fprintf(stderr, "[nosmoke] нет графики — запускайте из папки с Graphics/\n");
		return;
	}

	DrawSpriteTexture( &GameBG,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						GameBG.Width * 2, // X2
						GameBG.Height * 2, // Y2
						GameBG.Width * 2, // U2
						GameBG.Height * 2, // V2
						2,
						colour);	
						
	DrawSpriteTexture( &TextBG,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						TextBG.Width * 2, // X2
						TextBG.Height * 2, // Y2
						TextBG.Width * 2, // U2
						TextBG.Height * 2, // V2
						2,
						colour);	
						
	DrawSpriteTexture( &CharacterLeft, 40,  // X1
						183,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						176,
						315,
						CharacterLeft.Width * 2, // U2
						CharacterLeft.Height * 2, // V2
						2,
						colour);	
	
	DrawSpriteTexture( &CharacterRight, 468,  // X1
						183,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						600,
						315,
						CharacterRight.Width * 2, // U2
						CharacterRight.Height * 2, // V2
						2,
						colour);							
						
	DrawText(40, 325, VNTextName,2, colour,0);
	DrawText(40, 370, VNText,2, colour,1);
	
	
}

void GameEnd()
{

}

StateManager GameState =
{
	GameStart,
	GameUpdate,
	GameDraw,
	GameEnd
};

