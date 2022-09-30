#include "app_fft.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#include "math.h"

#include "adc_hll.h" 

u32 FFT_SourceData[SAMPLS_NUM] = {0};	//fft输入序列     
u32 FFT_OutData[SAMPLS_NUM] = {0};		//fft输出序列
u32 FFT_Mag[SAMPLS_NUM/2] = {0};		//幅频特性序列（序号代表频率分量，值代表幅值大小。由于FFT的频谱结果是关于奈奎斯特频率对称的，所以只计算一半的点即可）

/********************************************************************************************************
函数名称:GetPowerMag()
函数功能:计算各次谐波幅值
参数说明:
备　　注:先将ADC_FFT_OutData分解成实部(X)和虚部(Y)，然后计算幅频特性序列FFT_Mag
         本函数参考网页：https://wenku.baidu.com/view/08ccee0984868762cbaed532.html，关于幅频特性计算部分
**********************************************************************************************************/
void GetPowerMag(void)
{
	signed short lX,lY;
	float X,Y,Mag;
	unsigned short i;

	for(i=0; i<SAMPLS_NUM/2; i++)
	{
		lX = (FFT_OutData[i] << 16) >> 16;
		lY = (FFT_OutData[i] >> 16);
		
		X = SAMPLS_NUM * ((float)lX) / 32768;
		Y = SAMPLS_NUM * ((float)lY) / 32768;
		
		Mag = sqrt(X * X + Y * Y) / SAMPLS_NUM;
		
		if(i == 0)
			FFT_Mag[i] = (unsigned long)(Mag * 32768);
		else
			FFT_Mag[i] = (unsigned long)(Mag * 65536);
		//printf("%ld\r\n",lBufMagArray[i]);
	}

}

/************************************************
*由于在fft运算过程中不允许源数据更新
*将源数据拷贝到另一块内存
*此步骤可以被替换为：进行fft运算时，关闭adc转换
*************************************************/
void Get_FFT_Source_Data(void)
{
	u16 i,j;
	for(i=0; i<SAMPLS_NUM; i++)
	{
		FFT_SourceData[i] =F1ang.ADC_SourceData[i];
	}
}

void FFT_test(void)
{
	ADC_Cmd(ADC1, DISABLE);
	Get_FFT_Source_Data();//拷贝原始序列
	cr4_fft_1024_stm32(FFT_OutData, FFT_SourceData, SAMPLS_NUM);//FFT变换序列
	GetPowerMag();//幅频特性序列
	ADC_Cmd(ADC1, ENABLE);
}





#if 0
/****************************************************************************************************
函数名称:InitBufInArray()
函数功能:模拟采样数据，采样数据中包含3种频率正弦波(350Hz，8400Hz，18725Hz)
参数说明:
备     注:在lBufInArray数组中，每个数据的高16位存储采样数据的实部，低16位存储采样数据的虚部(总是为0)
****************************************************************************************************/

u16 lBufInArray[1024];

void InitBufInArray(void)
{
	unsigned short i;
	float fx;
	for(i=0; i<1024; i++)
	{
		fx = 1500 * sin(PI2 * i * 55.6 / Fs);
		lBufInArray[i] = ((signed short)fx)<<16;
	}
}
#endif