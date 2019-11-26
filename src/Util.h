/*
 * Util.h
 *
 *  Created on: 2013/11/20
 *      Author: Naoto
 */

#ifndef UTIL_H_
#define UTIL_H_

float calcLerp(float x0, float y0, float x1, float y1, float x) {
	return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
}
float getLerpValue(float dist, float *list, int list_size) {
	int idx = (int) dist;

	if (idx >= list_size) {
		return list[list_size - 1];
	}
	if (dist < 0) {
		return list[0];
	}

	float x0 = idx;
	float y0 = list[idx];
	float x1 = idx + 1;
	float y1 = list[idx + 1];
	float y = calcLerp(x0, y0, x1, y1, dist);

	return y;
}

char eigherRightLeft() {
	char res;
	char flag = false;
	LED_RIGHT = LED_LEFT = true;
	while (true) {
		if (!PushLeft) {
			res = Left;
			flag = true;
			LED_RIGHT = false;
			LED_LEFT = true;
		}
		if (!PushRight) {
			res = Right;
			flag = true;
			LED_RIGHT = true;
			LED_LEFT = false;
		}
		if (!PushCenter && flag) {
			break;
		}
	}
	LED_RIGHT = LED_LEFT = false;
	return res;
}

char uiVolatage(char res) {
	char old = res;
	char flag = false;

	singing = true;
	while (true) {
		if (!PushRight || !PushLeft) {
			flag = true;
		}
		if (!PushTop) {
			flag = true;
			res++;
		}
		if (!PushBottom) {
			flag = true;
			res--;
		}
		if (res < 1) {
			res = 1;
		}
		if (res > 4) {
			res = 4;
		}
		if (res == 1) {
			led(0, 0, 0, 1);
		} else if (res == 2) {
			led(0, 0, 1, 1);
		} else if (res == 3) {
			led(0, 1, 1, 1);
		} else if (res == 4) {
			led(1, 1, 1, 1);
		}

		if (res != old) {
//			myprintf("change %d to %d\r\n", old, res);
			coin(100);
			singing = true;
		}

		old = res;

		while (!PushTop || !PushRight || !PushLeft || !PushBottom) {

		}
		if (!PushCenter && flag) {
			break;
		}

		cmt_wait(10);
	}
	LED(0);
	singing = false;
	return res;
}

char updown() {
	volatile signed char mode = SEARCH;
	os_escape = 0;
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
		}

		if (swTop || swBottom) {
			if (swTop) {
				mode++;
				if (mode > CONFIG3) {
					mode = SEARCH;
				}
			}
			if (swBottom) {
				mode--;
				if (mode < 0) {
					mode = CONFIG3;
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
	return mode;
}

float getMaxVeloctiy() {
	char mode = updown();
	if (mode == 1) {
		return 2000;
	} else if (mode == 2) {
		return 2500;
	} else if (mode == 3) {
		return 3000;
	} else if (mode == 4) {
		return 3500;
	} else if (mode == 5) {
		return 4000;
	} else if (mode == 6) {
		return 4500;
	} else if (mode == 7) {
		return 4750;
	} else if (mode == 8) {
		return 5000;
	} else if (mode == 9) {
		return 5100;
	}
	return 2000;
}
char selectGoal();
void resetData2() {
	ang = 0;
	angle = 0;
	V_now = 0;
	W_now = 0;
	w_now = 0;
	acc = 0;
	alpha = 0;
	fail = 1;
	dia = 0;
	Velocity.error_now = 0;
	Velocity.error_old = 0;
	Velocity.error_delta = 0;
	Distance.error_now = 0;
	Distance.error_old = 0;
	Distance.error_delta = 0;
	Vr.error_now = 0;
	Vr.error_old = 0;
	Vr.error_delta = 0;
	Vl.error_now = 0;
	Vl.error_old = 0;
	Vl.error_delta = 0;
	Gy.error_now = 0;
	Gy.error_old = 0;
	Gy.error_delta = 0;
	Angle.error_now = 0;
	Angle.error_old = 0;
	Angle.error_delta = 0;
	ledOn = 1;
	mode_FF = 1;
	distance = 0;
	img_distance = 0;
	C_old.s = C_old.v = C_old.g = 0;
}

void resetAllData() {
	ang = 0;
	angle = 0;
	V_old = 0;
	W_old = 0;
	V_now = 0;
	W_now = 0;
	w_now = 0;
	acc = 0;
	alpha = 0;
	fail = 1;
	dia = 0;
	globalSkipFront = false;
	Velocity.error_now = 0;
	Velocity.error_old = 0;
	Velocity.error_delta = 0;
	Distance.error_now = 0;
	Distance.error_old = 0;
	Distance.error_delta = 0;
	W_enc.error_now = 0;
	W_enc.error_old = 0;
	W_enc.error_delta = 0;
	Vr.error_now = 0;
	Vr.error_old = 0;
	Vr.error_delta = 0;
	Vl.error_now = 0;
	Vl.error_old = 0;
	Vl.error_delta = 0;
	Gy.error_now = 0;
	Gy.error_old = 0;
	Gy.error_delta = 0;
	Gy.before = 0;
	Angle.error_now = 0;
	Angle.error_old = 0;
	Angle.error_delta = 0;
	Angle.before = 0;
	ledOn = 1;
	mode_FF = 1;
	distance = 0;
	img_distance = 0;
	testRunMode = false;
	C_old.s = C_old.v = C_old.g = 0;
	resetOmegaParam();
}
void clearLogs();
void mtu_start() {
	ledOn = 1;
	cmt_wait(5);
	resetAllData();
	GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
	enablePWM = true;
	clearLogs();
	GPT.GTSTR.BIT.CST0 = GPT.GTSTR.BIT.CST1 = 1;
}
void mtu_stop() {
	enablePWM = false;
	cmt_wait(25);
	GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
	V_now = 0;
	W_now = 0;
	resetGyroParam();
	resetAngleParam();
	resetOmegaParam();
	resetData2();
	cmt_wait(5);
	GPT.GTSTR.BIT.CST0 = GPT.GTSTR.BIT.CST1 = 0;
//	stopVacume();
	ledOn = 0;
}
void mtu_stop3() {
	enablePWM = false;
	GPT.GTSTR.BIT.CST0 = GPT.GTSTR.BIT.CST1 = 0;
	GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
//	resetData2();
//	V_now = 0;
//	W_now = 0;
//	resetGyroParam();
//	resetAngleParam();
//	resetOmegaParam();
//	cmt_wait(5);
//	stopVacume();
	ledOn = 0;
}
void mtu_stop2() {
	globalState = NONE;
	V_now = 0;
	W_now = 0;
	acc = 0;
	alpha = 0;
	resetGyroParam();
	resetAngleParam();
	resetOmegaParam();
	resetAllData();
	C_old.s = C_old.v = C_old.g = 0;
	cmt_wait(750);
	enablePWM = false;
	GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
	cmt_wait(5);
	GPT.GTSTR.BIT.CST0 = GPT.GTSTR.BIT.CST1 = 0;
	PORTB.PODR.BIT.B1 = 0;
	PORTB.PODR.BIT.B3 = 0;
	stopVacume();
	ledOn = 0;
	enableSensorCtrl = false;
}
char failOutR = 0, failOutL = 0;
#define order 200
char senCheck = 0;
#define conflictOrder 3000
char failR2, failL2;
char dutyLimit, velocityLimit;
#define DIST_LIMIT 50
#define ERROR_LIMIT 1000
//char sw;
void failCheck(float Dr, float Dl) {
//	return;
	float vOrder = *(float *) 1049484;
	float wOrder = *(float *) 1049488;
	float TIME_LIMIT = *(float *) 1049492;

	char checkR = 0;
	char checkL = 0;
	if (Front_SEN.now > conflictOrder) {
		senCheck++;
	} else {
		senCheck = 0;
	}
	if (ABS((V_Enc.r + V_Enc.l) / 2 - V_now) > vOrder) {
		failOutR++;
		checkR++;
	}
	if (ABS(ang - angle) > wOrder) {
		failOutR++;
		checkR++;
	}

	if (checkR == 0) {
		failOutR = 0;
	}
	if (checkL == 0) {
		failOutL = 0;
		velocityLimit = 0;
		dutyLimit = 0;
	}
	if (failOutR >= TIME_LIMIT) {
		fail = 0;
	}

	if (failOutL >= TIME_LIMIT) {
		fail = 0;
	}

}

void batteryCheck() {
	cmt_wait(250);

	if (battery > 10) {
		if (battery < 11.5) {
			while (Swich) {
				cmt_wait(250);
				LED1 = 1;
				cmt_wait(250);
				LED2 = 1;
				cmt_wait(250);
				LED3 = 1;
				cmt_wait(250);
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
			}
		}
	} else {
		if (battery < 7.5) {
			while (Swich) {
				cmt_wait(250);
				LED1 = 1;
				cmt_wait(250);
				LED2 = 1;
				cmt_wait(250);
				LED3 = 1;
				cmt_wait(250);
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
			}
		}
	}

	if (battery < 3.75) {
		while (Swich) {
			cmt_wait(250);
			LED1 = 1;
			cmt_wait(250);
			LED2 = 1;
			cmt_wait(250);
			LED3 = 1;
			cmt_wait(250);
			LED1 = 0;
			LED2 = 0;
			LED3 = 0;
		}
	}
}

float exchangeBlockDistance(float dist) {
	return 180.0 * dist;
}

void printAdData() {
	myprintf("%d %d %d %d %d %d %d\r\n", LF, LS45, RS45, FRONT_AD, BATTERY);
}
char checkStablly();
float check_sen_error(void);
void gyroZeroCheck(char bool2);
char skipPrint = false;
void printSensor() {
	ledOn = 1;
	sensingMode = AtackDia;
//	sensingMode = CtrlMode;

	gyroZeroCheck(true);
	globalState = STRAIGHT;
//	dia = 1;
	ang = 0;
	enableSciUpdate = true;
	while (1) {
		if (!skipPrint) {
			myprintf(
					"{\"battery\":%f,\"gyro\":%f,\"left\":%d,\"right\":%d,\"front\":%d,\"left90\":%d,\"right90\":%d,\"rightdist\":%d,\"leftdist\":%d}\r\n",
					battery, settleGyro, (int) LS_SEN45.now, (int) RS_SEN45.now,
					(int) Front_SEN.now, (int) LS_SEN2.now, (int) RS_SEN2.now,
					(int) RS_SEN45.dist, (int) LS_SEN45.dist);
//			myprintf(
//					"\"LS1_2\":%d,\"RS1_2\":%d,\"LF1_2\":%d,\"RF1_2\":%d,\"LS2_2\":%d,\"RS2_2\":%d,\"BATT\":%d}\r\n",
//					(int) LS_SEN45.dist, (int) RS_SEN45.dist, (int) 0,
//					(int) Front_SEN.dist, (int) LS_SEN2.dist,
//					(int) RS_SEN2.dist, BATTERY);
		}
		cmt_wait(50);
		if (!Swich) {
			break;
		}
	}
	ledOn = 0;
}
void printSensor2() {
	ledOn = 1;
	sensingMode = AtackDia;
//	gyroZeroCheck(true);
//	dia = 1;
	while (1) {
		myprintf("%c[2J", ESC); /* 画面消去 */

//		myprintf("a"); /* 画面消去 */
		myprintf("%c[0;0H", ESC); /* 戦闘戻す*/
		myprintf("battery=%f V\r\n", battery);
		myprintf("Gyro=%f %f\r\n", settleGyro, G.ref);
//		myprintf("	 %f %f\r\n", LS_SEN2.now, RS_SEN2.now);
		myprintf("	%f %f\r\n", LS_SEN45.now, RS_SEN45.now);
		myprintf("%f %f\r\n", 0, Front_SEN.now);
		//		float error = 0;
//		error -= LS_SEN1.now - LS_SEN1.ref;
//		error += RS_SEN1.now - RS_SEN1.ref;
		myprintf("%f %f %f\r\n", check_sen_error(), Gy.error_now, Gy.error_old);
		myprintf("%f\r\n", tmpData);
		cmt_wait(100);
//		checkStablly();
		if (Swich == 0) {
			break;
		}
	}
	ledOn = 0;
}
void checkIsoukeisu() {
	while (1) {
		cmt_wait(100);
		myprintf("%d %d %d %d %d %d\r\n", MTU2.TCNT, MTU1.TCNT,
				(int) (distance), (int) V_Enc.l, (int) V_Enc.r,
				(int) (ang * 180 / PI));
	}
}
#define CHECK_ORDER_RIGHT 1200
#define CHECK_ORDER_LEFT 1200
char motionCheck() {
	int tmp = sensingMode;
	sensingMode = SearchMode;
	globalState = START_WAIT;
	ledOn = 1;
	while (1) {
		if (Front_SEN.now > CHECK_ORDER_RIGHT) {
			LED1 = 1;
			cmt_wait(100);
			LED1 = 0;
			cmt_wait(100);
			LED1 = 1;
			cmt_wait(100);
			LED1 = 0;
			sensingMode = tmp;
			os_escape = 1;
			return 1;
		} else {
			LED3 = 1;
			cmt_wait(50);
			LED3 = 0;
			cmt_wait(50);
			LED3 = 1;
			cmt_wait(50);
			LED3 = 0;
		}
	}

	globalState = STRAIGHT;
	ledOn = 0;
}

float getZeroPoint() {
	float tempData = 0;
	int limit = 512;
	float result = 0;
	mpu = false;
	for (int i = 0; i < limit; i++) {
		signed short a = MPU6500_Read_2byte(0x47);
		tempData += a;
		cmt_wait(1);
	}
	mpu = true;
	result = (float) tempData / limit;
	tempData = 0;
	tempGyro2 = result;
	settlegyroData = result;
	return result;
}
void gyroZeroCheck(char bool2) {
	if (bool2) {
		motionCheck();
	}
	resetGyroParam();
	resetAllData();
	float tmpData = 0;
	while (true) {
		tmpData = getZeroPoint();
		if (ABS(tmpData) < 0.01) {
			while (!setupMpu6500())
				;
		} else if (ABS(tmpData) < 70) {
			break;
		}
	}
	if (bool2) {
		coin(100);
	}
	myprintf("%f\r\n", tmpData);
	G.ref = tmpData;
}
long er, el;

char realRun(float max, float ac, float diac, float dist, float sla, char type);
float FB_distance();
void keepZeroPoint() {
	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	readGyroParam();
	readVelocityGain();

//	resetVelocityGain();
//	resetGyroParam();

	resetAllData();
	mtu_start();
//	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;

	cmt_wait(500);
	sensingMode = AtackStraight;
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
		myprintf("img_distance:	%f\r\n", img_distance);
		myprintf("FB_distance:	%f\r\n", FB_distance());

		cmt_wait(100);
		if (Swich == 0) {
			break;
		}
		if (!fail) {
//			break;
		}
	}
	mtu_stop();
}
void keepZeroPoint2() {
//	motionCheck();
//	cmt_wait(500);
	gyroZeroCheck(true);
	readGyroParam();
	readAngleParam();
	readVelocityGain();
//	resetGyroParam();
	mtu_start();
//	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;

	cmt_wait(500);
	sensingMode = AtackStraight;
	while (1) {
		myprintf("%c[2J", ESC); /* 画面消去 */
		myprintf("%c[0;0H", ESC); /* 戦闘戻す*/
		myprintf("battery=%f V\r\n", battery);
		myprintf("Gyro=%f\r\n", settleGyro);
		myprintf("	%f %f\r\n", LS_SEN45.now, RS_SEN45.now);
		myprintf("	%f %f\r\n", LS_SEN45.on, RS_SEN45.on);
		myprintf("	%f %f\r\n", LS_SEN45.off, RS_SEN45.off);
		myprintf("%f 		%f\r\n", 0, Front_SEN.now);
		myprintf("Duty:	%f	%f\r\n", Duty_l, Duty_r);
		myprintf("Velocity:	%f	%f\r\n", V_Enc.l, V_Enc.r);
		myprintf("angle:	%f\r\n", ang * 180 / PI);
		myprintf("distance:	%f\r\n", distance);
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
	mtu_stop();
}
char existWall(int x, int y, int dir);
void printMap() {
	int i = 0;
	int j = 0;
	myprintf("\r\n");
	for (int j = 15; j >= 0; j--) {
		myprintf("+");
		for (int i = 0; i < 16; i++) {
			if (existWall(i, j, North)) {
				myprintf("----+");
			} else {
				myprintf("    +");
			}
		}
		myprintf("\r\n");
		for (i = 0; i < 16; i++) {
			if (existWall(i, j, West)) {
				myprintf("| ");
			} else {
				myprintf("  ");
			}
			myprintf("%2x ", dist[i][j]);
		}
		myprintf("|\r\n");
	}
	myprintf("+");
	i = 0;
	for (i = 0; i < 16; i++) {
		if (existWall(i, j, South)) {
			myprintf("----+");
		} else {
			myprintf("    +");
		}
	}
	myprintf("\r\n");
}

void printMap2() {
	int i = 0;
	int j = 0;
	myprintf("\r\n");
	for (int j = 15; j >= 0; j--) {
		myprintf("+");
		for (int i = 0; i < 16; i++) {
			if (existWall(i, j, North)) {
				myprintf("----+");
			} else {
				myprintf("    +");
			}
		}
		myprintf("\r\n");
		for (i = 0; i < 16; i++) {
			if (existWall(i, j, West)) {
				myprintf("| ");
			} else {
				myprintf("  ");
			}
			myprintf("%2x ", map[i][j]);
		}
		myprintf("|\r\n");
	}
	myprintf("+");
	i = 0;
	for (i = 0; i < 16; i++) {
		if (existWall(i, j, South)) {
			myprintf("----+");
		} else {
			myprintf("    +");
		}
	}
	myprintf("\r\n");
}

void printMap3() {
	int i = 0;
	int j = 0;
	myprintf("\r\n");
	for (int j = 15; j >= 0; j--) {
		myprintf("+");
		for (int i = 0; i < 16; i++) {
			if (existWall(i, j, North)) {
				myprintf("----+");
			} else {
				myprintf("    +");
			}
		}
		myprintf("\r\n");
		for (i = 0; i < 16; i++) {
			if (existWall(i, j, West)) {
				myprintf("| ");
			} else {
				myprintf("  ");
			}
			myprintf("%2x ", (map[i][j] & 0xf0) >> 4);
		}
		myprintf("|\r\n");
	}
	myprintf("+");
	i = 0;
	for (i = 0; i < 16; i++) {
		if (existWall(i, j, South)) {
			myprintf("----+");
		} else {
			myprintf("    +");
		}
	}
	myprintf("\r\n");
}

int direction(int Dir, int SLRB) {
	if (Dir == North) {
		if (SLRB == Left) {
			Dir = West;
			x--;
		} else if (SLRB == Right) {
			Dir = East;
			x++;
		} else if (SLRB == Straight) {
			Dir = North;
			y++;
		} else {
			Dir = South;
			y--;
		}
	} else if (Dir == East) {
		if (SLRB == Left) {
			Dir = North;
			y++;
		} else if (SLRB == Right) {
			Dir = South;
			y--;
		} else if (SLRB == Straight) {
			Dir = East;
			x++;
		} else {
			Dir = West;
			x--;
		}
	} else if (Dir == West) {
		if (SLRB == Left) {
			Dir = South;
			y--;
		} else if (SLRB == Right) {
			Dir = North;
			y++;
		} else if (SLRB == Straight) {
			Dir = West;
			x--;
		} else {
			Dir = East;
			x++;
		}
	} else if (Dir == South) {
		if (SLRB == Left) {
			Dir = East;
			x++;
		} else if (SLRB == Right) {
			Dir = West;
			x--;
		} else if (SLRB == Straight) {
			Dir = South;
			y--;
		} else {
			Dir = North;
			y++;
		}
	}
	return Dir;
}
void waitforprint() {
	for (int i = 0; 1024; i++)
		;
}

void logOutPut() {
	globalState = PIVOT;
	while (Swich == 1)
		;
	for (c = 0; c < L_Length; c++) {
		myprintf("%d %f %f %f", log1[c], logs2[c], log3[c], log4[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f", log5[c], log6[c], log7[c], log8[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f", log9[c], logs10[c], log11[c], log12[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f %f %f", log13[c], log14[c], log15[c], log16[c],
				log17[c], log18[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f %f %f", log19[c], log20[c], log21[c], log22[c],
				log23[c], log24[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f %f", log25[c], log26[c], log27[c],
				log28[c] * 100, log29[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f %f", log30[c], log31[c], log32[c], log33[c],
				log34[c]);
		cmt_wait(1);
		myprintf(" %f %f\r\n", log35[c], log36[c]);
		cmt_wait(1);
	}
	globalState = STRAIGHT;
}

void detectSysIdLogOutput() {
	while (Swich == 1)
		;
	for (int c = 0; c < DETECT_SYS_ID_Length; c++) {
		myprintf("%f,%f,%f,%f\r\n", vrlist[c], vllist[c], gyrolist[c],
				dutylist[c]);
		cmt_wait(1);
	}
}

void logOutput3() {
	while (Swich == 1)
		;
	for (c = 0; c < L_Length; c++) {
		if (c > 500 && log5[c] == 0) {
//			break;
		}
		myprintf("[%f,%f,%f,", log1[c], 0, log3[c]);
		cmt_wait(1);
		myprintf("%f,%f,%f,%f,", log4[c], log5[c], log6[c], log7[c]);
		cmt_wait(1);
		myprintf(",%f,%f,%f,%f", log8[c], log9[c], logs10[c], log11[c]);
		cmt_wait(1);
		myprintf(",%f,%f,%f]\r\n", log12[c], log13[c], log14[c]);
		cmt_wait(1);
	}
}
int updateMap[MAZE_SIZE][MAZE_SIZE];
#define VectorMax 1023
int clearMap(int x, int y, char isFull) {
	int tail = 0;
	for (char i = 0; i < MAZE_SIZE; i++) {
		for (char j = 0; j < MAZE_SIZE; j++) {
			dist[i][j] = 255;
			m[i][j].n = VectorMax;
			m[i][j].e = VectorMax;
			m[i][j].w = VectorMax;
			m[i][j].s = VectorMax;
			m[i][j].step = 0;
			m[i][j].v = 0;
			m[i][j].N1 = 0;
			m[i][j].E1 = 0;
			m[i][j].W1 = 0;
			m[i][j].S1 = 0;
			m[i][j].NE = 0;
			m[i][j].NW = 0;
			m[i][j].SE = 0;
			m[i][j].SW = 0;
			updateMap[i][j] = 0;
		}
	}

	for (int i = 0; i < Q_LENGTH; i++) {
		que[i][0] = 0;
		que[i][1] = 0;
		que[i][2] = 0;
	}
	int goalMass = isFull ? 2 : 1;

	for (int i = 0; i < goalMass; i++) {
		for (int j = 0; j < goalMass; j++) {
			if (!existWall(x + i, y + j, North)) {
				m[x + i][y + j].n = 0;
				que[tail][0] = (x + i) * 16 + (y + j);
				que[tail][1] = North;
				tail++;
				if (y + j < 15) {
					m[x + i][y + 1 + j].s = 0;
				}
			}
			if (!existWall(x + i, y + j, East)) {
				m[x + i][y + j].e = 0;
				que[tail][0] = (x + i) * 16 + (y + j);
				que[tail][1] = East;
				tail++;
				if (x + i < 15) {
					m[x + 1 + i][y + j].w = 0;
				}
			}
			if (!existWall(x + i, y + j, West)) {
				m[x + i][y + j].w = 0;
				que[tail][0] = (x + i) * 16 + (y + j);
				que[tail][1] = West;
				tail++;
				if (x + i > 0) {
					m[x - 1 + i][y + j].e = 0;
				}
			}
			if (!existWall(x + i, y + j, South)) {
				m[x + i][y + j].s = 0;
				que[tail][0] = (x + i) * 16 + (y + j);
				que[tail][1] = South;
				tail++;
				if (y + j > 0) {
					m[x + i][y - 1 + j].n = 0;
				}
			}
		}
	}
	dist[x][y] = 0;
	return tail;
}
void printPath() {
	myprintf("\r\n");
	for (short i = 0; i < pathLength; i++) {
		myprintf("%d:	%f	%d	%d\r\n", i, (0.5 * path_s[i] - 1), path_s[i],
				path_t[i]);
		if (path_t[i] == 0xff || path_t[i] == 0x00) {
			break;
		}
	}
}
void printRealPath() {
	myprintf("\r\n");
	float dist = 0;
	for (short i = 0; i < pathLength; i++) {

		if (i == 0) {
			dist = 0.5 * (path_s[i] - 1) - 0.5;
		} else {
			dist = 0.5 * path_s[i] - 1;
		}
		myprintf("path_s[%d]=%f(%d);path_t[%d]=%d;\r\n", i, dist, path_s[i], i,
				path_t[i]);
		if (path_t[i] == 0xff || path_t[i] == 0) {
			break;
		}
	}
}
/**
 * integrate[exp(1-1/(1-x^n)),0,1]
 * Series[exp(1-1/(1-x^n)),{x,0,8}]
 */
#define Euler  2.7182818284
const float z = 1.0f;
float Et2(float t, float s, float N) {
	float P = 0;
	float Q = 0;
	t = t / s;
	P = powf((t - z), N - z);
	Q = P * (t - z);
	return -N * P / ((Q - z) * (Q - z)) * powf(expf(1), z + z / (Q - z)) / s;
}
//double Et2(double t, double s, double N) {
//	double P = 0;
//	double Q = 0;
//	t = t / s;
//	P = pow((t - z), N - z);
//	Q = P * (t - z);
//	return -N * P / ((Q - z) * (Q - z)) * pow(exp(1), z + z / (Q - z)) / s;
//}
char turnRoL(char a) {
	return a % 2 == 1 ? R : L;
}
void pathClear() {
	for (int i = 0; i < pathLength; i++) {
		path_s[i] = 0;
		path_t[i] = 0;
	}
}

float turnVelocity(char a) {
	if (a != Finish) {
		return v_sla[a];
	}
	return 2000;
}
float turnVelocity_transam(char a) {
	if (a != Finish) {
		return vs[a][8];
	}
	return 2000;
}
float turnVelocitySlow(char a) {
	if (a != Finish) {
		return v_sla[a];
	}
	return v_sla[Normal];
}
#endif /* UTIL_H_ */
