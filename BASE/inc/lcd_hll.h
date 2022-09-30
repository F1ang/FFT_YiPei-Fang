#ifndef  _LCD_HLL_H
#define  _LCD_HLL_H

#include "sys.h" 
#include <stdio.h>
#include "delay.h"
#include "font.h"

#define      DEBUG_DELAY()
#define 		ILI9341_CMD_ADDR  		(__IO uint16_t*)(0x60000000)
#define 		ILI9341_DATA_ADDR  		(__IO uint16_t*)(0x60020000)
#define 		RGB888_2_RGB565(R,G,B)		 (uint16_t)(((R & 0x1F) << 11) | ((G & 0x3F) << 5) | (B & 0x1F) )

//测试
void ILI9341_Init(void);
void ILI9341_Open_Window(uint16_t usX,uint16_t usY,uint16_t usWidth,uint16_t usHeight);
void ILI9341_Draw_Rec(uint16_t width, uint16_t height);
//基本属性
void ILI9341_GramScan(uint8_t ucOption);
static void ILI9341_SetCursor (uint16_t usX, uint16_t usY);
static __inline void ILI9341_FillColor (uint32_t ulAmout_Point, uint16_t usColor);
void ILI9341_Clear (uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight );
void ILI9341_SetPointPixel (uint16_t usX, uint16_t usY);
void LCD_SetColors(uint16_t TextColor, uint16_t BackColor);
void LCD_SetFont(sFONT *fonts);
sFONT *LCD_GetFont(void);
void LCD_SetColors(uint16_t TextColor, uint16_t BackColor) ;
//基本应用
void ILI9341_DrawLine(uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2);
void ILI9341_DrawRectangle (uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight, uint8_t ucFilled );
void ILI9341_DrawCircle (uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled );
//英文字符
void ILI9341_DispChar_EN(uint16_t usX, uint16_t usY, const char cChar);
void ILI9341_DispString_EN(uint16_t usX ,uint16_t usY,  char * pStr);
void ILI9341_DispStringLine_EN(uint16_t line,  char * pStr);

#endif


