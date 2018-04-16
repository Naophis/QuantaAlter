/*
 * ParamImporter.h
 *
 *  Created on: 2017/09/02
 *      Author: Naoto
 */

#ifndef PARAMIMPORTER_H_
#define PARAMIMPORTER_H_

#define FLOAT_SIZE 4	//32byte
#define BASE_PARAM_KEY1 82	//基本パラメータ1
#define BASE_PARAM_KEY2 81	//基本パラメータ2
#define BASE_PARAM_KEY3 82	//基本パラメータ2
#define RUN_PARAM_KEY1 84	//ターンパラメータ1
#define RUN_PARAM_KEY2 86	//ターンパラメータ2

/**
 *   0~ 99	->	BASE_PARAM_KEY1
 * 100~199	->	BASE_PARAM_KEY2
 * 201~299	->	RUN_PARAM_KEY1
 * 301~399	->	RUN_PARAM_KEY2
 */

float getDataFlashData(long addr, int key) {
//	FLASH.FENTRYR.WORD = 0xAA00;
//	trans_farm_ = false;
	uint32_t address = 0; //g_flash_BlockAddresses[addr];
	return *(float *) (address + 4 * key);
}

/**
 * 1つだけの更新でも、配列すべてを書き換える必要がある。
 * @param key
 * @param val
 * @return
 */

char writeParam(int key, float val) {
	float array[16];
	int targetAddr;
	int offset = 0;
	if (0 <= key && key <= 15) {
		targetAddr = BASE_PARAM_KEY1;
		offset = 0;
	}
	for (int i = 0; i < 16; i++) {
		array[i] = getDataFlashData(targetAddr, key - offset);
	}
	array[key - offset] = val;
//	long target =0;// g_flash_BlockAddresses[targetAddr];
	char res1 =0;// erase(target);
	cmt_wait(100);
	myprintf("sizeof = %d\r\n", res1, sizeof(array));
	char res = 0;//R_FlashWrite(target, (uint32_t) array, sizeof(array));
	myprintf("erase = %d   write = %d\r\n", res1, res);
	return res1 & res;
}
void loadData() {
	enableSciUpdate = true;
	while (Swich) {

	}

//	cmt_wait(100);
//	myprintf("erase[80] %d\r\n", erase(g_flash_BlockAddresses[80]));
//	cmt_wait(100);
//	myprintf("erase[81] %d\r\n", erase(g_flash_BlockAddresses[81]));
//	cmt_wait(100);
//	myprintf("erase[82] %d\r\n", erase(g_flash_BlockAddresses[82]));
//	cmt_wait(100);
//	myprintf("erase[83] %d\r\n", erase(g_flash_BlockAddresses[83]));
//	cmt_wait(100);

	cmt_wait(100);
}
float readParam(int key) {
	int targetAddr, offset = 0;
	if (0 <= key && key <= 15) {
		targetAddr = BASE_PARAM_KEY1;
		offset = 0;
	}
//	if (16 <= key && key <= 31) {
//		targetAddr = BASE_PARAM_KEY2;
//		offset = 16;
//	}
//	if (32 <= key && key <= 47) {
//		targetAddr = BASE_PARAM_KEY3;
//		offset = 32;
//	}
	if (!targetAddr) {
		return false;
	}
	return getDataFlashData(targetAddr, key - offset);
}

void preread() {
//	gyroTh_R = readParam(0);
//	gyroTh_L = readParam(1);
//	tempGyro = readParam(2);
//	Vel.Kp = readParam(3);
//	Vel.Ki = readParam(4);
//	Vel.Kd = readParam(5);
//	Gyro.Kp = readParam(6);
//	Gyro.Ki = readParam(7);
//	Gyro.Kd = readParam(8);
//	Sen.Kp = readParam(9);
//	Sen.Ki = readParam(10);
//	Sen_Dia.Kp = readParam(11);
//	RS_SEN1.ref = readParam(12);
//	LS_SEN1.ref = readParam(13);
//	RF_SEN1.ref = readParam(14);
//	LF_SEN1.ref = readParam(15);
//	RF_SEN1.ref2 = readParam(16);
//	LF_SEN1.ref2 = readParam(17);
//	R_WALL_EXIST = readParam(18);
//	L_WALL_EXIST = readParam(19);
//	RF_WALL_EXIST = readParam(20);
//	LF_WALL_EXIST = readParam(21);
//	FRONT_CTRL_R = readParam(22);
//	FRONT_CTRL_L = readParam(23);
//	RF_WALL_EXIST2 = readParam(24);
//	LF_WALL_EXIST2 = readParam(25);
//	wallhosei = readParam(26);
//	RF_WALL = readParam(27);
//	LF_WALL = readParam(28);
//	RF_WALL1 = readParam(29);
//	LF_WALL1 = readParam(30);
//	R_WALL_dia = readParam(31);
//	L_WALL_dia = readParam(32);
//	R_WALL_OFF = readParam(33);
//	L_WALL_OFF = readParam(34);
//	R_WALL_OFF_D = readParam(35);
//	L_WALL_OFF_D = readParam(36);
//	FRONT_OUT_R = readParam(37);
//	FRONT_OUT_L = readParam(38);
//	existRightWall = readParam(39);
//	existLeftWall = readParam(40);
//	existRightWall3 = readParam(41);
//	existLeftWall3 = readParam(42);
//	existRightWall2 = readParam(43);
//	existLeftWall2 = readParam(44);

//	for (int i = 0; i <= 15; i++) {
//		myprintf("[%d]	%f\r\n", i, readParam(i));
//	}

}
void update(int key, float value) {
//	if (key == 0) {
//		gyroTh_R = value;
//	}
//	if (key == 1) {
//		gyroTh_L = value;
//	}
//	if (key == 2) {
//		tempGyro = value;
//	}
//	if (key == 3) {
//		Vel.Kp = value;
//	}
//	if (key == 4) {
//		Vel.Ki = value;
//	}
//	if (key == 5) {
//		Vel.Kd = value;
//	}
//	if (key == 6) {
//		Gyro.Kp = value;
//	}
//	if (key == 7) {
//		Gyro.Ki = value;
//	}
//	if (key == 8) {
//		Gyro.Kd = value;
//	}
//	if (key == 9) {
//		Sen.Kp = value;
//	}
//	if (key == 10) {
//		Sen.Ki = value;
//	}
//	if (key == 11) {
//		Sen_Dia.Kp = value;
//	}
//	if (key == 12) {
//		RS_SEN1.ref = value;
//	}
//	if (key == 13) {
//		LS_SEN1.ref = value;
//	}
//	if (key == 14) {
//		RF_SEN1.ref = value;
//	}
//	if (key == 15) {
//		LF_SEN1.ref = value;
//	}
//	if (key == 16) {
//		RF_SEN1.ref2 = value;
//	}
//	if (key == 17) {
//		LF_SEN1.ref2 = value;
//	}
//	if (key == 18) {
//		R_WALL_EXIST = value;
//	}
//	if (key == 19) {
//		L_WALL_EXIST = value;
//	}
//	if (key == 20) {
//		RF_WALL_EXIST = value;
//	}
//	if (key == 21) {
//		LF_WALL_EXIST = value;
//	}
//	if (key == 22) {
//		FRONT_CTRL_R = value;
//	}
//	if (key == 23) {
//		FRONT_CTRL_L = value;
//	}
//	if (key == 24) {
//		RF_WALL_EXIST2 = value;
//	}
//	if (key == 25) {
//		LF_WALL_EXIST2 = value;
//	}
//	if (key == 26) {
//		wallhosei = value;
//	}
//	if (key == 27) {
//		RF_WALL = value;
//	}
//	if (key == 28) {
//		LF_WALL = value;
//	}
//	if (key == 29) {
//		RF_WALL1 = value;
//	}
//	if (key == 30) {
//		LF_WALL1 = value;
//	}
//	if (key == 31) {
//		R_WALL_dia = value;
//	}
//	if (key == 32) {
//		L_WALL_dia = value;
//	}
//	if (key == 33) {
//		R_WALL_OFF = value;
//	}
//	if (key == 34) {
//		L_WALL_OFF = value;
//	}
//	if (key == 35) {
//		R_WALL_OFF_D = value;
//	}
//	if (key == 36) {
//		L_WALL_OFF_D = value;
//	}
//	if (key == 37) {
//		FRONT_OUT_R = value;
//	}
//	if (key == 38) {
//		FRONT_OUT_L = value;
//	}
//	if (key == 39) {
//		existRightWall = value;
//	}
//	if (key == 40) {
//		existLeftWall = value;
//	}
//	if (key == 41) {
//		existRightWall3 = value;
//	}
//	if (key == 42) {
//		existLeftWall3 = value;
//	}
//	if (key == 43) {
//		existRightWall2 = value;
//	}
//	if (key == 44) {
//		existLeftWall2 = value;
//	}

}

#endif /* PARAMIMPORTER_H_ */
