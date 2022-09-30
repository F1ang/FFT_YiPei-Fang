#ifndef _APP_FFT_H_
#define _APP_FFT_H_

#include "sys.h"

#define SAMPLS_NUM 1024 
#define PI2   (6.28318530717959)
#define PI    (3.141592653589795)
#define Fs    ((float)256)   //采样频率

extern u32 FFT_SourceData[SAMPLS_NUM];	//fft输入序列     
extern u32 FFT_OutData[SAMPLS_NUM];		//fft输出序列
extern u32 FFT_Mag[SAMPLS_NUM/2];		//幅频特性序列（序号代表频率分量，值代表幅值大小。由于FFT的频谱结果是关于奈奎斯特频率对称的，所以只计算一半的点即可）

void InitBufInArray(void);
void GetPowerMag(void);
void FFT_test(void);


#endif

