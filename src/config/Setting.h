/*
 * Setting.h
 *
 *  Created on: 2017/03/11
 *      Author: Naoto
 */

#ifndef SETTING_H_
#define SETTING_H_

// APEC用のパラメータ

void changeMode(int isApec) {
//	if (!isApec) {
		return;
//	}
	wallhosei = 100;
	R_WALL = 210;   //#define R_WALL 4000	//サーキット用
	L_WALL = 210;

	R_WALL_EXIST = 180; 		//探索時壁判定
	L_WALL_EXIST = 180;		 //探索時壁判定
	FRONT_WALL_EXIST = 150;		 //探索時壁判定
//	LF_WALL_EXIST = 150; 		//探索時壁判定

	FRONT_CTRL_1 = 292;		 //前壁補正
//	FRONT_CTRL_L = 244; 		//前壁補正
	RF_WALL_EXIST2 = 110; 	//前壁補正　開始
//	LF_WALL_EXIST2 = 110; 	//前壁補正　開始

	RF_WALL = 250;				//斜め時 姿勢制御閾値(壁アリ）
	LF_WALL = 20;				//斜め時 姿勢制御閾値(壁アリ）
	RF_WALL1 = 70;				//斜め時 姿勢制御閾値(壁ナシ）
	LF_WALL1 = 50;			//斜め時 姿勢制御閾値(壁ナシ）

	R_WALL_OFF = 300;			//壁切れ　閾値 310
	L_WALL_OFF = 280;			//壁切れ　閾値 380

	R_WALL_dia = 270;				//斜め時 横壁のアリ判定
	L_WALL_dia = 270;				//斜め時 横壁のアリ判定
	R_WALL_OFF_D = 880;		//壁切れ　閾値　斜め用
	L_WALL_OFF_D = 880;		//壁切れ　閾値　斜め用

	FRONT_OUT = 1000;		//袋小路時前センサー閾値
//	FRONT_OUT_L = 700;		//袋小路時前センサー閾値
	existRightWall = 100;		//壁切れの予備
	existLeftWall = 100;			//壁切れの予備
	existRightWall3 = 150;		//壁切れの予備
	existLeftWall3 = 150;			//壁切れの予備

	// 直線中央値
	RS_SEN45.ref = 345;
	LS_SEN45.ref = 404;
	// 斜め中央値　壁ナシ
	Front_SEN.ref = 55;
//	LF_SEN1.ref = 100;
	// 斜め中央値　壁あり
	Front_SEN.ref2 = 55;
//	LF_SEN1.ref2 = 180;

//	existRightWall2 = 400;	//壁切れの予備 斜め 不要
//	existLeftWall2 = 400;		//壁切れの予備 斜め 不要
}

#endif /* SETTING_H_ */
