#ifndef _APP_FFT_H_
#define _APP_FFT_H_

#include "sys.h"

#define SAMPLS_NUM 1024 
#define PI2   (6.28318530717959)
#define PI    (3.141592653589795)
#define Fs    ((float)256)   //����Ƶ��

extern u32 FFT_SourceData[SAMPLS_NUM];	//fft��������     
extern u32 FFT_OutData[SAMPLS_NUM];		//fft�������
extern u32 FFT_Mag[SAMPLS_NUM/2];		//��Ƶ�������У���Ŵ���Ƶ�ʷ�����ֵ�����ֵ��С������FFT��Ƶ�׽���ǹ����ο�˹��Ƶ�ʶԳƵģ�����ֻ����һ��ĵ㼴�ɣ�

void InitBufInArray(void);
void GetPowerMag(void);
void FFT_test(void);


#endif

