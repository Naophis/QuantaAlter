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
float Mass = 0.106f;
float Lm = 0.001f;
float friction = 0.00125f;
float friction2 = 0.001925f;

unsigned int running_wall_off_r = 500;
unsigned int running_wall_off_l = 500;

unsigned int search_wall_off_r = 1500;
unsigned int search_wall_off_l = 1400;

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

float wallhosei = 800;

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

float R_WALL_OFF = 220;	//壁切れ　閾値
float L_WALL_OFF = 580;	//壁切れ　閾値
float R_WALL_OFF2 = 270;	//壁切れ　閾値
float L_WALL_OFF2 = 650;	//壁切れ　閾値
float R_WALL_OFF_D2 = 485;  //壁切れ　閾値　斜め用
float L_WALL_OFF_D2 = 740; //壁切れ　閾値　斜め用
float R_WALL_OFF_D = 570;  //壁切れ　閾値　斜め用
float L_WALL_OFF_D = 1000; //壁切れ　閾値　斜め用

float FRONT_WALL_ON = 610; //壁切れ　閾値　斜め用
float FRONT_WALL_ORDER = 420; //壁切れ　閾値　斜め用

float DIA_N_LEFT_WALL = 850; //壁切れ　閾値　斜め用
float DIA_N_RIGHT_WALL = 910; //壁切れ　閾値　斜め用

float DIA_FRONT_WALL_ORDER = 360; //壁切れ　閾値　斜め用

float existRightWall5 = 10000;  //壁切れの予備
float existLeftWall5 = 10000;   //壁切れの予備

float R_WALL_DIA = 1900;
float L_WALL_DIA = 1500;

float R_WALL_DIA2 = 1900;
float L_WALL_DIA2 = 1500;

float R_WALL_DIA3 = 1900;
float L_WALL_DIA3 = 1500;

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
	Sen_Dia_Side.Kp = *(float *) 1049388;
	myprintf("Sen_Dia_Side.Kp	%f	%d\r\n", Sen_Dia_Side.Kp, 1049388);
	Sen_Dia_Side.Ki = *(float *) 1049392;
	myprintf("Sen_Dia_Side.Ki	%f	%d\r\n", Sen_Dia_Side.Ki, 1049392);
	Sen_Dia_Side.Kd = *(float *) 1049396;
	myprintf("Sen_Dia_Side.Kd	%f	%d\r\n", Sen_Dia_Side.Kd, 1049396);
	FrontCtrl.Kp = *(float *) 1049400;
	myprintf("FrontCtrl.Kp	%f	%d\r\n", FrontCtrl.Kp, 1049400);
	FrontCtrl.Ki = *(float *) 1049404;
	myprintf("FrontCtrl.Ki	%f	%d\r\n", FrontCtrl.Ki, 1049404);

	RS_SEN45.ref = *(float *) 1049600;
	myprintf("RS_SEN45.ref	%f	%d\r\n", RS_SEN45.ref, 1049600);
	LS_SEN45.ref = *(float *) 1049604;
	myprintf("LS_SEN45.ref	%f	%d\r\n", LS_SEN45.ref, 1049604);
	RS_SEN45.ref2 = *(float *) 1049608;
	myprintf("RS_SEN45.ref2	%f	%d\r\n", RS_SEN45.ref2, 1049608);
	LS_SEN45.ref2 = *(float *) 1049612;
	myprintf("LS_SEN45.ref2	%f	%d\r\n", LS_SEN45.ref2, 1049612);
	Front_SEN.ref = *(float *) 1049616;
	myprintf("Front_SEN.ref	%f	%d\r\n", Front_SEN.ref, 1049616);
	Front_SEN.ref2 = *(float *) 1049620;
	myprintf("Front_SEN.ref2	%f	%d\r\n", Front_SEN.ref2, 1049620);
//	LF_SEN1.ref = *(float *) 1049624;
//	myprintf("LF_SEN1.ref	%f	%d\r\n", LF_SEN1.ref, 1049624);
//	LF_SEN1.ref2 = *(float *) 1049628;
//	myprintf("LF_SEN1.ref2	%f	%d\r\n", LF_SEN1.ref2, 1049628);
	Front_SEN.ref3 = *(float *) 1049632;
	myprintf("Front_SEN.ref3	%f	%d\r\n", Front_SEN.ref3, 1049632);
//	LF_SEN1.ref3 = *(float *) 1049636;
//	myprintf("LF_SEN1.ref3	%f	%d\r\n", LF_SEN1.ref3, 1049636);
	wallhosei = *(float *) 1049640;
	myprintf("wallhosei	%f	%d\r\n", wallhosei, 1049640);
	FrontCtrl.Kp = *(float *) 1049644;
	myprintf("FrontCtrl.Kp	%f	%d\r\n", FrontCtrl.Kp, 1049644);
	FrontCtrl.Ki = *(float *) 1049648;
	myprintf("FrontCtrl.Ki	%f	%d\r\n", FrontCtrl.Ki, 1049648);
	RS_SEN2.ref2 = *(float *) 1049652;
	myprintf("RS_SEN2.ref2	%f	%d\r\n", RS_SEN2.ref2, 1049652);
	LS_SEN2.ref2 = *(float *) 1049656;
	myprintf("LS_SEN2.ref2	%f	%d\r\n", LS_SEN2.ref2, 1049656);
	R_WALL_DIA = *(float *) 1049660;
	myprintf("R_WALL_DIA	%f	%d\r\n", R_WALL_DIA, 1049660);
	L_WALL_DIA = *(float *) 1049664;
	myprintf("L_WALL_DIA	%f	%d\r\n", L_WALL_DIA, 1049664);
	R_WALL_DIA2 = *(float *) 1049668;
	myprintf("R_WALL_DIA2	%f	%d\r\n", R_WALL_DIA2, 1049668);
	L_WALL_DIA2 = *(float *) 1049672;
	myprintf("L_WALL_DIA2	%f	%d\r\n", L_WALL_DIA2, 1049672);
	R_WALL_DIA3 = *(float *) 1049676;
	myprintf("R_WALL_DIA3	%f	%d\r\n", R_WALL_DIA3, 1049676);
	R_WALL_DIA3 = *(float *) 1049680;
	myprintf("R_WALL_DIA3	%f	%d\r\n", R_WALL_DIA3, 1049680);
	L_WALL_EXIST2 = *(float *) 1049684;
	myprintf("L_WALL_EXIST2	%f	%d\r\n", L_WALL_EXIST2, 1049684);
	R_WALL_EXIST2 = *(float *) 1049688;
	myprintf("R_WALL_EXIST2	%f	%d\r\n", R_WALL_EXIST2, 1049688);
	FRONT_WALL_EXIST2 = *(float *) 1049692;
	myprintf("FRONT_WALL_EXIST2	%f	%d\r\n", FRONT_WALL_EXIST2, 1049692);
	L_WALL_EXIST3 = *(float *) 1049696;
	myprintf("L_WALL_EXIST3	%f	%d\r\n", L_WALL_EXIST3, 1049696);
	R_WALL_EXIST3 = *(float *) 1049700;
	myprintf("R_WALL_EXIST3	%f	%d\r\n", R_WALL_EXIST3, 1049700);
	FRONT_WALL_EXIST3 = *(float *) 1049704;
	myprintf("FRONT_WALL_EXIST3	%f	%d\r\n", FRONT_WALL_EXIST3, 1049704);
	running_wall_off_l = *(float *) 1049708;
	myprintf("running_wall_off_l	%f	%d\r\n", running_wall_off_l, 1049708);
	running_wall_off_r = *(float *) 1049712;
	myprintf("running_wall_off_r	%f	%d\r\n", running_wall_off_r, 1049712);
	search_wall_off_l = *(float *) 1049716;
	myprintf("search_wall_off_l	%f	%d\r\n", search_wall_off_l, 1049716);
	search_wall_off_r = *(float *) 1049720;
	myprintf("search_wall_off_r	%f	%d\r\n", search_wall_off_r, 1049720);

	R_WALL_OFF = *(float *) 1049856;
	myprintf("R_WALL_OFF	%f	%d\r\n", R_WALL_OFF, 1049856);
	L_WALL_OFF = *(float *) 1049860;
	myprintf("L_WALL_OFF	%f	%d\r\n", L_WALL_OFF, 1049860);
	R_WALL_OFF2 = *(float *) 1049864;
	myprintf("R_WALL_OFF2	%f	%d\r\n", R_WALL_OFF2, 1049864);
	L_WALL_OFF2 = *(float *) 1049868;
	myprintf("L_WALL_OFF2	%f	%d\r\n", L_WALL_OFF2, 1049868);
	R_WALL_OFF_D = *(float *) 1049872;
	myprintf("R_WALL_OFF_D	%f	%d\r\n", R_WALL_OFF_D, 1049872);
	L_WALL_OFF_D = *(float *) 1049876;
	myprintf("L_WALL_OFF_D	%f	%d\r\n", L_WALL_OFF_D, 1049876);
	existRightWall5 = *(float *) 1049880;
	myprintf("existRightWall5	%f	%d\r\n", existRightWall5, 1049880);
	existLeftWall5 = *(float *) 1049884;
	myprintf("existLeftWall5	%f	%d\r\n", existLeftWall5, 1049884);
	R_WALL_OFF_D2 = *(float *) 1049888;
	myprintf("R_WALL_OFF_D2	%f	%d\r\n", R_WALL_OFF_D2, 1049888);
	L_WALL_OFF_D2 = *(float *) 1049892;
	myprintf("L_WALL_OFF_D2	%f	%d\r\n", L_WALL_OFF_D2, 1049892);
	FRONT_WALL_ON = *(float *) 1049896;
	myprintf("FRONT_WALL_ON	%f	%d\r\n", FRONT_WALL_ON, 1049896);
	FRONT_WALL_ORDER = *(float *) 1049900;
	myprintf("FRONT_WALL_ORDER	%f	%d\r\n", FRONT_WALL_ORDER, 1049900);
	DIA_N_LEFT_WALL = *(float *) 1049904;
	myprintf("DIA_N_LEFT_WALL	%f	%d\r\n", DIA_N_LEFT_WALL, 1049904);
	DIA_N_RIGHT_WALL = *(float *) 1049908;
	myprintf("DIA_N_RIGHT_WALL	%f	%d\r\n", DIA_N_RIGHT_WALL, 1049908);
	DIA_FRONT_WALL_ORDER = *(float *) 1049912;
	myprintf("DIA_FRONT_WALL_ORDER	%f	%d\r\n", DIA_FRONT_WALL_ORDER, 1049912);

}

void override() {
	TIRE = 24.45;
	GEAR_A = 67;
	GEAR_B = 21;
	DUTY_MAX = 99.9;
	Ke = 0.000369;
	Km = 0.00352;
	Resist = 2.93;
	Mass = 0.106;
	Lm = 0.001;
	friction = 0.00125;
	friction2 = 0.001925;
	gyroTh_R = 0.001054;
	gyroTh_L = 0.001054;

	Vel.Kp = 0.004125;
	Vel.Ki = 0.00095;
	Vel.Kd = 0.0045;

	Gyro.Kp = 1.25;
	Gyro.Ki = 0.01;
	Gyro.Kd = 10.5;

	Sen.Kp = 0.0025;
	Sen.Ki = 0.001;
	Sen.Kd = 0.065;

	Sen_Dia.Kp = 0.1;
	Sen_Dia.Ki = 0;
	Sen_Dia.Kd = 0;

	Sen_Dia_Side.Kp = 0.0045;
	Sen_Dia_Side.Ki = 0;
	Sen_Dia_Side.Kd = 0.0;

	FrontCtrl.Kp = 0.125;
	FrontCtrl.Ki = 0;

	RS_SEN45.ref = 880;
	LS_SEN45.ref = 680;

	RS_SEN45.ref2 = 2200;
	LS_SEN45.ref2 = 1900;

	Front_SEN.ref = 200;
	Front_SEN.ref2 = 0;
	Front_SEN.ref3 = 2143;
	wallhosei = 100;
	FrontCtrl.Kp = 0.125;
	FrontCtrl.Ki = 0;
//壁切れ
	R_WALL_OFF = 590;
	L_WALL_OFF = 530;
	R_WALL_OFF2 = 590;
	L_WALL_OFF2 = 530;
//壁切れ　斜め
	R_WALL_OFF_D = 1700;
	L_WALL_OFF_D = 1400;
	existRightWall5 = 3900;
	existLeftWall5 = 3900;
	R_WALL_OFF_D2 = 1700;
	L_WALL_OFF_D2 = 1400;

}
void importParam() {
	importFromDataFlash();
//	override();
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
//	myprintf("%f	%f	%f\r\n", Vel.Kp, Vel.Ki, Vel.Kd);
}
void resetVelocityGain() {
	Vel.Kp = 0;
	Vel.Ki = 0;
	Vel.Kd = 0;
}
#endif /* PARAMDEF_H_ */
