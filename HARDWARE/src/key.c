#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;//KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//H->L
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)return WKUP_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	    
 	return 0;// �ް�������
}


u8 keyx_Scan(u8 mode)
{
	static u8 keyx_up=1;//�������ɿ���־
	if(mode)keyx_up=1;
	if(keyx_up&&(key1==1||key2==1))
	{
		delay_ms(10);//ȥ���� 
		keyx_up=0;
		if(key1==1)return key1_PRES;
		else if(key2==1)return key2_PRES;
	}else if(key1==0&&key2==0)keyx_up=1; 	    
 	return 0;// �ް�������
}





