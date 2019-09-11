/*
 * cirkit.h
 *
 *  Created on: 2016/09/11
 *      Author: Naoto
 */

#ifndef CIRKIT_H_
#define CIRKIT_H_

void cirquit() {
	cirquitMode = 1;
	pathClear();
	//////	//#define R_WALL 5025
	char maxcicle = 2;

	for (char i = 0; i < 4 * maxcicle; i += 2) {
		// 部室迷路サーキット #define R_WALLを4000にすること
		path_s[i] = 8;	//部屋のサーキット
		path_t[i] = 5;
		path_s[i + 1] = 4;
		path_t[i + 1] = 5;
		if(transam){
			path_s[i] -= 0.25;
			path_s[i + 1] -= 0.25;
		}
	}

	path_s[0] += 2;
	path_s[4 * maxcicle] = 2;
	path_t[4 * maxcicle] = 255;

}

void cirquitFull() {
	cirquitMode = 1;
	pathClear();

	char maxcicle = 2;
	for (char i = 0; i < 4 * maxcicle; i += 2) {
		// 部室迷路サーキット #define R_WALLを4000にすること
		path_s[i] = 28;
		path_t[i] = 5;
		path_s[i + 1] = 28;
		path_t[i + 1] = 5;
		if(transam){
			path_s[i] -= 0.25;
			path_s[i + 1] -= 0.25;
		}
	}

	path_s[0] += 2;
	path_s[4 * maxcicle] = 2;
	path_t[4 * maxcicle] = 255;

}

void cirquitDiaPractice() {
	cirquitMode = 1;
	pathClear();

	char maxcicle = (char) (*(float *) 1049308);

	char i = 0;
	for (i = 0; i < 4 * maxcicle; i += 4) {
		path_s[i] = 2;
		path_t[i] = 7;
		path_s[i + 1] = 5;
		path_t[i + 1] = 9;
		path_s[i + 2] = 2;
		path_t[i + 2] = 7;
		path_s[i + 3] = 5;
		path_t[i + 3] = 9;
	}

	path_s[0] += 2;
	path_s[i] = 3;
	path_t[i] = 255;

}

/*斜めの修行
 path_s[0]=5;path_t[0]=7;
 char tempI=0;
 for (tempI = 1; tempI < 4 * maxcicle; tempI += 4) {

 path_s[tempI]=6;path_t[tempI]=10;
 path_s[tempI+1]=4;path_t[tempI+1]=10;
 path_s[tempI+2]=6;path_t[tempI+2]=9;
 path_s[tempI+3]=4;path_t[tempI+3]=9;
 }
 path_s[tempI]=4;path_t[tempI]=255;
 */
#endif /* CIRKIT_H_ */
