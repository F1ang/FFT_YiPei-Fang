#include "tim_hll.h" 

void PWM_Init_TIM4(u16 Psc,u16 Per)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	/*RCC!!!*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;				//PB6 PB7 ch1 ch2
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=Per;
	TIM_TimeBaseInitStruct.TIM_Prescaler=Psc;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);   // TIM4
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;      // ��ʼ������Ƚ�
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OC1Init(TIM4,&TIM_OCInitStruct);
	TIM_OC2Init(TIM4,&TIM_OCInitStruct);
	TIM_OC3Init(TIM4,&TIM_OCInitStruct);
	TIM_OC4Init(TIM4,&TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);		
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	
	TIM_Cmd(TIM4,ENABLE); 
}


void PWM_Init_TIM1(u16 Psc,u16 Per)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1,ENABLE);
		
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;     
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct); 
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=Per;
	TIM_TimeBaseInitStruct.TIM_Prescaler=Psc;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);   // TIM1
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;      
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;
	//TIM_OC1Init(TIM1,&TIM_OCInitStruct);
	TIM_OC4Init(TIM1,&TIM_OCInitStruct);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);

	//TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_Cmd(TIM1,ENABLE);  
}

void TIM3_Mode_Config(u16 Psc,u16 Per)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseInitStructure.TIM_Period = Per;														//设置2048Hz采样频率
	TIM_TimeBaseInitStructure.TIM_Prescaler = Psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;						//时钟分频，TIM3是通用定时器，基本定时器不用设置
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;					//向上扫描
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);							//选择TRGO作为触发源为定时器更新时间	
	TIM_Cmd(TIM3,ENABLE);
}



