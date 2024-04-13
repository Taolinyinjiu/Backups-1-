#ifndef __PID_H
#define __PID_H

#include "sys.h"

extern float err[3] ;
extern float integral1 ;

float pid_increament(float v,float speed);   //
float pid_location(float v,float speed);   //


#endif















