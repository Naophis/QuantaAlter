/*
 * Run.h
 *
 *  Created on: 2013/11/20
 *      Author: Naoto
 */

#ifndef RUN_H_
#define RUN_H_

char checkSensorOff(char RorL, char bool) {
	if (RorL == R) {
		if (bool) {
			return sen_r[0] & sen_r[1] & sen_r[2] & sen_r[3] & sen_r[4];
		} else {
			return sen_r[0] | sen_r[1] | sen_r[2] | sen_r[3] | sen_r[4];
		}
	} else {
		if (bool) {
			return sen_l[0] & sen_l[1] & sen_l[2] & sen_l[3] & sen_l[4];
		} else {
			return sen_l[0] | sen_l[1] | sen_l[2] | sen_l[3] | sen_l[4];
		}

	}
}
char checkSensor2Off(char RorL, char bool) {
	if (RorL == R) {
		if (bool) {
			return sen_r2[0] & sen_r2[1] & sen_r2[2] & sen_r2[3] & sen_r2[4];
		} else {
			return sen_r2[0] | sen_r2[1] | sen_r2[2] | sen_r2[3] | sen_r2[4];
		}
	} else {
		if (bool) {
			return sen_l2[0] & sen_l2[1] & sen_l2[2] & sen_l2[3] & sen_l2[4];
		} else {
			return sen_l2[0] | sen_l2[1] | sen_l2[2] | sen_l2[3] | sen_l2[4];
		}
	}
}
float existRightWall = 450;  //壁切れの予備
float existLeftWall = 750;   //壁切れの予備

float existRightWall3 = 150; //壁切れの予備
float existLeftWall3 = 150;  //壁切れの予備

char checkUp(char RorL) {
	if (RorL == R) {
		return (RS_SEN45.now > existRightWall) && (sen_log_r[0] > sen_log_r[1])
				&& (sen_log_r[1] > sen_log_r[2]);
	} else {
		return (LS_SEN45.now > existLeftWall) && (sen_log_l[0] > sen_log_l[1])
				&& (sen_log_l[1] > sen_log_l[2]);
	}
}
char checkDown(char RorL) {
	if (RorL == R) {
		return (RS_SEN45.now > existRightWall) && (sen_log_r[0] < sen_log_r[1])
				&& (sen_log_r[1] < sen_log_r[2]);
	} else {
		return (LS_SEN45.now > existLeftWall) && (sen_log_l[0] < sen_log_l[1])
				&& (sen_log_l[1] < sen_log_l[2]);
	}
}
char checkDown3(char RorL) {
	if (RorL == R) {
		return (RS_SEN45.now > existRightWall) && (sen_log_r[0] < sen_log_r[1])
				&& (sen_log_r[1] < sen_log_r[2]);
	} else {
		return (LS_SEN45.now > existLeftWall) && (sen_log_l[0] < sen_log_l[1])
				&& (sen_log_l[1] < sen_log_l[2]);
	}
}

float existRightWall2 = 400; //壁切れの予備 斜め
float existLeftWall2 = 400;  //壁切れの予備 斜め

char checkUp2(char RorL) {
	if (RorL == R) {
		return (RS_SEN45.now > existRightWall2) && (sen_log_r[0] > sen_log_r[1])
				&& (sen_log_r[1] > sen_log_r[2]);
	} else {
		return (LS_SEN45.now > existLeftWall2) && (sen_log_l[0] > sen_log_l[1])
				&& (sen_log_l[1] > sen_log_l[2]);
	}
}
char checkDown2(char RorL) {
//	return false;
	if (RorL == R) {
		return (RS_SEN45.now > existRightWall2) && (sen_log_r[0] < sen_log_r[1])
				&& (sen_log_r[1] < sen_log_r[2])
				&& (sen_log_r[2] < sen_log_r[3])
				&& (sen_log_r[3] < sen_log_r[4]);
	} else {
		return (LS_SEN45.now > existLeftWall2) && (sen_log_l[0] < sen_log_l[1])
				&& (sen_log_l[1] < sen_log_l[2])
				&& (sen_log_l[2] < sen_log_l[3])
				&& (sen_log_l[3] < sen_log_l[4]);
	}
}
char running(float vmax, float ACC, float dist, char control) {
	//	char errorCheck = 1;
	rotate_r = rotate_l = true;
	friction_str = true;
	friction_roll = false;
	readGyroParam();
	if (!gyroOn) {
		resetGyroParam();
	} else {
		readGyroParam();
	}

	errorOld_dia = errorOld_dia_side = 0;
	readGyroParam();
	readAngleParam();
	readOmegaParam();
	if (testMode) {
		distance = 0;
		img_distance = 0;
	} else {
		distance = distance - img_distance;
		img_distance = 0;
	}
	alpha = 0;
	W_now = 0;
	W_now2 = 0;
	acc = ACC;
	sinCount = 0;
	positionControlValueFlg = control;
	V_max = vmax;
	runFlg = 1;
	while (ABS(distance) < ABS(dist)) {
		if (dia == 1) {
			if (distance >= dist * 0.85) {
				//	positionControlValueFlg = false;
			}
		}
		if (ACC > 0) {
			if (V_now < V_max) {
			} else if (V_now >= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		} else if (ACC < 0) {
			if (V_now > V_max) {
			} else if (V_now <= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		}
		if (!fail) {
			positionControlValueFlg = 0;
			runFlg = 0;
			return 0;
		}
	}
	alpha = 0;
	acc = 0;
	positionControlValueFlg = 0;
	V_now = V_max;
	W_now = 0;
	runFlg = 0;
	return 1;
}
char gyroRollTest(char RorL, float targetAng, float w_max, float al) {
	if (RorL == L) {
		al = -al;
	}
	globalState = PIVOT;
	rotate_r = (RorL != R);
	rotate_l = (RorL == R);
	friction_str = false;
	friction_roll = true;

	if (ABS(w_max) > W_max) {
		w_max = RorL == L ? -W_max : W_max;
	} else {
		w_max = RorL == L ? -w_max : w_max;
	}
	G.th = RorL == L ? pivotR : pivotL;
	mtu_start();
	alpha = al;
	acc = 0;
	w_now = 0;
	V_now = 0;
	ang = 0;
	W_now = 0;
	W_now2 = 0;
	readGyroParam();
	readAngleParam();
	C.angles = 0;
	C.g = 0;
	targetAng = targetAng * PI / 180;
	cc = 1;
	time = 0;
	logs = 0;
	char phase = 0;
	float targetWo = RorL == L ? -Wo : Wo;
	while (ABS(ang) < ABS(targetAng)) {
		float sita = ABS((W_now + targetWo) * (W_now - targetWo) / (2.0 * al));
		if (phase == 3) {
//			angle = RorL == L ? -Angle : Angle;
		} else if (phase == 2) {
			if (ABS(W_now) < Wo) {
				alpha = 0;
				W_now = RorL == L ? -Wo : Wo;
//				angle = RorL == L ? -Angle : Angle;
				phase = 3;
			}
		} else if (ABS(targetAng) <= ABS(angle) + ABS(sita)) {
			alpha = -al;
			phase = 2;
		} else if (ABS(W_now) >= ABS(w_max) && phase == 0) {
			W_now = w_max;
			alpha = 0;
			phase = 1;
		}
		if (!fail) {
			break;
		}
	}
	Gy.error_now = 0;
	Gy.error_old = 0;
	Gy.error_delta = 0;
	Angle.error_now = 0;
	Angle.error_old = 0;
	Angle.error_delta = 0;
	resetAngleParam();
	W_now = 0;
	alpha = 0;
	//	cmt_wait(200);
	ang = 0;
	angle = 0;
	C.g = 0;
	C.angles = 0;
	cc = 0;
	positionControlValueFlg = 0;
	mtu_stop();
//	cc = 0;
	return 1;
}
char gyroRoll(char RorL, float Angle, float w_max, float al) {
	if (RorL == L) {
		al = -al;
	}

	globalState = PIVOT;
	rotate_r = (RorL != R);
	rotate_l = (RorL == R);
	friction_str = false;
	friction_roll = true;

	if (ABS(w_max) > W_max) {
		w_max = RorL == R ? -W_max : W_max;
	} else {
		w_max = RorL == R ? -w_max : w_max;
	}
	G.th = RorL == R ? pivotR : pivotL;
	mtu_start();
	alpha = al;
	acc = 0;
	w_now = 0;
	V_now = 0;
	ang = 0;
	W_now = 0;
	W_now2 = 0;
	readGyroParam();
	readAngleParam();
	Angle = Angle * PI / 180;
	cc = 1;
	time = 0;
	logs = 0;
	char phase = 0;
	float targetWo = RorL == R ? -Wo : Wo;
	while (ABS(angle) < ABS(Angle)) {
		float sita = ABS((W_now + targetWo) * (W_now - targetWo) / (2.0 * al));
		if (phase == 3) {
			angle = RorL == R ? -Angle : Angle;
		} else if (phase == 2) {
			if (ABS(W_now) < Wo) {
				alpha = 0;
				W_now = RorL == R ? -Wo : Wo;
				angle = RorL == R ? -Angle : Angle;
				phase = 3;
			}
		} else if (ABS(Angle) <= ABS(angle) + ABS(sita)) {
			alpha = -al;
			phase = 2;
		} else if (ABS(W_now) >= ABS(w_max) && phase == 0) {
			W_now = w_max;
			alpha = 0;
			phase = 1;
		}
		if (!fail) {
			break;
		}
	}
	W_now = 0;
	alpha = 0;
	ang = 0;
	angle = 0;
	C.g = 0;
	C.angles = 0;
	cc = 0;
	positionControlValueFlg = 0;
	mtu_stop();
//	cmt_wait(200);
	return 1;
}
char roll_timer(char RorL, float Angle, float w_max, float al) {
	if (RorL == R) {
		al = -al;
	}
	if (RorL == R) {
		G.th = gyroTh_R;
	} else {
		G.th = gyroTh_L;
	}
	globalState = PIVOT;
	rotate_r = (RorL != R);
	rotate_l = (RorL == R);
	friction_str = false;
	friction_roll = true;
	cmt_wait(250);
	mtu_start();
	alpha = al;
	acc = 0;
	w_now = 0;
	V_now = 0;
	ang = 0;
	W_now = 0;
	W_now2 = 0;
//	resetGyroParam();
	readGyroParam();
	Angle = Angle * PI / 180;
	angle_enc = 0;
	angle = 0;
	ang = 0;
	cc = 1;
	while (ABS(angle) < ABS(Angle)) {
		if (ABS(angle) > ABS(Angle * 9 / 10)) {
			alpha = -al;
			if (ABS(W_now) < Wo) {
				alpha = 0;
				al = 0;
				if (RorL == R) {
					W_now = -Wo;
				} else {
					W_now = Wo;
				}
			}
		} else if (ABS(angle) > ABS(Angle * 1 / 3)) {
			alpha = 0;
		} else {
			if (ABS(W_now) > w_max) {
				alpha = 0;
			}
		}
		if (RorL == L) {
			if (W_now < 0) {
				W_now = Wo;
//				break;
			}
		} else {
			if (W_now > 0) {
				W_now = -Wo;
//				break;
			}
		}
		if (!fail) {
			break;
		}
	}
	cc = 0;
	positionControlValueFlg = 0;
	mtu_stop();
	return 1;
}
char roll(char RorL, float Angle, float w_max, float al) {
	if (RorL == R) {
		al = -al;
	}
	globalState = PIVOT;
	rotate_r = (RorL != R);
	rotate_l = (RorL == R);
	friction_str = false;
	friction_roll = true;
	if (RorL == R) {
		G.th = gyroTh_R;
	} else {
		G.th = gyroTh_L;
	}
	cmt_wait(50);
	mtu_start();
	alpha = al;
	acc = 0;
	w_now = 0;
	V_now = 0;
	ang = 0;
	W_now = 0;
	W_now2 = 0;
//	resetGyroParam();
	readGyroParam();
	readAngleParam();
	Angle = Angle * PI / 180;
	angle_enc = 0;
	cc = 1;
	while (ABS(angle_enc) < ABS(Angle)) {
		if (ABS(angle_enc) > ABS(Angle * 9 / 10)) {
			alpha = -al;
			if (ABS(W_now) < Wo) {
				alpha = 0;
				al = 0;
				if (RorL == R) {
					W_now = -Wo;
				} else {
					W_now = Wo;
				}
			}
		} else if (ABS(angle_enc) > ABS(Angle * 1 / 3)) {
			alpha = 0;
		} else {
			if (ABS(W_now) > w_max) {
				alpha = 0;
			}
		}
		if (RorL == L) {
			if (W_now < 0) {
				W_now = Wo;
//				break;
			}
		} else {
			if (W_now > 0) {
				W_now = -Wo;
//				break;
			}
		}
		if (!fail) {
			break;
		}
	}
	cc = 0;
	positionControlValueFlg = 0;
	mtu_stop();
	return 1;
}

float RF_WALL_EXIST2 = 750; //前壁補正　開始
char frontCtrl() {
	globalState = FRONT_ctrl;
	char tmp = sensingMode;
	if (Front_SEN.now > RF_WALL_EXIST2) {
		sensingMode = SearchMode;
		while (Front_SEN.now < FRONT_CTRL_1)
			;
		sensingMode = tmp;
		cmtMusic(D3_, 100);
		distance = img_distance = 0;
		Distance.error_now = 0;
		Distance.error_old = 0;
		Distance.error_delta = 0;
	}
	return 1;
}
float FRONT_CTRL = 1315;   //前壁補正
float F_WALL_EXIST5 = 750; //前壁補正　開始
char frontCtrl5() {
	char tmp = sensingMode;
	if (Front_SEN.now > F_WALL_EXIST5) {
		sensingMode = SearchMode;
		while (Front_SEN.now < FRONT_CTRL_1)
			;
		sensingMode = tmp;
		distance = img_distance = 0;
		Distance.error_now = 0;
		Distance.error_old = 0;
		Distance.error_delta = 0;
	}
	return 1;
}
float FRONT_CTRL_R4 = 1670;   //前壁補正
float FRONT_CTRL_L4 = 1530;	//前壁補正
char frontCtrl3() {
	char tmp = sensingMode;
	if (Front_SEN.now > RF_WALL_EXIST2) {
		sensingMode = SearchMode;
		while (Front_SEN.now < (FRONT_CTRL_1 + 400))
			;
		sensingMode = tmp;
		distance = img_distance = 0;
		Distance.error_now = 0;
		Distance.error_old = 0;
		Distance.error_delta = 0;
	}
	return 1;
}
#define FRONT_CTRL_R2 1000
#define FRONT_CTRL_L2 1000
char frontCtrl2() {
	char tmp = sensingMode;
	distance = 0;
	if (Front_SEN.now > 0 && distance < 100) {
		sensingMode = SearchMode;
		while (Front_SEN.now < FRONT_CTRL_1 + 300 && distance < 180)
			;
		sensingMode = tmp;
		distance = img_distance = 0;
		Distance.error_now = 0;
		Distance.error_old = 0;
		Distance.error_delta = 0;
	}
	return 1;
}
char targetRun(float vmax, float ACC, float dist, char control, char target) {
	char errorCheck = 1;
	readGyroParam();
	readGyroParam();

	distance = distance - img_distance;
	img_distance = 0;
	alpha = 0;
	W_now = 0;
	W_now2 = 0;
	acc = ACC;
	sinCount = 0;
	positionControlValueFlg = control;
//	positionControlValueFlg = 0;
	friction_str = true;
	friction_roll = false;
	V_max = vmax;
//	G.th = gyroTh_R;
	runFlg = 1;
//	angle = 0;
	while (ABS(distance) < ABS(dist)) {
		if (true) {
			if (errorCheck == 1 && errorFlg == 1) {
				if (dia == 0) {
//					if (ABS(globalError) > W_ENCORDER_LIMIT) {
//						W_enc.error_old = 0;
//						Gy.error_old = 0;
//					} else if (ABS(globalError) < W_ENCORDER_LIMIT2) {
//						errorCheck = 0;
//					}
				} else {
//					if (ABS(globalError) > W_ENCORDER_LIMIT_DIA) {
//						W_enc.error_old = 0;
//						Gy.error_old = 0;
//					} else if (ABS(globalError) < W_ENCORDER_LIMIT_DIA2) {
//						errorCheck = 0;
//					}
				}
			}
//			if (dia == 0 && ABS(globalError) > W_ENCORDER_LIMIT * 3) {
//				errorCheck = 1;
//			} else if (dia == 1
//					&& ABS(globalError) > W_ENCORDER_LIMIT_DIA * 3) {
//				errorCheck = 1;
//			}
		}
		if (ACC > 0) {
			if (V_now < V_max) {
			} else if (V_now >= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		} else if (ACC < 0) {
			if (V_now > V_max) {
			} else if (V_now <= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		}
		if (!fail) {
			positionControlValueFlg = 0;
			runFlg = 0;
			return 0;
		}
	}
	alpha = 0;
	acc = 0;
	positionControlValueFlg = 0;
	V_now = V_max;
	W_now = 0;
	runFlg = 0;
	return 1;
}
#define R_over1 400
#define L_over1 400
char runForWallOff(float vmax, float ACC, float dist, char control);
char runForWallOff2(float vmax, float ACC, float dist, char control, char type,
		char dir);
void back(float v1, float ac, float dist, char control);
char slalom(char dir, char type, float Velocity, float vel2, float ac) {
	float radius = getRadius(type);
	float rad = toRadians(getTargetAngle(type));
	float time = getNaiperTime(type);
	etN = getNaiperN(type);
	w_now = W_now = 0;
	cc = 1;

	if (dir == R) {
		G.th = gyroTh_R;
	} else {
		G.th = gyroTh_L;
	}
	if (type == Normal) {
		frontCtrl();
	}
	globalState = SLA_BEFORE;
	if (!globalSkipFront) {
		if (dia == 0) {
			if (type == Dia45) {
				if (!running(Velocity, 0, getFrontDistance(type, dir), 1)) {
					return 0;
				}
			} else {
				if (!running(Velocity, 0, getFrontDistance(type, dir), 1)) {
					return 0;
				}
			}
		} else {
			if (!running(Velocity, 0, getFrontDistance(type, dir), 0)) {
				return 0;
			}
		}
	}
	globalSkipFront = false;

	rotate_r = rotate_l = true;
	friction_str = true;
	friction_roll = true;
	sinCount = 0;
	readGyroParam();
	readAngleParam();
	sinCount = 1;
	alphaMode = 1;
	alphaTemp = ((dir == R) ? -1 : 1) * (Velocity / radius);

	slaTerm = time;
	globalState = SLA_TURN;

	px = py = 0;

	while (1) {
		if (!fail) {
			positionControlValueFlg = 0;
			runFlg = 0;
			return 0;
		}
		if (dt * sinCount / time < 2.0) {

		} else {
			alpha = 0;
			alphaMode = 0;
			alphaTemp = 0;
			slaTerm = 0;
			omegaTemp = 0;
			W_now = 0;
			if (dir == L) {
				angle = rad;
			} else {
				angle = -rad;
			}
			break;
		}
		if (type != Dia90) {
			if (!fail) {
				alphaMode = 0;
				alphaTemp = 0;
				slaTerm = 0;
				omegaTemp = 0;
				return 0;
			}
		}
	}

	px2 = px;
	py2 = py;

	fail = 1;
	if (dia == 0 && (type == Dia45 || type == Dia135)) {
		dia = 1;
	} else if (dia == 1 && (type == Dia45 || type == Dia135)) {
		dia = 0;
	}

	if (dir == L) {
		angle -= rad;
		ang -= rad;
	} else {
		angle += rad;
		ang += rad;
	}

	globalState = SLA_AFTER;
	float back = getBackDist(type, dir);
	char returnStatus = true;
	if (dia == 0) {
		if (type == Normal && getBackDist(type, dir) > 25) {
			returnStatus = runForWallOff(vel2, ac, back, true);
		} else if (type == Dia45 || type == Dia135) {
			returnStatus = runForWallOff2(vel2, ac, back, true, type, dir);
		} else {
			returnStatus = runForWallOff2(vel2, ac, back, true, type, dir);
		}
	} else {
		returnStatus = runForWallOff2(vel2, ac, back, false, type, dir);
	}
	resetAngleParam();
	cc = 0;
	alpha = 0;
	W_now = 0;
	return returnStatus;
}

void front(float vmax, float ACC, float dist, char control) {
	resetGyroParam();
	distance = 0;
	alpha = 0;
	W_now = 0;
	acc = ACC;
	positionControlValueFlg = control;
	V_max = vmax;
	friction_str = true;
	friction_roll = false;
	while (distance < dist) {
		if (!fail) {
			positionControlValueFlg = 0;
			break;
		}
		if (ACC > 0) {
			if (V_now < V_max) {
			} else if (V_now >= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		} else if (ACC < 0) {
			if (V_now > V_max) {
				if ((V_Enc.r + V_Enc.l) / 2 < V_now) {
				} else {
					acc = ACC;
				}
			} else if (V_now <= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		}
	}
	alpha = 0;
	acc = 0;
}
#define ACCELE 1
#define DIACCELE 2
#define FIX 3

#define R_over_side 900
#define L_over_side 800

#define R_over_front 2200
#define L_over_front 2000

char checkStablly() {
	char flg = false;
	if (dia == 1) {
		flg = lastPeekR > R_over_front || lastPeekL > L_over_front;
	} else {
		flg = RS_SEN45.now > R_over_side || LS_SEN45.now > L_over_side;
		flg = false;
	}
	if (flg == true) {
		cmtMusic(C3_, 500);
	}
	return flg;
//	return 0;
}

char asc(float d, float d2) {
	if (d < d2) {
		return DIACCELE;
	} else if (checkStablly()) {
		return FIX;
	}
	return ACCELE;
}
char asc2(float d, float d2) {
	return checkStablly();
}

char pararelMove(float v2, float diff, float length, char mode);
char orignalRunDia(float v1, float v2, float ac, float diac, float dist) {
	float d2;
	char sequence = ACCELE;

	globalState = DIA_STRAIGHT;

	errorOld_dia = errorOld_dia_side = 0;
	targetVelocity = v2;
	positionControlValueFlg = 1;
	acc = ac;
	tmpDiac = -diac;
	readGyroParam();
	readAngleParam();

	peekRight = peekLeft = 0;

	if (testMode) {
		distance = 0;
		img_distance = 0;
	} else {
		distance = distance - img_distance;
		img_distance = 0;
	}

	alpha = 0;
	W_now = 0;
	sinCount = 0;

	rotate_r = rotate_l = true;
	friction_str = true;
	friction_roll = false;
	runFlg = 1;
	originalDiaMode = true;
	lastPeekR = lastPeekL = 0;
	cc = 1;

	Se2.error_old = Se2.before = Se2.error_delta = 0;

	while (ABS(distance) < ABS(dist)) {
		d2 = ABS((V_now + v2) * (V_now - v2) / (2.0 * diac));
		switch (sequence) {
		case FIX:
			acc = 0;
			sequence = checkStablly() ? FIX : ACCELE;
			if (sequence == FIX) {
				break;
			}
		case ACCELE:
			sequence = asc(dist - distance, d2);
			if (V_now >= v1) {
				acc = 0;
				V_now = v1;
			} else {
				acc = ac;
			}
			break;
		case DIACCELE:
			tmpDiac = 0;
			originalDiaMode = false;
			if (V_now <= v2) {
				acc = 0;
				V_now = v2;
			} else {
				acc = -diac;
			}
			break;
		}
		if (!fail) {
			positionControlValueFlg = 0;
			runFlg = 0;
			originalDiaMode = false;
			tmpDiac = 0;
			targetVelocity = 0;
			peekSideR = peekSideL = 0;
			cc = 0;
			return 0;
		}
	}
	cc = 0;
	peekSideR = peekSideL = 0;
	alpha = 0;
	acc = 0;
	positionControlValueFlg = 0;
	V_now = v2;
	W_now = 0;
	runFlg = 0;
	originalDiaMode = false;
	tmpDiac = 0;
	targetVelocity = 0;

	cmtMusic(10, 100);

	return true;
}

char orignalRun(float v1, float v2, float ac, float diac, float dist) {
	float d2;
	char sequence = ACCELE;
	errorOld_dia = errorOld_dia_side = 0;
	targetVelocity = v2;
	positionControlValueFlg = 1;
	acc = ac;
	tmpDiac = -diac;
	readGyroParam();
	readAngleParam();

	if (testMode) {
		distance = 0;
		img_distance = 0;
	} else {
		distance = distance - img_distance;
		img_distance = 0;
	}

	alpha = 0;
	W_now = 0;
	sinCount = 0;

	rotate_r = rotate_l = true;
	friction_str = true;
	friction_roll = false;
//	G.th = gyroTh_R;
	runFlg = 1;
	originalDiaMode = true;
	peekSideR = peekSideL = 0;
	cc = 1;

	gyroErrResetEnable = dist >= 180;

	while (ABS(distance) < ABS(dist)) {

		if (gyroErrResetEnable && (dist - distance) < 90) {
			gyroErrResetEnable = false;
		}

		if (startDecrease(R)) {
			peekSideR = RS_SEN45.now;
		}
		if (startDecrease(L)) {
			peekSideL = LS_SEN45.now;
		}
		d2 = ABS((V_now + v2) * (V_now - v2) / (2.0 * diac));
		switch (sequence) {
		case FIX:
			acc = 0;
			sequence = checkStablly() ? FIX : ACCELE;
			if (sequence == FIX) {
				break;
			}
		case ACCELE:
			sequence = asc(dist - distance, d2);
			if (V_now >= v1) {
				acc = 0;
				V_now = v1;
			} else {
				acc = ac;
			}
			if (sequence != DIACCELE) {
				break;
			}
		case DIACCELE:
			tmpDiac = 0;
			originalDiaMode = false;
			if (V_now <= v2) {
				acc = 0;
				V_now = v2;
			} else {
				acc = -diac;
			}
			break;
		}
		if (!fail) {
			positionControlValueFlg = 0;
			runFlg = 0;
			originalDiaMode = false;
			tmpDiac = 0;
			targetVelocity = 0;
			peekSideR = peekSideL = 0;
			cc = 0;
			return 0;
		}
	}
	cc = 0;
	peekSideR = peekSideL = 0;
	alpha = 0;
	acc = 0;
	positionControlValueFlg = 0;
	V_now = v2;
	W_now = 0;
	runFlg = 0;
	originalDiaMode = false;
	tmpDiac = 0;
	targetVelocity = 0;
	return true;
}

void back(float v1, float ac, float dist, char control) {
	float d2;
	float v2 = -50;
	float diac = ac;
	char sequence = ACCELE;
	mtu_start();
	readGyroParam();

	rotate_r = rotate_l = false;
	friction_str = true;
	friction_roll = false;
	distance = 0;
	img_distance = 0;
	alpha = 0;
	W_now = 0;
	acc = ac;
	positionControlValueFlg = control;
	V_max = v1;
	G.th = gyroTh_R;
	ang = 0;
	angle = 0;

	while (ABS(distance) < ABS(dist)) {
		d2 = ABS((V_now + v2) * (V_now - v2) / (2.0 * diac));
		switch (sequence) {
		case FIX:
			sequence = checkStablly() ? FIX : ACCELE;
			if (sequence == FIX) {
				break;
			}
		case ACCELE:
			sequence = asc(dist - distance, d2);
			if (ABS(V_now) >= ABS(v1)) {
				acc = 0;
				V_now = v1;
			} else {
				acc = ac;
			}
			if (sequence != DIACCELE) {
				break;
			}
		case DIACCELE:
			tmpDiac = 0;
			originalDiaMode = false;
			if (ABS(V_now) <= ABS(v2)) {
				acc = 0;
				V_now = v2;
			} else {
				acc = -diac;
			}
			break;
		}
		if (!fail) {
			positionControlValueFlg = 0;
			runFlg = 0;
			originalDiaMode = false;
			tmpDiac = 0;
			targetVelocity = 0;
			mtu_stop();
			return;
		}
	}
	alpha = 0;
	acc = 0;
	mtu_stop();
}
char goStraight(float vmax, float term, float dist, char bool, char control) {
	float delta_V = vmax - V_now;
//readGyroParam();
	resetGyroParam();
	if (!gyroOn) {
		resetGyroParam();
	} else {
//		readGyroParam();
		readGyroParamP();
	}
	rotate_r = rotate_l = true;

	distance = 0;
	alpha = 0;
	W_now = 0;
	W_now2 = 0;
//	ang = 0;
//	angle = 0;
	C.g = 0;
//	Gy.error_old = 0;
	Gy.error_delta = 0;
	sinCount = 0;
	positionControlValueFlg = control;
//	G.th = gyroTh_R;
	while (dist > distance) {
		if (delta_V > 0) {
			if (vmax > V_now) {
				acc = delta_V * Et2(dt * sinCount, term, 2);
			}
		} else {
			if (vmax < V_now) {
				acc = -delta_V * Et2(dt * sinCount, term, 2);
			}
		}
		if (!fail) {
			positionControlValueFlg = 0;
			return 0;
		}
	}
	alpha = 0;
	acc = 0;
	positionControlValueFlg = 0;
	return 1;
}

char runForWallOff(float vmax, float ACC, float dist, char control) {
	globalState = SLA_AFTER;
	readGyroParam();
	if (!gyroOn) {
		resetGyroParam();
	} else {
		readGyroParam();
	}

	rotate_r = rotate_l = true;
	friction_str = true;
	friction_roll = false;
	errorOld_dia = errorOld_dia_side = 0;
	readGyroParam();
	readAngleParam();

	if (testMode) {
		distance = 0;
		img_distance = 0;
	} else {
		distance = distance - img_distance;
		img_distance = 0;
	}
	alpha = 0;
	W_now = 0;
	W_now2 = 0;
	acc = ACC;
	sinCount = 0;
	positionControlValueFlg = control;
	V_max = vmax;
//	G.th = gyroTh_R;
	runFlg = 1;
	char bool2 = RS_SEN2.now > search_wall_off_r; // checkSensorOff(R, false);
	char bool3 = LS_SEN2.now > search_wall_off_l; // checkSensorOff(L, false);
	char bool = bool2 | bool3;

	resetAngleError();
	gyroErrResetEnable = dist >= 180;

	while (distance < dist) {

		if (gyroErrResetEnable && (dist - distance) < 100) {
			gyroErrResetEnable = false;
		}

		if (ACC > 0) {
			if (V_now < V_max) {
			} else if (V_now >= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		} else if (ACC < 0) {
			if (V_now > V_max) {
			} else if (V_now <= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		}
		if (bool) {
			if (bool2) {
				if (checkSensor2Off(R, false)) {
				} else {
					bool = false;
					cmtMusic(G2_, 100);
					distance = img_distance = 0;
					Distance.error_now = 0;
					Distance.error_old = 0;
					Distance.error_delta = 0;
					dist = *(float *) 1049916;
					continue;
				}
			}
			if (bool3) {
				if (checkSensor2Off(L, false)) {
				} else {
					bool = false;
					cmtMusic(G2_, 100);
					distance = img_distance = 0;
					Distance.error_now = 0;
					Distance.error_old = 0;
					Distance.error_delta = 0;
					dist = *(float *) 1049920;
					continue;
				}
			}
		}
		if (!fail) {
			positionControlValueFlg = 0;
			runFlg = 0;
			return 0;
		}
	}
	alpha = 0;
	acc = 0;
	positionControlValueFlg = 0;
	V_now = V_max;
	W_now = 0;
	runFlg = 0;
	return 1;
}

char runForWallOff2(float vmax, float ACC, float dist, char control, char type,
		char dir) {
	globalState = SLA_AFTER;
	readGyroParam();

	rotate_r = rotate_l = true;
	friction_str = true;
	friction_roll = false;
	errorOld_dia = errorOld_dia_side = 0;
	readGyroParam();
	if (testMode) {
		distance = 0;
		img_distance = 0;
	} else {
		distance = distance - img_distance;
		img_distance = 0;
	}
	alpha = 0;
	W_now = 0;
	W_now2 = 0;
	acc = ACC;
	sinCount = 0;
	positionControlValueFlg = control;
	V_max = vmax;
	runFlg = 1;

	Se.before = Se.error_old = Se.error_delta = 0;
	Se2.before = Se2.error_old = Se.error_delta = 0;

//	resetAngleError();

	while (distance < dist) {
		if (ACC > 0) {
			if (V_now < V_max) {
			} else if (V_now >= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		} else if (ACC < 0) {
			if (V_now > V_max) {
			} else if (V_now <= V_max) {
				ACC = 0;
				acc = 0;
				V_now = V_max;
			}
		}
		if (!fail) {
			positionControlValueFlg = 0;
			runFlg = 0;
			return 0;
		}
	}
	alpha = 0;
	acc = 0;
	positionControlValueFlg = 0;
	V_now = V_max;
	W_now = 0;
	runFlg = 0;
	return 1;
}

char pararelMove(float v2, float diff, float length, char mode) {
	float width = ABS(diff);
	float tmpDist = distance;
	float al = 2.0 * (mode ? 1 : -1) * (length / width);
	float ang1 = atanf(width / length) / 2;
	globalState = PARAREL;

	errorOld_dia = errorOld_dia_side = 0;
	targetVelocity = v2;
	positionControlValueFlg = 0;
	readGyroParam();
	peekRight = peekLeft = 0;
	alpha = al;
	W_now = 0;
	sinCount = 0;

	rotate_r = rotate_l = true;
	friction_str = true;
	friction_roll = true;
	runFlg = 1;
	originalDiaMode = true;
//	peekSideR = peekSideL = 0;
	cc = 1;

	char state = 0;
	ang = 0;
	angle = 0;

	while (true) {
		if (state < 2) {
			switch (state) {
			case 0:
				if (ABS(ang) >= ABS(ang1 / 2)) {
					state = 1;
					alpha *= (-1);
				}
				break;
			case 1:
				if (ABS(ang) >= ABS(ang1)) {
					state = 2;
					alpha = 0;
					ang = 0;
					angle = 0;
					W_now = 0;
				}
				break;
			}
		} else {
			break;
		}
	}
	return 0;
}

#endif /* RUN_H_ */
