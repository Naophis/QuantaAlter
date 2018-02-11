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
//		path_s[i] = 12;
//		path_t[i] = 5;
//		path_s[i + 1] = 2;
//		path_t[i + 1] = 5;
//
//// フル迷路サーキット
////
////		path_s[i] = 14;
////				path_t[i] = 5;
////				path_s[i + 1] = 14;
////				path_t[i + 1] = 5;
//
		/*
		 path_s[i] = 28;
		 path_t[i] = 5;
		 path_s[i + 1] = 28;
		 path_t[i + 1] = 5;*/

		path_s[i] = 8;	//部屋のサーキット
		path_t[i] = 5;
		path_s[i + 1] = 4;
		path_t[i + 1] = 5;
	}

	path_s[0] += 3;
	path_s[4 * maxcicle] = 2;
	path_t[4 * maxcicle] = 255;

//	path_s[0]=2;path_t[0]=9;
//	path_s[1]=2;path_t[1]=12;
//	path_s[2]=2;path_t[2]=7;
//	path_s[3]=2;path_t[3]=9;
//	path_s[4]=2;path_t[4]=10;

}
#endif /* CIRKIT_H_ */
