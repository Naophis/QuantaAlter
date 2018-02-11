/*
 * OperationSystem.h
 *
 *  Created on: 2013/11/22
 *      Author: Naoto
 */

#ifndef OPERATIONSYSTEM_H_
#define OPERATIONSYSTEM_H_

void operation();
char encorderOperation();

void sensourCheck() {
	positionControlValueFlg = 1;
	ledOn = 1;
	resetGyroParam();
	resetAllData();
//	mtu_start();
	V_now = 0;
	while (Swich == 1) {
		myprintf("%d	%d	%d	%d	%d\n", (int) LS_SEN1.now, (int) LF_SEN1.now,
				(int) RF_SEN1.now, (int) RS_SEN1.now, (int) (Se.error_now));
		cmt_wait(100);
//		SCI_SCI_printf("%d %d	%d	%d\n", MTU2.TCNT, MTU1.TCNT, (int) V_Enc.l,
//				(int) V_Enc.r);
	}
	while (Swich == 0)
		;
	cmt_wait(500);
	ledOn = 0;
}
void testRun() {
	float velocity = 500;
	float accele = 2000;
	float diaccele = 1800;
	float vMax = 100;

	gyroZeroCheck(true);
	cmt_wait(500);
	if (velocity > 2000) {
		startVacume2(99);
		cmt_wait(200);
	}
	cc = 1;
	gyroOn = 1;
	V_now = 0;

	mtu_start();
//	dia = 1;
	if (dia == 1) {
		realRun(velocity, accele, diaccele, 180.0 * ROOT2 * 3.0, vMax);
	} else {
		realRun(velocity, accele, diaccele, 180.0 * 4.5, vMax);
	}
//	running(100, -diaccele, 180, 1);
//	mtu_stop2();
//	gyroRoll(R, 180, 20, 25);
//
//	mtu_start();
////	dia = 1;
//	realRun(velocity, accele, diaccele, 180.0 * 3.5, vMax);

//	wallOff(R);
//	running2(velocity, accele, 180, 1);
//	V_now = 0;
//	cmt_wait(1000);
//	resetAllData();

//	frontCtrl();
//	isOverFront();
//	resetAllData();
//	mtu_stop2();
//	ledOn = 1;

	mtu_stop2();
	logOutPut();
}
void testRun1(float v, float accele, float diaccele, float dist, float vM,
		char b1) {
	char check = 1;
	gyroZeroCheck(true);
	if (b1) {
		startVacume();
		cmt_wait(1000);
	}
	cc = 1;
	gyroOn = 1;
	V_now = 0;
	mtu_start();
	dia = 0;
	check = realRun(v, accele, diaccele, dist - 180, vM);
	if (check == 1) {
		running(100, -diaccele, 180, 1);
	}
	cc = 0;
	mtu_stop();
	stopVacume();
}
void testRun2(float v, float accele, float diaccele, float dist, float vM) {
	char check = 1;
	gyroZeroCheck(false);
	cc = 1;
	gyroOn = 1;
	V_now = 0;
	mtu_start();
	dia = 0;
	check = realRun(v, accele, diaccele, dist - 90, vM);
	if (check == 1) {
		running(100, -diaccele, 90, 1);
	}
	cc = 0;
	mtu_stop();
	stopVacume();
}
// search parm
//inputRadiusDatas(Normal, 44.5, 45.5, 108.75, 33, 9, 21.5, 0, 0);

void inputNaiperTurnAll500_2() {
	setPrms(Large, 90, 125.0, 22.0, 5.0, 0, 0, 0.16079235076904297, 4, 800);
	setPrms3(Large, 20.0, 0);
	setPrms(Orval, 180, 88.0, 30.0, 15.0, 0, 0, 0.2263946533203125, 4, 800);
	setPrms3(Orval, 30, 0);
	setPrms(Dia45, 45, 130, 20, 20.0, 66, 20, 0.08361244201660156, 4, 800);
	setPrms3(Dia45, 15.5, 60);
	setPrms(Dia135, 135, 83, 30, 10, 28, 15.5, 0.16014862060546875, 4, 800);
	setPrms3(Dia135, 36, 32);
	setPrms(Dia90, 90, 83.0, 29, 10.0, 0, 0, 0.1067657470703125, 4, 800);
	setPrms3(Dia90, 25, 0);
	setPrms(Normal, 90, 45, 12, 30, 0, 0, 0.09761428833007812, 2, 600);
	setPrms3(Normal, 7, 35);

	setPrms(Large, 90, 125.0, 22.0, 20.0, 0, 0, 0.16079235076904297, 4, 800);
	setPrms3(Large, 16.75, 0);
	setPrms(Orval, 180, 88.0, 30.0, 25.0, 0, 0, 0.2263946533203125, 4, 800);
	setPrms3(Orval, 30, 0);
	setPrms(Dia45, 45, 130, 16, 20.0, 62, 10, 0.08361244201660156, 4, 800);
	setPrms3(Dia45, 16, 60);
	setPrms(Dia135, 135, 83, 36, 10, 22, 20, 0.16014862060546875, 4, 800);
	setPrms3(Dia135, 26, 26);
	setPrms(Dia90, 90, 83.0, 25, 10.0, 0, 0, 0.1067657470703125, 4, 800);
	setPrms3(Dia90, 24, 0);

	setPrms(Normal, 90, 50, 16.75, 39.0, 0, 0, 0.10290718078613281, 4, 500);
	setPrms3(Normal, 19, 39.5);

	setPrms(Normal, 90, 50, 15.25, 45.0, 0, 0, 0.10290718078613281, 4, 500);
	setPrms3(Normal, 21, 43.0);

	setPrms(Normal, 90, 50, 19.0, 36.5, 0, 0, 0.10290718078613281, 4, 500);
	setPrms3(Normal, 19, 37.0);

	setPrms(Normal, 90, 50, 17.0, 37.5, 0, 0, 0.10290718078613281, 4, 500);
	setPrms3(Normal, 18.0, 39.75);

	setPrms(Normal, 90, 50, 17.0, 39.0, 0, 0, 0.10290718078613281, 4, 500);
	setPrms3(Normal, 19.0, 39.0);

	setPrms(Normal, 90, 55, 10.0, 27.5, 0, 0, 0.056598663330078125, 4, 1000);
	setPrms3(Normal, 10.0, 30.5);
}

void inputNaiperTurnAll1200() {
	setPrms(Large, 90, 125.0, 12.5, 22, 0, 0, 0.10719490051269531, 4, 1200);
	setPrms3(Large, 16.25, 0);
	setPrms(Orval, 180, 86.5, 35, 35, 0, 0, 0.14835739135742188, 4, 1200);
	setPrms3(Orval, 35, 0);
	setPrms(Dia45, 45, 120, 18.0, 50, 64, 15, 0.051453590393066406, 4, 1200);
	setPrms3(Dia45, 23, 65.5);
	setPrms(Dia135, 135, 80, 34.5, 20, 26, 31, 0.10290718078613281, 4, 1200);
	setPrms3(Dia135, 36.5, 25.0);
	setPrms(Dia90, 90, 80.0, 26.5, 17, 0, 0, 0.0686044692993164, 4, 1200);
	setPrms3(Dia90, 25.5, 0);

	setPrms(Large, 90, 125.0, 11.5, 22, 0, 0, 0.10719490051269531, 4, 1200);
	setPrms3(Large, 16.125, 0);
	setPrms(Orval, 180, 86.5, 35, 35, 0, 0, 0.14835739135742188, 4, 1200);
	setPrms3(Orval, 35, 0);
	setPrms(Dia45, 45, 120, 14.0, 50, 68, 15, 0.051453590393066406, 4, 1200);
	setPrms3(Dia45, 19.5, 64.0);
	setPrms(Dia135, 135, 80, 31.0, 20, 30.5, 30, 0.10290718078613281, 4, 1200);
	setPrms3(Dia135, 37.0, 30.5);
	setPrms(Dia90, 90, 80.0, 29.25, 17, 0, 0, 0.0686044692993164, 4, 1200);
	setPrms3(Dia90, 26.5, 0);
}

void inputNaiperTurnAll1500() {
	setPrms(Large, 90, 125.0, 8.5, 20, 0, 0, 0.08575630187988281, 4, 1500);
	setPrms3(Large, 13.5, 0);
	setPrms(Orval, 180, 86.5, 20, 35, 0, 0, 0.11868572235107422, 4, 1500);
	setPrms3(Orval, 20, 38);
	setPrms(Dia45, 45, 125, 9.25, 53, 62.0, 14, 0.042878150939941406, 4, 1500);
	setPrms3(Dia45, 13.0, 58.0);
	setPrms(Dia135, 135, 85, 13.5, 15, 13.0, 25, 0.08747100830078125, 4, 1500);
	setPrms3(Dia135, 18.5, 8.75);
	setPrms(Dia90, 90, 85.0, 18.25, 15.0, 0, 0, 0.05831432342529297, 4, 1500);
	setPrms3(Dia90, 15.25, 0);
}

void inputNaiperTurnAll1700() {
	setPrms(Large, 90, 125, 5.5, 20.0, 0, 0, 0.0756673812866211, 4, 1700);
	setPrms3(Large, 10.85, 0);
	setPrms(Orval, 180, 86.5, 20.0, 50.0, 0, 0, 0.10472297668457031, 4, 1700);
	setPrms3(Orval, 20, 52);
	setPrms(Dia45, 45, 120.0, 6.0, 60, 59.5, 25, 0.03632068634033203, 4, 1700);
	setPrms3(Dia45, 10.5, 57.0);
	setPrms(Dia135, 135, 85, 5.75, 20, 8.25, 35, 0.07718086242675781, 4, 1700);
	setPrms3(Dia135, 17.0, 5.5);
	setPrms(Dia90, 90, 85, 13.5, 20.0, 0, 0, 0.051453590393066406, 4, 1700);
	setPrms3(Dia90, 10.9, 0);

}
void inputNaiperTurnAll1800() {

	setPrms(Large, 90, 120.0, 7.75, 20.0, 0, 0, 0.0686044692993164, 4, 1800);
	setPrms3(Large, 13.0, 0);
	setPrms(Orval, 180, 86.5, 10.0, 65.0, 0, 0, 0.09890556335449219, 4, 1800);
	setPrms3(Orval, 10, 65);
	setPrms(Dia45, 45, 110.0, 8, 68.0, 62.0, 30, 0.031444549560546875, 4, 1800);
	setPrms3(Dia45, 10.75, 53);
	setPrms(Dia135, 135, 80, 16.125, 45, 21.5, 45, 0.0686044692993164, 4, 1800);
	setPrms3(Dia135, 24.25, 19.5);
	setPrms(Dia90, 90, 83.0, 7.5, 45.0, 0, 0, 0.04745197296142578, 4, 1800);
	setPrms3(Dia90, 3.9, 0);

	setPrms(Dia90, 90, 85, 13.5, 20.0, 0, 0, 0.051453590393066406, 4, 1700);
	setPrms3(Dia90, 10.9, 0);

}
void inputNaiperTurnAll1900() {
	inputNaiperTurnAll1800();
	setPrms(Large, 90, 115.0, 9.875, 45.0, 0, 0, 0.062286376953125, 4, 1900);
	setPrms3(Large, 15.0, 0);
	setPrms(Orval, 180, 87.5, 10.0, 65.0, 0, 0, 0.09478282928466797, 4, 1900);
	setPrms3(Orval, 10, 65);

}
void inputNaiperTurnAll2000() {
	inputNaiperTurnAll1800();
	setPrms(Orval, 180, 88.5, 10.0, 80.0, 0, 0, 0.09107303619384766, 4, 2000);
	setPrms3(Orval, 10, 90);
}
/**
 * 	t_radiusData large;
 t_radiusData orval;
 t_radiusData dia45;
 t_radiusData dia135;
 t_radiusData dia90;
 t_radiusData kojima;
 */
void testSlalom() {
	float vMax = 1500;
	float maxVelocity = 500;
	float accele = 8000;
	float diaccele = 8000;
	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
	dia = 1;
	realRun(maxVelocity, accele, diaccele, 90 * 1, vMax);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	led(1, 1, 1, 1);
	slalom3(R, Normal, vMax, vMax, 0);
	led(0, 0, 0, 0);
	cc = 0;
	realRun(maxVelocity, accele, diaccele, 90.0 * 1.0, 50);
	C.g = 0;
	C.angles = 0;
	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	Angle.error_old = 0;
	mtu_stop();
	cmt_wait(500);
	logOutPut();
}

void loadNaname(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
	wall_off_limit = 20;
	wall_off_limit_d = 25;
	for (int i = 0; i < 1; i++) {
		wallOff(R);
		slalom3(R, Dia45, vMax, vMax, 0);
		realRun(maxVelocity, accele, diaccele, 180.0 * ROOT2 * 1.5, vMax);
		wallOff(R);
		slalom3(R, Dia135, vMax, vMax, 0);
		wallOff(R);
		slalom3(R, Dia45, vMax, vMax, 0);
		realRun(maxVelocity, accele, diaccele, 180.0 * ROOT2 * 2, vMax);
		wallOff(L);
		slalom3(L, Dia135, vMax, vMax, 0);
		realRun(maxVelocity, accele, diaccele, 180.0 * 1, vMax);
		wallOff(L);
		slalom3(L, Large, vMax, vMax, 0);
		wallOff(L);
		slalom3(L, Dia45, vMax, vMax, 0);
		realRun(maxVelocity, accele, diaccele, 180.0 * ROOT2 * 2, vMax);
		wallOff(R);
		slalom3(R, Dia135, vMax, vMax, 0);
		wallOff(R);
		slalom3(R, Dia135, vMax, vMax, 0);
		realRun(maxVelocity, accele, diaccele, 180.0 * ROOT2, vMax);
		wallOff(L);
		slalom3(L, Dia45, vMax, vMax, 0);
		realRun(maxVelocity, accele, diaccele, 180.0 * 1, vMax);
		wallOff(L);
		slalom3(L, Large, vMax, vMax, 0);
		wallOff(L);
		slalom3(L, Large, vMax, vMax, 0);
		wallOff(L);
		slalom3(L, Dia135, vMax, vMax, 0);
		wallOff(R);
		slalom3(R, Dia135, vMax, vMax, 0);
	}
}
void testLargeTurn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
	for (int i = 0; i < 4; i++) {
		wallOff(RorL);
		slalom3(RorL, Large, vMax, vMax, 0);
	}
}
void testOrvalTurn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
	for (int i = 0; i < 4; i++) {
		wallOff(RorL);
		slalom3(RorL, Orval, vMax, vMax, 0);
	}
}
void testDia45Turn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
	for (int i = 0; i < 1; i++) {
		wallOff(RorL);
		slalom3(RorL, Dia45, vMax, vMax, 0);
		wallOff(RorL == R ? L : R);
		slalom3(RorL == R ? L : R, Dia45, vMax, vMax, 0);
		wallOff(RorL == R ? L : R);
		slalom3(RorL == R ? L : R, Dia45, vMax, vMax, 0);
		wallOff(RorL);
		slalom3(RorL, Dia45, vMax, vMax, 0);
	}
}
void testDia135Turn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
	for (int i = 0; i < 1; i++) {
		wallOff(RorL);
		slalom3(RorL, Dia135, vMax, vMax, 0);
		wallOff(RorL == R ? L : R);
		slalom3(RorL == R ? L : R, Dia135, vMax, vMax, 0);
		wallOff(RorL);
		slalom3(RorL, Dia45, vMax, vMax, 0);
		wallOff(RorL == R ? L : R);
		slalom3(RorL == R ? L : R, Dia45, vMax, vMax, 0);
	}
}
void testDia90Turn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
	wallOff(RorL);
	slalom3(RorL, Dia45, vMax, vMax, 0);
	for (int i = 0; i < 1; i++) {
		wallOff(RorL == R ? L : R);
		slalom3(RorL == R ? L : R, Dia90, vMax, vMax, 0);
		wallOff(RorL);
		slalom3(RorL, Dia90, vMax, vMax, 0);
	}
}

void sla3(float vMax) {
	float maxVelocity = vMax;
	float accele = 20000;
	float diaccele = 18000;
	inputNaiperTurnAll1500();
	char RorL = eigherRightLeft() == Right ? R : L;
	wall_off_limit = wall_off_limit_d = 400;
	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	readGyroParam();
	readVelocityGain();

	if (vMax >= 1200) {
		startVacume2(95);
	}
	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
//	dia = 1;

//	changeMode(true);
	Sen_Dia.Kp = 0.0;

	inputNaiperTurnAll1500();

	save();

//	running2(maxVelocity, accele, 200, 1);
	realRun(maxVelocity, accele, diaccele, 180.0 * 1.22, vMax);
//	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;

	wallOff(RorL);
	slalom3(RorL, Orval, vMax, vMax, 0);
//	wallOff(RorL == R ? L : R);
//	slalom3(RorL == R ? L : R, Dia90, vMax, vMax, 0);

//	loadNaname(R, vMax, maxVelocity, accele, diaccele);
//	testLargeTurn(RorL, vMax, maxVelocity, accele, diaccele);
//	testOrvalTurn(RorL, vMax, maxVelocity, accele, diaccele);
//	testDia90Turn(RorL, vMax, maxVelocity, accele, diaccele);
	cc = 0;
	if (dia == 1) {
		realRun(vMax, accele, diaccele, 90.0 * ROOT2, 50);
//		realRun(vMax, accele, diaccele, 180.0 * ROOT2, 50);
	} else {
//		realRun(vMax, accele, diaccele, 90.0 * 1, 50);
		realRun(vMax, accele, diaccele, 180.0 * 1.0, 50);
		//		realRun(maxVelocity, accele, diaccele, 180.0 * 6, 50);
	}
//	running(50, 0, 90, 0);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testNormalSlalom(float vMax) {
	float maxVelocity = vMax;
	float accele = 4000;
	float diaccele = 4000;
	inputNaiperTurnAll1500();
	char RorL = eigherRightLeft() == Right ? R : L;

	fanMode = SearchRun;

	Sen.Kp = 0.0036;
	Sen.Ki = 0.001;
	Sen.Kd = 0.125;

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);

	if (vMax >= 1000) {
		startVacume2(70);
	}

	mtu_start();
	readGyroParam();
	readVelocityGain();

	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
	changeMode(true);
	inputNaiperTurnAll1500();

//	setPrms(Normal, 90, 50, 13.75, 47.5, 0, 0, 0.10290718078613281, 4, 500);
//	setPrms3(Normal, 21, 43.0);

	setPrms(Normal, 90, 55, 10.0, 27.5, 0, 0, 0.056598663330078125, 4, 1000);
	setPrms3(Normal, 10.0, 30.5);

	save();

//	running2(maxVelocity, accele, 360, 1);
	realRun(maxVelocity, accele, diaccele, 180.0 * 1, vMax);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
//
//	frontCtrl();
//	resetAllData();
//	mtu_stop2();
//	ledOn = 1;
//	while (1) {
//		myprintf("%f %f %d %d %f %f  \r\n", LF_SEN1.now, RF_SEN1.now,
//				LF_SEN1.now < FRONT_CTRL_L, RF_SEN1.now < FRONT_CTRL_R,
//				FRONT_CTRL_L, FRONT_CTRL_R);
//		cmt_wait(10);
//	}
//		printSensor();
	slalom3(RorL, Normal, vMax, vMax, 0);
//	slalom3(RorL == R ? L : R, Normal, vMax, vMax, 0);
//	slalom3(RorL == R ? L : R, Normal, vMax, vMax, 0);
//	slalom3(RorL == R ? L : R, Normal, vMax, vMax, 0);
//	slalom3(RorL == R ? L : R, Normal, vMax, vMax, 0);
	cc = 0;
	realRun(vMax, accele, diaccele, 180.0 * 0.5, 50);
//	running(50, 0, 90, 0);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testWallOff(float vMax) {
	float maxVelocity = vMax;
	float accele = 2000;
	float diaccele = 2000;
	wall_off_limit = wall_off_limit_d = 400;
	inputNaiperTurnAll1500();
	char RorL = eigherRightLeft() == Right ? R : L;

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	readGyroParam();
	readVelocityGain();

	if (vMax > 1200) {
		startVacume2(70);
	}
	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
//	dia = 1;

	changeMode(true);
//	realRun(maxVelocity, accele, diaccele, 90.0, vMax);
	running2(maxVelocity, accele, 360, 1);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
//	wallOff(RorL);
//	cc = 0;
//	V_now = 0;
//	cmt_wait(1000);
	realRun(vMax, accele, diaccele, 90.0 * 1, 50);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testWallOffSeach(float vMax) {
	float maxVelocity = vMax;
	float accele = 2000;
	float diaccele = 2000;

	inputNaiperTurnAll1500();

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	readGyroParam();
	readVelocityGain();

	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
//	dia = 1;

	changeMode(true);
//	realRun(maxVelocity, accele, diaccele, 180, vMax);
	cc = 1;
	running2(maxVelocity, accele, 200, 1);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
	cc = 0;
	realRun(vMax, accele, diaccele, 90.0 * 1, 50);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}

void testRoll(char r) {
	char a = 0;
	r = eigherRightLeft() == Right ? R : L;
	gyroZeroCheck(true);

	for (a = 0; a < 5 * 1; a++) {
		cmt_wait(150);
		cc = 1;
//		gyroRoll(L, 180, 60, 80);
//		gyroRoll(r, 180 * 2 * 1, 10, 15);
//		gyroRoll(r, 180 * 2 * 1, 60, 20);
//		gyroRollTest(r == R ? L : R, 180 * 2 * 1, 15, 7);
		gyroRollTest(r == R ? L : R, 180 * 2 * 1, 60, 80);
//		gyroRoll(r == R ? L : R, 180 * 2 * 1, 20, 25);
//		cmt_wait(250);
//		gyroZeroCheck(false);
		cc = 0;
	}
	logOutPut();
}

void searchMode(char X, char Y) {
	char x1 = 0, y1 = 0;
	char check = 0;
	x = 0;
	y = 0;
	next_dir = North;
	gyroZeroCheck(true);
	cmt_wait(500);
	now_dir = North;
//	check = Adachi2(X, Y, 1);
	if (check == 0) {
		return;
	}
	cmt_wait(500);
	roll(L, 180, 5, 30);
	x1 = x;
	y1 = y;
	now_dir = direction(now_dir, Back);
	next_dir = now_dir;
	x = x1;
	y = y1;
	cmt_wait(500);
	gyroZeroCheck(false);
//	Adachi(0, 0);
}

char isFullMaze(char X, char Y) {
	return ((X == 7 && Y == 7) || (X == 8 && Y == 7) || (X == 7 && Y == 8)
			|| (X == 8 && Y == 8));
}

void flushcheckQ() {
	for (int i = 0; i < checkQlength; i++) {
		checkQ[i] = 0;
	}
}

void printRealPath();
char makePath3(char goalX, char goalY, char isFull) {
	Dia2 = Dia - minus + 2;
	Dia3 = Dia - minus + 1;
	St2 = St1 - minus;
	St3 = St1 - minus - 1;
	x = 0;
	y = 0;
	now_dir = North;
	vetorPathCreate(goalX, goalY, isFull);
	drawChangePathRoot(goalX, goalY, isFull);
	largePath(true);
	diagonalPath(isFull, true);
	return countPathLength2();
}
char makePath4() {
	Dia2 = Dia - minus + 2;
	Dia3 = Dia - minus + 1;
	St2 = St1 - minus;
	St3 = St1 - minus - 1;
	vetorPathCreate(0, 0, false);
	largePath(true);
	diagonalPath(false, true);

	return true;
}
void makePath(char goalX, char goalY, char isFull) {
	flushcheckQ();
	printMap();
	if (cirquitMode == false) {
		minus = 3;
		int minus3 = makePath3(goalX, goalY, isFull);
	}
	printRealPath();
}
void makePath2() {
	flushcheckQ();
	if (cirquitMode == false) {
		minus = 3;
		makePath4();
	}
	printRealPath();
}
void testVacume() {
	gyroZeroCheck(true);
	cmt_wait(500);
	mtu_start();
	readVelocityGain();
	resetGyroParam();
	startVacume();
	cmt_wait(50000);
	stopVacume();
	mtu_stop();
}
void testVacume2(int duty) {
	gyroZeroCheck(true);
	cmt_wait(500);
	mtu_start();
	readVelocityGain();
	resetGyroParam();
	startVacume2(duty);
//	cmt_wait(15000);
	for (int i = 0; i < 200; i++) {
		myprintf("%d %f \r\n", (int) (FAN_AMP / battery * FAN_CYCLE), battery);
		cmt_wait(100);

	}
	stopVacume();
	mtu_stop();
}
char switchOn() {
	return !Swich;
}

char modeCheck() {
	char swTop = !PushTop;
	char swBottom = !PushBottom;
	char swRight = !PushRight;
	char swLeft = !PushLeft;
	char swCenter = !PushCenter;
	return swTop + swBottom * 2 + swLeft * 4 + swRight * 8 + swCenter * 16;
}
char encorderOperation() {
	volatile signed char mode = SEARCH;
	os_escape = 0;
	MTU1.TCNT = 4500;
	MTU2.TCNT = 30000;
	MTU.TSTRA.BIT.CST4 = 0;
	while (1) {
		char swTop = !PushTop;
		char swBottom = !PushBottom;
		char swRight = !PushRight;
		char swLeft = !PushLeft;
		char swCenter = !PushCenter;

		if (mode == SEARCH) {
			led(1, 0, 0, 0);
		} else if (mode == SEARCH2) {
			led(0, 1, 0, 0);
		} else if (mode == RUN) {
			led(1, 1, 0, 0);
		} else if (mode == RUN2) {
			led(0, 0, 1, 0);
		} else if (mode == RUN3) {
			led(1, 0, 1, 0);
		} else if (mode == RUN4) {
			led(0, 1, 1, 0);
		} else if (mode == RUN5) {
			led(1, 1, 1, 0);
		} else if (mode == CONFIG) {
			led(0, 0, 0, 1);
		} else if (mode == CONFIG2) {
			led(1, 0, 0, 1);
		} else if (mode == CONFIG3) {
			led(0, 1, 0, 1);
		} else if (mode == CONFIG4) {
			led(1, 1, 0, 1);
		} else if (mode == CONFIG5) {
			led(0, 0, 1, 1);
		} else if (mode == CONFIG6) {
			led(1, 0, 1, 1);
		} else if (mode == CONFIG7) {
			led(0, 1, 1, 1);
		} else if (mode == CONFIG8) {
			led(1, 1, 1, 1);
		} else if (mode == CONFIG9) {
			led(1, 0, 0, 0);
			cmt_wait(50);
			led(0, 0, 0, 0);
			cmt_wait(50);
			led(1, 0, 0, 0);
			cmt_wait(50);
		} else if (mode == KeepZeroPoint) {
			led(0, 1, 0, 0);
			cmt_wait(50);
			led(0, 0, 0, 0);
			cmt_wait(50);
			led(0, 1, 0, 0);
			cmt_wait(50);
		} else if (mode == MapMemory) {
			led(0, 0, 1, 0);
			cmt_wait(50);
			led(0, 0, 0, 0);
			cmt_wait(50);
			led(0, 0, 1, 0);
			cmt_wait(50);
		} else if (mode == VacumeTest) {
			led(0, 0, 0, 1);
			cmt_wait(50);
			led(0, 0, 0, 0);
			cmt_wait(50);
			led(0, 0, 0, 1);
			cmt_wait(50);
		} else if (mode == Mentenance) {
			led(0, 0, 0, 0);
		}

		if (swTop || swBottom) {
			if (swTop) {
				mode++;
				if (mode > Mentenance) {
					mode = SEARCH;
				}
			}
			if (swBottom) {
				mode--;
				if (mode < 0) {
					mode = Mentenance;
				}
			}
			for (int i = 0; i < 60000; i++)
				;
		}

		while (swTop || swBottom) {
			swTop = !PushTop;
			swBottom = !PushBottom;
			swRight = !PushRight;
			swLeft = !PushLeft;
			swCenter = !PushCenter;
		};

		if (swCenter) {
			os_escape = 1;
			decide(100);
			led(1, 1, 1, 1);
			cmt_wait(500);
			led(0, 0, 0, 0);
			cmt_wait(500);
			break;
		}
		cmt_wait(10);
	}
	os_escape = true;
	MTU.TSTRA.BIT.CST4 = 1;
	return mode;
}

void cirquitRun() {
	cirquit();
}
void FF_print() {
	mtu_start();
	while (1) {
		cmt_wait(50);
		myprintf("%d %d \n", (int) (FF_calc(L) * 1000),
				(int) (FF_calc(R) * 1000));
	}
	mtu_stop();
}

#define goal7 10000
#define goal8 25000

char selectGoal() {
	char goal = 0;
	os_escape = 0;
	MTU1.TCNT = 4500;
	MTU2.TCNT = 30000;

	MTU.TSTRA.BIT.CST4 = 0;
	while (1) {
		if (MTU1.TCNT < goal7) {
			LED1 = 1;
			LED6 = 0;
			goal = 7;
		} else if (MTU1.TCNT < goal8) {
			LED1 = 0;
			LED6 = 1;
			goal = 8;
		}
		if (MTU1.TCNT > OVERFLOW) {
			MTU1.TCNT = 5000;
		}
		if (MTU1.TCNT < UNDERFLOW) {
			MTU1.TCNT = 15000;
		}
		if (!Swich) {
			os_escape = 1;
			LED1 = 1;
			LED2 = 1;
			LED3 = 1;
			cmt_wait(500);
			LED1 = 0;
			LED2 = 0;
			LED3 = 0;
			cmt_wait(500);
			break;
		}
	}
	led(0, 0, 0, 0);
	if (goal == 7) {
		coin(250);
		cmt_wait(100);
	}
	if (goal == 8) {
		coin(250);
		cmt_wait(100);
		coin(250);
		cmt_wait(100);
	}

	MTU.TSTRA.BIT.CST4 = 1;
	return goal;
}

void printCheckMapping() {
	myprintf("\r\n");
	for (int i = 0; i < 255; i++) {
		int x = (checkQ[i] & 0xf0) >> 4;
		int y = checkQ[i] & 0x0f;
		myprintf("(%2x,%2x)\r\n", x, y);
		if (x == 0 && y == 0) {
			break;
		}
	}
	myprintf("\r\n");
	for (int j = 15; j >= 0; j--) {
		for (int i = 0; i < 16; i++) {
			myprintf("%2x, ", checkMap[i][j]);
		}
		myprintf("\r\n");
	}
	myprintf("\r\n");
}

char action(char mode, char goalX, char goalY, char fastMode) {
	char isFull = isFullMaze(goalX, goalY);

	wall_off_limit = 20;
	wall_off_limit_d = 20;

	if (mode == SEARCH || mode == SEARCH2) {
		Sen.Kp = 0.0036;
		Sen.Ki = 0.001;
		Sen.Kd = 0.125;
		fanMode = SearchRun;
	} else {
		Sen.Kp = 0.0075;
//		Sen.Kp = 0.0125;
		Sen.Ki = 0.001;
		Sen.Kd = 0.25;
		fanMode = FastRun;
	}

	if (mode == SEARCH) {
		fanMode = SearchRun;
		wall_off_limit = wall_off_limit_d = 35;
		gyroKeepFlg = 0;
		now_dir = North;
		next_dir = North;
		x = 0;
		y = 0;
		cirquitMode = 0;
		inputNaiperTurnAll500_2();
		save();
		pathClear();
		return Adachi2(goalX, goalY, Zentansaku, isFull);
	} else if (mode == SEARCH2) {
		wall_off_limit = wall_off_limit_d = 35;
		char m2 = eigherRightLeft() == Right ? Oufuku : Kata;
		gyroKeepFlg = 0;
		now_dir = North;
		next_dir = North;
		x = 0;
		y = 0;
		cirquitMode = 0;
		inputNaiperTurnAll500_2();
		save();
		pathClear();
		return Adachi2(goalX, goalY, m2, isFull);
	} else if (mode == RUN) {
		float v = eigherRightLeft() == Right ? 4500 : 3500;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1200();
		save();
		inputNaiperTurnAll1200();
		save2();
		char check = runForPath(v, 18000, 18000);
	} else if (mode == RUN2) {
		float v = eigherRightLeft() == Right ? 4700 : 4000;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1500();
		setPrms(Large, 90, 125, 3.0, 25.0, 0, 0, 0.0756673812866211, 4, 1700);
		setPrms3(Large, 9.25, 0);
		save();
		inputNaiperTurnAll1200();
		save2();
		char check = runForPath(v, 18000, 18000);
	} else if (mode == RUN3) {
		float v = eigherRightLeft() == Right ? 5000 : 4500;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1700();
		setPrms(Large, 90, 120.0, 5, 20.0, 0, 0, 0.0686044692993164, 4, 1800);
		setPrms3(Large, 11.0, 0);
		save();
		inputNaiperTurnAll1200();
		save2();
		char check = runForPath(v, 18000, 18000);
	} else if (mode == RUN4) {
		float v = eigherRightLeft() == Right ? 5000 : 4500;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1200();
		save2();
		char check = runForPath(v, 20000, 18000);
	} else if (mode == RUN5) {
		float v = eigherRightLeft() == Right ? 5100 : 4700;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll2000();
		save();
		inputNaiperTurnAll1200();
		save2();
		char check = runForPath(v, 20000, 18000);
	} else if (mode == CONFIG) {
		float v = eigherRightLeft() == Right ? 5100 : 5000;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll2000();
		save();
		inputNaiperTurnAll1200();
		save2();
		char check = runForPath(v, 20500, 19000);
	} else if (mode == CONFIG2) {
		float v = eigherRightLeft() == Right ? 5100 : 5000;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll2000();
		save();
		inputNaiperTurnAll1200();
		save2();
		char check = runForPath(v, 21000, 19500);
	} else if (mode == CONFIG3) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1500();
		save();
		inputNaiperTurnAll1200();
		save2();
		float v = getMaxVeloctiy();
		char check = runForPath(v, 20000, 18000);
	} else if (mode == CONFIG4) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1700();
		save();
		inputNaiperTurnAll1200();
		save2();
		float v = getMaxVeloctiy();
		char check = runForPath(v, 20000, 18000);
	} else if (mode == CONFIG5) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1200();
		save();
		inputNaiperTurnAll1200();
		save2();
		float v = getMaxVeloctiy();
		char check = runForPath(v, 20000, 18000);
	} else if (mode == CONFIG6) {
	} else if (mode == CONFIG7) {
	} else if (mode == CONFIG8) {
		goalChangeFlg = 1;
		operation();
	} else if (mode == CONFIG9) {
		keepZeroPoint2();
	} else if (mode == KeepZeroPoint) {
		if (saveFcuBlock(FLASH_DF_BLOCK_4)) {
			oneUp(100);
		}
	} else if (mode == MapMemory) {
		testVacume2(10);
	} else if (mode == VacumeTest) {
		printSensor();
	} else if (mode == Mentenance) {
		resetFull();
	}
	mtu_stop2();
//	TRANSAM = false;
	LED6 = false;
	LED1 = false;
	return 0;
}

void exportMap() {
	myprintf("{");
	for (int i = 0; i < 16; i++) {
		myprintf("{");
		for (int j = 0; j < 16; j++) {
			myprintf("%d", (map[i][j] & 0x0f));
			if (j != 15) {
				myprintf(",");
			}
		}
		myprintf("}");
		if (i != 15) {
			myprintf(",");
		}
		myprintf("\r\n");
	}
	myprintf("}\r\n");
}
void exportMap2() {
	myprintf("[");
	for (int i = 0; i < 16; i++) {
		myprintf("[");
		for (int j = 0; j < 16; j++) {
			myprintf("%d", (map[i][j] & 0x0f));
			if (j != 15) {
				myprintf(",");
			}
		}
		myprintf("]");
		if (i != 15) {
			myprintf(",");
		}
		myprintf("");
	}
	myprintf("]\r\n");
}
void checkMemory(int goalX, int goalY) {
	if (writeMap2(FLASH_DF_BLOCK_0)) {
		startTransam(150);
	} else {
//		coin(125);
	}
	readMaze();
	updateDist(goalX, goalY, 0, isFullMaze(goalX, goalY));
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 15; i++) {
			if ((existWall(i, j, North) != existWall(i, j + 1, South))
					|| (existWall(i, j, East) != existWall(i + 1, j, West))) {
				resetFull();
				return;
			}
		}
	}
	exportMap();
	cirquitMode = false;
	myprintf("not cirquit \r\n");
//	resetMap();
	printMap();

	exportMap2();
}
void test12() {
	sensingMode = AtackStraight;
	ledOn = true;
	char up = false;
	while (1) {
		myprintf("%d	%d\r\n", (sen_log_r[0] > sen_log_r[1]),
				(sen_log_r[1] > sen_log_r[2]));

		myprintf("%f	%f	%f	%f	%f\r\n", sen_log_r[0], sen_log_r[1], sen_log_r[2],
				sen_log_r[3], sen_log_r[4]);
		cmt_wait(100);
		if (!up) {
			up = checkUp(R);
		} else {
			if (checkDown(R)) {
				positionControlValueFlg = 0;
				cmtMusic(C2_, 500);
				cmt_wait(500);
				up = false;
//				return true;
			}
		}
	}
	ledOn = false;
}

void frontCtrlTest() {
	char RorL = eigherRightLeft() == Right ? R : L;
	float Velocity = 500;
	gyroZeroCheck(true);
	cmt_wait(500);
	cc = 1;
	gyroOn = 1;
	V_now = 0;
	mtu_start();
	realRun3(Velocity, 3500, 3500, 60, 40);
	frontCtrl4();

	frontWallCtrl = true;
	cmt_wait(500);
	frontWallCtrl = false;
	mtu_stop();
	cmt_wait(500);
	mtu_start();
	if (RorL == R) {
		gyroRoll(R, 90, 30, 30);
	} else {
		gyroRoll(L, 90, 30, 30);
	}
//	back(-500, -2000, 480, 0);
	logOutPut();
}

void frontCtrlTest2() {
	gyroZeroCheck(true);
	cmt_wait(500);
	cc = 1;
	gyroOn = 1;
	V_now = 0;
	mtu_start();
	frontWallCtrl = true;
	readGyroParam();
	while (1) {
		myprintf("%c[2J", ESC); /* 画面消去 */
		myprintf("%c[0;0H", ESC); /* 戦闘戻す*/
		myprintf("battery=%f V\r\n", battery);
		myprintf("Gyro=%f\r\n", settleGyro);
		myprintf("	%f %f\r\n", LS_SEN1.now, RS_SEN1.now);
		myprintf("%f 		%f\r\n", LF_SEN1.now, RF_SEN1.now);
		myprintf("Duty:	%f	%f\r\n", Duty_l, Duty_r);
		myprintf("Velocity:	%f	%f\r\n", V_Enc.l, V_Enc.r);
		myprintf("angle:	%f\r\n", ang * 180 / PI);
		myprintf("distance:	%f\r\n", distance);

		float dutyR = FrontCtrl.Kp * check_sen_error_dia_FrontCtrl(R);
		float dutyL = FrontCtrl.Kp * check_sen_error_dia_FrontCtrl(L);
		myprintf("duty:	%f	%d\r\n", dutyL, dutyR);

//		myprintf(
//				"{\"mode\":%d,\"battery\":%f,\"gyro\":%f,\"LS1\":%f,\"RS1\":%f,\"LF1\":%f,\"RF1\":%f}\r\n",
//				ledOn, battery, settleGyro, LS_SEN1.now, RS_SEN1.now,
//				LF_SEN1.now, RF_SEN1.now);
		cmt_wait(100);
//		myprintf("%f	%f	%d	%d	%f	%f\r\n", V_Enc.l, V_Enc.r, el, er, Duty_l,
//				Duty_r);
		if (Swich == 0) {
			break;
		}
		if (!fail) {
//			break;
		}
	}
	frontWallCtrl = false;
	logOutPut();
}

void operation() {
	volatile char goalX = 1; // selectGoal();
	volatile char goalY = 0; //selectGoal();

	fanMode = FastRun;
	if (!PushBottom) {
		goalX = 7;
		goalY = 7;
	}

	if (goalChangeFlg == 1) {
		goalX = 7;
		goalY = 7;
	}

//	printSensor();

	if (!PushTop) {

		enableSciUpdate = true;
		while (PushBottom)
			;
	}

	if (PushLeft) {
		if (!PushTop) {
			printSensor();
		}
//		if (PushRight) {
//		testRun();
//		}
//		frontCtrlTest();
//		frontCtrlTest2();
//		testRun();
//		mtu_start();
//		while (1)
//			;
//		keepZeroPoint();
//		testRoll(L);
//		testWallOff(500);
//	testWallOffSeach(500);
//		testNormalSlalom(1000);
//		sla3(2000);
//	inputData2();
//	testVacume2(90);
//	testWallOff();
//	checkIsoukeisu();
	}
//	mtu_start();
//	while(1);

	cirquit();
	checkMemory(goalX, goalY);

//	while(1){
//		gyroZeroCheck(true);
//	}
//	cirquit();
	wall_off_limit = 25;
	wall_off_limit_d = 25;

	while (1) {
		int res = action(encorderOperation(), goalX, goalY, false);
		mtu_stop2();
//		if (res != 0) {
//			action(RUN, goalX, goalY, true);
//		}
		mtu_stop2();
	}
}

#endif /* OPERATIONSYSTEM_H_ */
