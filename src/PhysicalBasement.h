/*
 * PhysicalBasement.h
 *
 *  Created on: 2013/11/20
 *      Author: Naoto
 */

#ifndef PHYSICALBASEMENT_H_
#define PHYSICALBASEMENT_H_

char directionCheck_R = 0;
char directionCheck_L = 0;
float enc_r, enc_l;
long er, el;
float vr, vl;
float vr2, vl2;
#define logSize  200
float logR[logSize];
float logL[logSize];

void clearLogs() {
	for (char i = 0; i < logSize; i++) {
		logR[i] = 0;
		logL[i] = 0;
	}
}
float peekRight = 0;
float peekLeft = 0;
float lastPeekR = 0;
float lastPeekL = 0;
float peekRight2 = 0;
float peekLeft2 = 0;
float lastPeekR2 = 0;
float lastPeekL2 = 0;

float peekOrderR = 1800;
float peekOrderL = 1800;
void pushLatestSensor(float r, float l) {
	if (r > peekOrderR) {
		if (peekRight < r) {
			peekRight = r;
		}
	} else {
		if (lastPeekR == 0 && peekRight > peekOrderR) {
			lastPeekR = peekRight;
			lastPeekR2 = 0;
		}
		peekRight = 0;
	}
	if (l > peekOrderL) {
		if (peekLeft < l) {
			peekLeft = l;
		}
	} else {
		if (lastPeekL == 0 && peekLeft > peekOrderL) {
			lastPeekL = peekLeft;
			lastPeekL2 = 0;
		}
		peekLeft = 0;
	}
}

float peekOrderR2 = 2000;
float peekOrderL2 = 2000;
void pushLatestSensor2(float r, float l) {
	if (r > peekOrderR2) {
		if (peekRight2 < r) {
			peekRight2 = r;
		}
	} else {
		if (lastPeekR2 == 0 && peekRight2 > peekOrderR2) {
			lastPeekR2 = peekRight2;
			lastPeekR = 0;
		}
		peekRight2 = 0;
	}
	if (l > peekOrderL2) {
		if (peekLeft2 < l) {
			peekLeft2 = l;
		}
	} else {
		if (lastPeekL2 == 0 && peekLeft2 > peekOrderL2) {
			lastPeekL2 = peekLeft2;
			lastPeekL = 0;
		}
		peekLeft2 = 0;
	}
}

void pushLog(float r, float l) {
	for (char i = 0; i < logSize - 1; i++) {
		logR[i + 1] = logR[i];
		logL[i + 1] = logL[i];
	}
	logR[0] = r;
	logL[0] = l;
}

void searchPeek() {
	for (int i = 0; i < logSize; i++) {

	}
}

float getAverageR() {
	float sum = 0;
	for (char i = 0; i < logSize; i++) {
		sum += logR[i];
	}
	return sum / logSize;
}
float getAverageL() {
	float sum = 0;
	for (char i = 0; i < logSize; i++) {
		sum += logL[i];
	}
	return sum / logSize;
}

void enc_to_vel(void) {
	float temp = Velocity.error_now;
	Velocity.error_old += Velocity.error_now;

	vr = -(float) (PI * TIRE * enc_r * CMT_CYCLE / GEAR / 4096.0);
	vl = -(float) (PI * TIRE * enc_l * CMT_CYCLE / GEAR / 4096.0);

	V_Enc.r = vr; // vr * 0.1 + vr2 * 0.9;
	V_Enc.l = vl; // vl * 0.1 + vl2 * 0.9;

	vr2 = V_Enc.r;
	vl2 = V_Enc.l;

	Velocity.error_delta = (V_now - (V_Enc.l + V_Enc.r) / 2) - temp;

	rpmR_old = rpmR;
	rpmL_old = rpmL;

	rpmR = ((V_now - Tread * 500 * W_now) / (TIRE / 2)) * 60.0 / (2.0 * PI);
	rpmL = ((V_now + Tread * 500 * W_now) / (TIRE / 2)) * 60.0 / (2.0 * PI);

	Velocity.error_now = V_now - (V_Enc.r + V_Enc.l) / 2;

	// px += V_now * sinf(ABS(ang)) * dt;
	// py += V_now * cosf(ABS(ang)) * dt;

}
#define KIREME_R 11 //11/12
#define KIREME_L 11
#define KIREME_R2 10
#define KIREME_L2 10
unsigned int R_WALL = 880; //820; //#define R_WALL 4000	//サーキット用
unsigned int L_WALL = 750; //600;	//制御壁閾値
volatile float FRONT_OUT = 2250;	//袋小路時前センサー閾値

int checkStr = 0;
float check_sen_error(void) {
	float error = 0;
	char check = 0;
	const float rightCtrlDiff = *(float *) 1049964;
	const float leftCtrlDiff = *(float *) 1049968;
	const int kireme_R = (int) (*(float *) 1049972);
	const int kireme_L = (int) (*(float *) 1049976);
	if (Front_SEN.now < FRONT_OUT) {
		if (ABS(RS_SEN45.now - RS_SEN45.old) < kireme_R) {
			if (RS_SEN45.now > (RS_SEN45.ref - rightCtrlDiff)) {
				error += RS_SEN45.now - RS_SEN45.ref;
				check++;
			}
		}
		if (ABS(LS_SEN45.now - LS_SEN45.old) < kireme_L) {
			if (LS_SEN45.now > (LS_SEN45.ref - leftCtrlDiff)) {
				error -= LS_SEN45.now - LS_SEN45.ref;
				check++;
			}
		}
	}
	if (check == 0) {
		Se.error_old = Se.before = Se.error_delta = 0;
	} else {
		if (!testRunMode && gyroErrResetEnable) {
			Gy.error_old = 0;
			Angle.error_old = 0;
			angle = ang = 0;
		}
	}

	if (check != 0) {
		errorFlg = 1;
		globalError = error;
	} else {
		errorFlg = 0;
	}
	if (check == 2) {
		return error;
	}
	return 2 * error;
}
void resetAngleError(void) {
	char check = 0;
	if (ABS(RS_SEN45.now - RS_SEN45.old) < KIREME_R) {
		if (RS_SEN45.now > R_WALL) {
			if (Front_SEN.now < FRONT_OUT) {
				check++;
			}
		}
	} else {
		if (RS_SEN45.now > (R_WALL + orderup_r)) {
			check++;
		}
	}
	if (ABS(LS_SEN45.now - LS_SEN45.old) < KIREME_L) {
		if (LS_SEN45.now > L_WALL) {
			if (Front_SEN.now < FRONT_OUT) {
				check++;
			}
		}
	} else {
		if (LS_SEN45.now > (L_WALL + orderup_l)) {
			check++;
		}
	}
	if (check > 0) {
		Gy.error_old = 0;
		Angle.error_old = 0;
		angle = 0;
		ang = 0;
	}

}
int gyroReset = 0;

volatile char isControl = 0;
volatile int errorOld_dia = 0;
volatile int errorOld_dia_side = 0;

char validateImgIndex(int a) {
	return 30 <= a && a <= 220;
}

char validateImg90Index(int a) {
	return (0 <= a && a <= 25) || (55 <= a && a <= 145)
			|| (190 <= a && a <= 250);
}
float lastR45Data = 0;
float lastL45Data = 0;
float check_sen_error_dia_side_v2(void) {
	float error = 0;
	float error2 = 0;
	char check = 0;
	char check2 = 0;

	const float diff = *(float *) 1049732;
	const float diff90 = *(float *) 1049736;

	const float diffthread = *(float *) 1049740;
	const float diffthread90 = *(float *) 1049744;

	char flag45 = false;

	if (diaStrwallCount_r > 0) {
		float tmpRightRef = sen_r_dia_img[(int) img_dist_r];
		float tmpRightRef90 = sen_r90_dia[(int) img_dist_r];
		if (ABS(RS_SEN45.now - RS_SEN45.old) < diff
				&& RS_SEN45.now > (tmpRightRef - diffthread)
				&& validateImgIndex((int) img_dist_r)) {
			flag45 = true;
			error += RS_SEN45.now - tmpRightRef;
			check++;
		} else if (ABS(RS_SEN2.now - RS_SEN2.old) < diff90
				&& RS_SEN2.now > (tmpRightRef90 - diffthread90)
				&& RS_SEN2.now > 590 && validateImg90Index((int) img_dist_r)) {
			error += RS_SEN2.now - tmpRightRef90;
			check++;
		}
	}
	if (diaStrwallCount_l > 0) {
		float tmpLeftRef = sen_l_dia_img[(int) img_dist_l];
		float tmpLeftRef90 = sen_l90_dia[(int) img_dist_l];
		if (ABS(LS_SEN45.now - LS_SEN45.old) < diff
				&& LS_SEN45.now > (tmpLeftRef - diffthread)
				&& validateImgIndex((int) img_dist_l)) {
			error -= LS_SEN45.now - tmpLeftRef;
			check++;
		} else if (ABS(LS_SEN2.now - LS_SEN2.old) < diff90
				&& LS_SEN2.now > (tmpLeftRef90 - diffthread90)
				&& LS_SEN2.now > 590 && !flag45
				&& validateImg90Index((int) img_dist_l)) {
			error -= LS_SEN2.now - tmpLeftRef90;
			check++;
		}
	}
	if (check == 0) {
		Se2.error_old = Se2.before = Se2.error_delta = 0;
	} else if (check == 2) {
//		Gy.error_old = 0;
//		Angle.error_old = 0;
//		angle = ang = 0;
	}
	isControl = false;
	if (check != 0) {
		errorFlg = 1;
	} else {
		errorFlg = 0;
	}

//	if (check != 0 && check2 != 0) {
//		float tmp = 0;
//		if (check == 1) {
//			tmp += (2 * error);
//		} else {
//			tmp += (error);
//		}
//		if (check2 == 1) {
//			tmp += (2 * error2);
//		} else {
//			tmp += (error2);
//
//		}
//		return tmp / 2;
//	} else {
//
//		errorOld_dia = error;
//
//		if (check == 2) {
//			return error;
//		}
//
//		if (check2 == 2) {
//			return error2;
//		}

	if (check == 2) {
		return error;
	}

	return 2 * error;
//	}
}
float RF_WALL_FrontCTRL = 520; //斜め時 姿勢制御閾値(壁ナシ）
float LF_WALL_FrontCTRL = 450; //斜め時 姿勢制御閾値(壁ナシ）

float R_WALL_dia = 400;	//斜め時 横壁のアリ判定
float L_WALL_dia = 400;	//斜め時 横壁のアリ判定

float RF_WALL1 = 210; //斜め時 姿勢制御閾値(壁ナシ）
float LF_WALL1 = 220; //斜め時 姿勢制御閾値(壁ナシ）
#define KIREME_R_DIA 40
#define KIREME_L_DIA 40
float RF_WALL = 175; //斜め時 姿勢制御閾値(壁アリ）
float LF_WALL = 210;  //斜め時 姿勢制御閾値(壁アリ）

float D1 = 0.0001;
float k1 = 76.25;
float k2 = 10370;
float P = 100;
void errorVelocity(void) {
	C.s2 = 0;
	C.s = 0;
	const float CsLimit = *(float *) 1049456;
	const float CsLimitDia = *(float *) 1049460;
	const float CanlgesLimit = *(float *) 1049464;
	const float CgLimit = *(float *) 1049468;

	if (positionControlValueFlg == 1) {
		if (dia == 0) {
			Se.error_now = check_sen_error();
			if (Se.before != 0) {
				Se.error_delta = Se.error_now - Se.before;
			} else {
				Se.error_delta = 0;
			}
			C.s = Sen.Kp * Se.error_now + Sen.Ki * Se.error_old
					+ Sen.Kd * Se.error_delta;

			if (C.s > CsLimit) {
				C.s = CsLimit;
			} else if (C.s < -CsLimit) {
				C.s = -CsLimit;
			}

			Se.before = Se.error_now;
			Se.error_old += Se.error_now;
		} else if (dia == 1) {
//			Se2.error_now = check_sen_error_dia_side();

			Se2.error_now = check_sen_error_dia_side_v2();

			if (Se2.before != 0) {
				Se2.error_delta = Se2.error_now - Se2.before;
			} else {
				Se2.error_delta = 0;
			}
			C.s = Sen_Dia_Side.Kp * Se2.error_now
					+ Sen_Dia_Side.Ki * Se2.error_old
					+ Sen_Dia_Side.Kd * Se2.error_delta;
			if (C.s > CsLimitDia) {
				C.s = CsLimitDia;
			} else if (C.s < -CsLimitDia) {
				C.s = -CsLimitDia;
			}
			Se2.before = Se2.error_now;
			Se2.error_old += Se2.error_now;
		}
	} else {
		Se.error_delta = Se.error_old = Se.before = 0;
		Se2.error_delta = Se2.error_old = Se2.before = 0;
		C.s = 0;
	}
	Gy.error_now = (W_now - settleGyro);
	if (C.g > CgLimit || C.g < -CgLimit) {
	} else {
		Gy.error_old += Gy.error_now;
	}
	if (Gy.before != 0) {
		Gy.error_delta = Gy.error_now - Gy.before;
	} else {
		Gy.error_delta = 0;
	}
	Gy.before = Gy.error_now;

	C.g = Gyro.Kp * Gy.error_now + Gyro.Ki * Gy.error_old
			+ Gyro.Kd * Gy.error_delta;
	if (C.g > CgLimit) {
		C.g = CgLimit;
	}
	if (C.g < -CgLimit) {
		C.g = -CgLimit;
	}

}

float checkDuty(float duty) {
	duty = ABS(duty);
	if (duty > DUTY_MAX) {
		duty = DUTY_MAX;
	}
	return duty;
}
void changeRotation(float duty, char RorL) {
	if (RorL == L) {
		if (duty > 0.0) {
			CW_R();
		} else {
			CCW_R();
		}
	} else if (RorL == R) {
		if (duty > 0.0) {
			CCW_L();
		} else {
			CW_L();
		}
	}
}
float getRpm(char RorL) {
	return RorL == R ? rpmR : rpmL;
}

float feadforward(char RorL) {
	return Mass * acc * WHEEL * Resist / (GEAR * Km * 1000);
}
float feadforward_para(char RorL) {
	if (RorL == R) {
		return Lm * (-alpha) * WHEEL * Resist / (GEAR * Km) / Tread;
	}
	return Lm * (alpha) * WHEEL * Resist / (GEAR * Km) / Tread;
}

float wheel_lm(char RorL) {
	if (RorL == R) {
		return (rpmR - rpmR_old) / dt / 2 * Mass * WHEEL * WHEEL * Resist / Km;
	}
	return (rpmL - rpmL_old) / dt / 2 * Mass * WHEEL * WHEEL * Resist / Km;
}

float FF_calc(char RorL, float w, float al) {
	float rpm = getRpm(RorL);
	float resist_str = 0;  //friction_str ? Resist * friction / Km : 0;
	float resist_roll = friction_roll ? ABS(Resist * friction2 / Km) : 0;
	float whrlm = 0;
	float counterV = ABS((Ke + friction) * rpm);
	float ff = feadforward(RorL);
	float ffp = feadforward_para(RorL);

//	return 0;

	if (V_now == 0) {
		resist_str = 0;
	}
	if (W_now == 0) {
		resist_roll = 0;
	}
	if (RorL == R) {
		if (rotate_r) {
			return ((ff + ffp) / 2 + counterV + resist_roll) + whrlm;
		} else {
			return ((ff + ffp) / 2 - counterV - resist_roll) - whrlm;
		}
	} else {
		if (rotate_l) {
			return ((ff + ffp) / 2 + counterV + resist_roll) + whrlm;
		} else {
			return ((ff + ffp) / 2 - counterV - resist_roll) - whrlm;
		}
	}
	return ((ff + ffp) / 2 + Ke * rpm + resist_str) + whrlm;
}
float FB_calc(char RorL) {
	float duty;
	if (RorL == R) {
		duty = Vel_r.Kp * (Vr.error_now)
				+ Vel_r.Ki * (Vr.error_now + Vr.error_old)
				+ Vel_r.Kd * (Vr.error_now - Vr.error_delta);
		return duty;
	}
	duty = Vel_l.Kp * (Vl.error_now) + Vel_l.Ki * (Vl.error_now + Vl.error_old)
			+ Vel_l.Kd * (Vl.error_now - Vl.error_delta);
	return duty;
}

float FB_calc_omega() {
	return Omega.Kp * (W_enc.error_now)
			+ Omega.Ki * (W_enc.error_now + W_enc.error_old)
			+ Omega.Kd * (W_enc.error_now - W_enc.error_delta);
}

float FB_velocity() {
	return (Vel.Kp * Velocity.error_now + Vel.Ki * Velocity.error_old
			+ Vel.Kd * Velocity.error_delta);
}

float FB_distance() {
	float dist_before = (img_distance - distance);

	img_distance += V_now * dt;
	distance += (V_Enc.r + V_Enc.l) * dt / 2;

	Distance.error_now = (img_distance - distance);
	Distance.error_old += Distance.error_now;
	Distance.error_delta = Distance.error_now - dist_before;
	return (Dists.Kp * Distance.error_now + Dists.Ki * Distance.error_old
			+ Dists.Kd * Distance.error_delta);
}

float FB_calc_straight() {
	return FB_velocity() + FB_distance();
}

float FB_calc_pararell() {
	return C.angles + C.g + C.s + C.s2;
}

void dutyCalcuration2(void) {
	float dutyR = 0, dutyL = 0;
	float FB_straight_duty = FB_calc_straight();
	float FB_pararell_duty = FB_calc_pararell();
	float w, al;

	ffR = FF_calc(R, w, al);
	ffL = FF_calc(L, w, al);

	dutyR = (ffL + FB_straight_duty + FB_pararell_duty) / battery * 100;
	dutyL = (ffR + FB_straight_duty - FB_pararell_duty) / battery * 100;

	SeFrnt.error_old = 0;
	SeFrntL.error_old = 0;

	Duty_r = dutyR;
	Duty_l = dutyL;
	changeRotation(dutyR, R);	//R_CW/CCW
	changeRotation(dutyL, L);	//L_CW/CCW

	failCheck(dutyR, dutyL);
	dutyR = checkDuty(dutyR);
	dutyL = checkDuty(dutyL);

	gra_r = (long) (dutyR * M_CYCLE / 100.0);
	gra_l = (long) (dutyL * M_CYCLE / 100.0);

	if (enablePWM) {
		GPT0.GTCCRA = GPT0.GTCCRC = gra_l;
		GPT1.GTCCRA = GPT1.GTCCRC = gra_r;
	} else {
		GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
	}
}

//物理量ベース計算
void Physical_Basement(void) {
	enc_r = MTU1.TCNT - 30000;
	enc_l = MTU2.TCNT - 30000;
	if (os_escape) {
		MTU2.TCNT = MTU1.TCNT = 30000;
	}
	if (alphaMode == 1) {
		if (dt * sinCount / slaTerm < 2.0) {
			alpha = alphaTemp * Et2(dt * sinCount, slaTerm, etN);
		} else {
			alpha = 0;
		}
	}
	if (dia == 1 && originalDiaMode == true && checkStablly() == true) {
		if (targetVelocity > V_now) {
			if (tmpDiac < 0) {
				acc = 0;
			}
		}
	}
	errorVelocity();

	V_old = V_now;
	W_old = W_now;
	V_now += acc * dt;
	W_now += alpha * dt;

	ang += settleGyro * dt;
	angle += W_now * dt;

	enc_to_vel();

	if (enableSystemIdentification) {

		gra_r = (short) (ABS(*(float *) 1049472) / battery * M_CYCLE);
		gra_l = (short) (ABS(*(float *) 1049476) / battery * M_CYCLE);

		float dutyR = gra_r * 100 / M_CYCLE;
		float dutyL = gra_l * 100 / M_CYCLE;

		changeRotation(*(float *) 1049472, R);	//R_CW/CCW
		changeRotation(*(float *) 1049476, L);	//L_CW/CCW

		if (enablePWM) {
			GPT0.GTCCRA = GPT0.GTCCRC = gra_l;
			GPT1.GTCCRA = GPT1.GTCCRC = gra_r;
		} else {
			GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
		}
	} else {
		dutyCalcuration2();
	}
}
#endif /* PHYSICALBASEMENT_H_ */
