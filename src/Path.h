/*
 * Path.h
 *
 *  Created on: 2014/05/06
 *      Author: Naoto
 */

#ifndef PATH_H_
#define PATH_H_

void largePath(char b1);
void diagonalPath(char isFull, char a1);
float pathCreateChange(int Goal_X, int Goal_Y, int qX, int qY, int fixedMove);
void vectorDistUpdate(int x, int y, char isFull);
float countPathLength(char bool);
void clearCheckMap() {
	for (char i = 0; i < 16; i++) {
		for (char j = 0; j < 16; j++) {
			checkMap[i][j] = 0;
		}
	}
}
int countTurnLisk() {
	int j = 0;
	for (int i = 0; path_t[i] != 255; i++) {
		if (path_t[i] > 6) {
			j++;
		}
	}
	return j;
}
void printCheckMap() {
	for (char j = 0; j < 16; j++) {
		for (char i = 0; i < 16; i++) {
			myprintf("%2x ", checkMap[i][15 - j]);
		}
		myprintf("\n");
	}
	myprintf("\n");
}
void addQ(int x, int y) {
	int i = 0;
	for (i = 0; checkQDuality[i] != 0; i++)
		;
	checkQDuality[i] = x * 16 + y;
}
void deleteQ(int x, int y) {
	char bool = false;
	for (int i = 0; checkQ[i] != 0; i++) {
		if (checkQ[i] / 16 == x && (checkQ[i] & 0x0f) == y) {
			checkQ[i] = 0;
			bool = true;
		}
		if (bool) {
			checkQ[i] = checkQ[i + 1];
		}
	}
}
void addCheckQ(int x, int y) {
	for (int i = 0; i < checkQlength; i++) {
		if ((checkQ[i] & 0xf0) >> 4 == x && (checkQ[i] & 0x0f) == y) {
			return;
		}
	}
	for (int i = 0; i < checkQlength; i++) {
		if (checkQ[i] == 0) {
			checkQ[i] = x * 16 + y;
			return;
		}
	}
}
char checkDualCheck(int x, int y) {
	char bool = false;
	int i = 0;
	for (i = 0; checkQDuality[i] != 0; i++) {
		if (checkQDuality[i] == x * 16 + y) {
			bool = true;
		}
	}
	if (!bool) {
		addQ(x, y);
	}
	return bool;
}
void checkOtherRoot(int x, int y, int now) {
	int temp = 0;
	int a[4];
	int index = 0;
	for (int d = 1; d <= 8; d *= 2) {
		int dist = getDistVector(x, y, d);
		if (now_dir * d != 8 && !existWall(x, y, d) && dist < now) {
			temp += d;
			a[index] = dist;
			index++;
		}
	}
	int ch = a[0];
	for (int i = 0; i < 4; i++) {
		if (a[i] == 0)
			continue;
		if (a[i] != ch)
			// return;
			ch = a[i];
	}

	if (temp == 0) {
		return;
	}
	if ((temp == 0x01) || (temp == 0x02) || (temp == 0x04) || (temp == 0x08)) {
	} else {
		checkMap[x][y] = temp;
		addCheckQ(x, y);
	}
}
float drawChangePathRoot(char goalX, char goalY, char isFull) {
	float pathVariation[4];
	unsigned char check = 0;
	unsigned char x = 0;
	unsigned char y = 0;
	unsigned char checkPoint[4];
	unsigned char temp = 255;
	unsigned char i = 0;
	unsigned char j = 0;
	unsigned char k = 0;
	unsigned char turnVariety[4][2];
	unsigned char Priority = 1;
	unsigned char p = 0;
	unsigned char q = 0;
	unsigned char checkker = 0;
	unsigned int turnLisk[4];
	int tempLisk = 0;
	deadEnd(goalX, goalY);
	vectorDistUpdate(goalX, goalY, isFull);
	for (i = 0; checkQ[i] != 0; i++) {
		pathVariation[0] = 255;
		pathVariation[1] = 255;
		pathVariation[2] = 255;
		pathVariation[3] = 255;
		checkPoint[0] = 0;
		checkPoint[1] = 0;
		checkPoint[2] = 0;
		checkPoint[3] = 0;
		turnLisk[0] = 255;
		turnLisk[1] = 255;
		turnLisk[2] = 255;
		turnLisk[3] = 255;
		x = (checkQ[i] / 16);
		y = checkQ[i] & 0x0f;
		if (checkMap[x][y] != 0 && (checkMap[x][y] & 0xf0) == 0) {
			if ((checkMap[x][y] & 0x01) == 0x01) {
				pathVariation[0] = pathCreateChange(goalX, goalY, x, y, North);
				if (checkTurningPoint) {
					checkPoint[0] = North;
				}
				if (pathVariation[0] != 255) {
					turnLisk[0] = countTurnLisk();
					for (k = 0; path_t[k] != 255; k++) {
						if (path_t[k] < 7) {
							turnVariety[0][0] += 1;
						} else {
							turnVariety[0][1] += 1;
						}
					}
				}
			}
			if ((checkMap[x][y] & 0x02) == 0x02) {
				pathVariation[1] = pathCreateChange(goalX, goalY, x, y, East);
				if (checkTurningPoint) {
					checkPoint[0] = East;
				}
				if (pathVariation[1] != 255) {
					turnLisk[1] = countTurnLisk();
					for (k = 0; path_t[k] != 255; k++) {
						if (path_t[k] < 7) {
							turnVariety[1][0] += 1;
						} else {
							turnVariety[1][1] += 1;
						}
					}
				}
			}
			if ((checkMap[x][y] & 0x04) == 0x04) {
				pathVariation[2] = pathCreateChange(goalX, goalY, x, y, West);
				if (checkTurningPoint) {
					checkPoint[0] = West;
				}
				if (pathVariation[2] != 255) {
					turnLisk[2] = countTurnLisk();
					for (k = 0; path_t[k] != 255; k++) {
						if (path_t[k] < 7) {
							turnVariety[2][0] += 1;
						} else {
							turnVariety[2][1] += 1;
						}
					}
				}
			}
			if ((checkMap[x][y] & 0x08) == 0x08) {
				pathVariation[3] = pathCreateChange(goalX, goalY, x, y, South);
				if (checkTurningPoint) {
					checkPoint[0] = South;
				}
				if (pathVariation[3] != 255) {
					turnLisk[3] = countTurnLisk();
					for (k = 0; path_t[k] != 255; k++) {
						if (path_t[k] < 7) {
							turnVariety[3][0] += 1;
						} else {
							turnVariety[3][1] += 1;
						}
					}
				}
			}
			temp = 255;
			tempLisk = 0;
//			myprintf("%f	%f	%f	%f\r\n", pathVariation[0], pathVariation[1],
//					pathVariation[2], pathVariation[3]);
			for (j = 0; j < 4; j++) {
				if (pathVariation[j] < temp) {
					temp = pathVariation[j];
					if (j == 0) {
						check = 1;
					} else if (j == 1) {
						check = 2;
					} else if (j == 2) {
						check = 4;
					} else if (j == 3) {
						check = 8;
					}
				} else if (pathVariation[j] != 255
						&& pathVariation[j] == temp) {
					if (tempLisk < turnLisk[j]) {
						temp = pathVariation[j];
						tempLisk = turnLisk[j];
						if (j == 0) {
							check = 1;
						} else if (j == 1) {
							check = 2;
						} else if (j == 2) {
							check = 4;
						} else if (j == 3) {
							check = 8;
						}
					}
				}
			}
//			myprintf("check=%d", check);
			if (Priority == 1) {
				if (pathVariation[0] == pathVariation[1]
						&& pathVariation[0] != 255) {
					if (turnVariety[0][1] > turnVariety[1][1]) {
						check = 1;
					} else if (turnVariety[0][1] < turnVariety[1][1]) {
						check = 2;
					}
				} else if (pathVariation[1] == pathVariation[2]
						&& pathVariation[1] != 255) {
					if (turnVariety[1][1] > turnVariety[2][1]) {
						check = 2;
					} else if (turnVariety[1][1] < turnVariety[2][1]) {
						check = 4;
					}
				} else if (pathVariation[2] == pathVariation[3]
						&& pathVariation[2] != 255) {
					if (turnVariety[2][1] > turnVariety[3][1]) {
						check = 4;
					} else if (turnVariety[2][1] < turnVariety[3][1]) {
						check = 8;
					}
				} else if (pathVariation[3] == pathVariation[0]
						&& pathVariation[3] != 255) {
					if (turnVariety[0][1] > turnVariety[3][1]) {
						check = 1;
					} else if (turnVariety[0][1] < turnVariety[3][1]) {
						check = 8;
					}
				} else if (pathVariation[3] == pathVariation[1]
						&& pathVariation[1] != 255) {
					if (turnVariety[1][1] > turnVariety[3][1]) {
						check = 2;
					} else if (turnVariety[1][1] < turnVariety[3][1]) {
						check = 8;
					}
				} else if (pathVariation[0] == pathVariation[2]
						&& pathVariation[2] != 255) {
					if (turnVariety[0][1] > turnVariety[2][1]) {
						check = 1;
					} else if (turnVariety[0][1] < turnVariety[2][1]) {
						check = 4;
					}
				}
			} else {
				if (pathVariation[0] == pathVariation[1]
						&& pathVariation[0] != 255) {
					if (turnVariety[0][1] < turnVariety[1][1]) {
						check = 1;
					} else if (turnVariety[0][1] > turnVariety[1][1]) {
						check = 2;
					}
				} else if (pathVariation[1] == pathVariation[2]
						&& pathVariation[1] != 255) {
					if (turnVariety[1][1] < turnVariety[2][1]) {
						check = 2;
					} else if (turnVariety[1][1] > turnVariety[2][1]) {
						check = 4;
					}
				} else if (pathVariation[2] == pathVariation[3]
						&& pathVariation[2] != 255) {
					if (turnVariety[2][1] < turnVariety[3][1]) {
						check = 4;
					} else if (turnVariety[2][1] > turnVariety[3][1]) {
						check = 8;
					}
				} else if (pathVariation[3] == pathVariation[0]
						&& pathVariation[3] != 255) {
					if (turnVariety[0][1] < turnVariety[3][1]) {
						check = 1;
					} else if (turnVariety[0][1] > turnVariety[3][1]) {
						check = 8;
					}
				} else if (pathVariation[3] == pathVariation[1]
						&& pathVariation[1] != 255) {
					if (turnVariety[1][1] < turnVariety[3][1]) {
						check = 2;
					} else if (turnVariety[1][1] > turnVariety[3][1]) {
						check = 8;
					}
				} else if (pathVariation[0] == pathVariation[2]
						&& pathVariation[2] != 255) {
					if (turnVariety[0][1] < turnVariety[2][1]) {
						check = 1;
					} else if (turnVariety[0][1] > turnVariety[2][1]) {
						check = 4;
					}
				}
			}
//			myprintf("check=%d", check);
			if ((checkPoint[0] == 0 && checkPoint[1] == 0 && checkPoint[2] == 0
					&& checkPoint[3] == 0) || check == 0) {
				deleteQ(x, y);
				if (!checkDualCheck(x, y)) {
					addQ(x, y);
				}
				i -= 1;
			} else {
				checkker = (check << 4) | (checkMap[x][y] & 0x0f);
				checkMap[x][y] = checkker;
			}
			for (p = 0; p < 4; p++) {
				for (q = 0; q < 2; q++) {
					turnVariety[p][q] = 0;
				}
			}
		}
	}
	for (i = 0; checkQ[i] != 0; i++) {
		pathVariation[0] = 255;
		pathVariation[1] = 255;
		pathVariation[2] = 255;
		pathVariation[3] = 255;
		checkPoint[0] = 0;
		checkPoint[1] = 0;
		checkPoint[2] = 0;
		checkPoint[3] = 0;
		x = (checkQ[i] / 16);
		y = checkQ[i] & 0x0f;
		if ((checkMap[x][y] & 0x01) == 0x01) {
			pathVariation[0] = pathCreateChange(goalX, goalY, x, y, North);
			if (checkPoint) {
				checkPoint[0] = North;
			}
			if (pathVariation[0] != 255) {
				for (k = 0; path_t[k] != 255; k++) {
					if (path_t[k] < 7) {
						turnVariety[0][0] += 1;
					} else {
						turnVariety[0][1] += 1;
					}
				}
			}
		}
		if ((checkMap[x][y] & 0x02) == 0x02) {
			pathVariation[1] = pathCreateChange(goalX, goalY, x, y, East);
			if (checkPoint) {
				checkPoint[0] = East;
			}
			if (pathVariation[1] != 255) {
				for (k = 0; path_t[k] != 255; k++) {
					if (path_t[k] < 7) {
						turnVariety[1][0] += 1;
					} else {
						turnVariety[1][1] += 1;
					}
				}
			}
		}
		if ((checkMap[x][y] & 0x04) == 0x04) {
			pathVariation[2] = pathCreateChange(goalX, goalY, x, y, West);
			if (checkPoint) {
				checkPoint[0] = West;
			}
			if (pathVariation[2] != 255) {
				for (k = 0; path_t[k] != 255; k++) {
					if (path_t[k] < 7) {
						turnVariety[2][0] += 1;
					} else {
						turnVariety[2][1] += 1;
					}
				}
			}
		}
		if ((checkMap[x][y] & 0x08) == 0x08) {
			pathVariation[3] = pathCreateChange(goalX, goalY, x, y, South);
			if (checkPoint) {
				checkPoint[0] = South;
			}
			if (pathVariation[3] != 255) {
				for (k = 0; path_t[k] != 255; k++) {
					if (path_t[k] < 7) {
						turnVariety[3][0] += 1;
					} else {
						turnVariety[3][1] += 1;
					}
				}
			}
		}
//		myprintf("%f	%f	%f	%f\r\n", pathVariation[0], pathVariation[1],
//				pathVariation[2], pathVariation[3]);
		temp = 255;
		tempLisk = 0;
		for (j = 0; j < 4; j++) {
			if (pathVariation[j] < temp) {
				temp = pathVariation[j];
				if (j == 0) {
					check = 1;
				} else if (j == 1) {
					check = 2;
				} else if (j == 2) {
					check = 4;
				} else if (j == 3) {
					check = 8;
				}
//			} else if (pathVariation[j] != 255 && pathVariation[j] == temp) {
//				if (tempLisk < turnLisk[j]) {
//					temp = pathVariation[j];
//					tempLisk = turnLisk[j];
//					if (j == 0) {
//						check = 1;
//					} else if (j == 1) {
//						check = 2;
//					} else if (j == 2) {
//						check = 4;
//					} else if (j == 3) {
//						check = 8;
//					}
//				}
			}
		}
//		myprintf("check=%d", check);
		if (Priority == 1) {
			if (pathVariation[0] == pathVariation[1]
					&& pathVariation[0] != 255) {
				if (turnVariety[0][1] > turnVariety[1][1]) {
					check = 1;
				} else if (turnVariety[0][1] < turnVariety[1][1]) {
					check = 2;
				}
			} else if (pathVariation[1] == pathVariation[2]
					&& pathVariation[1] != 255) {
				if (turnVariety[1][1] > turnVariety[2][1]) {
					check = 2;
				} else if (turnVariety[1][1] < turnVariety[2][1]) {
					check = 4;
				}
			} else if (pathVariation[2] == pathVariation[3]
					&& pathVariation[2] != 255) {
				if (turnVariety[2][1] > turnVariety[3][1]) {
					check = 4;
				} else if (turnVariety[2][1] < turnVariety[3][1]) {
					check = 8;
				}
			} else if (pathVariation[3] == pathVariation[0]
					&& pathVariation[3] != 255) {
				if (turnVariety[0][1] > turnVariety[3][1]) {
					check = 1;
				} else if (turnVariety[0][1] < turnVariety[3][1]) {
					check = 8;
				}
			} else if (pathVariation[3] == pathVariation[1]
					&& pathVariation[1] != 255) {
				if (turnVariety[1][1] > turnVariety[3][1]) {
					check = 2;
				} else if (turnVariety[1][1] < turnVariety[3][1]) {
					check = 8;
				}
			} else if (pathVariation[0] == pathVariation[2]
					&& pathVariation[2] != 255) {
				if (turnVariety[0][1] > turnVariety[2][1]) {
					check = 1;
				} else if (turnVariety[0][1] < turnVariety[2][1]) {
					check = 4;
				}
			}
		} else {
			if (pathVariation[0] == pathVariation[1]
					&& pathVariation[0] != 255) {
				if (turnVariety[0][1] < turnVariety[1][1]) {
					check = 1;
				} else if (turnVariety[0][1] > turnVariety[1][1]) {
					check = 2;
				}
			} else if (pathVariation[1] == pathVariation[2]
					&& pathVariation[1] != 255) {
				if (turnVariety[1][1] < turnVariety[2][1]) {
					check = 2;
				} else if (turnVariety[1][1] > turnVariety[2][1]) {
					check = 4;
				}
			} else if (pathVariation[2] == pathVariation[3]
					&& pathVariation[2] != 255) {
				if (turnVariety[2][1] < turnVariety[3][1]) {
					check = 4;
				} else if (turnVariety[2][1] > turnVariety[3][1]) {
					check = 8;
				}
			} else if (pathVariation[3] == pathVariation[0]
					&& pathVariation[3] != 255) {
				if (turnVariety[0][1] < turnVariety[3][1]) {
					check = 1;
				} else if (turnVariety[0][1] > turnVariety[3][1]) {
					check = 8;
				}
			} else if (pathVariation[3] == pathVariation[1]
					&& pathVariation[1] != 255) {
				if (turnVariety[1][1] < turnVariety[3][1]) {
					check = 2;
				} else if (turnVariety[1][1] > turnVariety[3][1]) {
					check = 8;
				}
			} else if (pathVariation[0] == pathVariation[2]
					&& pathVariation[2] != 255) {
				if (turnVariety[0][1] < turnVariety[2][1]) {
					check = 1;
				} else if (turnVariety[0][1] > turnVariety[2][1]) {
					check = 4;
				}
			}
		}
		if (checkPoint[0] == 0 && checkPoint[1] == 0 && checkPoint[2] == 0
				&& checkPoint[3] == 0) {
			deleteQ(x, y);
			if (!checkDualCheck(x, y)) {
				addQ(x, y);
			}
			i -= 1;
		} else {
			int checkker = (check << 4) | (checkMap[x][y] & 0x0f);
			checkMap[x][y] = checkker;
//			myprintf("(%2x,%2x)=%2x\r\n", x, y, checkker);
		}
		for (p = 0; p < 4; p++) {
			for (q = 0; q < 2; q++) {
				turnVariety[p][q] = 0;
			}
		}
	}
	return pathCreateChange(goalX, goalY, 0, 0, 1);
}

float countPathLength(char bool) {
	int i = 0;
	float j = 0;
	if (bool) {
		largePath(true);
		diagonalPath(true, true);
		for (i = 0; path_t[i] != 255; i++) {
			if (path_t[i] == 7 || path_t[i] == 8 || path_t[i] == 9
					|| path_t[i] == 10) {
				if ((path_s[i + 1] * 0.5 - 1) > 0) {
					j += 0.5;
				} else {
					j += 1;
				}
			} else if (path_t[i] == 11 || path_t[i] == 12) {
				j += 0.5;
			} else {
				j += 1;
			}
		}
		return j;
	}
	return 255;
}
float countPathLength2() {
	int i = 0;
	float j = 0;
	for (i = 0; path_t[i] != 255; i++) {
		if (path_t[i] == 7 || path_t[i] == 8 || path_t[i] == 9
				|| path_t[i] == 10) {
			if ((path_s[i + 1] * 0.5 - 1) > 0) {
				j += 0.5;
			} else {
				j += 1;
			}
		} else if (path_t[i] == 11 || path_t[i] == 12) {
			j += 0.5;
		} else {
			j += 1;
		}
	}
	return j;
}
int countStraightLength() {
	int i = 0;
	int length;
	for (i = 0; path_t[i] != 255; i++) {
		length += path_s[i];
	};
	return length;
}

float pathCreateChange(int Goal_X, int Goal_Y, int qX, int qY, int fixedMove) {
	int next_dir = North;
	int nextMotion = 0;
	int p = 0;
	int dirLog[3];
	char b1 = false;
	char b2 = false;
	char dirX = East;
	char dirY = North;
	char bool = false;
	checkTurningPoint = false;
//	deadEnd(Goal_X, Goal_Y);
	pathClear();
	x = 0;
	y = 0;
	now_dir = North;
	next_dir = North;
//	vectorDistUpdate(Goal_X, Goal_Y, 1);
	path_s[0] += 1;
	while (true) {
		if (p == 255) {
			return 255;
		}
		now_dir = next_dir;
		dirLog[2] = dirLog[1];
		dirLog[1] = dirLog[0];
		dirLog[0] = now_dir;
		Value = MAX;
		nextDirection = 255;
		if ((Goal_X == 7 && Goal_Y == 7) || (Goal_X == 7 && Goal_Y == 8)
				|| (Goal_X == 8 && Goal_Y == 7)
				|| (Goal_X == 8 && Goal_Y == 8)) {
			if ((x == Goal_X && y == Goal_Y) || (x == Goal_X + 1 && y == Goal_Y)
					|| (x == Goal_X && y == Goal_Y + 1)
					|| (x == Goal_X + 1 && y == Goal_Y + 1)) {
				b1 = true;
				bool = true;
			}
		} else {
			if ((x == Goal_X && y == Goal_Y)) {
				b1 = true;
			}
		}
		if (now_dir == North) {
			position = m[x][y].s;
		} else if (now_dir == East) {
			position = m[x][y].w;
		} else if (now_dir == West) {
			position = m[x][y].e;
		} else if (now_dir == South) {
			position = m[x][y].n;
		}
		if (b1) {
			if (dirLog[0] == dirLog[1] || dirLog[0] != dirLog[2]) {
				if (!setNextRootDirection(x, y, dirLog[0])) {
					break;
				}
			} else {
				if (!setNextRootDirection(x, y, dirLog[1])) {
					if (!b2) {
						priorityStraight2(x, y, dirLog[0]);
					} else {
						break;
					}
				}
				b2 = true;
			}
		} else {
			setNextRootDirectionPath(x, y, North);
			setNextRootDirectionPath(x, y, East);
			setNextRootDirectionPath(x, y, West);
			setNextRootDirectionPath(x, y, South);
			if (dirLog[0] == dirLog[1] || dirLog[0] != dirLog[2]) {
				priorityStraight2(x, y, dirLog[0]);
			} else {
				priorityStraight2(x, y, dirLog[1]);
			}
		}
		if (x == qX && y == qY) {
			nextDirection = fixedMove;
			checkPoint = true;
			checkTurningPoint = true;
		} else if ((checkMap[x][y] & 0xf0) != 0) {
			if ((checkMap[x][y] & 0x0f) == 0x06
					&& getDistVector(x, y, East) == getDistVector(x, y, West)) {
				nextDirection = dirX;
			} else if ((checkMap[x][y] & 0x0f) == 0x09
					&& getDistVector(x, y, North)
							== getDistVector(x, y, South)) {
				nextDirection = dirY;
			} else {
				nextDirection = (checkMap[x][y] & 0xf0) >> 4;
			}
		} else if ((checkMap[x][y] & 0x0f) == 0) {
			checkOtherRoot(x, y, position);
		}

		if (nextDirection != 255) {
			nextMotion = setNextMotion(nextDirection);
		} else {
			nextMotion = Back;
		}
		if (nextMotion == Straight) {
			path_s[p] += 2;
		} else if (nextMotion == Right) {
			path_t[p] = 1;
			p++;
			path_s[p] = 2;
		} else if (nextMotion == Left) {
			path_t[p] = 2;
			p++;
			path_s[p] = 2;
		} else {
			break;
		}
		next_dir = setNewPosition(nextDirection);
		if (next_dir == North || next_dir == South) {
			dirY = next_dir;
		} else {
			dirX = next_dir;
		}
	}
	if (qX == 0 && qY == 0) {
		return 0;
	}
	return countPathLength(bool);
}

#endif /* PATH_H_ */
