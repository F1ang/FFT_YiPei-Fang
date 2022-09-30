#include "function_hll.h"
#include "app_fft.h"
extern Picture_S F1ang;
void Picturex(uint8_t picturex)
{
	switch(picturex)
	{
		case 1:
			
			break;
		
		case 2:
			
			break;
		
		default:
			
			break;
	}
	
	
	
}


void Paragram_Init(Picture_S *Fxang)
{
	Fxang->Freq=1;
	Fxang->Duty=50;
	Fxang->Temp=0;
	Fxang->ADC_ConvertedValue=1;
	for(int i=0;i<5;i++)	
		Fxang->V[i]=0;

	Fxang->adc_finish=0;	
	for(int i=0;i<1024;i++)
		Fxang->ADC_SourceData[i]=0;
}


//P1
void Picture_One(void)
{	
	LCD_SetFont(&Font8x16);
	ILI9341_Open_Window(0,0,240,320);
   
  ILI9341_DispString_EN(50 ,16,"Jiangsu University");
  ILI9341_DispString_EN(120 ,34,"OF");
	ILI9341_DispString_EN(70 ,54,"SCI and TECH");
	ILI9341_DispString_EN(80 ,240,"FangYipei");
	ILI9341_DispString_EN(75 ,260,"Student Yes");
}
//P2
void Picture_Two(void)
{
	static uint8_t F2ang;
	LCD_SetFont(&Font8x16);
	ILI9341_Open_Window(0,0,240,320);
	
	ILI9341_DispString_EN(50 ,16,"Freq:");
	sprintf(F1ang.display,"%d     kHZ",F1ang.Freq);
	ILI9341_DispString_EN(120 ,16,F1ang.display);
	
	ILI9341_DispString_EN(50 ,48,"Duty:");
	sprintf(F1ang.display,"%d     %%",F1ang.Duty);
	ILI9341_DispString_EN(120 ,48,F1ang.display);
	
	ILI9341_DispString_EN(50 ,80,"Temp:");
	sprintf(F1ang.display,"%d     C",F1ang.Temp);
	ILI9341_DispString_EN(120 ,80,F1ang.display);
	
	
	ILI9341_DispString_EN(90 ,120,"Harmonic");
	
	ILI9341_DispString_EN(70 ,140,"0st:");
	sprintf(F1ang.display,"%d     V",F1ang.V[0]);
	ILI9341_DispString_EN(120 ,140,F1ang.display);
	
	ILI9341_DispString_EN(70 ,156,"1st:");
	sprintf(F1ang.display,"%d     V",F1ang.V[1]);
	ILI9341_DispString_EN(120 ,156,F1ang.display);
	
	ILI9341_DispString_EN(70 ,172,"2st:");
	sprintf(F1ang.display,"%d     V",F1ang.V[2]);
	ILI9341_DispString_EN(120 ,172,F1ang.display);
	
	ILI9341_DispString_EN(70 ,190,"3st:");
	sprintf(F1ang.display,"%d     V",F1ang.V[3]);
	ILI9341_DispString_EN(120 ,190,F1ang.display);
	
	ILI9341_DispString_EN(70 ,206,"4st:");
	sprintf(F1ang.display,"%d     V",F1ang.V[4]);  
	ILI9341_DispString_EN(120 ,206,F1ang.display);
	
	ILI9341_DispString_EN(70 ,240,"Adc:");
	sprintf(F1ang.display,"%d ",F1ang.ADC_ConvertedValue);  
	ILI9341_DispString_EN(120 ,240,F1ang.display);
	

	for(int i =0;i<240;i++)
		ILI9341_SetPointPixel(i,260);
	
	LCD_SetColors(RGB888_2_RGB565(255,0,0),RGB888_2_RGB565(255,255,255));
	if(F2ang==240){F2ang=0;ILI9341_Clear(0,270,240,50);}
	else F2ang+=1;
	ILI9341_SetPointPixel(F2ang,280+8*F1ang.V[0]);
	LCD_SetColors(RGB888_2_RGB565(0,0,0),RGB888_2_RGB565(255,255,255));
}
//Change freq/duty
void Change_freq_duty(void)
{
	switch(keyx_Scan(0))   
	{
			case 1:
						F1ang.Freq+=1;
				break;
			case 2:
						F1ang.Duty+=5;
				break;
			default:
						F1ang.Temp=10;
				break;
	}

	if(F1ang.Freq>100)F1ang.Freq=0;
	else if(F1ang.Duty>100)F1ang.Duty=0;
}


void oled_show(void)
{	
			static uint8_t i;
			if(i==110)i=0;
			else i++;
			OLED_DrawLine(i,5,i+10,10);	
			OLED_Refresh();	
			OLED_DrawPoint2(i,10+i);    
}


