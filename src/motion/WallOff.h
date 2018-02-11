/*
 * WallOff.h
 *
 *  Created on: 2016/08/27
 *      Author: Naoto
 */

#ifndef WALLOFF_H_
#define WALLOFF_H_

#define SEN_R RS_SEN1.now
#define SEN_L LS_SEN1.now
#define SEN_R2 RS_SEN2.now
#define SEN_L2 LS_SEN2.now

char wallOff(char RorL);
char wallOff_D(char RorL);
volatile int wall_off_limit = 40;
volatile int wall_off_limit_d = 40;

float R_WALL_OFF = 220;	//壁切れ　閾値
float L_WALL_OFF = 580;	//壁切れ　閾値

void walloff1(char RorL) {
	if (RorL == R) {
		while (SEN_R < R_WALL_OFF && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_R > R_WALL_OFF) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L < L_WALL_OFF && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_L > L_WALL_OFF) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

float R_WALL_OFF2 = 270;	//壁切れ　閾値
float L_WALL_OFF2 = 650;	//壁切れ　閾値
void walloff2(char RorL) {
	if (RorL == R) {
		while (SEN_R > R_WALL_OFF2) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L > L_WALL_OFF2) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

float existRightWall4 = 330;  //壁切れの予備
float existLeftWall4 = 310;   //壁切れの予備

char wallOff(char RorL) {
	if (dia == 1) {
		return wallOff_D(RorL);
	}
	sensingMode = AtackStraight;
	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;
	distance = 0;
	if (RorL == R) {
		if (SEN_R < existRightWall4) {
			cmtMusic(C4_, 250);
			walloff1(R);
		} else {
			walloff2(R);
		}
	} else {
		if (SEN_L < existLeftWall4) {
			walloff1(L);
		} else {
			cmtMusic(C4_, 250);
			walloff2(L);
		}
	}
	positionControlValueFlg = 0;
	return 1;
}

float R_WALL_OFF_D = 570;  //壁切れ　閾値　斜め用
float L_WALL_OFF_D = 1000; //壁切れ　閾値　斜め用

//float R_WALL_OFF_D = 270;  //壁切れ　閾値　斜め用
//float L_WALL_OFF_D = 430; //壁切れ　閾値　斜め用

void walloff3(char RorL) {
	if (RorL == R) {
		while (SEN_R < R_WALL_OFF_D && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_R > R_WALL_OFF_D) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L < L_WALL_OFF_D && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_L > L_WALL_OFF_D) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

float R_WALL_OFF_D2 = 485;  //壁切れ　閾値　斜め用
float L_WALL_OFF_D2 = 740; //壁切れ　閾値　斜め用

void walloff4(char RorL) {
	if (RorL == R) {
		while (SEN_R > R_WALL_OFF_D2) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L > L_WALL_OFF_D2) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

float existRightWall5 = 10000;  //壁切れの予備
float existLeftWall5 = 10000;   //壁切れの予備
char wallOff_D(char RorL) {
//	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;
	distance = 0;
	sensingMode = AtackDia;
	if (RorL == R) {
		if (SEN_R < existRightWall5) {
			walloff3(R);
		} else {
			walloff4(R);
		}
	} else {
		if (SEN_L < existLeftWall5) {
			walloff3(L);
		} else {
			walloff4(L);
		}
	}
	positionControlValueFlg = 0;
	return 1;
}
#endif /* WALLOFF_H_ */
