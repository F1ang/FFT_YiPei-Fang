#ifndef  _FUNCTION_HLL_H
#define  _FUNCTION_HLL_H

#include "sys.h" 
#include "lcd_hll.h"
#include "key.h"
#include "oled.h"

#include "delay.h"
typedef struct
{
	int Freq; 
	int Duty;
	int Temp;
	int V[5];//FFT谐波
	int ADC_ConvertedValue;
	char display[60];

	int adc_finish;
	u16 ADC_SourceData[1024];//DMA1采集
}Picture_S;

void Paragram_Init(Picture_S *Fxang);
void Picture_One(void);
void Picture_Two(void);

void Change_freq_duty(void);

void oled_show(void);
#endif


