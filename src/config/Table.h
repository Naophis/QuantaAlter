/*
 * Table.h
 *
 *  Created on: 2014/04/27
 *      Author: Naoto
 */

#ifndef TABLE_H_
#define TABLE_H_

volatile char isDebug = true;

#define Normal 0
#define Large 1
#define Orval 2
#define Dia45 3
#define Dia135 4
#define Dia90 5
#define Kojima 6
#define Hira 7
#define Hira2 8
#define Finish 9
#define Straight 0
#define Right 1
#define Left 2
#define Back 3

#define OVERFLOW 32500
#define UNDERFLOW 2500
#define SEARCH 0
#define SEARCH2 1
#define RUN 2
#define RUN2 3
#define RUN3 4
#define RUN4 5
#define RUN5 6
#define CONFIG 7
#define CONFIG2 8
#define CONFIG3 9
#define CONFIG4 10
#define CONFIG5 11
#define CONFIG6 12
#define CONFIG7 13
#define CONFIG8 14
#define CONFIG9 15

#define KeepZeroPoint 16
#define MapMemory 17
#define VacumeTest 18
#define Mentenance 19

#define RUNNING 1
char turnVary(char a) {
	if (a == 1 || a == 2)
		return Normal;
	if (a == 3 || a == 4)
		return Orval;
	if (a == 5 || a == 6)
		return Large;
	if (a == 7 || a == 8)
		return Dia45;
	if (a == 9 || a == 10)
		return Dia135;
	if (a == 11 || a == 12)
		return Dia90;
	if (a == 13 || a == 14)
		return Kojima;
	if (a == 255)
		return Finish;
	return Finish;
}

#endif /* TABLE_H_ */
