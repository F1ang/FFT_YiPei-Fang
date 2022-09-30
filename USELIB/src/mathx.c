#include "mathx.h"

//extern double PI;	//定义π 因为tan(π/4)=1 所以arctan（1）*4=π，增加π的精度  3.1415....	
//complex x1[N], *W1;  	 //定义输入序列和旋转因子  
//int size=0;  		 			//定义数据长度   
//    
//																			/*FFT变换*/
///*
//	1、定义复数的输出函数,输出实现
//	param: complex
//*/
//void output(complex *x)
//{
//	int i;
//	for(i=0;i<size;i++)
//	{	
//		printf("%.4f",x[i].real); 			 //输出复数的实部
//		if(x[i].imag>=0.0001)
//		{
//			printf("+%.4fj\n",x[i].imag);  //当复数的虚补大于0.0001时，输出+ 虚部 j的形式
//		}
//		else if(fabs(x[i].imag)<0.0001)
//		{
//			printf("\n");									//当虚部小于0.001时，跳过虚部，不输出
//		}
//		else
//		{
//			printf("%.4fj\n",x[i].imag);	//上述两个条件除外的形式，输出 虚部 j的形式
//		}
//	}
//}
///*
//	2、数据点经过log(N)/log2级分割后重新排序，分治实现
//	param:complex,size
//*/
//void change(complex *x,int size)
//{
//	complex temp;
//	unsigned short i=0,j=0,k=0;
//	double t;
//	for(i=0;i<size;i++)
//	{
//		k=i;
//		j=0;
//		t=(log(size)/log(2));  //算出序列的级数
//		while( (t--)>0 )  //利用按位与以及循环实现码位颠倒
//		{
//			j=j<<1;
//			j|=(k & 1);
//			k=k>>1;
//		}
//		if(j>i)    //将x(n)的码位互换
//		{
//			temp=x[i];
//			x[i]=x[j];
//			x[j]=temp;
//		}
//	}
//}
///*
//	3、旋转因子Wn的表示
//	param:complex,size
//*/
//void transform(complex *W,int size)
//{
//	int i;
//	W=(complex *)malloc(sizeof(complex) * size);//给指针分配size的空间 size是数据长度
//	for(i=0;i<size;i++)
//	{
//		W[i].real=cos(2*PI/size*i);  //欧拉表示的实部
//		W[i].imag=-1*sin(2*PI/size*i);  //欧拉表示的虚部
//	}
//}
///*
//	4、复数的加、减、乘运算
//	param:complex
//*/
//void add(complex a,complex b,complex *c)//定义结构体a、b和指针c    加法
//{
//	c->real=a.real+b.real; //c的目的是取出结构体中的数据
//	c->imag=a.imag+b.imag;
//}
//void sub(complex a,complex b,complex *c)   //减法
//{
//	c->real=a.real-b.real;
//	c->imag=a.imag-b.imag;
//}
//void mul(complex a,complex b,complex *c)   //乘法
//{
//	c->real=a.real*b.real - a.imag*b.imag;
//	c->imag=a.real*b.imag + a.imag*b.real;
//}
///*
//	5、碟形运算
//	param:complex,size
//*/
//void fft(complex *x,complex *W,int size)  
//{
//	int i=0,j=0,k=0,m=0;
//	complex q,y,z;
//	change(x,size);
//	for(i=0;i<log(size)/log(2) ;i++)  //蝶形运算的级数
//	{
//		m=1<<i;   //移位 每次都是2的指数的形式增加，其实也可以用m=2^i代替
//		for(j=0;j<size;j+=2*m)  //一组蝶形运算，每一组的蝶形因子乘数不同
//		{
//			for(k=0;k<m;k++)  //蝶形结点的距离  一个蝶形运算 每个组内的蝶形运算
//			{
//				mul(x[k+j+m],W[size*k/2/m],&q);
//				add(x[j+k],q,&y);
//				sub(x[j+k],q,&z);
//				x[j+k]=y;
//				x[j+k+m]=z;
//			}
//		}
//	}
//}

///*
//	参数:W-旋转因子Wn的表示,x-输入的序列，size-序列的长度
//*/

//int FFT_HLL(complex *x,complex *W,int size)
//{
//	transform(W,size);//变换序列顺序
//	fft(x,W,size);//蝶形运算  
//	printf("输出FFT后的结果\n");
//	output(x);//输出结果
//	return 0;
//}










///*
//  #include "math.h"
//  void kfft(pr,pi,n,k,fr,fi)
//  int n,k;
//  double pr[],pi[],fr[],fi[];
//  { 
//	int it,m,is,i,j,nv,l0;
//    double p,q,s,vr,vi,poddr,poddi;
//    for (it=0; it<=n-1; it++)  //将pr[0]和pi[0]循环赋值给fr[]和fi[]
//    { 
//		m=it; 
//		is=0;
//		for(i=0; i<=k-1; i++)
//        { 
//			j=m/2; 
//			is=2*is+(m-2*j); 
//			m=j;
//		}
//        fr[it]=pr[is]; 
//        fi[it]=pi[is];
//    }
//    pr[0]=1.0; 
//    pi[0]=0.0;
//    p=6.283185306/(1.0*n);
//    pr[1]=cos(p); //将w=e^-j2pi/n用欧拉公式表示
//    pi[1]=-sin(p);

//    for (i=2; i<=n-1; i++)  //计算pr[]
//    { 
//		p=pr[i-1]*pr[1]; 
//		q=pi[i-1]*pi[1];
//		s=(pr[i-1]+pi[i-1])*(pr[1]+pi[1]);
//		pr[i]=p-q; pi[i]=s-p-q;
//    }
//    for (it=0; it<=n-2; it=it+2)  
//    { 
//		vr=fr[it]; 
//		vi=fi[it];
//		fr[it]=vr+fr[it+1]; 
//		fi[it]=vi+fi[it+1];
//		fr[it+1]=vr-fr[it+1]; 
//		fi[it+1]=vi-fi[it+1];
//    }
//	m=n/2; 
//	nv=2;
//    for (l0=k-2; l0>=0; l0--) //蝴蝶操作
//    { 
//		m=m/2; 
//		nv=2*nv;
//        for (it=0; it<=(m-1)*nv; it=it+nv)
//          for (j=0; j<=(nv/2)-1; j++)
//            { 
//				p=pr[m*j]*fr[it+j+nv/2];
//				q=pi[m*j]*fi[it+j+nv/2];
//				s=pr[m*j]+pi[m*j];
//				s=s*(fr[it+j+nv/2]+fi[it+j+nv/2]);
//				poddr=p-q; 
//				poddi=s-p-q;
//				fr[it+j+nv/2]=fr[it+j]-poddr;
//				fi[it+j+nv/2]=fi[it+j]-poddi;
//				fr[it+j]=fr[it+j]+poddr;
//				fi[it+j]=fi[it+j]+poddi;
//            }
//    }
//    for (i=0; i<=n-1; i++)
//       { 
//		  pr[i]=sqrt(fr[i]*fr[i]+fi[i]*fi[i]);  //幅值计算
//       }
//    return;
//  }

//	#include "stdio.h"
//	#include "math.h"
//	#include "kfft.c"

//	#define PI 3.1415926535

//	main()
//	{ 
//		int i,j;
//		double pr[64],pi[64],fr[64],fi[64],t[64];
//		for (i=0; i<=63; i++)  //生成输入信号
//		{ 
//			t[i] = i*0.001;
//			pr[i]=1.2+2.7*cos(2*PI*33*t[i])+5*cos(2*PI*200*t[i]+PI/2); pi[i]=0.0;
//		}
//			
//		kfft(pr,pi,64,6,fr,fi);  //调用FFT函数
//		for (i=0; i<64; i++)
//		{ 
//			printf("%d\t%lf\n",i,pr[i]); //输出结果
//		}
//	}


//*/


//斜坡函数

void Ramp_(int *Output_value, int Pace, int Remote_value)
{
	if(Remote_value>*Output_value)
	{
		*Output_value += Pace;
		if(*Output_value>Remote_value)
		{
			*Output_value=Remote_value;
		}
	}
	else if(Remote_value<*Output_value)
	{
		*Output_value -= Pace;
		if(*Output_value<Remote_value)
		{
			*Output_value=Remote_value;
		}
	}
	else *Output_value=Remote_value;
}















