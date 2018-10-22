/*
 * sensor.h
 *
 *  Created on: 2017/07/30
 *      Author: Naoto
 */

#ifndef SENSOR_H_
#define SENSOR_H_

void sensor_led_off() {
	PORTE.PODR.BIT.B0 = 0;	//righ45
	PORTE.PODR.BIT.B1 = 0;	//right
	PORT2.PODR.BIT.B5 = 0;	//left45
	PORT2.PODR.BIT.B4 = 0;	//left
	PORTD.PODR.BIT.B6 = 0;	// fornt
}
void getBattery();
void sensing_battery() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x80; //battery
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	getBattery();
}
void sensing_in_off() {
	S12AD.ADANSA0.BIT.ANSA0 = 0xfE;
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	Front_SEN.off = FRONT_AD;
	RS_SEN45.off = RS45;
	LS_SEN45.off = LS45;
	RS_SEN2.off = RS2;
	LS_SEN2.off = LS2;
	getBattery();
}

void sensing_side2() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x24;
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	LS_SEN2.on = LS2;
	RS_SEN2.on = RS2;
}

void sensing_side() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x12;
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	LS_SEN45.on = LS45;
	RS_SEN45.on = RS45;
}

void sensing_front() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x08;
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	Front_SEN.on = FRONT_AD;
}

char isIncrease(char RorL) {
	if (RorL == R) {
		char flag = true;
		for (char i = 0; i < 3; i++) {
			if (sen_log_r[i] < sen_log_r[i + 1]) {
				flag = false;
			}
		}
		return flag;
	} else {
		char flag = true;
		for (char i = 0; i < 3; i++) {
			if (sen_log_l[i] < sen_log_l[i + 1]) {
				flag = false;
			}
		}
		return flag;
	}
	return false;
}

char isDecrease(char RorL) {
	if (RorL == R) {
		char flag = true;
		for (char i = 0; i < 5; i++) {
			if (sen_log_r[i] > sen_log_r[i + 1]) {
				flag = false;
			}
		}
		return flag;
	} else {
		char flag = true;
		for (char i = 0; i < 5; i++) {
			if (sen_log_l[i] > sen_log_l[i + 1]) {
				flag = false;
			}
		}
		return flag;
	}
	return false;
}

char startDecrease(char RorL) {
	if (RorL == R) {
		char flag = true;
		char flag2 = true;
		for (char i = 1; i < 3; i++) {
			if (sen_log_r[i] < sen_log_r[i + 1]) {
				flag = false;
			}
		}
		if (sen_log_r[0] < sen_log_r[1]) {
			flag2 = false;
		}
		return flag && !flag2;
	} else {
		char flag = true;
		char flag2 = true;
		for (char i = 1; i < 3; i++) {
			if (sen_log_l[i] < sen_log_l[i + 1]) {
				flag = false;
			}
		}
		if (sen_log_l[0] < sen_log_l[1]) {
			flag2 = false;
		}
		return flag && !flag2;
	}
	return false;
}

char isIncreaseFront(char RorL) {
	if (RorL == R) {
		char flag = true;
		for (char i = 0; i < 3; i++) {
			if (sen_log_front[i] < sen_log_front[i + 1]) {
				flag = false;
			}
		}
		return flag;
	} else {
		char flag = true;
		for (char i = 0; i < 3; i++) {
			if (sen_log_fl[i] < sen_log_fl[i + 1]) {
				flag = false;
			}
		}
		return flag;
	}
	return false;
}

#endif /* SENSOR_H_ */
