#include "adc_hll.h" 
/*
	FS=2048HZ,N=1024->2HZ(最高分辨率)
	Per=487,Psc=71--->2048HZ
	
*/
void ADCx_Mode_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1, ENABLE );
//ADC1-DMA1:ADC1-DMA1-CH1   ADC_Channel_11=PC1
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)F1ang.ADC_SourceData;
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize         = 1024;
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);//使能DMA
    //NVIC			
	NVIC_InitStructure.NVIC_IRQChannel					 = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	DMA_ClearITPendingBit(DMA1_IT_TC1);
	DMA_ITConfig(DMA1_Channel1,DMA1_IT_TC1,ENABLE);
 //ADC1
	//GPIO:PC1->PB6/PB7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	//MODE
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(ADC1);
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;	
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;//选择TIM3外部触发
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_239Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_ExternalTrigConvCmd(ADC1, ENABLE);
}


void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
	{
		F1ang.adc_finish=1;
		DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
}


//EOC
uint16_t count_adc;
void ADC1_2_IRQHandler(void)
{
	if( ADC_GetITStatus(ADC2, ADC_IT_EOC) == SET)
  {
		count_adc++;
		if(count_adc==10){
			count_adc=0;
			F1ang.ADC_ConvertedValue = ADC_GetConversionValue(ADC2);
		}
	}
	ADC_ClearITPendingBit(ADC2, ADC_IT_EOC);
}

