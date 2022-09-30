#ifndef  _FONT_HLL_H
#define  _FONT_HLL_H

#include "sys.h" 
#include <stdio.h>

#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->Height))
#define LINEY(x) ((x) * (((sFONT *)LCD_GetFont())->Width))

typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;  
//ASCII±í
extern sFONT Font24x32;
extern sFONT Font16x24;
extern sFONT Font8x16;


#endif














