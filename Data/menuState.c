/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2					             */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                              */
/*                                                                           */
/*  Содержимое файла	: Стадия главного меню		                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: menuState.c	                                     */
/*                                                                           */
/*****************************************************************************/


#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/musicManager.h"
#include "include/textToGraphics.h"
#include "include/pad.h"
#include "include/renderCompat.h"

#include <stdio.h>
#include <string.h>

static char menu_music_path[4096];

/****** User External Files ********/
#include "extern/menuState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/menuState.def"

GSTEXTURE TitleImage; 

BGM MenuMusicy;

int selectedOption; // 0 - New Game 1 - Load Game 2- ShutDown game

int idleTimer;

void MenuStart()
{
	idleTimer = 0; // Once the Idle timer reaches 6000 then restart the screen to prevent screen burn on CRT
	initMusicFormat();
	
	strncpy(menu_music_path, relativePath, sizeof(menu_music_path) - 1);
	menu_music_path[sizeof(menu_music_path) - 1] = '\0';
	strncat(menu_music_path, PickMusic(1), sizeof(menu_music_path) - strlen(menu_music_path) - 1);
	MenuMusicy.fileName = menu_music_path;
	MenuMusicy.wav = NULL;

	LoadMusic(&MenuMusicy);

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, TITLEIMAGEPATH);
	TextureLoadPng(&TitleImage,tempy);

	SetUpFontIfNeeded();
	
	selectedOption = 0;
}

void MenuUpdate()
{
	// This part here plays the music
	PlayMusic(&MenuMusicy);
	idleTimer++; // Once the Idle timer reaches 6000 then restart the screen to prevent screen burn on CRT
	// This is to prevent the screen burn. We force the game to reset
	if(idleTimer > 12000)
	{
		idleTimer = 0;
		StateMachineChange(&GameMachineState, &IntroState);
	}
	
	// Change Menu
	if(PlaystationGamePad.UP_KEY_TAP && selectedOption != 0)
    {
    	selectedOption--;
    }
    else if(PlaystationGamePad.DOWN_KEY_TAP && selectedOption != 3)
    {
    	selectedOption++;
    }

	if(PlaystationGamePad.START_KEY_TAP || PlaystationGamePad.BUTTON_X_KEY_TAP)
    	{	
		switch(selectedOption)
		{
			// Start New Game
			case 0:
				StateMachineChange(&GameMachineState, &GameState);
			break;

			case 1: 
	   			// Open Load screen
			break;

			case 2:
	   			// settings
			break;
			
			case 3:
				// Shut Down
				GameRunning = 0;
				UnloadMusic(&MenuMusicy);
			break;
			
			default:
			
		}
	}

}

void MenuDraw( u64 colour)
{

	/*int i = (4096 - gsGlobal->CurrentPointer/1024);
	printf("VRAM: %d\n", i);*/
	
	DrawSpriteTexture(&TitleImage,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						TitleImage.Width * 2, // X2
						TitleImage.Height * 2, // Y2
						TitleImage.Width * 2, // U2
						TitleImage.Height * 2, // V2
						2,
						colour);				



	switch(selectedOption)
	{
		// Start New Game
		case 0:
			DrawText(120, 360, "YJDFZ BUHF",2, colour,1);
			DrawText(120, 385, "GHJLJK:BNM",2, colour,0);
			DrawText(120, 410, "YFCNHJQRB",2, colour,0);
			DrawText(120, 435, "PFDTHIBNM BUHE",2, colour,0);
		break;
		case 1: 
	  		DrawText(120, 360, "YJDFZ BUHF",2, colour,0);
			DrawText(120, 385, "GHJLJK:BNM",2, colour,1);
			DrawText(120, 410, "YFCNHJQRB",2, colour,0);
			DrawText(120, 435, "PFDTHIBNM BUHE",2, colour,0);
		break;
		case 2:
	   		DrawText(120, 360, "YJDFZ BUHF",2, colour,0);
			DrawText(120, 385, "GHJLJK:BNM",2, colour,0);
			DrawText(120, 410, "YFCNHJQRB",2, colour,1);
			DrawText(120, 435, "PFDTHIBNM BUHE",2, colour,0);
		break;
		case 3:
			DrawText(120, 360, "YJDFZ BUHF",2, colour,0);
			DrawText(120, 385, "GHJLJK:BNM",2, colour,0);
			DrawText(120, 410, "YFCNHJQRB",2, colour,0);
			DrawText(120, 435, "PFDTHIBNM BUHE",2, colour,1);
		break;
		default:
	}
	
	//ClearScreen(GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00));
}

void MenuEnd()
{
	fprintf(stderr, "[nosmoke] MenuEnd\n");
	fflush(stderr);
	VramClear();
	UnloadMusic(&MenuMusicy);
	fprintf(stderr, "[nosmoke] MenuEnd done\n");
	fflush(stderr);
}

StateManager MenuState =
{
	MenuStart,
	MenuUpdate,
	MenuDraw,
	MenuEnd
};

