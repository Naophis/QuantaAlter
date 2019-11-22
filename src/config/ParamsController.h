/*
 * ParamsController.h
 *
 *  Created on: 2016/09/07
 *      Author: Naoto
 */

#ifndef PARAMSCONTROLLER_H_
#define PARAMSCONTROLLER_H_

void inputParameters2(char type, float frontLeft, float frontLeft2) {
	switch (type) {
	case Normal:
		pNormal.frontLeft1 = frontLeft;
		pNormal.frontLeft2 = frontLeft2;
		break;
	case Large:
		pLarge.frontLeft1 = frontLeft;
		pLarge.frontLeft2 = frontLeft2;
		break;
	case Orval:
		pOrval.frontLeft1 = frontLeft;
		pOrval.frontLeft2 = frontLeft2;
		break;
	case Dia45:
		pD45.frontLeft1 = frontLeft;
		pD45.frontLeft2 = frontLeft2;
		break;
	case Dia135:
		pD135.frontLeft1 = frontLeft;
		pD135.frontLeft2 = frontLeft2;
		break;
	case Dia90:
		pD90.frontLeft1 = frontLeft;
		pD90.frontLeft2 = frontLeft2;
		break;
	case Kojima:
		pKojima.frontLeft1 = frontLeft;
		pKojima.frontLeft2 = frontLeft2;
		break;
	}
}
void setFirstFrontDistance(char type, float firstFront) {
	switch (type) {
	case Large:
		pLarge.firstFront = firstFront;
		break;
	case Orval:
		pOrval.firstFront = firstFront;
		break;
	case Dia45:
		pD45.firstFront = firstFront;
		break;
	case Dia135:
		pD135.firstFront = firstFront;
		break;
	}
}
void inputParameters(char type, float targetAngle, float radius, float front1,
		float back1, float front2, float back2, float time, float n, float v) {
	switch (type) {
	case Normal:
		pNormal.targetAngle = targetAngle;
		pNormal.radius = radius;
		pNormal.front1 = front1;
		pNormal.back1 = back1;
		pNormal.front2 = front2;
		pNormal.time = time;
		pNormal.n = n;
		pNormal.velocity = v;
		break;
	case Large:
		pLarge.targetAngle = targetAngle;
		pLarge.radius = radius;
		pLarge.front1 = front1;
		pLarge.back1 = back1;
		pLarge.front2 = front2;
		pLarge.time = time;
		pLarge.n = n;
		pLarge.velocity = v;
		break;
	case Orval:
		pOrval.targetAngle = targetAngle;
		pOrval.radius = radius;
		pOrval.front1 = front1;
		pOrval.front2 = front2;
		pOrval.back1 = back1;
		pOrval.back2 = back2;
		pOrval.time = time;
		pOrval.n = n;
		pOrval.velocity = v;
		break;
	case Dia45:
		pD45.targetAngle = targetAngle;
		pD45.radius = radius;
		pD45.front1 = front1;
		pD45.back1 = back1;
		pD45.front2 = front2;
		pD45.back2 = back2;
		pD45.time = time;
		pD45.n = n;
		pD45.velocity = v;
		break;
	case Dia135:
		pD135.targetAngle = targetAngle;
		pD135.radius = radius;
		pD135.front1 = front1;
		pD135.back1 = back1;
		pD135.front2 = front2;
		pD135.back2 = back2;
		pD135.time = time;
		pD135.n = n;
		pD135.velocity = v;
		break;
	case Dia90:
		pD90.targetAngle = targetAngle;
		pD90.radius = radius;
		pD90.front1 = front1;
		pD90.back1 = back1;
		pD90.time = time;
		pD90.n = n;
		pD90.velocity = v;
		break;
	case Kojima:
		pKojima.targetAngle = targetAngle;
		pKojima.radius = radius;
		pKojima.front1 = front1;
		pKojima.back1 = back1;
		pKojima.time = time;
		pKojima.n = n;
		pKojima.velocity = v;
		break;
	}
}
//#define Normal 0
//#define Large 1
//#define Orval 2
//#define Dia45 3
//#define Dia135 4
//#define Dia90 5
//#define Kojima 6
//#define Hira 7
//#define Hira2 8
//#define Finish 9
void setPrms(char type, float targetAngle, float radius, float front1,
		float back1, float front2, float back2, float time, float n, float v) {
	inputParameters(type, targetAngle, radius, front1, back1, front2, back2,
			time, n, v);
}

void setPrms2(char type, float targetAngle, float radius, float front1,
		float back1, float front2, float back2, float time, float n, float v) {
	inputParameters(type, targetAngle, radius, front1, back1, front2, back2,
			time, n, v);
}
void setPrms3(char type, float front1, float front2, float firstFront) {
	inputParameters2(type, front1, front2);
	setFirstFrontDistance(type, firstFront);
}
void getPrm(char type) {
	float targetAngle = vs[type][0];
	float radius = vs[type][1];
	float front1 = vs[type][2];
	float back1 = vs[type][3];
	float front2 = vs[type][4];
	float back2 = vs[type][5];
	float time = vs[type][6];
	float n = vs[type][7];
	float v = vs[type][8];
	float frontleft1 = vs[type][9];
	float frontleft2 = vs[type][10];
	float firstFront = vs[type][11];
	v_sla[type] = v;
	inputParameters(type, targetAngle, radius, front1, back1, front2, back2,
			time, n, v);
	inputParameters2(type, frontleft1, frontleft2);
	setFirstFrontDistance(type, firstFront);
}
void showParam(char type) {
	float targetAngle = vs[type][0];
	float radius = vs[type][1];
	float front1 = vs[type][2];
	float back1 = vs[type][3];
	float front2 = vs[type][4];
	float back2 = vs[type][5];
	float time = vs[type][6];
	float n = vs[type][7];
	float v = vs[type][8];
//	myprintf("%d	%f\r\n", type, v);
}
void showParam2(char type) {
	float targetAngle = vs2[type][0];
	float radius = vs2[type][1];
	float front1 = vs2[type][2];
	float back1 = vs2[type][3];
	float front2 = vs2[type][4];
	float back2 = vs2[type][5];
	float time = vs2[type][6];
	float n = vs2[type][7];
	float v = vs2[type][8];
//	myprintf("%d	%f\r\n", type, v);
}
void showParams() {
	showParam(Normal);
	showParam(Large);
	showParam(Orval);
	showParam(Dia45);
	showParam(Dia135);
	showParam(Dia90);
	showParam(Kojima);
}
void showParams2() {
	showParam2(Normal);
	showParam2(Large);
	showParam2(Orval);
	showParam2(Dia45);
	showParam2(Dia135);
	showParam2(Dia90);
	showParam2(Kojima);
}
void getPrm2(char type) {
	float targetAngle = vs2[type][0];
	float radius = vs2[type][1];
	float front1 = vs2[type][2];
	float back1 = vs2[type][3];
	float front2 = vs2[type][4];
	float back2 = vs2[type][5];
	float time = vs2[type][6];
	float n = vs2[type][7];
	float v = vs2[type][8];
	float frontleft1 = vs2[type][9];
	float frontleft2 = vs2[type][10];
	float firstFront = vs2[type][11];
	v_sla[type] = v;
//	myprintf("%d	%f\r\n", type, v);
	inputParameters(type, targetAngle, radius, front1, back1, front2, back2,
			time, n, v);
	inputParameters2(type, frontleft1, frontleft2);
	setFirstFrontDistance(type, firstFront);
}
void getAllPram() {
	getPrm(Normal);
	getPrm(Large);
	getPrm(Orval);
	getPrm(Dia45);
	getPrm(Dia135);
	getPrm(Dia90);
	getPrm(Kojima);
}
void getAllPram2() {
	getPrm2(Normal);
	getPrm2(Large);
	getPrm2(Orval);
	getPrm2(Dia45);
	getPrm2(Dia135);
	getPrm2(Dia90);
	getPrm2(Kojima);
}

void save() {
	vs[Normal][0] = pNormal.targetAngle;
	vs[Normal][1] = pNormal.radius;
	vs[Normal][2] = pNormal.front1;
	vs[Normal][3] = pNormal.back1;

	vs[Normal][6] = pNormal.time;
	vs[Normal][7] = pNormal.n;

	vs[Normal][8] = pNormal.velocity;
	vs[Normal][9] = pNormal.frontLeft1;
	vs[Normal][10] = pNormal.frontLeft2;

	vs[Large][0] = pLarge.targetAngle;
	vs[Large][1] = pLarge.radius;
	vs[Large][2] = pLarge.front1;
	vs[Large][3] = pLarge.back1;
	vs[Large][6] = pLarge.time;
	vs[Large][7] = pLarge.n;
	vs[Large][8] = pLarge.velocity;
	vs[Large][9] = pLarge.frontLeft1;
	vs[Large][10] = pLarge.frontLeft2;
	vs[Large][11] = pLarge.firstFront;

	vs[Orval][0] = pOrval.targetAngle;
	vs[Orval][1] = pOrval.radius;
	vs[Orval][2] = pOrval.front1;
	vs[Orval][3] = pOrval.back1;
	vs[Orval][4] = pOrval.front2;
	vs[Orval][5] = pOrval.back2;
	vs[Orval][6] = pOrval.time;
	vs[Orval][7] = pOrval.n;
	vs[Orval][8] = pOrval.velocity;
	vs[Orval][9] = pOrval.frontLeft1;
	vs[Orval][10] = pOrval.frontLeft2;
	vs[Orval][11] = pOrval.firstFront;

	vs[Dia45][0] = pD45.targetAngle;
	vs[Dia45][1] = pD45.radius;
	vs[Dia45][2] = pD45.front1;
	vs[Dia45][3] = pD45.back1;
	vs[Dia45][4] = pD45.front2;
	vs[Dia45][5] = pD45.back2;
	vs[Dia45][6] = pD45.time;
	vs[Dia45][7] = pD45.n;
	vs[Dia45][8] = pD45.velocity;
	vs[Dia45][9] = pD45.frontLeft1;
	vs[Dia45][10] = pD45.frontLeft2;
	vs[Dia45][11] = pD45.firstFront;

	vs[Dia135][0] = pD135.targetAngle;
	vs[Dia135][1] = pD135.radius;
	vs[Dia135][2] = pD135.front1;
	vs[Dia135][3] = pD135.back1;
	vs[Dia135][4] = pD135.front2;
	vs[Dia135][5] = pD135.back2;
	vs[Dia135][6] = pD135.time;
	vs[Dia135][7] = pD135.n;
	vs[Dia135][8] = pD135.velocity;
	vs[Dia135][9] = pD135.frontLeft1;
	vs[Dia135][10] = pD135.frontLeft2;
	vs[Dia135][11] = pD135.firstFront;

	vs[Dia90][0] = pD90.targetAngle;
	vs[Dia90][1] = pD90.radius;
	vs[Dia90][2] = pD90.front1;
	vs[Dia90][3] = pD90.back1;
	vs[Dia90][6] = pD90.time;
	vs[Dia90][7] = pD90.n;
	vs[Dia90][8] = pD90.velocity;
	vs[Dia90][9] = pD90.frontLeft1;
	vs[Dia90][10] = pD90.frontLeft2;

	vs[Kojima][0] = pKojima.targetAngle;
	vs[Kojima][1] = pKojima.radius;
	vs[Kojima][2] = pKojima.front1;
	vs[Kojima][3] = pKojima.back1;
	vs[Kojima][6] = pKojima.time;
	vs[Kojima][7] = pKojima.n;
	vs[Kojima][8] = pKojima.velocity;
	vs[Kojima][9] = pKojima.frontLeft1;
	vs[Kojima][10] = pKojima.frontLeft2;

	for (int i = 0; i <= Kojima; i++) {
		myprintf("%d", i);
		for (int j = 0; j < 12; j++) {
			myprintf("	%f", vs[i][j]);
		}
		myprintf("\r\n");
	}
}
void save2() {
	vs2[Normal][0] = pNormal.targetAngle;
	vs2[Normal][1] = pNormal.radius;
	vs2[Normal][2] = pNormal.front1;
	vs2[Normal][3] = pNormal.back1;
	vs2[Normal][6] = pNormal.time;
	vs2[Normal][7] = pNormal.n;
	vs2[Normal][8] = pNormal.velocity;

	vs2[Normal][9] = pNormal.frontLeft1;
	vs2[Normal][10] = pNormal.frontLeft2;
	vs2[Large][0] = pLarge.targetAngle;
	vs2[Large][1] = pLarge.radius;
	vs2[Large][2] = pLarge.front1;
	vs2[Large][3] = pLarge.back1;
	vs2[Large][6] = pLarge.time;
	vs2[Large][7] = pLarge.n;
	vs2[Large][8] = pLarge.velocity;
	vs2[Large][9] = pLarge.frontLeft1;
	vs2[Large][10] = pLarge.frontLeft2;
	vs2[Large][11] = pLarge.firstFront;

	vs2[Orval][0] = pOrval.targetAngle;
	vs2[Orval][1] = pOrval.radius;
	vs2[Orval][2] = pOrval.front1;
	vs2[Orval][3] = pOrval.back1;
	vs2[Orval][4] = pOrval.front2;
	vs2[Orval][5] = pOrval.back2;
	vs2[Orval][6] = pOrval.time;
	vs2[Orval][7] = pOrval.n;
	vs2[Orval][8] = pOrval.velocity;
	vs2[Orval][9] = pOrval.frontLeft1;
	vs2[Orval][10] = pOrval.frontLeft2;
	vs2[Orval][11] = pOrval.firstFront;

	vs2[Dia45][0] = pD45.targetAngle;
	vs2[Dia45][1] = pD45.radius;
	vs2[Dia45][2] = pD45.front1;
	vs2[Dia45][3] = pD45.back1;
	vs2[Dia45][4] = pD45.front2;
	vs2[Dia45][5] = pD45.back2;
	vs2[Dia45][6] = pD45.time;
	vs2[Dia45][7] = pD45.n;
	vs2[Dia45][8] = pD45.velocity;
	vs2[Dia45][9] = pD45.frontLeft1;
	vs2[Dia45][10] = pD45.frontLeft2;
	vs2[Dia45][11] = pD45.firstFront;

	vs2[Dia135][0] = pD135.targetAngle;
	vs2[Dia135][1] = pD135.radius;
	vs2[Dia135][2] = pD135.front1;
	vs2[Dia135][3] = pD135.back1;
	vs2[Dia135][4] = pD135.front2;
	vs2[Dia135][5] = pD135.back2;
	vs2[Dia135][6] = pD135.time;
	vs2[Dia135][7] = pD135.n;
	vs2[Dia135][8] = pD135.velocity;
	vs2[Dia135][9] = pD135.frontLeft1;
	vs2[Dia135][10] = pD135.frontLeft2;
	vs2[Dia135][11] = pD135.firstFront;

	vs2[Dia90][0] = pD90.targetAngle;
	vs2[Dia90][1] = pD90.radius;
	vs2[Dia90][2] = pD90.front1;
	vs2[Dia90][3] = pD90.back1;
	vs2[Dia90][6] = pD90.time;
	vs2[Dia90][7] = pD90.n;
	vs2[Dia90][8] = pD90.velocity;
	vs2[Dia90][9] = pD90.frontLeft1;
	vs2[Dia90][10] = pD90.frontLeft2;

	vs2[Kojima][0] = pKojima.targetAngle;
	vs2[Kojima][1] = pKojima.radius;
	vs2[Kojima][2] = pKojima.front1;
	vs2[Kojima][3] = pKojima.back1;
	vs2[Kojima][6] = pKojima.time;
	vs2[Kojima][7] = pKojima.n;
	vs2[Kojima][8] = pKojima.velocity;
	vs2[Kojima][9] = pKojima.frontLeft1;
	vs2[Kojima][10] = pKojima.frontLeft2;

	for (int i = 0; i <= Kojima; i++) {
		myprintf("%d", i);
		for (int j = 0; j < 12; j++) {
			myprintf("	%f", vs2[i][j]);
		}
		myprintf("\r\n");
	}
}

void save3() {
	vs3[Normal][0] = pNormal.targetAngle;
	vs3[Normal][1] = pNormal.radius;
	vs3[Normal][2] = pNormal.front1;
	vs3[Normal][3] = pNormal.back1;
	vs3[Normal][6] = pNormal.time;
	vs3[Normal][7] = pNormal.n;
	vs3[Normal][8] = pNormal.velocity;

	vs3[Normal][9] = pNormal.frontLeft1;
	vs3[Normal][10] = pNormal.frontLeft2;
	vs3[Large][0] = pLarge.targetAngle;
	vs3[Large][1] = pLarge.radius;
	vs3[Large][2] = pLarge.front1;
	vs3[Large][3] = pLarge.back1;
	vs3[Large][6] = pLarge.time;
	vs3[Large][7] = pLarge.n;
	vs3[Large][8] = pLarge.velocity;
	vs3[Large][9] = pLarge.frontLeft1;
	vs3[Large][10] = pLarge.frontLeft2;
	vs3[Large][11] = pLarge.firstFront;

	vs3[Orval][0] = pOrval.targetAngle;
	vs3[Orval][1] = pOrval.radius;
	vs3[Orval][2] = pOrval.front1;
	vs3[Orval][3] = pOrval.back1;
	vs3[Orval][4] = pOrval.front2;
	vs3[Orval][5] = pOrval.back2;
	vs3[Orval][6] = pOrval.time;
	vs3[Orval][7] = pOrval.n;
	vs3[Orval][8] = pOrval.velocity;
	vs3[Orval][9] = pOrval.frontLeft1;
	vs3[Orval][10] = pOrval.frontLeft2;
	vs3[Orval][11] = pOrval.firstFront;

	vs3[Dia45][0] = pD45.targetAngle;
	vs3[Dia45][1] = pD45.radius;
	vs3[Dia45][2] = pD45.front1;
	vs3[Dia45][3] = pD45.back1;
	vs3[Dia45][4] = pD45.front2;
	vs3[Dia45][5] = pD45.back2;
	vs3[Dia45][6] = pD45.time;
	vs3[Dia45][7] = pD45.n;
	vs3[Dia45][8] = pD45.velocity;
	vs3[Dia45][9] = pD45.frontLeft1;
	vs3[Dia45][10] = pD45.frontLeft2;
	vs3[Dia45][11] = pD45.firstFront;

	vs3[Dia135][0] = pD135.targetAngle;
	vs3[Dia135][1] = pD135.radius;
	vs3[Dia135][2] = pD135.front1;
	vs3[Dia135][3] = pD135.back1;
	vs3[Dia135][4] = pD135.front2;
	vs3[Dia135][5] = pD135.back2;
	vs3[Dia135][6] = pD135.time;
	vs3[Dia135][7] = pD135.n;
	vs3[Dia135][8] = pD135.velocity;
	vs3[Dia135][9] = pD135.frontLeft1;
	vs3[Dia135][10] = pD135.frontLeft2;
	vs3[Dia135][11] = pD135.firstFront;

	vs3[Dia90][0] = pD90.targetAngle;
	vs3[Dia90][1] = pD90.radius;
	vs3[Dia90][2] = pD90.front1;
	vs3[Dia90][3] = pD90.back1;
	vs3[Dia90][6] = pD90.time;
	vs3[Dia90][7] = pD90.n;
	vs3[Dia90][8] = pD90.velocity;
	vs3[Dia90][9] = pD90.frontLeft1;
	vs3[Dia90][10] = pD90.frontLeft2;

	vs3[Kojima][0] = pKojima.targetAngle;
	vs3[Kojima][1] = pKojima.radius;
	vs3[Kojima][2] = pKojima.front1;
	vs3[Kojima][3] = pKojima.back1;
	vs3[Kojima][6] = pKojima.time;
	vs3[Kojima][7] = pKojima.n;
	vs3[Kojima][8] = pKojima.velocity;
	vs3[Kojima][9] = pKojima.frontLeft1;
	vs3[Kojima][10] = pKojima.frontLeft2;

	for (int i = 0; i <= Kojima; i++) {
		myprintf("%d", i);
		for (int j = 0; j < 12; j++) {
			myprintf("	%f", vs3[i][j]);
		}
		myprintf("\r\n");
	}
}

float getTargetAngle(char type) {
	switch (type) {
	case Normal:
		return pNormal.targetAngle;
	case Large:
		return pLarge.targetAngle;
	case Orval:
		return pOrval.targetAngle;
	case Dia45:
		return pD45.targetAngle;
	case Dia135:
		return pD135.targetAngle;
	case Dia90:
		return pD90.targetAngle;
	case Kojima:
		return pKojima.targetAngle;
	}
	return 0;
}
float getFrontDistanceLeft(char type) {
	switch (type) {
	case Normal:
		return pNormal.frontLeft1;
	case Large:
		return pLarge.frontLeft1;
	case Orval:
		return pOrval.frontLeft1;
	case Dia45:
		return dia == 0 ? pD45.frontLeft1 : pD45.frontLeft2;
	case Dia135:
		return dia == 0 ? pD135.frontLeft1 : pD135.frontLeft2;
	case Dia90:
		return pD90.frontLeft1;
	case Kojima:
		return pKojima.frontLeft1;
	}
	return 0;
}

float getFrontDistance(char type, char RorL) {
	if (RorL == L) {
		return getFrontDistanceLeft(type);
	}
	switch (type) {
	case Normal:
		return pNormal.front1;
	case Large:
		return pLarge.front1;
	case Orval:
		return pOrval.front1;
	case Dia45:
		return dia == 0 ? pD45.front1 : pD45.front2;
	case Dia135:
		return dia == 0 ? pD135.front1 : pD135.front2;
	case Dia90:
		return pD90.front1;
	case Kojima:
		return pKojima.front1;
	}
	return 0;
}
float getBackDistanceLeft(char type) {
	switch (type) {
	case Normal:
		return pNormal.frontLeft2;
	case Large:
		return pLarge.frontLeft2;
	case Orval:
		return pOrval.frontLeft2;
	case Dia45:
		return dia == 1 ? pD45.frontLeft1 : pD45.frontLeft2;
	case Dia135:
		return dia == 1 ? pD135.frontLeft1 : pD135.frontLeft2;
	case Dia90:
		return pD90.frontLeft2;
	case Kojima:
		return pKojima.frontLeft2;
	}
	return 0;
}
float getBackDistance_v2(char type, char RorL) {
	if (RorL == L) {
		return getBackDistanceLeft(RorL);
	}
	switch (type) {
	case Normal:
		return pNormal.back1;
	case Large:
		return pLarge.back1;
	case Orval:
		return pOrval.back1;
	case Dia45:
		return dia == 1 ? pD45.back1 : pD45.back2;
	case Dia135:
		return dia == 1 ? pD135.back1 : pD135.back2;
	case Dia90:
		return pD90.back1;
	case Kojima:
		return pKojima.back1;
	}
	return 0;
}
float getBackDist(char type, char RorL) {
	switch (type) {
	case Normal:
		return RorL == L ? pNormal.frontLeft2 : pNormal.back1;
	case Large:
		return pLarge.back1;
	case Orval:
		return RorL == L ? pOrval.frontLeft2 : pOrval.back1;
	case Dia45:
		return dia == 1 ? pD45.back1 : pD45.back2;
	case Dia135:
		return dia == 1 ? pD135.back1 : pD135.back2;
	case Dia90:
		return pD90.back1;
	case Kojima:
		return pKojima.back1;
	}
	return 0;
}
float getNaiperTime(char type, char RorL) {
	switch (type) {
	case Normal:
		return pNormal.time;
	case Large:
		return pLarge.time;
	case Orval:
		return RorL == R ? pOrval.time : pOrval.back2;
	case Dia45:
		return pD45.time;
	case Dia135:
		return pD135.time;
	case Dia90:
		return pD90.time;
	case Kojima:
		return pKojima.time;
	}
	return 0;
}

float getNaiperN(char type) {
	switch (type) {
	case Normal:
		return pNormal.n;
	case Large:
		return pLarge.n;
	case Orval:
		return pOrval.n;
	case Dia45:
		return pD45.n;
	case Dia135:
		return pD135.n;
	case Dia90:
		return pD90.n;
	case Kojima:
		return pKojima.n;
	}
	return 0;
}
float toRadians(float data) {
	return data * PI / 180;
}
float getRadius(char type, char RorL) {
	switch (type) {
	case Normal:
		return pNormal.radius;
	case Large:
		return pLarge.radius;
	case Orval:
		return RorL == R ? pOrval.radius : pOrval.front2;
	case Dia45:
		return pD45.radius;
	case Dia135:
		return pD135.radius;
	case Dia90:
		return pD90.radius;
	case Kojima:
		return pKojima.radius;
	}
	return 0;
}
float getFirstFront(char type) {
	switch (type) {
	case Normal:
		return pNormal.firstFront;
	case Large:
		return pLarge.firstFront;
	case Orval:
		return pOrval.firstFront;
	case Dia45:
		return pD45.firstFront;
	case Dia135:
		return pD135.firstFront;
	case Dia90:
		return pD90.firstFront;
	case Kojima:
		return pKojima.firstFront;
	}
	return 0;
}

#endif /* PARAMSCONTROLLER_H_ */
