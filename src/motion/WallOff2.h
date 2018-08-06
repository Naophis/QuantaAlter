/*
 * WallOff.h
 *
 *  Created on: 2016/08/27
 *      Author: Naoto
 */

#ifndef WALLOFF2_H_
#define WALLOFF2_H_

char wallOff_v2(char RorL);
char wallOff_D_v2(char RorL);
volatile int wall_off_limit_v2 = 40;
volatile int wall_off_limit_d_v2 = 40;

float R_WALL_OFF_v2 = 380;	//壁切れ　閾値
float L_WALL_OFF_v2 = 580;	//壁切れ　閾値

void walloff1_v2(char RorL) {
	if (RorL == R) {
		while (SEN_R < R_WALL_OFF && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_R > R_WALL_OFF && distance <= wall_off_limit) {
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
		while (SEN_L > L_WALL_OFF && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

float R_WALL_OFF2_v2 = 500;	//壁切れ　閾値
float L_WALL_OFF2_v2 = 640;	//壁切れ　閾値
void walloff2_v2(char RorL) {
	if (RorL == R) {
		while (SEN_R > R_WALL_OFF2 && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L > L_WALL_OFF2 && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

float existRightWall4_v2 = 330;  //壁切れの予備
float existLeftWall4_v2 = 500;   //壁切れの予備

char wallOff_v2(char RorL) {
	if (dia == 1) {
		return wallOff_D(RorL, false);
	}
	sensingMode = AtackStraight;
	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;
	distance = 0;
	img_distance = 0;
	if (RorL == R) {
		if (SEN_R < existRightWall4) {
			walloff1(R);
		} else {
			cmtMusic(C4_, 250);
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

float R_WALL_OFF_D_v2 = 630;  //壁切れ　閾値　斜め用
float L_WALL_OFF_D_v2 = 933; //壁切れ　閾値　斜め用

void walloff3_v2(char RorL) {
	if (RorL == R) {
		while (SEN_R < R_WALL_OFF_D && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_R > R_WALL_OFF_D && distance <= wall_off_limit_d) {
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
		while (SEN_L > L_WALL_OFF_D && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

float R_WALL_OFF_D2_v2 = 485;  //壁切れ　閾値　斜め用
float L_WALL_OFF_D2_v2 = 740; //壁切れ　閾値　斜め用

void walloff4_v2(char RorL) {
	if (RorL == R) {
		while (SEN_R > R_WALL_OFF_D2 && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L > L_WALL_OFF_D2 && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

float existRightWall5_v2 = 10000;  //壁切れの予備
float existLeftWall5_v2 = 10000;   //壁切れの予備
char wallOff_D_v2(char RorL) {
//	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;
	distance = 0;
	img_distance = 0;
	sensingMode = AtackDia;
	if (RorL == R) {
		if (SEN_R < existRightWall5) {
			walloff3_v2(R);
		} else {
			walloff4_v2(R);
		}
	} else {
		if (SEN_L < existLeftWall5) {
			walloff3_v2(L);
		} else {
			walloff4_v2(L);
		}
	}
	positionControlValueFlg = 0;
	return 1;
}
#endif /* WALLOFF_H_ */
