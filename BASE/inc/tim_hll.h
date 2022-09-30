#ifndef  _TIM_HLL_H
#define  _TIM_HLL_H

#include "sys.h" 
//X选一组即可
#define PB6_ARR_OUT(arr)	TIM4->ARR= arr;
#define PB7_ARR_OUT(arr)	TIM4->ARR= arr;
#define PB8_ARR_OUT(arr)	TIM4->ARR= arr;
#define PB9_ARR_OUT(arr)	TIM4->ARR= arr;

#define PB6_PWM_OUT(ccr)  TIM4->CCR1 = ccr;
#define PB7_PWM_OUT(ccr)  TIM4->CCR2 = ccr;
#define PB8_PWM_OUT(ccr)  TIM4->CCR3 = ccr;
#define PB9_PWM_OUT(ccr)  TIM4->CCR4 = ccr;


#define PA8_ARR_OUT(arr)	TIM1->ARR= arr;
#define PA11_ARR_OUT(arr)	TIM1->ARR= arr;

#define PA8_PWM_OUT(ccr)  TIM1->CCR1 = ccr;
#define PA11_PWM_OUT(ccr)  TIM1->CCR4 = ccr;



void PWM_Init_TIM4(u16 Psc,u16 Per);// div arr
void PWM_Init_TIM1(u16 Psc,u16 Per);

void TIM3_Mode_Config(u16 Psc,u16 Per);//采集FFT 2048
#endif


