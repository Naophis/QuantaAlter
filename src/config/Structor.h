/*
 * Structor.h
 *
 *  Created on: 2013/11/21
 *      Author: Naoto
 */

#ifndef STRUCTOR_H_
#define STRUCTOR_H_

typedef struct {			//センサ情報用
	float on;				//LEDがON
	float off;			//LEDがOFF
	float now;			//現在の値
	float old;
	float ref;			//リファレンス
	float ref2;
	float ref3;

	float th;				//閾値
	int th_control;		//制御をかけるか否かの閾値
	int wall_limit;
	int exitst;
	int exitstCount;
	int vanishCount;

	float dist;	//距離[mm]

} t_sensor;
volatile t_sensor LS_SEN45, RS_SEN45, Front_SEN, G, LS_SEN2, RS_SEN2;

volatile char sen_r[5];
volatile char sen_l[5];
volatile char sen_r2[5];
volatile char sen_l2[5];
volatile float sen_log_r[5];
volatile float sen_log_l[5];
volatile float sen_log_front[5];
volatile float sen_log_fl[5];
volatile float sen_log_r2[5];
volatile float sen_log_l2[5];

volatile float peekSideR, peekSideL;

typedef struct {
	float error_now;
	float error_old;
	float error_delta;
	float before;
} t_Errors;
volatile t_Errors Se, Se2, Se3, Vr, Vl, Gy, Velocity, W_enc, Wl, Angle, SeFrntL,
		SeFrnt, SeFrntAngle, Distance;
typedef struct {
	float Kp;
	float Ki;
	float Kd;
} t_PID;
volatile t_PID Vel_r, Vel_l, Gyro, Sen, Sen_Dia, Sen_Dia_Side, Vel, Omega,
		Angles, Backs, FrontCtrl, FrontCtrlAngle, Dists, Dists2;
typedef struct {
	float r;
	float l;
} t_Enc;
volatile t_Enc V_Enc;
typedef struct {
	float s;
	float g;
	float angles;
	float s2;
	float v;
	float v2;
	float w;
} t_Control;
volatile t_Control C, C_old;

typedef struct {
	float targetAngle;
	float radius;
	float front1;
	float front2;
	float back1;
	float back2;
	float time;
	float n;
	float velocity;
	float frontLeft1;
	float frontLeft2;
	float firstFront;
} t_radiusData;
volatile t_radiusData pNormal, pLarge, pOrval, pD45, pD135, pD90, pKojima;

typedef struct {
	float sequence;
	float accele;
} t_mode;
#endif /* STRUCTOR_H_ */
