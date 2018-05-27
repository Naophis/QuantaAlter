#include "iodefine.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>
#include "machine.h"
#include "mathf.h"
#include "config/defines.h"
#include "config/Table.h"

#include "config/Structor.h"

#include "config/init.h"
#include "serial.h"
#include "spi.h"
#include "Music.h"

#include "config/ParamDef.h"
#include "sensor.h"

#include "config/ParamDef.h"
#include "config/ParamsController.h"
#include "config/ParamUartImporter.h"
#include "Util.h"
#include "PhysicalBasement.h"

#include "motion/Run.h"
#include "motion/WallOff.h"
#include "motion/WallOff2.h"
#include "search/Map.h"
#include "search/Search.h"
#include "search/VectorSearch.h"
#include "search/VectorPath.h"
#include "Path.h"
#include "motion/RealRun.h"

#include "flash/r_flash_rx_config.h"
#include "flash/r_flash_rx_if.h"
#include "flash/flash.h"

#include "search/Adachi.h"
#include "search/cirkit.h"

#include "config/ParamImporter.h"

#include "config/Setting.h"
//#include "Mram.h"

#include "OperationSystem.h"
#include "config/SerialMapper.h"

volatile void buzzer() {
//	if ((buzzerTimer % 2) == 0) {
//		PORTD.PODR.BIT.B7 = 1;
//	} else {
//		PORTD.PODR.BIT.B7 = 0;
//	}
	buzzerTimer++;
	if (m_time > 0 && buzzerTimer >= m_time) {
		stopCmt1();
	}
}
volatile int tmp1 = 0;
volatile int tmp2 = 0;
volatile void mtu6A() {
	PORTD.PODR.BIT.B7 = 1;
	tmp1++;
}
volatile void mtu6B() {
	PORTD.PODR.BIT.B7 = 0;
	tmp2++;
}
volatile char rightTrend = 0;
volatile char leftTrend = 0;
volatile void cmt() {
	timer++;
	time++;
	if (singing) {
		buzzerTimer++;
		if (m_time > 0 && buzzerTimer >= (CMT_CYCLE / 1000) * m_time) {
			stopCmt1();
		}
	}
	sinCount++;
	swTop = !PushTop;
	swBottom = !PushBottom;
	swRight = !PushRight;
	swLeft = !PushLeft;
	swCenter = !PushCenter;
	if (!singing) {
		if (!PushTop) {
			cmtMusic(C2_, 100);
		}
		if (!PushRight) {
			cmtMusic(D2_, 100);
		}
		if (!PushLeft) {
			cmtMusic(E2_, 100);
		}
		if (!PushBottom) {
			cmtMusic(F2_, 100);
		}
	}
//	if (singing) {
//		buzzer();
//	}
	if (dia == 1) {
		pushLatestSensor(RS_SEN45.now, LS_SEN45.now);
		pushLatestSensor2(RS_SEN2.now, LS_SEN2.now);
	} else {
		peekRight = 0;
		peekLeft = 0;
		lastPeekR = 0;
		lastPeekL = 0;
		peekRight2 = 0;
		peekLeft2 = 0;
		lastPeekR2 = 0;
		lastPeekL2 = 0;
		Se2.error_old = Se2.before = Se2.error_delta = 0;
	}
	Physical_Basement();
	if (logs < L_Length && cc == 1) {
		if ((time % 4) == 0) {
			log1[logs] = (int) (V_now);
			logs2[logs] = ((Wo * Wo - W_now * W_now) / (2.0 * alpha));
			log3[logs] = (V_Enc.r + V_Enc.l) / 2;
			log4[logs] = (ang * 180 / PI); //ジャイロ
			log5[logs] = Duty_l * 100;
			log6[logs] = Duty_r * 100;
			log7[logs] = (battery);
			log8[logs] = (LS_SEN45.now);
			log9[logs] = (RS_SEN45.now);
			logs10[logs] = Se.error_now;
			log11[logs] = (Front_SEN.now);
			log12[logs] = (settleGyro);
			log13[logs] = (W_now);
			log14[logs] = (angle * 180 / PI); //理論値
			log15[logs] = (V_Enc.r);
			log16[logs] = (V_Enc.l);
			log17[logs] = (float) (alpha);
			log18[logs] = peekRight; //lastPeekR;
			log19[logs] = (feadforward_para(L));
			log20[logs] = (feadforward_para(R));
			log21[logs] = (LS_SEN2.now);
			log22[logs] = (RS_SEN2.now);
			log23[logs] = peekRight2;
			log24[logs] = peekLeft2;
			log25[logs] = C.g;
			log26[logs] = C.s;
			log27[logs] = peekLeft;
			log28[logs] = globalState;
			log29[logs] = Se2.error_now;
			log30[logs] = lastPeekL;
			log31[logs] = lastPeekR;
			log32[logs] = lastPeekL2;
			log33[logs] = lastPeekR2;
			logs++;
		}
	}
}

volatile int timer2 = 0;

void mtu4_A() {
	tpu_count++;
	switch (tpu_count) {
	case 1:
		timer2++;
		sensing_in_off();
		if (mpu) {
			callMpu(0x47);
		}
		PORTD.PODR.BIT.B6 = 1; //Front
		break;
	case 2:
		if (mpu) {
			callMpu(0x47);
		}
		PORTE.PODR.BIT.B0 = 1; //Right45
		PORT2.PODR.BIT.B5 = 1; //Left45
		break;
	case 3:
		if (mpu) {
			callMpu(0x47);
		}
		PORTE.PODR.BIT.B1 = 1; //Right
		PORT2.PODR.BIT.B4 = 1; //Left
		break;
	case 4:
		if (mpu) {
			callMpu(0x47);
		}
		sensing_battery();
		break;
	}
}

void getBattery() {
	float tmp = 3.34;
	if (BATTERY != 0) {
		battery = 0.1 * tmp * BATTERY / 4096 * 4 + 0.9 * batteryOld;
	} else {
		battery = tmp * BATTERY / 4096 * 4;
	}
	batteryOld = battery;
}
int gyros[4];

void mtu4_B() {
	switch (tpu_count) {
	case 1:
		sensing_front();
		gyros[0] = getMpuData();
		break;
	case 2:
		sensing_side();
		gyros[1] = getMpuData();
		break;
	case 3:
		sensing_side2();
		gyros[2] = getMpuData();
		break;
	case 4:
		if (fanStart) {
			if (fanMode == TestRun) {
				GPT2.GTCCRA = (short) (myVacumeDuty / battery * FAN_CYCLE);
				GPT2.GTCCRC = (short) (myVacumeDuty / battery * FAN_CYCLE);
			} else if (fanMode == FastRun) {
				GPT2.GTCCRA = (short) (FAN_AMP / battery * FAN_CYCLE);
				GPT2.GTCCRC = (short) (FAN_AMP / battery * FAN_CYCLE);
			} else {
				GPT2.GTCCRA = (short) (FAN_AMP2 / battery * FAN_CYCLE);
				GPT2.GTCCRC = (short) (FAN_AMP2 / battery * FAN_CYCLE);
			}
		} else {
			GPT2.GTCCRA = GPT2.GTCCRC = 0;
		}

		gyros[3] = getMpuData();

		RS_SEN45.old = RS_SEN45.now;
		LS_SEN45.old = LS_SEN45.now;
		Front_SEN.old = Front_SEN.now;
		RS_SEN2.old = RS_SEN2.now;
		LS_SEN2.old = LS_SEN2.now;

		getSensorData();

		float tmpGyros = (gyros[0] + gyros[1] + gyros[2] + gyros[3]) / 4;
		settleGyro2 = (tmpGyros - G.ref) * G.th;
		G.now = settleGyro2;
		settleGyroOld = settleGyro;
		settleGyro = 0.1 * G.now + 0.9 * G.old;
		//		settleGyro = settleGyro2;
		G.old = settleGyro;

		tpu_count = 0;

		for (char i = 4; i > 0; i--) {
			sen_log_r[i] = sen_log_r[i - 1];
			sen_log_l[i] = sen_log_l[i - 1];
			sen_log_front[i] = sen_log_front[i - 1];
			sen_r[i] = sen_r[i - 1];
			sen_l[i] = sen_l[i - 1];
			sen_r2[i] = sen_r2[i - 1];
			sen_l2[i] = sen_l2[i - 1];
		}
		sen_log_r[0] = RS_SEN45.now;
		sen_log_l[0] = LS_SEN45.now;
		sen_r[0] = RS_SEN45.now > running_wall_off_r;
		sen_l[0] = LS_SEN45.now > running_wall_off_l;
		sen_r2[0] = RS_SEN2.now > search_wall_off_r;
		sen_l2[0] = LS_SEN2.now > search_wall_off_l;
		sen_log_front[0] = Front_SEN.now;
		break;
	}
	sensor_led_off();
}

void initRX64M() {
	initClock();
	initLED();
	initSensorLED();
	initMotorDriverRotate();
	initS12AD();
	initSci1();
	initCmt0();
	initIsouKeisu();
	initGPT01();
//	initGPT2();
	Init_SPI();
	init_Mtu4();
	init_Mtu6();
	myprintf("Flash Open %d\r\n", R_FLASH_Open());
	importParam();

}
void test() {
	ComFlag = true;
}

void printErrorEnum() {
	myprintf("%s %d\r\n", STR(FLASH_SUCCESS), FLASH_SUCCESS);
	myprintf("%s %d\r\n", STR(FLASH_ERR_BUSY), FLASH_ERR_BUSY);
	myprintf("%s %d\r\n", STR(FLASH_ERR_ACCESSW), FLASH_ERR_ACCESSW);
	myprintf("%s %d\r\n", STR(FLASH_ERR_FAILURE), FLASH_ERR_FAILURE);
	myprintf("%s %d\r\n", STR(FLASH_ERR_CMD_LOCKED), FLASH_ERR_CMD_LOCKED);
	myprintf("%s %d\r\n", STR(FLASH_ERR_LOCKBIT_SET), FLASH_ERR_LOCKBIT_SET);
	myprintf("%s %d\r\n", STR(FLASH_ERR_FREQUENCY), FLASH_ERR_FREQUENCY);
	myprintf("%s %d\r\n", STR(FLASH_ERR_ALIGNED), FLASH_ERR_ALIGNED);
	myprintf("%s %d\r\n", STR(FLASH_ERR_BOUNDARY), FLASH_ERR_BOUNDARY);
	myprintf("%s %d\r\n", STR(FLASH_ERR_OVERFLOW), FLASH_ERR_OVERFLOW);
	myprintf("%s %d\r\n", STR(FLASH_ERR_BYTES), FLASH_ERR_BYTES);
	myprintf("%s %d\r\n", STR(FLASH_ERR_ADDRESS), FLASH_ERR_ADDRESS);
	myprintf("%s %d\r\n", STR(FLASH_ERR_BLOCKS), FLASH_ERR_BLOCKS);
	myprintf("%s %d\r\n", STR(FLASH_ERR_PARAM), FLASH_ERR_PARAM);
	myprintf("%s %d\r\n", STR(FLASH_ERR_NULL_PTR), FLASH_ERR_NULL_PTR);
	myprintf("%s %d\r\n", STR(FLASH_ERR_UNSUPPORTED), FLASH_ERR_UNSUPPORTED);
	myprintf("%s %d\r\n", STR(FLASH_ERR_SECURITY), FLASH_ERR_SECURITY);
	myprintf("%s %d\r\n", STR(FLASH_ERR_TIMEOUT), FLASH_ERR_TIMEOUT);
}

void main(void) {
	initRX64M();
	batteryCheck();
	setupCmt = enableMPU = os_escape = true;

	while (1) {
		float result = getZeroPoint();
		if (ABS(result) < 0.5) {
			decide2(125);
			setupMpu6500();
		} else {
			break;
		}
	}
	coin(100);
	ledOn = 1;
	os_escape = 1;
	myprintf("%c[33m", ESC); /* 文字を黄色に */
	operation();
	os_escape = 0;
}
