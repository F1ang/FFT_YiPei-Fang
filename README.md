注：stm32f103x_conf.h包含相关头文件，Manage Project items头文件

BASE-基本驱动(从)，HARDWARE-硬件驱动(主)，USELIB-算法库


				/****本例为FFT变换的理论证明****/
核心:
1，ADC采样，配合DMA传输（采样点1024）
2，TIM外部触发ADC采样（采样频率2048hz）
3，采样分辨率2hz
4，自动产生PWM并让ADC采集
5，显示幅度特性曲线
6，DSP库的FFT运算（采样有限制）

主要参考:
https://blog.csdn.net/shenziheng1/article/details/52891807

https://www.cnblogs.com/h2zZhou/p/8405717.html











