/*****************************************************************************/
/*  Автор         		 : Дракончик			                             */
/*  Приставка     		 : Sony PlayStation 2					             */
/*  ОС			  		 : OSDSYS											 */
/*  Язык	      		 : GNU C                                             */
/*                                                                           */
/*  Содержимое файла	 : Рисует шрифт текста на экран		                 */
/*  Атрибут файла		 : SOURCE                                            */
/*  Имя файла     		 : textToGraphics.c	                                 */
/*  Автор шрифта RUS.png : Шадак/Shadak						                 */
/*                                                                           */
/*****************************************************************************/

#include <string.h>

#include "include/textToGraphics.h"
#include "include/renderCompat.h"


/****** User Define Files ***********/
#include "define/textToGraphics.def"

Font fontENG[128];

Font fontRUS[128];

u64 fontColour;

extern char relativePath[];

// Graphics Synthesizer Texture structs
GSTEXTURE fontRussianGold, fontRussian;

Font setUpFontStruct(int x, int y, int width, int height)
{
	Font fonty;
	fonty.x = x;
	fonty.y = y;
	fonty.width = width;
	fonty.height = height;
	
	return fonty;
}


void SetUpFont()
{

	fontColour = GS_SETREG_RGBAQ(0x80,0x80,0x80,0x80,0x00);

	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, RUSSIANFONTPATH);

	TextureLoadPng(&fontRussian, temp);
	
	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, RUSSIANGOLDFONTPATH);

	TextureLoadPng(&fontRussianGold, tempy);

	// This part here cuts the font in small pieces 
	int shift = 0;
	for(int i = 48; i < 58; i++)
	{
		fontRUS[i] = setUpFontStruct(shift*9, 0, 9, 13);
		
		shift++;
	}
	
	shift = 0;

	for(int i = 65; i < 75; i++)
	{
		fontRUS[i] = setUpFontStruct(shift*9, 13, 9, 13);
		shift++;
	}
	
	shift = 0;
		    
	for(int i = 75; i < 85; i++)
	{
		fontRUS[i] = setUpFontStruct(shift*9, 26, 9, 13);
		shift++;
	}
		    
	shift = 0;
		    
	for(int i = 85; i < 92; i++)
	{
		fontRUS[i] = setUpFontStruct(shift*9, 39, 9, 13);
		shift++;
	}
	
	fontRUS[39] = setUpFontStruct(6*9, 52, 9, 13);
	fontRUS[40] = setUpFontStruct(9*9, 52, 9, 13);
	fontRUS[41] = setUpFontStruct(0*9, 65, 9, 13);
	fontRUS[58] = setUpFontStruct(4*9, 65, 9, 13);
	fontRUS[60] = setUpFontStruct(6*9, 65, 9, 13);
	fontRUS[62] = setUpFontStruct(7*9, 65, 9, 13);
	fontRUS[126] = setUpFontStruct(9*9, 78, 9, 13);
	fontRUS[127] = setUpFontStruct(0*9, 78, 9, 13);
}



void DrawText(int xpos, int ypos, char* Text, int scale, u64 colour, int selected)
{
	for(int i = 0; i < strlen(Text); i++)
	{
		int ascii = Text[i];
		
		if(ascii != 32)
		{
			if(selected == 0)
			{
				DrawSpriteTexture(&fontRussian,xpos + i * (fontRUS[ascii].width * scale),  // X1
						ypos,  // Y1
						fontRUS[ascii].x,  // U1
						fontRUS[ascii].y,  // V1
						xpos + i * (fontRUS[ascii].width * scale) + (fontRUS[ascii].width * scale), // X2
						ypos + (fontRUS[ascii].height * scale), // Y2
						fontRUS[ascii].x + fontRUS[ascii].width, // U2
						fontRUS[ascii].y + fontRUS[ascii].height, // V2
						2,
						fontColour);
			}
			else if(selected == 1)
			{
				DrawSpriteTexture(&fontRussianGold,xpos + i * (fontRUS[ascii].width * scale),  // X1
						ypos,  // Y1
						fontRUS[ascii].x,  // U1
						fontRUS[ascii].y,  // V1
						xpos + i * (fontRUS[ascii].width * scale) + (fontRUS[ascii].width * scale), // X2
						ypos + (fontRUS[ascii].height * scale), // Y2
						fontRUS[ascii].x + fontRUS[ascii].width, // U2
						fontRUS[ascii].y + fontRUS[ascii].height, // V2
						2,
						fontColour);
			}
			else
			{
				DrawSpriteTexture(&fontRussian,xpos + i * (fontRUS[ascii].width * scale),  // X1
						ypos,  // Y1
						fontRUS[ascii].x,  // U1
						fontRUS[ascii].y,  // V1
						xpos + i * (fontRUS[ascii].width * scale) + (fontRUS[ascii].width * scale), // X2
						ypos + (fontRUS[ascii].height * scale), // Y2
						fontRUS[ascii].x + fontRUS[ascii].width, // U2
						fontRUS[ascii].y + fontRUS[ascii].height, // V2
						2,
						fontColour);
			}
		}
		else
		{
			// ???
		}
	}
}

void DrawAnimatedText(int xpos, int ypos, char* Text, int type)
{
	
}

void textSelfDestruct()
{

}

