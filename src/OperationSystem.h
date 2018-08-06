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
		myprintf("%d	%d	%d	%d	%d\n", (int) LS_SEN45.now, (int) 0,
				(int) Front_SEN.now, (int) RS_SEN45.now, (int) (Se.error_now));
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

	float test_acc = *(float *) 1049268;
	float test_max_v = *(float *) 1049272;
	float test_dia = *(float *) 1049276;

	float velocity = test_max_v;
	float accele = test_acc;
	float diaccele = test_acc;
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
	dia = test_dia > 0;

	if (dia == 1) {
		float targetDistDia = *(float *) 1049300;
		realRun(velocity, accele, diaccele, targetDistDia, vMax);
	} else {
		float targetdist = *(float *) 1049296;
		realRun(velocity, accele, diaccele, targetdist, vMax);
	}

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

void inputNaiperTurnAll500() {
	setNormalParam500();
	setLargeParam1000();
	setOrvalParam1000();
	setDia45Param1000();
	setDia135Param1000();
	setDia90Param1000();
}

void inputNaiperTurnAll1000() {
	setNormalParam1000();
	setLargeParam1000();
	setOrvalParam1000();
	setDia45Param1000();
	setDia135Param1000();
	setDia90Param1000();
}

void inputNaiperTurnAll1200() {
	setPrms(Large, 90, 115.0, 33.5, 20, 0, 0, 0.07889556884765625, 4, 1500);
	setPrms3(Large, 13.5, 0, 40);
	setPrms(Orval, 180, 88.5, 20, 35, 0, 0, 0.1214303970336914, 4, 1500);
	setPrms3(Orval, 20, 38, 35);
	setPrms(Dia45, 45, 125, 13, 40, 57, 10, 0.042878150939941406, 4, 1500);
	setPrms3(Dia45, 8.0, 47.0, 26);
	setPrms(Dia135, 135, 85, 26, 20, 17.25, 25, 0.08747100830078125, 4, 1500);
	setPrms3(Dia135, 25, 6.5, 28);
	setPrms(Dia90, 90, 85.0, 16.75, 22.0, 0, 0, 0.05831432342529297, 4, 1500);
	setPrms3(Dia90, 11.0, 0, 0);

}

void inputNaiperTurnAll1500() {
	setLargeParam1500();
	setOrvalParam1500();
	setDia45Param1500();
	setDia135Param1500();
	setDia90Param1500();
}

void inputNaiperTurnAll1700() {
	setLargeParam1700();
	setOrvalParam1700();
	setDia45Param1700();
	setDia135Param1700();
	setDia90Param1700();

}
void inputNaiperTurnAll1800() {
	setLargeParam1800();
	setOrvalParam1800();
	setDia45Param1800();
	setDia135Param1800();
	setDia90Param1800();
}
void inputNaiperTurnAll1900() {
	setLargeParam1900();
	setOrvalParam1900();
	setDia45Param1900();
	setDia135Param1900();
	setDia90Param1900();
}
void inputNaiperTurnAll2000() {
	inputNaiperTurnAll1900();
	setLargeParam2000();
}
void inputNaiperTurnAll2100() {
	inputNaiperTurnAll1900();
	setLargeParam2100();
}
/**
 * 	t_radiusData large;
 t_radiusData orval;
 t_radiusData dia45;
 t_radiusData dia135;
 t_radiusData dia90;
 t_radiusData kojima;
 */

void loadNaname(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
	wall_off_limit = 20;
	wall_off_limit_d = 25;
//	for (int i = 0; i < 1; i++) {
//		wallOff(R);
//		slalom(R, Dia45, vMax, vMax, 0);
//		realRun(maxVelocity, accele, diaccele, 180.0 * ROOT2 * 1.5, vMax);
//		wallOff(R);
//		slalom(R, Dia135, vMax, vMax, 0);
//		wallOff(R);
//		slalom(R, Dia45, vMax, vMax, 0);
//		realRun(maxVelocity, accele, diaccele, 180.0 * ROOT2 * 2, vMax);
//		wallOff(L);
//		slalom(L, Dia135, vMax, vMax, 0);
//		realRun(maxVelocity, accele, diaccele, 180.0 * 1, vMax);
//		wallOff(L);
//		slalom(L, Large, vMax, vMax, 0);
//		wallOff(L);
//		slalom(L, Dia45, vMax, vMax, 0);
//		realRun(maxVelocity, accele, diaccele, 180.0 * ROOT2 * 2, vMax);
//		wallOff(R);
//		slalom(R, Dia135, vMax, vMax, 0);
//		wallOff(R);
//		slalom(R, Dia135, vMax, vMax, 0);
//		realRun(maxVelocity, accele, diaccele, 180.0 * ROOT2, vMax);
//		wallOff(L);
//		slalom(L, Dia45, vMax, vMax, 0);
//		realRun(maxVelocity, accele, diaccele, 180.0 * 1, vMax);
//		wallOff(L);
//		slalom(L, Large, vMax, vMax, 0);
//		wallOff(L);
//		slalom(L, Large, vMax, vMax, 0);
//		wallOff(L);
//		slalom(L, Dia135, vMax, vMax, 0);
//		wallOff(R);
//		slalom(R, Dia135, vMax, vMax, 0);
//	}
}
void testLargeTurn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
	for (int i = 0; i < 4; i++) {
		wallOff(RorL, true);
		slalom(RorL, Large, vMax, vMax, 0);
	}
}
void testOrvalTurn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
//	for (int i = 0; i < 4; i++) {
//		wallOff(RorL);
//		slalom(RorL, Orval, vMax, vMax, 0);
//	}
}
void testDia45Turn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
//	for (int i = 0; i < 1; i++) {
//		wallOff(RorL);
//		slalom(RorL, Dia45, vMax, vMax, 0);
//		wallOff(RorL == R ? L : R);
//		slalom(RorL == R ? L : R, Dia45, vMax, vMax, 0);
//		wallOff(RorL == R ? L : R);
//		slalom(RorL == R ? L : R, Dia45, vMax, vMax, 0);
//		wallOff(RorL);
//		slalom(RorL, Dia45, vMax, vMax, 0);
//	}
}
void testDia135Turn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
//	for (int i = 0; i < 1; i++) {
//		wallOff(RorL);
//		slalom(RorL, Dia135, vMax, vMax, 0);
//		wallOff(RorL == R ? L : R);
//		slalom(RorL == R ? L : R, Dia135, vMax, vMax, 0);
//		wallOff(RorL);
//		slalom(RorL, Dia45, vMax, vMax, 0);
//		wallOff(RorL == R ? L : R);
//		slalom(RorL == R ? L : R, Dia45, vMax, vMax, 0);
//	}
}
void testDia90Turn(char RorL, float vMax, float maxVelocity, float accele,
		float diaccele) {
//	wallOff(RorL);
//	slalom(RorL, Dia45, vMax, vMax, 0);
//	for (int i = 0; i < 1; i++) {
//		wallOff(RorL == R ? L : R);
//		slalom(RorL == R ? L : R, Dia90, vMax, vMax, 0);
//		wallOff(RorL);
//		slalom(RorL, Dia90, vMax, vMax, 0);
//	}
}

void testSlalom3() {
	float vMax = *(float *) 1049264;
	char test_dia = (char) (*(float *) 1049276);
	char turnType = (char) (*(float *) 1049280);
	char test_sla_scenario2 = (char) (*(float *) 1049284);

	char test_sla_return_flg = (char) (*(float *) 1049288);
	char test_sla_return_scenario = (char) (*(float *) 1049292);

	float accele = *(float *) 1049268;
	float diaccele = *(float *) 1049268;

	if (vMax == 1500) {
		inputNaiperTurnAll1500();
	} else if (vMax == 1700) {
		inputNaiperTurnAll1700();
	} else if (vMax == 1800) {
		inputNaiperTurnAll1800();
	} else if (vMax == 1900) {
		inputNaiperTurnAll1900();
	} else if (vMax == 2000) {
		setLargeParam2000();
		setOrvalParam2000();
		setDia45Param2000();
		setDia135Param2000();
		setDia90Param2000();
	} else if (vMax == 2100) {
		setLargeParam2100();
		setOrvalParam2100();
		setDia45Param2100();
		setDia135Param2100();
		setDia90Param2100();
	} else if (vMax == 2200) {
		setLargeParam2200();
		setOrvalParam2200();
		setDia45Param2200();
		setDia135Param2200();
		setDia90Param2200();
	}

	char RorL = eigherRightLeft() == Right ? R : L;
	wall_off_limit = wall_off_limit_d = 400;
	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	resetAllData();
	mtu_start();

	readGyroParam();
	readAngleParam();
	readVelocityGain();
//	resetVelocityGain();

	if (vMax >= 1200) {
		TRANSAM = true;
		startVacume2(90);
	}
	Sen_Dia_Side.Kp = 0.0;
	Sen_Dia_Side.Ki = 0.0;
	Sen_Dia_Side.Kd = 0.0;

	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;

	dia = (char) test_dia > 0;

	save();

	globalSkipFront = test_sla_scenario2;

	char type = turnType;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
	if (globalSkipFront) {
		realRun(vMax, accele, diaccele, 41 + getFirstFront(type), vMax);
	} else {
		realRun(vMax, accele, diaccele, 180.0 * 1.22, vMax);
	}
	if (!globalSkipFront) {
		wallOff(RorL, true);
	}

//	realRun(vMax, accele, diaccele, 90.0 * ROOT2, 50);
//	mtu_stop2();
//	V_now = 0;
//	cmt_wait(1000);
//	mtu_stop2();
	slalom(RorL, type, vMax, vMax, 0);

	peekRight = peekLeft = 0;

	Sen.Kp = Sen.Ki = Sen.Kd = 0.0;
	if (test_sla_return_flg) {
		wallOff(RorL == R ? L : R, !dia);
		slalom(RorL == R ? L : R, test_sla_return_scenario, vMax, vMax, 0);
	}
	cc = 0;
	if (dia == 1) {
		realRun(vMax, accele, diaccele, 180.0 * ROOT2, 50);
	} else {
		realRun(vMax, accele, diaccele, 180.0 * 1.0, 50);
	}
//	running(50, 0, 90, 0);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testNormalSlalom() {

	char testCmd = (char) (*(float *) 1049260);
	char test_front_ctrl = testCmd == 4;

	float accele = *(float *) 1049324;
	float diaccele = *(float *) 1049328;
	float vMax = *(float *) 1049320;

	char RorL = eigherRightLeft() == Right ? R : L;

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);

	if (vMax >= 1000) {
		fanMode = SearchRun;
		startVacume2(70);
		setNormalParam1000();
	} else {
		setNormalParam500();
	}

	mtu_start();
	readGyroParam();
	readVelocityGain();

	ang = angle = Gy.error_old = 0;
	mode_FF = 1;
	save();

	if (test_front_ctrl) {
		realRun(vMax, accele, diaccele, 180.0 * 1, vMax);
		frontCtrl();
		realRun(vMax, accele, diaccele, 90.0 * 1, 50);
		resetAllData();
		mtu_stop2();
	} else {
//		runForWallOff(vMax, accele, 270, 1);
		realRun(vMax, accele, diaccele, 180.0 * 1, vMax);
		logs = 0;
		time = 0;
		cc = 1;
		logs = 0;
		slalom(RorL, Normal, vMax, vMax, 0);

		char test_turn_times = (char) (*(float *) 1049308);
		if (test_turn_times > 0) {
			for (char i = 0; i < test_turn_times; i++) {
				slalom(RorL == R ? L : R, Normal, vMax, vMax, 0);
			}
		}
		cc = 0;
		realRun(vMax, accele, diaccele, 180.0 * 1, 50);
	}
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testWallOff() {
	float test_acc = *(float *) 1049268;
	float test_max_v = *(float *) 1049264;
	float test_dia = *(float *) 1049276;

	float maxVelocity = test_max_v;
	float vMax = maxVelocity;

	float accele = test_acc;
	float diaccele = test_acc;

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
	ang = angle = Gy.error_old = 0;
	mode_FF = 1;
	dia = test_dia > 0;

	realRun(maxVelocity, accele, diaccele, 200.0, vMax);
//	runForWallOff(maxVelocity, accele, 180, 1);
	logs = time = 0;
	cc = 1;

	wallOff(RorL, !dia);

	if (dia) {
		realRun(vMax, accele, diaccele, 90.0 * ROOT2, 50);
	} else {
		realRun(vMax, accele, diaccele, 90.0 * 1, 50);
	}
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testWallOffSeach() {

	float vMax = *(float *) 1049320;
	float accele = *(float *) 1049324;
	float diaccele = *(float *) 1049324;

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	readGyroParam();
	readVelocityGain();

	if (vMax >= 1000) {
		fanMode = SearchRun;
		startVacume2(70);
	}

	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
	cc = 1;
	runForWallOff(vMax, accele, 200, 1);
	realRun(vMax, accele, diaccele, 90.0 * 1, 50);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}

void testRoll(char r) {

	float test_turn_angle = *(float *) 1049304;
	char test_turn_times = (char) (*(float *) 1049308);
	float test_turn_acc = *(float *) 1049312;
	float test_turn_w = *(float *) 1049316;

	r = eigherRightLeft() == Right ? R : L;
	gyroZeroCheck(true);

	for (char a = 0; a < test_turn_times; a++) {
		cmt_wait(150);
		cc = 1;
		gyroRollTest(r == R ? L : R, test_turn_angle, test_turn_w,
				test_turn_acc);
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
	St2 = St1 - minus - 1;
	St3 = St1 - minus - 2;
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
	printMap2();
	if (cirquitMode == false) {
		minus = 4;
		int minus3 = makePath3(goalX, goalY, isFull);
	}
	printRealPath();
}
void makePath2() {
	flushcheckQ();
	if (cirquitMode == false) {
		minus = 4;
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
//	mtu_start();
//	readVelocityGain();
//	resetGyroParam();
	startVacume2(duty);
	fanMode = TestRun;
	//	cmt_wait(15000);
	int mode = 0;
	while (PushCenter) {

		if (!PushTop) {
			mode++;
		}
		if (!PushBottom) {
			mode--;
		}

		if (mode > 6) {
			mode = 0;
		}

		if (mode < 0) {
			mode = 0;
		}
		ledHex(mode);
		if (mode == 0) {
			myVacumeDuty = 4;
		} else if (mode == 1) {
			myVacumeDuty = 5;
		} else if (mode == 2) {
			myVacumeDuty = 6;
		} else if (mode == 3) {
			myVacumeDuty = 7;
		} else if (mode == 4) {
			myVacumeDuty = 8;
		} else if (mode == 5) {
			myVacumeDuty = 9;
		} else if (mode == 6) {
			myVacumeDuty = 9;
		}

		while (!PushTop || !PushBottom)
			;
	}

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
		myprintf("%d %d \n", (int) (FF_calc(L, 0, 0) * 1000),
				(int) (FF_calc(R, 0, 0) * 1000));
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
//			LED6 = 0;
			goal = 7;
		} else if (MTU1.TCNT < goal8) {
			LED1 = 0;
//			LED6 = 1;
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

	wall_off_limit = wall_off_limit_d = 200;

	if (mode == SEARCH || mode == SEARCH2) {
		Sen.Kp = *(float *) 1049376;
		Sen.Ki = *(float *) 1049380;
		Sen.Kd = *(float *) 1049384;
		fanMode = SearchRun;
	} else {
		Sen.Kp = 0.035;
		Sen.Ki = 0.0;
		Sen.Kd = 0.0825;
		fanMode = FastRun;
	}

	if (mode == SEARCH) {
		fanMode = SearchRun;
		wall_off_limit = wall_off_limit_d = 35;
		char m2 = eigherRightLeft() == Right;
		now_dir = North;
		next_dir = North;
		x = 0;
		y = 0;
		cirquitMode = 0;
		if (m2) {
			inputNaiperTurnAll1000();
		} else {
			inputNaiperTurnAll500();
		}
		save();
		pathClear();
//		return Adachi2(goalX, goalY, Zentansaku, isFull, m2);

		return Adachi2(goalX, goalY, Zentansaku, isFull, m2) ? 2 : 0;
	} else if (mode == SEARCH2) {
		fanMode = SearchRun;
		wall_off_limit = wall_off_limit_d = 35;
		char m2 = eigherRightLeft() == Right;
		now_dir = North;
		next_dir = North;
		x = 0;
		y = 0;
		cirquitMode = 0;

		if (m2) {
			inputNaiperTurnAll1000();
		} else {
			inputNaiperTurnAll500();
		}
		save();
		pathClear();
		return Adachi2(goalX, goalY, Oufuku, isFull, m2) ? 2 : 0;
	} else if (mode == RUN) {
		float v = 4500;
		if (!fastMode) {
			v = eigherRightLeft() == Right ? 4500 : 3500;
		}
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1500();
		save();
		save2();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 18000, 18000);
	} else if (mode == RUN2) {
		float v = 4700;
		if (!fastMode) {
			v = eigherRightLeft() == Right ? 4700 : 4000;
		}
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1700();
		save();
		inputNaiperTurnAll1500();
		save2();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 20000, 18000);
	} else if (mode == RUN3) {
		float v = 5000;
		if (!fastMode) {
			v = eigherRightLeft() == Right ? 5000 : 4500;
		}
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1800();
		save();
		inputNaiperTurnAll1500();
		save2();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 20000, 18000);
	} else if (mode == RUN4) {
		float v = eigherRightLeft() == Right ? 5000 : 4500;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 20000, 18000);
	} else if (mode == RUN5) {
		float v = eigherRightLeft() == Right ? 5100 : 4700;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll2000();
		save();
		inputNaiperTurnAll1500();
		save2();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 20000, 18000);
	} else if (mode == CONFIG) {
		float v = eigherRightLeft() == Right ? 5100 : 5000;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 20500, 19000);
	} else if (mode == CONFIG2) {
		float v = eigherRightLeft() == Right ? 5100 : 5000;
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 21000, 19500);
	} else if (mode == CONFIG3) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		if (!fastMode) {
			motionCheck();
		}
		float v = getMaxVeloctiy();
		char check = runForPath(v, 20000, 18000);
	} else if (mode == CONFIG4) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		float v = getMaxVeloctiy();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 20000, 18000);
	} else if (mode == CONFIG5) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		float v = getMaxVeloctiy();
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, 20000, 18000);
	} else if (mode == CONFIG6) {
	} else if (mode == CONFIG7) {
		goalChangeFlg = 1;
		operation();
	} else if (mode == CONFIG8) {
		showMotionLog();
//		if (saveFcuBlock(FLASH_DF_BLOCK_4)) {
//			oneUp(100);
//		}
	} else if (mode == CONFIG9) {
		keepZeroPoint2();
	} else if (mode == KeepZeroPoint) {
//		if (saveFcuBlock(FLASH_DF_BLOCK_4)) {
//			oneUp(100);
//		}
		keepZeroPoint();
	} else if (mode == MapMemory) {
//		testVacume2(70);
		motionCheck();
		startVacume2(70);
		cmt_wait(15000);
	} else if (mode == VacumeTest) {
		printSensor();
	} else if (mode == Mentenance) {
		resetFull();
	}
	mtu_stop2();
//	TRANSAM = false;
//	LED6 = false;
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
//		quoria(400);
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
//	float Velocity = 500;
	gyroZeroCheck(true);
	cmt_wait(500);
	cc = 1;
	gyroOn = 1;
	V_now = 0;
	mtu_start();
	V_now = 100;
	while (distance < 180 * 1) {

	}
//	realRun(Velocity, 3500, 3500, 60, 40);
//	frontCtrl4();

//	frontWallCtrl = true;
//	cmt_wait(500);
//	frontWallCtrl = false;
	mtu_stop();
	cmt_wait(500);
//	mtu_start();
//	if (RorL == R) {
//		gyroRoll(R, 90, 30, 30);
//	} else {
//		gyroRoll(L, 90, 30, 30);
//	}
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
		myprintf("	%f %f\r\n", LS_SEN45.now, RS_SEN45.now);
		myprintf("%f 		%f\r\n", 0, Front_SEN.now);
		myprintf("Duty:	%f	%f\r\n", Duty_l, Duty_r);
		myprintf("Velocity:	%f	%f\r\n", V_Enc.l, V_Enc.r);
		myprintf("angle:	%f\r\n", ang * 180 / PI);
		myprintf("distance:	%f\r\n", distance);

		cmt_wait(100);
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

void testRpm1() {
	while (1) {
		myprintf("%c[2J", ESC); /* 画面消去 */
		myprintf("%c[0;0H", ESC); /* 戦闘戻す*/
		myprintf("battery=%f V\r\n", battery);
		myprintf("Gyro=%f\r\n", settleGyro);
		myprintf("	%f %f\r\n", LS_SEN45.now, RS_SEN45.now);
		myprintf("%f 		%f\r\n", 0, Front_SEN.now);
		myprintf("Duty:	%f	%f\r\n", Duty_l, Duty_r);
		myprintf("Velocity:	%f	%f\r\n", V_Enc.l, V_Enc.r);
		myprintf("angle:	%f\r\n", ang * 180 / PI);
		myprintf("distance:	%f\r\n", distance);
		myprintf("RPM_R:	%f\r\n", getRpm(R));
		myprintf("RPM_L:	%f\r\n", getRpm(L));
		cmt_wait(100);
		if (!PushTop) {
			V_now = 500;
		}
		if (!PushRight) {
			W_now = 1;
		}
		if (!PushLeft) {
			W_now = -1;
		}
		if (Swich == 0) {
			break;
		}
	}
}

void operation() {
	volatile char goalX = (char) (*(float *) 1049336);
	volatile char goalY = (char) (*(float *) 1049340); //selectGoal();

	myprintf("Goal=(%d, %d)\r\n", goalX, goalY);
	fanMode = FastRun;
	if (!PushBottom) {
		goalX = 7;
		goalY = 7;
		coin(100);
		coin(100);
		coin(100);
	}

	if (goalChangeFlg == 1) {
		goalX = 7;
		goalY = 7;
	}

	if (!PushTop) {
		printSensor();
	}

	enableSciUpdate = true;
	while (PushBottom)
		;
	if (!PushTop) {
		enableSciUpdate = true;
		while (PushBottom)
			;
	}
	char testCmd = (char) (*(float *) 1049260);

//	keepZeroPoint();

	resetAllData();

//	testRpm1();

	if (testCmd > 0) {
		switch (testCmd) {
		case 1:
			cmtMusic(D2_, 100);
			testSlalom3();
			break;
		case 2:
			cmtMusic(E2_, 100);
			testRun();
			break;
		case 3:
			cmtMusic(F2_, 100);
			testRoll(R);
			break;
		case 4:
			cmtMusic(G2_, 100);
			testNormalSlalom();
			break;
		case 5:
			cmtMusic(A2_, 100);
			testWallOff();
			break;
		case 6:
			cmtMusic(B2_, 100);
			testWallOffSeach();
			break;
		case 7:
			cmtMusic(C3_, 100);
			testNormalSlalom();
			break;
		case 8:
			cmtMusic(D3_, 100);
			checkIsoukeisu();
			break;
		case 9:
			cmtMusic(E3_, 100);
			cirquit();
			break;
		}
	} else {
		cmtMusic(C2_, 100);
	}
	if (PushLeft) {
		if (!PushTop) {
			printSensor();
		}
	}

	cirquit();
	checkMemory(goalX, goalY);

//	while(1){
//		gyroZeroCheck(true);
//	}
//	cirquit();
	wall_off_limit = 25;
	wall_off_limit_d = 25;

	volatile char autostart = (char) (*(float *) 1049408);

	while (1) {
		TRANSAM = false;
		int res = action(encorderOperation(), goalX, goalY, false);
		mtu_stop2();
		if (autostart && res == 2) {
			action(RUN2, goalX, goalY, true);
		}
		mtu_stop2();
	}
}

#endif /* OPERATIONSYSTEM_H_ */
