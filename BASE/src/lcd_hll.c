/*
	����Ұ����ֲLCD
*/

#include "lcd_hll.h"


__inline void                 ILI9341_Write_Cmd           ( uint16_t usCmd );
__inline void                 ILI9341_Write_Data          ( uint16_t usData );
__inline uint16_t             ILI9341_Read_Data           ( void );
void GPIOx_Init(void)
{
	//GPIO
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);
	//PP
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//AF_PP
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//FSMC-D0~D15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init ( GPIOD, & GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init ( GPIOD, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init ( GPIOD, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init ( GPIOD, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init ( GPIOE, & GPIO_InitStructure );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init ( GPIOD, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init ( GPIOD, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init ( GPIOD, & GPIO_InitStructure );

}

void FSMC_Init()
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  ReadWriteTiming;	//ʱ��ṹ��->FSMC�ṹ��һ��Ա
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
	
	/*ģ��8080ʱ��*/
	ReadWriteTiming.FSMC_AddressSetupTime = 0x01;//��ַ����ʱ�䣨ADDSET��	
	ReadWriteTiming.FSMC_DataSetupTime = 0x04;//���ݱ���ʱ�䣨DATAST��		 	
	ReadWriteTiming.FSMC_AddressHoldTime = 0x00;//��ַ����ʱ�䣨ADDHLD��ģʽBδ�õ�	 	
	ReadWriteTiming.FSMC_BusTurnAroundDuration = 0x00;//��������ת�����ڣ������ڸ���ģʽ��NOR����	
	ReadWriteTiming.FSMC_CLKDivision = 0x00;//����ʱ�ӷ�Ƶ��������ͬ�����͵Ĵ洢��	
	ReadWriteTiming.FSMC_DataLatency = 0x00;//���ݱ���ʱ�䣬������NOR			
	ReadWriteTiming.FSMC_AccessMode = FSMC_AccessMode_B;//ѡ��ƥ��SRAM��ģʽ	 
	/*FSMC�ṹ��*/
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;// ѡ��FSMCӳ��Ĵ洢���� Bank1 NORSRAMx 	
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;//���õ�ַ���������������Ƿ��ã�������NOR 
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_NOR;//����Ҫ���ƵĴ洢�����ͣ�NOR����   
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ�ȣ�16λ 
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;//�����Ƿ�ʹ��ͻ������ģʽ��������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;//�����Ƿ�ʹ�ܵȴ��źţ�������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;//���õȴ��źŵ���Ч���ԣ�������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;//�����Ƿ�֧�ְѷǶ����ͻ��������������ͬ�����͵Ĵ洢�� 
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;//���õȴ��źŲ����ʱ�䣬������ͬ�����͵Ĵ洢��
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;//�洢��дʹ��
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;//��ʹ�õȴ��ź�  		
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;// ��ʹ����չģʽ����дʹ����ͬ��ʱ�� 
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;//ͻ��д����  
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &ReadWriteTiming;//��дʱ������
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &ReadWriteTiming;//��дͬ��ʱ��ʹ����չģʽʱ������ò���Ч 
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // ʹ��BANK
}


																				/*ILI9341����Э��*/
//read and write
void ILI9341_Write_Cmd ( uint16_t usCmd )
{
	*ILI9341_CMD_ADDR=usCmd;	    
}
void ILI9341_Write_Data ( uint16_t usData )
{
	*ILI9341_DATA_ADDR=usData; 
}
uint16_t ILI9341_Read_Data ( void )
{
	return ( *ILI9341_DATA_ADDR );
}
static void ILI9341_Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );	
}

//reg_init
static void ILI9341_REG_Config ( void )
{
	/*  Power control B (CFh)  */
	DEBUG_DELAY  ();
	ILI9341_Write_Cmd ( 0xCF  );
	ILI9341_Write_Data ( 0x00  );
	ILI9341_Write_Data ( 0x81  );
	ILI9341_Write_Data ( 0x30  );
	
	/*  Power on sequence control (EDh) */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xED );
	ILI9341_Write_Data ( 0x64 );
	ILI9341_Write_Data ( 0x03 );
	ILI9341_Write_Data ( 0x12 );
	ILI9341_Write_Data ( 0x81 );
	
	/*  Driver timing control A (E8h) */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xE8 );
	ILI9341_Write_Data ( 0x85 );
	ILI9341_Write_Data ( 0x10 );
	ILI9341_Write_Data ( 0x78 );
	
	/*  Power control A (CBh) */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xCB );
	ILI9341_Write_Data ( 0x39 );
	ILI9341_Write_Data ( 0x2C );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x34 );
	ILI9341_Write_Data ( 0x02 );
	
	/* Pump ratio control (F7h) */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xF7 );
	ILI9341_Write_Data ( 0x20 );
	
	/* Driver timing control B */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xEA );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xB1 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x1B );
	
	/*  Display Function Control (B6h) */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xB6 );
	ILI9341_Write_Data ( 0x0A );
	ILI9341_Write_Data ( 0xA2 );
	
	/* Power Control 1 (C0h) */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xC0 );
	ILI9341_Write_Data ( 0x35 );
	
	/* Power Control 2 (C1h) */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0xC1 );
	ILI9341_Write_Data ( 0x11 );
	
	/* VCOM Control 1 (C5h) */
	ILI9341_Write_Cmd ( 0xC5 );
	ILI9341_Write_Data ( 0x45 );
	ILI9341_Write_Data ( 0x45 );
	
	/*  VCOM Control 2 (C7h)  */
	ILI9341_Write_Cmd ( 0xC7 );
	ILI9341_Write_Data ( 0xA2 );
	
	/* Enable 3G (F2h) */
	ILI9341_Write_Cmd ( 0xF2 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Gamma Set (26h) */
	ILI9341_Write_Cmd ( 0x26 );
	ILI9341_Write_Data ( 0x01 );
	DEBUG_DELAY ();
	
	/* Positive Gamma Correction */
	ILI9341_Write_Cmd ( 0xE0 ); //Set Gamma
	ILI9341_Write_Data ( 0x0F );
	ILI9341_Write_Data ( 0x26 );
	ILI9341_Write_Data ( 0x24 );
	ILI9341_Write_Data ( 0x0B );
	ILI9341_Write_Data ( 0x0E );
	ILI9341_Write_Data ( 0x09 );
	ILI9341_Write_Data ( 0x54 );
	ILI9341_Write_Data ( 0xA8 );
	ILI9341_Write_Data ( 0x46 );
	ILI9341_Write_Data ( 0x0C );
	ILI9341_Write_Data ( 0x17 );
	ILI9341_Write_Data ( 0x09 );
	ILI9341_Write_Data ( 0x0F );
	ILI9341_Write_Data ( 0x07 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Negative Gamma Correction (E1h) */
	ILI9341_Write_Cmd ( 0XE1 ); //Set Gamma
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x19 );
	ILI9341_Write_Data ( 0x1B );
	ILI9341_Write_Data ( 0x04 );
	ILI9341_Write_Data ( 0x10 );
	ILI9341_Write_Data ( 0x07 );
	ILI9341_Write_Data ( 0x2A );
	ILI9341_Write_Data ( 0x47 );
	ILI9341_Write_Data ( 0x39 );
	ILI9341_Write_Data ( 0x03 );
	ILI9341_Write_Data ( 0x06 );
	ILI9341_Write_Data ( 0x06 );
	ILI9341_Write_Data ( 0x30 );
	ILI9341_Write_Data ( 0x38 );
	ILI9341_Write_Data ( 0x0F );
	
	/* memory access control set */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0x36 ); 	
	ILI9341_Write_Data ( 0xC8 );    /*����  ���Ͻǵ� (���)�����½� (�յ�)ɨ�跽ʽ*/
	DEBUG_DELAY ();
	
	/* column address control set */
	ILI9341_Write_Cmd ( 0x2A ); 
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0xEF );
	
	/* page address control set */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0x2B ); 
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x01 );
	ILI9341_Write_Data ( 0x3F );
	
	/*  Pixel Format Set (3Ah)  */
	DEBUG_DELAY ();
	ILI9341_Write_Cmd ( 0x3a ); 
	ILI9341_Write_Data ( 0x55 );
	
	/* Sleep Out (11h)  */
	ILI9341_Write_Cmd ( 0x11 );	
	ILI9341_Delay ( 0xAFFf<<2 );
	DEBUG_DELAY ();
	
	/* Display ON (29h) */
	ILI9341_Write_Cmd ( 0x29 ); 
}

void ILI9341_BackLed(FunctionalState enumState)
{
	if (enumState)
		GPIO_ResetBits ( GPIOD, GPIO_Pin_12 );	
	else
		GPIO_SetBits ( GPIOD, GPIO_Pin_12 );		
}

void ILI9341_Rst ( void )
{			
	GPIO_ResetBits ( GPIOE,GPIO_Pin_1);
	ILI9341_Delay ( 0xAFF ); 				
	GPIO_SetBits ( GPIOE,GPIO_Pin_1);		 	 
	ILI9341_Delay ( 0xAFF ); 
}

/*��ʼ��LCD*/
void ILI9341_Init(void)
{
	GPIOx_Init();
	FSMC_Init();
	ILI9341_BackLed(ENABLE);
	ILI9341_Rst();
	ILI9341_REG_Config();
	ILI9341_GramScan(6);
}

/*дLCD_API*/
static sFONT *LCD_Currentfonts = &Font8x16;  //Ӣ������
static uint16_t CurrentTextColor   = 0x0000;//ǰ��ɫ
static uint16_t CurrentBackColor   = 0xFFFF;//����ɫ

uint16_t LCD_X_LENGTH,LCD_Y_LENGTH;
/*
	Scan Mode:0~6.
	LCD��ʾ��ʽ.
*/
void ILI9341_GramScan ( uint8_t ucOption )   
{	
	uint8_t LCD_SCAN_MODE;
	//������飬ֻ������0-7
	if(ucOption >7 )
		return;
	//����ģʽ����LCD_SCAN_MODE��ֵ����Ҫ���ڴ�����ѡ��������
	LCD_SCAN_MODE = ucOption;
	//����ģʽ����XY��������ؿ��
	if(ucOption%2 == 0)	
	{
		//0 2 4 6ģʽ��X�������ؿ��Ϊ240��Y����Ϊ320
		LCD_X_LENGTH = 240;
		LCD_Y_LENGTH =	320; 
	}
	else				
	{
		//1 3 5 7ģʽ��X�������ؿ��Ϊ320��Y����Ϊ240
		LCD_X_LENGTH = 320;
		LCD_Y_LENGTH =	240; 
	}
	//0x36��������ĸ�3λ����������GRAMɨ�跽��	
	ILI9341_Write_Cmd ( 0x36 ); 
	ILI9341_Write_Data ( 0x08 |(ucOption<<5));//����ucOption��ֵ����LCD��������0-7��ģʽ
	ILI9341_Write_Cmd ( 0x2A ); 
	ILI9341_Write_Data ( 0x00 );		/* x ��ʼ�����8λ */
	ILI9341_Write_Data ( 0x00 );		/* x ��ʼ�����8λ */
	ILI9341_Write_Data ( ((LCD_X_LENGTH-1)>>8)&0xFF ); /* x ���������8λ */	
	ILI9341_Write_Data ( (LCD_X_LENGTH-1)&0xFF );				/* x ���������8λ */

	ILI9341_Write_Cmd ( 0x2AB ); 
	ILI9341_Write_Data ( 0x00 );		/* y ��ʼ�����8λ */
	ILI9341_Write_Data ( 0x00 );		/* y ��ʼ�����8λ */
	ILI9341_Write_Data ( ((LCD_Y_LENGTH-1)>>8)&0xFF );	/* y ���������8λ */	 
	ILI9341_Write_Data ( (LCD_Y_LENGTH-1)&0xFF );				/* y ���������8λ */
	/* write gram start */
	ILI9341_Write_Cmd ( 0x2C );	
}
//Open Window:����ע���������Ұ������1���Ǵ�ģ��˲�������2��д��
void ILI9341_Open_Window(uint16_t usX,uint16_t usY,uint16_t usWidth,uint16_t usHeight)
{
	ILI9341_Write_Cmd ( 0X2A ); 				 /* ����X���� */
	ILI9341_Write_Data ( usX >> 8  );	 /* �ȸ�8λ��Ȼ���8λ */
	ILI9341_Write_Data ( usX & 0xff  );	 /* ������ʼ��ͽ�����*/
	ILI9341_Write_Data ( ( usX + usWidth - 1 ) >> 8  );
	ILI9341_Write_Data ( ( usX + usWidth - 1 ) & 0xff  );

	ILI9341_Write_Cmd ( 0X2B ); 			     /* ����Y����*/
	ILI9341_Write_Data ( usY >> 8  );
	ILI9341_Write_Data ( usY & 0xff  );
	ILI9341_Write_Data ( ( usY + usHeight - 1 ) >> 8 );
	ILI9341_Write_Data ( ( usY + usHeight - 1) & 0xff );	
}
//����
void ILI9341_Draw_Rec(uint16_t width, uint16_t height)  
{
	uint32_t i;
	ILI9341_Open_Window(0,0,width,height);	//240*320
	ILI9341_Write_Cmd(0x2C);//�������
	for(i=0;i<width*height;i++)
	ILI9341_Write_Data(RGB888_2_RGB565(79,67,188));   
}

//Cursor
static void ILI9341_SetCursor ( uint16_t usX, uint16_t usY )	
{
	 ILI9341_Open_Window( usX, usY, 1, 1 );
}
//Fill
static __inline void ILI9341_FillColor ( uint32_t ulAmout_Point, uint16_t usColor )
{
	uint32_t i = 0;
	ILI9341_Write_Cmd (0x2C);			
	for ( i = 0; i < ulAmout_Point; i ++ )
		ILI9341_Write_Data ( usColor );
}
//Clear
void ILI9341_Clear ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight )
{
	ILI9341_Open_Window ( usX, usY, usWidth, usHeight );
	ILI9341_FillColor ( usWidth * usHeight, CurrentBackColor );		
}
//Point
void ILI9341_SetPointPixel ( uint16_t usX, uint16_t usY )	
{	
	if ( ( usX < LCD_X_LENGTH ) && ( usY < LCD_Y_LENGTH ) )
  {
		ILI9341_SetCursor ( usX, usY );
		
		ILI9341_FillColor ( 1, CurrentTextColor );
	}
	
}
//Line
void ILI9341_DrawLine ( uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2 )
{
	uint16_t us; 
	uint16_t usX_Current, usY_Current;	
	int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int32_t lIncrease_X, lIncrease_Y; 	
	lDelta_X = usX2 - usX1; //������������ 
	lDelta_Y = usY2 - usY1; 	
	usX_Current = usX1; 
	usY_Current = usY1; 
	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; //���õ������� 
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;//��ֱ�� 	
	else 
  { 
    lIncrease_X = -1;
    lDelta_X = - lDelta_X;
  } 	
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 	
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;//ˮƽ�� 	
	else 
  {
    lIncrease_Y = -1;
    lDelta_Y = - lDelta_Y;
  } 	
	if (  lDelta_X > lDelta_Y )
		lDistance = lDelta_X; //ѡȡ�������������� 	
	else 
		lDistance = lDelta_Y; 	
	for ( us = 0; us <= lDistance + 1; us ++ )//������� 
	{  
		ILI9341_SetPointPixel ( usX_Current, usY_Current );//���� 
		
		lError_X += lDelta_X ; 
		lError_Y += lDelta_Y ; 		
		if ( lError_X > lDistance ) 
		{ 
			lError_X -= lDistance; 
			usX_Current += lIncrease_X; 
		}  	
		if ( lError_Y > lDistance ) 
		{ 
			lError_Y -= lDistance; 
			usY_Current += lIncrease_Y; 
		} 		
	}  
} 
//Rectangle
void ILI9341_DrawRectangle ( uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight, uint8_t ucFilled )
{
	if ( ucFilled )
	{
		ILI9341_Open_Window ( usX_Start, usY_Start, usWidth, usHeight );
		ILI9341_FillColor ( usWidth * usHeight ,CurrentTextColor);	
	}
	else
	{
		ILI9341_DrawLine ( usX_Start, usY_Start, usX_Start + usWidth - 1, usY_Start );
		ILI9341_DrawLine ( usX_Start, usY_Start + usHeight - 1, usX_Start + usWidth - 1, usY_Start + usHeight - 1 );
		ILI9341_DrawLine ( usX_Start, usY_Start, usX_Start, usY_Start + usHeight - 1 );
		ILI9341_DrawLine ( usX_Start + usWidth - 1, usY_Start, usX_Start + usWidth - 1, usY_Start + usHeight - 1 );		
	}
}
//Circle
void ILI9341_DrawCircle ( uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled )
{
	int16_t sCurrentX, sCurrentY;
	int16_t sError;
	sCurrentX = 0; sCurrentY = usRadius;	  
	sError = 3 - ( usRadius << 1 );     //�ж��¸���λ�õı�־
	while ( sCurrentX <= sCurrentY )
	{
		int16_t sCountY;	
		if ( ucFilled ) 			
			for ( sCountY = sCurrentX; sCountY <= sCurrentY; sCountY ++ ) 
			{                      
				ILI9341_SetPointPixel ( usX_Center + sCurrentX, usY_Center + sCountY );           //1���о����� 
				ILI9341_SetPointPixel ( usX_Center - sCurrentX, usY_Center + sCountY );           //2       
				ILI9341_SetPointPixel ( usX_Center - sCountY,   usY_Center + sCurrentX );           //3
				ILI9341_SetPointPixel ( usX_Center - sCountY,   usY_Center - sCurrentX );           //4
				ILI9341_SetPointPixel ( usX_Center - sCurrentX, usY_Center - sCountY );           //5    
        ILI9341_SetPointPixel ( usX_Center + sCurrentX, usY_Center - sCountY );           //6
				ILI9341_SetPointPixel ( usX_Center + sCountY,   usY_Center - sCurrentX );           //7 	
        ILI9341_SetPointPixel ( usX_Center + sCountY,   usY_Center + sCurrentX );           //0				
			}	
		else
		{          
			ILI9341_SetPointPixel ( usX_Center + sCurrentX, usY_Center + sCurrentY );             //1���о�����
			ILI9341_SetPointPixel ( usX_Center - sCurrentX, usY_Center + sCurrentY );             //2      
			ILI9341_SetPointPixel ( usX_Center - sCurrentY, usY_Center + sCurrentX );             //3
			ILI9341_SetPointPixel ( usX_Center - sCurrentY, usY_Center - sCurrentX );             //4
			ILI9341_SetPointPixel ( usX_Center - sCurrentX, usY_Center - sCurrentY );             //5       
			ILI9341_SetPointPixel ( usX_Center + sCurrentX, usY_Center - sCurrentY );             //6
			ILI9341_SetPointPixel ( usX_Center + sCurrentY, usY_Center - sCurrentX );             //7 
			ILI9341_SetPointPixel ( usX_Center + sCurrentY, usY_Center + sCurrentX );             //0
    }					
		sCurrentX ++;	
		if ( sError < 0 ) 
			sError += 4 * sCurrentX + 6;	  
		else
		{
			sError += 10 + 4 * ( sCurrentX - sCurrentY );   
			sCurrentY --;
		} 	
	}
}
															/*��ʾ�ַ�������*/
//Set_Font
void LCD_SetFont(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}
//Get_Font
sFONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}
//ǰ��ɫ������ɫ-->RGB565
void LCD_SetColors(uint16_t TextColor, uint16_t BackColor) 
{
  CurrentTextColor = TextColor; 
  CurrentBackColor = BackColor;
}
//Show_EN
void ILI9341_DispChar_EN ( uint16_t usX, uint16_t usY, const char cChar )
{
	uint8_t  byteCount, bitCount,fontLength;	
	uint16_t ucRelativePositon;
	uint8_t *Pfont;
	ucRelativePositon = cChar - ' ';//��ascii���ƫ�ƣ���ģ������ASCII���ǰ32����ͼ�η��ţ�
	fontLength = (LCD_Currentfonts->Width*LCD_Currentfonts->Height)/8;//ÿ����ģ���ֽ���	
	//��ģ�׵�ַ
	/*ascii���ƫ��ֵ����ÿ����ģ���ֽ����������ģ��ƫ��λ��*/
	Pfont = (uint8_t *)&LCD_Currentfonts->table[ucRelativePositon * fontLength];
	ILI9341_Open_Window( usX, usY, LCD_Currentfonts->Width, LCD_Currentfonts->Height);//������ʾ����	
	ILI9341_Write_Cmd (0x2C);			
	//���ֽڶ�ȡ��ģ����
	//����ǰ��ֱ����������ʾ���ڣ���ʾ���ݻ��Զ�����
	for ( byteCount = 0; byteCount < fontLength; byteCount++ )
	{
			//һλһλ����Ҫ��ʾ����ɫ
			for ( bitCount = 0; bitCount < 8; bitCount++ )
			{
					if ( Pfont[byteCount] & (0x80>>bitCount) )
						ILI9341_Write_Data ( CurrentTextColor );			
					else
						ILI9341_Write_Data ( CurrentBackColor );
			}	
	}	
}
//String_EN-->Line
void ILI9341_DispStringLine_EN (  uint16_t line,  char * pStr )
{
	uint16_t usX = 0;	
	while ( * pStr != '\0' )
	{
		if ( ( usX - 0 + LCD_Currentfonts->Width ) > LCD_X_LENGTH )
		{
			usX = 0;
			line += LCD_Currentfonts->Height;
		}	
		if ( ( line - 0 + LCD_Currentfonts->Height ) > LCD_Y_LENGTH )
		{
			usX = 0;
			line = 0;
		}	
		ILI9341_DispChar_EN ( usX, line, * pStr);		
		pStr ++;		
		usX += LCD_Currentfonts->Width;		
	}
}
//String_EN-->x,y
void ILI9341_DispString_EN ( 	uint16_t usX ,uint16_t usY,  char * pStr )
{
	while ( * pStr != '\0' )
	{
		if ( ( usX - 0 + LCD_Currentfonts->Width ) > LCD_X_LENGTH )
		{
			usX = 0;
			usY += LCD_Currentfonts->Height;
		}		
		if ( ( usY - 0 + LCD_Currentfonts->Height ) > LCD_Y_LENGTH )
		{
			usX = 0;
			usY = 0;
		}		
		ILI9341_DispChar_EN ( usX, usY, * pStr);	
		pStr ++;		
		usX += LCD_Currentfonts->Width;		
	}
}


