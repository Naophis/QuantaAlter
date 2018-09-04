/*
 * DistCalc.h
 *
 *  Created on: 2018/07/19
 *      Author: Naoto
 */

#ifndef MOTION_DISTCALC_H_
#define MOTION_DISTCALC_H_

//float getFrontDistX(char type) {
//	return 0;
//}
//
//float getFrontDistY(char type) {
//	return 0;
//}
//
//float getHogeY(char type, char RorL) {
//
//	float offsetLarge = 10;
//	float offsetOrval = 10;
//
//	float front = getFrontDistance(type, RorL);
//	float back = getBackDist(type, RorL);
//	float radius = getRadius(type, RorL);
//
//	if (type == Normal) {
//		return back;
//	} else if (type == Large) {
//		return 180 - (ABS(px2) + back) - offsetLarge;
//	} else if (type == Orval) {
//		return (py2 + back - front) - offsetOrval;
//	}
//
//	if (dia == 0) {
//		if (type == Dia45) {
//			return 180 - (back * cosf(radius) + ABS(py2));
//		} else if (type == Dia135) {
//			return 90 - (front + back + py2);
//		}
//	} else {
//		if (type == Dia45) {
//			return 180 - (back * cosf(radius) + ABS(py2));
//		} else if (type == Dia135) {
//			return back + px2;
//		} else if (type == Dia90) {
//			return back + px2;
//		}
//	}
//
//	return 0;
//}

#endif /* MOTION_DISTCALC_H_ */
