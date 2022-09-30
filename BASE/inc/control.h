#ifndef  _CONTROL_H
#define  _CONTROL_H

#include "sys.h" 
#include "pid.h"
typedef enum
{
    balance=1,
    aviod=3,
    remote=2,
}MODE;
typedef struct
{
	float Pitch,Roll,Yaw;
	short gyrox,gyroy,gyroz;
	short aacx,aacy,aacz;
	
	MODE mode;
	uint8_t Forword,Back,Left,Right;
	
}	Posture;

#endif


