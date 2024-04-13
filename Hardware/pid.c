#include "pid.h"

#define SPEED_PID_MAX 2000   //PID限幅值
#define integral1_max 300
#define v_max 3000

#define balance 1200
u32 errmax = 530;
int errmin = -530;

unsigned char PID_Sub = 0;



//float Kp[6] = {-0.802,   };
//float Ki[6] = {-0.0081, };
//float Kd[6] = {-24,  };

float Kp[6] = {-3.0,    -2.0,   -2.5,     -5 	};//3:-1.75,-0.01,-15.0
float Ki[6] = {-0.03, -0.01,  -0.01,    -0.02	};
float Kd[6] = {-40.0,     -50,    -35.0,    0.2 	};


//float Kp[6] = {-2.5,  -2.1,   -2.5,   -2.4 	};
//float Ki[6] = {-0.01, -0.004, -0.006, -0.01	};
//float Kd[6] = {-30,   -28,  	-35,    -60 	};
float err[3] = {0};
float integral1 = 0;
/*
以下为两类pid模板
int pid_del(int16_t v,int16_t speed) :增量式
int pid_location(int16_t v,int16_t speed):位置式 
*/
#define MOBAN 1
#if MOBAN
	float pid_increament(float goal,float current)   //ok
	{
		static float pid_delta;//
		//static float err[3]={0};//PID差值
		float Kp = -4.5;
		float	Ki = -0;
		float Kd = -0;
		err[2] = err[1];//上上次偏差
		err[1] = err[0];//上次误差
		err[0] = goal-current;  //设定值 - 反馈值//当前误差
		pid_delta += (float)(Kp*(float)(err[0]-err[1]) +Ki*err[0]+ Kd*(err[0]-2*err[1]+err[2]));//
		// printf("%f", pid_delta);
		if(pid_delta>SPEED_PID_MAX)pid_delta=SPEED_PID_MAX;
		else if(pid_delta<-SPEED_PID_MAX)pid_delta=-SPEED_PID_MAX;
		return pid_delta;
	}
	//
	float pid_location(float goal,float current)   //
	{
		static uint8_t state = 0;
		float out;
		float ki_integral1;
		float err_sum = 0;
		// static float integral1;
		//static float err[3]={0};//四个PID差值
//		float Kp=-1;//-0.91
//		float	Ki=-0 ;
//		float Kd=-0 ;//-28
		err[1] = err[0];//上次误差
		err[0] = goal-current;  //设定值 - 反馈值//当前误差
		integral1 +=  err[0];
		err_sum += err[0];
		if(err_sum > errmax)
			err[0] = errmax;
		else if (err_sum < errmin)
			err[0] = errmin;
		ki_integral1=Ki[PID_Sub] * integral1;
		if(ki_integral1>=30) ki_integral1=30;
		else if(ki_integral1<=-30) ki_integral1=-30;
//		out = (float)(Kp*(float)err[0] + Ki*integral1 + Kd*(err[0]-err[1]));
//		out = (float)(Kp*(float)err[0] + ki_integral1 + Kd*(err[0]-err[1]));
		out = (float)(Kp[PID_Sub] * (float)err[0] + Ki[PID_Sub] * integral1 + Kd[PID_Sub] * (err[0] - err[1]));
		if(out>SPEED_PID_MAX)out=SPEED_PID_MAX;
		else if(out<-SPEED_PID_MAX)out=-SPEED_PID_MAX;
		
		out += balance;
//		out = 0;
		return out;
	}
#endif
//












