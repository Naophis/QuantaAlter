/*
 * ParamDef.h
 *
 *  Created on: 2013/11/21
 *      Author: Naoto
 */

#ifndef PARAMDEF_H_
#define PARAMDEF_H_

float TIRE = 24.745f;
float WHEEL;
float GEAR_A;
float GEAR_B;
float GEAR = 63.0 / 19.0;
float DUTY_MAX = 99.9f;
float Ke = 0.000368613538f;
float Km = 0.00352f;
float Resist = 2.93f;
float Mass = 0.101f;
float Lm = 0.001f;
float friction = 0.00125f;
float friction2 = 0.001925f;

#define W_ENCORDER_LIMIT 100
#define W_ENCORDER_LIMIT2 10
#define W_ENCORDER_LIMIT_DIA 150
#define W_ENCORDER_LIMIT_DIA2 10
float gyroTh_R, gyroTh_L;
float pivotR, pivotL;
float Gkp, Gki, Gkd;
float Gkp2, Gki2, Gkd2;
float Akp, Aki, Akd;
float Akp2, Aki2, Akd2;
float Wkp, Wki, Wkd;
float Beta = 0;
float BetaOld = 0;
float k = 10;
float Vkp_r, Vki_r, Vkd_r;
float Vkp_l, Vki_l, Vkd_l;
float Vkp, Vki, Vkd;

#define orderup_r 4000
#define orderup_l 4000
#define supR_WALL 2000
#define supL_WALL 2000

//#define KIREME_R_DIA_SIDE 20
//#define KIREME_L_DIA_SIDE 20

/**
 * ↓　迷路・壁に依存する　調整パラメータ
 */

float wallhosei = 100;

/**
 * 調整以上
 */
int bias = 1;
int strBias = 3;
int diaBias = 3;
int Dia = 5;
int St1 = 7;
int minus = 3;
int Dia2;
int Dia3;
int St2;
int St3;

void importFromDataFlash() {
	TIRE = *(float *) 1049216;
	myprintf("TIRE	%f	%d\r\n", TIRE, 1049216);
	GEAR_A = *(float *) 1049220;
	myprintf("GEAR_A	%f	%d\r\n", GEAR_A, 1049220);
	GEAR_B = *(float *) 1049224;
	myprintf("GEAR_B	%f	%d\r\n", GEAR_B, 1049224);
	DUTY_MAX = *(float *) 1049228;
	myprintf("DUTY_MAX	%f	%d\r\n", DUTY_MAX, 1049228);
	Ke = *(float *) 1049232;
	myprintf("Ke	%f	%d\r\n", Ke, 1049232);
	Km = *(float *) 1049236;
	myprintf("Km	%f	%d\r\n", Km, 1049236);
	Resist = *(float *) 1049240;
	myprintf("Resist	%f	%d\r\n", Resist, 1049240);
	Mass = *(float *) 1049244;
	myprintf("Mass	%f	%d\r\n", Mass, 1049244);
	Lm = *(float *) 1049248;
	myprintf("Lm	%f	%d\r\n", Lm, 1049248);
	friction = *(float *) 1049252;
	myprintf("friction	%f	%d\r\n", friction, 1049252);
	friction2 = *(float *) 1049256;
	myprintf("friction2	%f	%d\r\n", friction2, 1049256);

	gyroTh_R = *(float *) 1049344;
	myprintf("gyroTh_R	%f	%d\r\n", gyroTh_R, 1049344);
	gyroTh_L = *(float *) 1049348;
	myprintf("gyroTh_L	%f	%d\r\n", gyroTh_L, 1049348);
	Vel.Kp = *(float *) 1049352;
	myprintf("Vel.Kp	%f	%d\r\n", Vel.Kp, 1049352);
	Vel.Ki = *(float *) 1049356;
	myprintf("Vel.Ki	%f	%d\r\n", Vel.Ki, 1049356);
	Vel.Kd = *(float *) 1049360;
	myprintf("Vel.Kd	%f	%d\r\n", Vel.Kd, 1049360);
	Gyro.Kp = *(float *) 1049364;
	myprintf("Gyro.Kp	%f	%d\r\n", Gyro.Kp, 1049364);
	Gyro.Ki = *(float *) 1049368;
	myprintf("Gyro.Ki	%f	%d\r\n", Gyro.Ki, 1049368);
	Gyro.Kd = *(float *) 1049372;
	myprintf("Gyro.Kd	%f	%d\r\n", Gyro.Kd, 1049372);
	Sen.Kp = *(float *) 1049376;
	myprintf("Sen.Kp	%f	%d\r\n", Sen.Kp, 1049376);
	Sen.Ki = *(float *) 1049380;
	myprintf("Sen.Ki	%f	%d\r\n", Sen.Ki, 1049380);
	Sen.Kd = *(float *) 1049384;
	myprintf("Sen.Kd	%f	%d\r\n", Sen.Kd, 1049384);
	Sen_Dia.Kp = *(float *) 1049388;
	myprintf("Sen_Dia.Kp	%f	%d\r\n", Sen_Dia.Kp, 1049388);
	Sen_Dia.Ki = *(float *) 1049392;
	myprintf("Sen_Dia.Ki	%f	%d\r\n", Sen_Dia.Ki, 1049392);
	Sen_Dia.Kd = *(float *) 1049396;
	myprintf("Sen_Dia.Kd	%f	%d\r\n", Sen_Dia.Kd, 1049396);
	FrontCtrl.Kp = *(float *) 1049400;
	myprintf("FrontCtrl.Kp	%f	%d\r\n", FrontCtrl.Kp, 1049400);
	FrontCtrl.Ki = *(float *) 1049404;
	myprintf("FrontCtrl.Ki	%f	%d\r\n", FrontCtrl.Ki, 1049404);

	RS_SEN1.ref = *(float *) 1049600;
	myprintf("RS_SEN1.ref	%f	%d\r\n", RS_SEN1.ref, 1049600);
	LS_SEN1.ref = *(float *) 1049604;
	myprintf("LS_SEN1.ref	%f	%d\r\n", LS_SEN1.ref, 1049604);
	RS_SEN1.ref2 = *(float *) 1049608;
	myprintf("RS_SEN1.ref2	%f	%d\r\n", RS_SEN1.ref2, 1049608);
	LS_SEN1.ref2 = *(float *) 1049612;
	myprintf("LS_SEN1.ref2	%f	%d\r\n", LS_SEN1.ref2, 1049612);
	RF_SEN1.ref = *(float *) 1049616;
	myprintf("RF_SEN1.ref	%f	%d\r\n", RF_SEN1.ref, 1049616);
	RF_SEN1.ref2 = *(float *) 1049620;
	myprintf("RF_SEN1.ref2	%f	%d\r\n", RF_SEN1.ref2, 1049620);
	LF_SEN1.ref = *(float *) 1049624;
	myprintf("LF_SEN1.ref	%f	%d\r\n", LF_SEN1.ref, 1049624);
	LF_SEN1.ref2 = *(float *) 1049628;
	myprintf("LF_SEN1.ref2	%f	%d\r\n", LF_SEN1.ref2, 1049628);
	RF_SEN1.ref3 = *(float *) 1049632;
	myprintf("RF_SEN1.ref3	%f	%d\r\n", RF_SEN1.ref3, 1049632);
	LF_SEN1.ref3 = *(float *) 1049636;
	myprintf("LF_SEN1.ref3	%f	%d\r\n", LF_SEN1.ref3, 1049636);
	wallhosei = *(float *) 1049640;
	myprintf("wallhosei	%f	%d\r\n", wallhosei, 1049640);
	FrontCtrl.Kp = *(float *) 1049644;
	myprintf("FrontCtrl.Kp	%f	%d\r\n", FrontCtrl.Kp, 1049644);
	FrontCtrl.Ki = *(float *) 1049648;
	myprintf("FrontCtrl.Ki	%f	%d\r\n", FrontCtrl.Ki, 1049648);

}
void importParam() {
	importFromDataFlash();
	WHEEL = TIRE / 2000;
	GEAR = GEAR_A / GEAR_B;

	Dia2 = Dia - minus + 2;
	Dia3 = Dia - minus + 1;
	St2 = St1 - minus;
	St3 = St1 - minus - 1;

	G.th = gyroTh_R;
	pivotR = gyroTh_R;
	pivotL = gyroTh_L;

	tempGyro = 0;

	Vkp = Vel.Kp;
	Vki = Vel.Ki;
	Vkd = Vel.Kd;
	Gkp = Gyro.Kp;
	Gki = Gyro.Ki;
	Gkd = Gyro.Kd;
	Akp = Angles.Kp;
	Aki = Angles.Ki;
	Akd = Angles.Kd;

}

void resetFB() {
	Vel_r.Kp = 0.0;
	Vel_r.Ki = 0.0;
	Vel_r.Kd = 0.0;
	Vel_l.Kp = 0.0;
	Vel_l.Ki = 0.00;
	Vel_l.Kd = 0.0;
}

void readGyroParamP() {
	Gyro.Kp = Gkp;
	Gyro.Ki = 0;
	Gyro.Kd = 0;
}
void readGyroParam() {
	Gyro.Kp = Gkp;
	Gyro.Ki = Gki;
	Gyro.Kd = Gkd;
}
void readGyroParam2() {
	Gyro.Kp = Gkp2;
	Gyro.Ki = Gki2;
	Gyro.Kd = Gkd2;
}
void resetGyroParam() {
	Gyro.Kp = 0;
	Gyro.Ki = 0;
	Gyro.Kd = 0;
}
void resetAngleParam() {
	Angles.Kp = 0;
	Angles.Ki = 0;
	Angles.Kd = 0;
}

void resetOmegaParam() {
	Omega.Kp = 0;
	Omega.Ki = 0;
	Omega.Kd = 0;
}
void readOmegaParam() {
	Omega.Kp = Wkp;
	Omega.Ki = Wki;
	Omega.Kd = Wkd;
}
void readAngleParam() {
	Angles.Kp = Akp;
	Angles.Ki = Aki;
	Angles.Kd = Akd;
}
void readAngleParamP() {
	Angles.Kp = Akp;
	Angles.Ki = 0;
	Angles.Kd = 0;
}
void readVelocityGain() {
	Vel.Kp = Vkp;
	Vel.Ki = Vki;
	Vel.Kd = Vkd;
}
#endif /* PARAMDEF_H_ */
