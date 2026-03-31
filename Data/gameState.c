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


void GameStart()
{
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(1));
	MikuSong.fileName = temp;
	
	LoadMusic(&MikuSong);

	VNSTEP = 0;

}

void GameUpdate()
{
	// This part here plays the music
		PlayMusic(&MikuSong);
		
		char tempy[4096];
		strcpy(tempy, relativePath);
		char tempy2[4096];
		strcpy(tempy2, relativePath);
		char tempy3[4096];
		strcpy(tempy3, relativePath);
		char tempy4[4096];
		strcpy(tempy4, relativePath);
		
		
			// Change Menu
		if(PlaystationGamePad.BUTTON_X_KEY_TAP)
		{
			VNSTEP++;
		}
		
		
		switch(VNSTEP)
		{
			case 0:
			VramClear();
			
			strcat(tempy3, NON);
			TextureLoadPng(&CharacterLeft,tempy3);
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy, GIRLBGIMAGE);
			TextureLoadPng(&GameBG,tempy);
			
			SetUpFont();
			VNSTEP++;
			break;
			
			case 1:
			VNTextName = "RNJ NJ";
			VNText = "RV RV[";
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, KING);
			TextureLoadPng(&CharacterLeft,tempy4);
			
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng(&CharacterLeft,tempy4);
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
			
			strcat(tempy3, NON);
			TextureLoadPng(&CharacterLeft,tempy3);
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy, GIRLBGIMAGE);
			TextureLoadPng(&GameBG,tempy);
			
			SetUpFont();
			VNSTEP++;
			break;
			
			case 13:
			VNTextName = "";
			VNText = "NJKGF FGKJLBHETN";
			break;
			
			case 14: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, LADYGRAY);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "KTLB UHTQ";
			VNText = "J UJCGJLB JY NFRJQ RHFCFDXBR";
			break;
			
			case 15: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, LADYGREEN);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "KTLB GEHGEH";
			VNText = "KTLB UHTQ[ DFIT GJDTLTYBT JNCNJQ";
			break;
			
			case 16: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, LADYGRAY);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "KTLB UHTQ";
			VNText = "YJ DTLM GHFDLF";
			break;
			
			case 17: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, MAN);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "UHFA HTL";
			VNText = "LFVS ECGJRJQNTCM";
			break;
			
			case 18: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "GHBYW";
			VNText = "JNTW[[[";
			break;
			
			case 19:
			
			break;
			
			case 20: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, KING);
			TextureLoadPng(&CharacterLeft,tempy4);
			
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, NON);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "";
			VNText = "PFK D IJRT";
			break;
			
			case 26: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng(&CharacterLeft,tempy4);
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, KING);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "RJHJKM";
			VNText = "CSYJR";
			break;
			
			case 30:
			VNText = "NS JNGHFDBIMCZ BCRFNM RJHJYE";
			break;
			
			case 31: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, NON);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "";
			VNText = "DCT EIKB GJ RJVYFNFV";
			break;
			
			//СЦЕНА 2
			
			case 32:
			VramClear();
			
			strcat(tempy3, NON);
			TextureLoadPng(&CharacterLeft,tempy3);
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy, HALLWAY1);
			TextureLoadPng(&GameBG,tempy);
			
			SetUpFont();
			VNSTEP++;
			
			VNTextName = "";
			VNText = "";
			break;
			
			case 33: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng(&CharacterLeft,tempy4);
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, NON);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "";
			VNText = "NER NER";
			break;
			
			case 39: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, PRINCESS);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "GHBYWTCCF";
			VNText = "RNJ NFV";
			break;
			
			case 40:
			VNText = "PLHFDCNDEQNT GHBYW";
			break;
			
			case 41: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng(&CharacterLeft,tempy4);
			VNTextName = "GHBYW";
			VNText = "";
			break;
			
			case 42:
			VNTextName = "GHBYW";
			VNText = "PLHFDNCDEQ CTDTHYFZ GHBYWTCCF";
			break;
			
			case 43: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, PRINCESS);
			TextureLoadPng(&CharacterLeft,tempy4);
			
			VNTextName = "GHBYWTCCF";
			VNText = "XTV Z VJUE DFV GJVJXM";
			break;
			
			case 44: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng(&CharacterLeft,tempy4);
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(&TextBG,tempy2);
			
			strcat(tempy4, PRINCESS);
			TextureLoadPng(&CharacterLeft,tempy4);
			
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			VNTextName = "GHBYW";
			VNText = "GHBYWTCCF[[[ UJDJHB VYT[[[";
			break;
			
			case 52: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCESS);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "GHBYWTCCF";
			VNText = "Z DBLTKF XTKJDTRF D VFCRT";
			break;
			
			case 53:
			VNText = "YT LEVFNM JY YT BP NDJTUJ PFDVRF";
			break;
			
			case 54: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCESS);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "GHBYWTCCF";
			VNText = "CGJRB YJRB GHBYW";
			break;
			
			case 59: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, NON);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "";
			VNText = "NER NER";
			break;
			
			case 63:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, LADYBLOND);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "KTLB DFQN";
			VNText = "GHBYW[[[";
			break;
			
			case 64: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			VNTextName = "GHBYW";
			VNText = "KTLB DFQN";
			break;
			
			case 65:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, LADYBLOND);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "KTLB DFQN";
			VNText = "CHFPE UJDJHBNM XNJ Z YBXTUJ YT DBLTKF";
			break;
			
			case 66: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			VNTextName = "GHBYW";
			VNText = "KFLYJ GJRF[[[";
			break;
			
			case 67:
			VNText = "GJQLE D LHEUJT RHSKJ[[[";
			break;
			
			//СЦЕНА 3
			
			case 68: 
			VramClear();
			
			strcat(tempy3, NON);
			TextureLoadPng( &CharacterLeft,tempy3);
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy, HALLWAY2);
			TextureLoadPng( &GameBG,tempy);
			
			SetUpFont();
			VNSTEP++;
			
			VNTextName = "";
			VNText = "";
			break;
			
			case 69: 
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			VNTextName = "GHBYW";
			VNText = "XNJ I[[[";
			break;
			
			case 70:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, NON);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "";
			VNText = "NER NER";
			break;
			
			case 71:
			VNText = "VTYZ YTN";
			break;
			
			case 72:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "GHBYW";
			VNText = "KFLYJ[[[";
			break;
			
			case 73:
			VNText = "RNJ BLTN";
			break;
			
			case 74:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, CLOWN);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "IEN";
			VNText = "PLHFDCNDEQNT GHBYW";
			break;
			
			case 75:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "GHBYW";
			VNText = "GHBDTN IEN";
			break;
			
			case 76:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, CLOWN);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "IEN";
			VNText = "GJXTVE DS NFRJQ UHECNYSQ";
			break;
			
			case 77:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "GHBYW";
			VNText = "E VTYZ ERHFKB RJHJYE";
			break;
			
			case 78:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, CLOWN);
			TextureLoadPng( &CharacterLeft,tempy4);
			
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
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "GHBYW";
			VNText = "[[[";
			break;
			
			case 82:
			VNText = "NJXYJ[[[";
			break;
			
			case 83:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, KING);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "RJHJKM";
			VNText = "JQ[[[";
			break;
			
			//СЦЕНА 4
			
			case 84: 
			VramClear();
			
			strcat(tempy3, NON);
			TextureLoadPng( &CharacterLeft,tempy3);
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy, HALL3);
			TextureLoadPng( &GameBG,tempy);
			
			SetUpFont();
			VNSTEP++;
			
			VNTextName = "";
			VNText = "";
			break;
			
			case 85:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, KING);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "RJHJKM";
			VNText = "BPDBYBNT VTYZ[[[";
			break;
			
			case 86:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, NON);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "DCT";
			VNText = "GHJOFTV";
			break;
			
			case 87:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, KING);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "RJHJKM";
			VNText = "GHBYW NTGTHM RJHJKM";
			break;
			
			case 88:
			VramClear();
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng( &TextBG,tempy2);
			
			strcat(tempy4, PRINCE);
			TextureLoadPng( &CharacterLeft,tempy4);
			
			VNTextName = "GHBYW";
			VNText = "Z RJHJKM";
			break;
			
			/*
			case 86:
			VramClear(gsGlobal);
			
			strcat(tempy2, TEXTBC);
			TextureLoadPng(gsGlobal, &TextBG,tempy2);
			
			strcat(tempy4, NON);
			TextureLoadPng(gsGlobal, &CharacterLeft,tempy4);
			
			VNTextName = "";
			VNText = "RJYTW";
			break;
			
			//case 8:
			//VramClear(gsGlobal);
			//strcat(tempy, HALL2);
			//TextureLoadPng(gsGlobal, &GameBG,tempy);
			//SetUpFont(gsGlobal);
			//VNSTEP++;
			//break;
			
			//case 8:

			//break;
			
			//case 9:
			//VramClear(gsGlobal);
			//strcat(tempy, HALL3);
			//TextureLoadPng(gsGlobal, &GameBG,tempy);
			//SetUpFont(gsGlobal);
			//VNSTEP++;
			//break;
			
			//case 10:

			//break;
			
			//case 11:
			//VramClear(gsGlobal);
			//strcat(tempy, HALLWAY1);
			//TextureLoadPng(gsGlobal, &GameBG,tempy);
			//SetUpFont(gsGlobal);
			//VNSTEP++;
			//break;
			
			//case 12:
			//break;
			
			//case 13:
			//VramClear(gsGlobal);
			//strcat(tempy, HALLWAY2);
			//TextureLoadPng(gsGlobal, &GameBG,tempy);
			//SetUpFont(gsGlobal);
			//VNSTEP++;
			//break;*/
		
		}
		
}

void GameDraw( u64 colour)
{
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

