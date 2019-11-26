/*
 * Action.h
 *
 *  Created on: 2019/11/10
 *      Author: Naoto
 */

#ifndef ACTION_H_
#define ACTION_H_

void operation();
void inputNaiperTurnAll500();
void inputNaiperTurnAll1000();
void inputNaiperTurnAll1800();
void inputNaiperTurnAll1900();
void inputNaiperTurnAll1950();
void inputNaiperTurnAll2000();
void inputNaiperTurnAll2050();
void inputNaiperTurnAll2100();
void callParam(float vMax);
char isFullMaze(char X, char Y);
void makePath(char goalX, char goalY, char isFull, float vmax, float acc,
		float diac);
void easyMakePath(char isFull);

char action(char mode, char goalX, char goalY, char fastMode) {
	char isFull = isFullMaze(goalX, goalY);

	wall_off_limit = wall_off_limit_d = 200;
	Sen.Kp = *(float *) 1049376;
	Sen.Ki = *(float *) 1049380;
	Sen.Kd = *(float *) 1049384;
	fanMode = FastRun;

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
		save_high_param();
		pathClear();
		motionCheck();
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
		save_high_param();
		pathClear();
		motionCheck();
		return Adachi2(goalX, goalY, Oufuku, isFull, m2) ? 2 : 0;
	} else if (mode == RUN) {
		float v = 4500;
		float acc = 18000;
		float diac = 18000;
		inputNaiperTurnAll1800();
		save_high_param();
		save_low_param();
		save_transam_param();
		if (!fastMode) {
			v = eigherRightLeft() == Right ? 4500 : 3500;
		}
		makePath(goalX, goalY, isFull, 0, 0, 0);
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, acc, diac);
		const int Return = (int) (*(float *) 1049844);
		if (check && Return) {
			easyMakePath(isFull);
			check = runForPath(v, acc, diac);
		}
	} else if (mode == RUN2) {
		float v = 4700;
		float acc = 18000;
		float diac = 22000;
		inputNaiperTurnAll1800();
		save_low_param();
		save_high_param();
		save_transam_param();
		if (!fastMode) {
			v = eigherRightLeft() == Right ? 4700 : 4000;
		}
		makePath(goalX, goalY, isFull, 0, 0, 0);
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, acc, diac);
		const int Return = (int) (*(float *) 1049844);
		if (check && Return) {
			easyMakePath(isFull);
			check = runForPath(v, acc, diac);
		}
	} else if (mode == RUN3) {
		float v = 5000;
		float acc = 18000;
		float diac = 22000;
		if (!fastMode) {
			v = eigherRightLeft() == Right ? 5000 : 4750;
		}
		inputNaiperTurnAll1800();
		save_low_param();
		save_high_param();
		save_transam_param();
		makePath(goalX, goalY, isFull, 0, 0, 0);
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, acc, diac);
		const int Return = (int) (*(float *) 1049844);
		if (check && Return) {
			easyMakePath(isFull);
			check = runForPath(v, acc, diac);
		}
	} else if (mode == RUN4) {
		float v = eigherRightLeft() == Right ? 5100 : 5000;
		float acc = 18000;
		float diac = 22000;
		fanMode = FastRun2;
		inputNaiperTurnAll1800();
		save_low_param();
		inputNaiperTurnAll1900();
		save_high_param();
		char res2 = uiVolatage(2);
		if (res2 == 1) {
			v = 5000;
		} else if (res2 == 2) {
			v = 5100;
		} else if (res2 == 3) {
			v = 5300;
		} else if (res2 == 4) {
			v = 5500;
		}
		if (res2 > 2) {
			setLargeParam2500();
			setOrvalParam2300();
		} else {
			setLargeParam2400();
			setOrvalParam2200();
		}
		save_transam_param();
		makePath(goalX, goalY, isFull, 0, 0, 0);
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, acc, diac);
		const int Return = (int) (*(float *) 1049844);
		if (check && Return) {
			easyMakePath(isFull);
			fanMode = FastRun2;
			check = runForPath(v, acc, diac);
		}
	} else if (mode == RUN5) {
		float v = eigherRightLeft() == Right ? 5100 : 5000;
		float acc = 18000;
		float diac = 22000;
		fanMode = FastRun2;

		inputNaiperTurnAll1800();
		save_low_param();

		inputNaiperTurnAll1950();
		char res2 = uiVolatage(2);
		if (res2 == 1) {
			setLargeParam2000();
			setOrvalParam2000();
			v = 5000;
		} else if (res2 == 2) {
			setLargeParam2050();
			setOrvalParam2050();
			v = 5300;
		} else if (res2 == 3) {
			setLargeParam2100();
			setOrvalParam2050();
			v = 5500;
		} else if (res2 == 4) {
			setLargeParam2200();
			setOrvalParam2050();
			v = 5700;
		}
		save_high_param();
		char res3 = uiVolatage(2);
		if (res3 > 2) {
			setLargeParam2500();
			setOrvalParam2300();
		} else {
			setLargeParam2400();
			setOrvalParam2200();
		}
		save_transam_param();

		makePath(goalX, goalY, isFull, 0, 0, 0);
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, acc, diac);
		const int Return = (int) (*(float *) 1049844);
		if (check && Return) {
			easyMakePath(isFull);
			fanMode = FastRun2;
			check = runForPath(v, acc, diac);
		}
	} else if (mode == CONFIG) {
		fanMode = FastRun2;
		float v = eigherRightLeft() == Right ? 5100 : 5000;
		float acc = 18000;
		float diac = 22000;
		char res2 = uiVolatage(2);

		inputNaiperTurnAll1800();
		save_low_param();

		inputNaiperTurnAll2000();
		if (res2 == 1) {
			v = 5100;
		} else if (res2 == 2) {
			setLargeParam2050();
			setOrvalParam2050();
			v = 5300;
		} else if (res2 == 3) {
			setLargeParam2100();
			setOrvalParam2050();
			v = 5700;
		} else if (res2 == 4) {
			setLargeParam2200();
			setOrvalParam2050();
			v = 5800;
		}
		save_high_param();
		char res3 = uiVolatage(2);
		if (res3 > 2) {
			setLargeParam2500();
			setOrvalParam2300();
		} else {
			setLargeParam2400();
			setOrvalParam2200();
		}
		save_transam_param();

		makePath(goalX, goalY, isFull, 0, 0, 0);
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, acc, diac);
		const int Return = (int) (*(float *) 1049844);
		if (check && Return) {
			easyMakePath(isFull);
			fanMode = FastRun2;
			check = runForPath(v, acc, diac);
		}
	} else if (mode == CONFIG2) {
		fanMode = FastRun2;
		float acc = 18000;
		float diac = 22000;
		float v = eigherRightLeft() == Right ? 5250 : 5000;
		char res2 = uiVolatage(2);

		inputNaiperTurnAll1800();
		save_low_param();

		inputNaiperTurnAll2050();
		if (res2 == 1) {
			setLargeParam2050();
			v = 5300;
		} else if (res2 == 2) {
			setLargeParam2100();
			v = 5500;
		} else if (res2 == 3) {
			setLargeParam2200();
			v = 5800;
		} else if (res2 == 4) {
			setLargeParam2300();
			v = 6000;
		}
		save_high_param();
		char res3 = uiVolatage(2);
		if (res3 > 2) {
			setLargeParam2500();
			setOrvalParam2300();
		} else {
			setLargeParam2400();
			setOrvalParam2200();
		}
		save_transam_param();
		makePath(goalX, goalY, isFull, 0, 0, 0);
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, acc, diac);
		const int Return = (int) (*(float *) 1049844);
		if (check && Return) {
			easyMakePath(isFull);
			fanMode = FastRun2;
			check = runForPath(v, acc, diac);
		}
	} else if (mode == CONFIG3) {
		fanMode = FastRun2;
		float v = eigherRightLeft() == Right ? 5300 : 5000;
		float acc = 18000;
		float diac = 22000;

		inputNaiperTurnAll1800();
		save_low_param();

		char res2 = uiVolatage(2);
		inputNaiperTurnAll2100();
		if (res2 == 1) {
			setLargeParam2200();
		} else if (res2 == 2) {
			setLargeParam2200();
		} else if (res2 == 3) {
			setLargeParam2300();
		} else if (res2 == 4) {
			setLargeParam2300();
		}
		save_high_param();

		char res3 = uiVolatage(2);
		if (res3 > 2) {
			setLargeParam2500();
			setOrvalParam2300();
		} else {
			setLargeParam2400();
			setOrvalParam2200();
		}

		save_transam_param();
		makePath(goalX, goalY, isFull, 0, 0, 0);
		if (!fastMode) {
			motionCheck();
		}
		char check = runForPath(v, acc, diac);
		const int Return = (int) (*(float *) 1049844);
		if (check && Return) {
			easyMakePath(isFull);
			fanMode = FastRun2;
			check = runForPath(v, acc, diac);
		}
	} else if (mode == CONFIG4) {
	} else if (mode == CONFIG5) {
	} else if (mode == CONFIG6) {
	} else if (mode == CONFIG7) {
		goalChangeFlg = 1;
		operation();
	} else if (mode == CONFIG8) {
	} else if (mode == CONFIG9) {
		keepZeroPoint2();
	} else if (mode == KeepZeroPoint) {
		keepZeroPoint();
	} else if (mode == MapMemory) {
		motionCheck();
		fanMode = CtrlFan3;
		startVacume2(70);
		cmt_wait(15000);
	} else if (mode == VacumeTest) {
		if (saveFcuBlock(FLASH_DF_BLOCK_4)) {
			oneUp(100);
		}
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

#endif /* ACTION_H_ */
