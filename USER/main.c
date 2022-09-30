/*              
							GND   电源地
              VCC   接5V或3.3v电源
              SCL   接PB8（SCL）
              SDA   接PB9（SDA）        注：软件模拟协议，改引脚    
							I2C
*/
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "usart.h"

#include "lcd_hll.h"
#include "function_hll.h" 
#include "key.h"
#include "tim_hll.h"
#include "adc_hll.h"

#include "app_fft.h"

Picture_S F1ang;
void OLED(void);
int main(void)
{	
		delay_init();	
	 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		uart_init(115200);
		KEY_Init();
		OLED_Init();		  
		OLED_Clear(); 
		OLED();
	
		ILI9341_Init (); 
		
		Paragram_Init(&F1ang);
		Picture_One();
		delay_ms(5000);
		while(keyx_Scan(1)==0){};
		ILI9341_Clear(0,0,240,320);  
		Picture_Two();
		/*用一个即可*/	
		PWM_Init_TIM4(99,719);//1khz div arr      100~1khz,1000~10khz
		PB6_PWM_OUT(359);//50%										360~50，720~100	
		PWM_Init_TIM1(99,719);//1khz div arr      100~1khz,1000~10khz	
		PA11_PWM_OUT(359);//50%										360~50，720~100	
		
					
		ADCx_Mode_Config();	//ADC1,DMA1-->外部触发采样(即tim3)
		TIM3_Mode_Config(71,487);//2048hz采集->采样点1024->2HZ采样分辨率->0.5S进行一次FFT 
		while(1) 
		{		
			Change_freq_duty();
			Picture_Two();
			
			PA11_ARR_OUT(F1ang.Freq*100-1); 
			PA11_PWM_OUT(F1ang.Duty*7.2);//频率和占空比显示
			
			if(F1ang.adc_finish==1)//采样完毕
			{
				F1ang.adc_finish=0;
				FFT_test();
				/*
					测试可得，随着频率越高，幅值越小，符合傅里叶变换理论，
					且基波(第二个点)分辨率2hz.
					示波器则利用DAC（理论验证常规显示->TIM触发DAC输出）
					如：TIM->DAC_DR采样值->DAC : 波形数据DMA传输:M TO P(只要填充M即可)
				*/
//				printf("FFT_Mag[1]=%d\r\n",FFT_Mag[1]);//2hz
//				printf("FFT_Mag[500]=%d\r\n",FFT_Mag[500]);//1000hz
//				printf("FFT_Mag[400]=%d\r\n",FFT_Mag[400]);
//				printf("FFT_Mag[300]=%d\r\n",FFT_Mag[300]);
//				printf("FFT_Mag[508]=%d\r\n",FFT_Mag[508]);
//				printf("FFT_Mag[511]=%d\r\n",FFT_Mag[511]);
//				printf("\r\n");
				//下面为各个频率的点对应的幅度特性
				F1ang.V[0]=FFT_Mag[500];//第511个点-频率1024hz*2<=2048,香农采样定理
				F1ang.V[1]=FFT_Mag[501];
				F1ang.V[2]=FFT_Mag[502];
				F1ang.V[3]=FFT_Mag[503];
				F1ang.V[4]=FFT_Mag[504];
				F1ang.ADC_ConvertedValue=FFT_Mag[0];//DAC的M
				
			}
		}	  
	
}


void OLED(void)
{		
		OLED_DrawLine(5,0,5,60);  
		OLED_DrawLine(5,0,10,5);
		OLED_DrawLine(5,60,127,60);
		OLED_DrawLine(122,55,127,60);
		OLED_Refresh();
}

