/*
 * VectorPath.h
 *
 *  Created on: 2015/10/25
 *      Author: Naoto
 */

#ifndef VECTORPATH_H_
#define VECTORPATH_H_

void overWrap(int x, int y, int d) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return;
	map[x][y] |= d;
}

void vectorDistUpdate(int x, int y, char isFull) {
	char head = true;
	int min = 0;
	int c = 0;
	int d = 0;
	int val = 0;
	char bool2 = true;
	clearVectorMap(x, y, isFull);
	while (bool2) {
		head = false;
		for (char i = 0; i < 16; i++) {
			for (char j = 0; j < 16; j++) {
				c++;
				if (m[i][j].n == min) {
					head = true;
					if (!existWall(i, j + 1, North)
							&& isStep(i, j + 1, North)) {
						val = m[i][j].N1 == 0 ? min + St1 : min + St2;
						val = m[i][j].N1 >= strBias ? min + St3 : val;
						if (up(i, j + 1, North, true, val)) {
							m[i][j + 1].N1 = m[i][j].N1 + 1;
						}
					}
					if (!existWall(i, j + 1, East) && isStep(i, j + 1, East)) {
						val = m[i][j].NE <= bias ? min + Dia : min + Dia2;
						val = m[i][j].NE > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, West)
								&& up(i, j + 1, East, true, val)) {
							m[i][j + 1].NE = m[i][j].NE + 1;
						} else if (up(i, j + 1, East, true, val)) {
							m[i][j + 1].NE = m[i][j].NE + 1;
						}
					}
					if (!existWall(i, j + 1, West) && isStep(i, j + 1, West)) {
						val = m[i][j].NW <= bias ? min + Dia : min + Dia2;
						val = m[i][j].NW > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, East)
								&& up(i, j + 1, West, true, val)) {
							m[i][j + 1].NW = m[i][j].NW + 1;
						} else if (up(i, j + 1, West, true, val)) {
							m[i][j + 1].NW = m[i][j].NW + 1;
						}
					}
				}
				if (m[i][j].e == min) {
					head = true;
					if (!existWall(i + 1, j, East) && isStep(i + 1, j, East)) {
						val = m[i][j].E1 == 0 ? min + St1 : min + St2;
						val = m[i][j].E1 >= strBias ? min + St3 : val;
						if (up(i + 1, j, East, true, val)) {
							m[i + 1][j].E1 = m[i][j].E1 + 1;
						}
					}
					if (!existWall(i + 1, j, South)
							&& isStep(i + 1, j, South)) {
						val = m[i][j].SE <= bias ? min + Dia : min + Dia2;
						val = m[i][j].SE > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, North)
								&& up(i + 1, j, South, true, val)) {
							m[i + 1][j].SE = m[i][j].SE + 1;
						} else if (up(i + 1, j, South, true, val)) {
							m[i + 1][j].SE = m[i][j].SE + 1;
						}
					}
					if (!existWall(i + 1, j, North)
							&& isStep(i + 1, j, North)) {
						val = m[i][j].NE <= bias ? min + Dia : min + Dia2;
						val = m[i][j].NE > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, South)
								&& up(i + 1, j, North, true, val)) {
							m[i + 1][j].NE = m[i][j].NE + 1;
						} else if (up(i + 1, j, North, true, val)) {
							m[i + 1][j].NE = m[i][j].NE + 1;
						}
					}
				}
				if (m[i][j].w == min) {
					head = true;
					if (!existWall(i - 1, j, West) && isStep(i - 1, j, West)) {
						val = m[i][j].W1 == 0 ? min + St1 : min + St2;
						val = m[i][j].W1 >= strBias ? min + St3 : val;
						if (up(i - 1, j, West, true, val)) {
							m[i - 1][j].W1 = m[i][j].W1 + 1;
						}
					}
					if (!existWall(i - 1, j, North)
							&& isStep(i - 1, j, North)) {
						val = m[i][j].NW <= bias ? min + Dia : min + Dia2;
						val = m[i][j].NW > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, South)
								&& up(i - 1, j, North, true, val)) {
							m[i - 1][j].NW = m[i][j].NW + 1;
						} else if (up(i - 1, j, North, true, val)) {
							m[i - 1][j].NW = m[i][j].NW + 1;
						}
					}
					if (!existWall(i - 1, j, South)
							&& isStep(i - 1, j, South)) {
						val = m[i][j].SW <= bias ? min + Dia : min + Dia2;
						val = m[i][j].SW > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, North)
								&& up(i - 1, j, South, true, val)) {
							m[i - 1][j].SW = m[i][j].SW + 1;
						} else if (up(i - 1, j, South, true, val)) {
							m[i - 1][j].SW = m[i][j].SW + 1;
						}
					}
				}
				if (m[i][j].s == min) {
					head = true;
					if (!existWall(i, j - 1, South)
							&& isStep(i, j - 1, South)) {
						val = m[i][j].S1 == 0 ? min + St1 : min + St2;
						val = m[i][j].S1 >= strBias ? min + St3 : val;
						if (up(i, j - 1, South, true, val)) {
							m[i][j - 1].S1 = m[i][j].S1 + 1;
						}
					}
					if (!existWall(i, j - 1, West) && isStep(i, j - 1, West)) {
						val = m[i][j].SW <= bias ? min + Dia : min + Dia2;
						val = m[i][j].SW > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, East)
								&& up(i, j - 1, West, true, val)) {
							m[i][j - 1].SW = m[i][j].SW + 1;
						} else if (up(i, j - 1, West, true, val)) {
							m[i][j - 1].SW = m[i][j].SW + 1;
						}
					}
					if (!existWall(i, j - 1, East) && isStep(i, j - 1, East)) {
						val = m[i][j].SE <= bias ? min + Dia : min + Dia2;
						val = m[i][j].SE > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, West)
								&& up(i, j - 1, East, true, val)) {
							m[i][j - 1].SE = m[i][j].SE + 1;
						} else if (up(i, j - 1, East, true, val)) {
							m[i][j - 1].SE = m[i][j].SE + 1;
						}
					}
				}
			}
		}
		if (head) {
			bool2 = true;
			d = 0;
		} else {
			d++;
			if (d > 8) {
				bool2 = false;
			}
		}
		min++;
	}
}

void largePath(char b1) {
	int i = 0;
	int finish = 0;
	for (i = 0; i < pathLength; i++) {
		if (path_s[i + 1] == 2) {
			if (path_s[i] > 2 && path_s[i + 2] > 2) {
				if (path_t[i] == path_t[i + 1]) {
					if (path_t[i] == 1) {
						path_t[i] = 3;
						path_t[i + 1] = 254;
					} else if (path_t[i] == 2) {
						path_t[i] = 4;
						path_t[i + 1] = 254;
					}
					path_s[i] -= 1;
					path_s[i + 2] -= 1;
					i++;
				}
			}
		}
		if (path_t[i] == 0) {
			break;
		}
	}
	for (i = 0; i < pathLength; i++) {
		if (path_s[i] > 2 && path_s[i + 1] > 2) {
			if (path_t[i] == 1) {
				path_t[i] = 5;
				path_s[i + 1] -= 1;
				path_s[i] -= 1;
			} else if (path_t[i] == 2) {
				path_t[i] = 6;
				path_s[i + 1] -= 1;
				path_s[i] -= 1;
			}
		}
		if (path_t[i] == 0) {
			break;
		}
	}
	if (b1) {
		if (path_s[0] == 2 && path_t[0] == 1 && path_s[1] > 2) {
			path_s[0] -= 1;
			path_s[1] -= 1;
			path_t[0] = 5;
		}
		i = 0;
		while (path_t[i] != 0) {
			i++;
		}
		finish = i;
		if (finish >= 1) {
			if (path_s[finish] == 2 && path_s[finish - 1] > 2
					&& (path_t[finish - 1] == 1 || path_t[finish - 1] == 2)) {
				path_s[finish - 1] -= 1;
				path_s[finish] -= 1;
				if (path_t[finish - 1] == 1) {
					path_t[finish - 1] = 5;
				} else if (path_t[finish - 1] == 2) {
					path_t[finish - 1] = 6;
				}
			}
		}
		if (finish > 2) {
			if (path_s[finish] == 2 && path_s[finish - 1] == 2
					&& path_s[finish - 2] > 2 && path_t[finish - 1] == 1
					&& path_t[finish - 2] == 1) {
				path_s[finish - 2] -= 1;
				path_s[finish] -= 1;
				path_t[finish - 2] = 3;
				path_t[finish - 1] = 254;
			}
			if (path_s[finish] == 2 && path_s[finish - 1] == 2
					&& path_s[finish - 2] > 2 && path_t[finish - 1] == 2
					&& path_t[finish - 2] == 2) {
				path_s[finish - 2] -= 1;
				path_s[finish] -= 1;
				path_t[finish - 2] = 4;
				path_t[finish - 1] = 254;
			}
		}
		if (finish == 2) {
			if (path_s[finish] == 2 && path_s[finish - 1] == 2
					&& path_s[finish - 2] >= 2 && path_t[finish - 1] == 1
					&& path_t[finish - 2] == 1) {
				path_s[finish - 2] -= 1;
				path_s[finish] -= 1;
				path_t[finish - 2] = 3;
				path_t[finish - 1] = 254;
			}
			if (path_s[finish] == 2 && path_s[finish - 1] == 2
					&& path_s[finish - 2] >= 2 && path_t[finish - 1] == 2
					&& path_t[finish - 2] == 2) {
				path_s[finish - 2] -= 1;
				path_s[finish] -= 1;
				path_t[finish - 2] = 4;
				path_t[finish - 1] = 254;
			}
		}
	}
}

void pathOffset() {
	int i = 0;
	for (i = 0; i < pathLength; i++) {
		if (path_t[i] == 0) {
			path_t[i] = 0xff;
			break;
		}
	}
	i = 0;
	while (path_t[i] != 0xff) {
		if (i > 0) {
			if (path_t[i] == 254) {
				path_s[i] = 0;
				path_t[i] = 0;
			}
		}
		i++;
	}
	i = 0;
	while (path_t[i] != 0xff) {
		while (path_t[i] == 0) {
			for (int j = i; path_t[j] != 0xff; j++) {
				path_s[j] = path_s[j + 1];
				path_t[j] = path_t[j + 1];
			}
		}
		i++;
	}
}
void kojima() {
	for (int i = 0; i < pathLength; i++) {
		if (path_s[i + 1] <= 2) {
			if (path_t[i] == 7 && path_t[i + 1] == 7) {
				path_t[i] = 13;
				path_t[i + 1] = 1;
			} else if (path_t[i] == 8 && path_t[i + 1] == 8) {
				path_t[i] = 14;
				path_t[i + 1] = 2;
			}
		}
		if (path_t[i] == 0) {
			break;
		}
	}
	pathOffset();
}
void diagonalPath(char isFull, char a1) {
	int i = 0;
	int j = 0;
	int dir = 0;
	int check = 0;
	int diaMode = false;
	int m = 0;
	int check2 = false;
	int check3 = false;

	char virtual = !a1;
	char flag = false;
	while (path_t[i] != 0) {
		check = 0;
		if (virtual) {
			a1 = false;
			if (path_s[i] > 2) {
				flag = true;
			}
			if (flag/* && i != 0*/) {
				for (m = i + 1;; m++) {
					if (path_s[m] > 2) {
						a1 = true;
						break;
					}
					if (path_t[m] == 0) {
						a1 = false;
						break;
					}
				}
			}
		}

//		if (/*i > 0 &&*/m != 0 && path_s[m] > 2) {
//			a1 = true;
//		}
		if (path_t[i] == R && (a1 ? true : path_s[i] > 2)) {
			dir = R;
			for (j = i + 1; path_t[j] != dir; j++) {
				if (path_t[j] == R && path_s[j] == 2) {
					dir = R;
				} else if (path_t[j] == L && path_s[j] == 2) {
					dir = L;
				} else {
					break;
				}
				check++;
			}
		} else if (path_t[i] == L && (a1 ? true : path_s[i] > 2)) {
			dir = L;
			for (j = i + 1; path_t[j] != dir; j++) {
				if (path_t[j] == R && path_s[j] == 2) {
					dir = R;
				} else if (path_t[j] == L && path_s[j] == 2) {
					dir = L;
				} else {
					break;
				}
				check++;
			}
		}
		if (check != 0) {
			j -= 1;
			if (i != 0 && path_s[i] == 2 && path_t[i] == path_t[i - 1]
					&& path_s[i - 1] > 2) {
				if (path_t[i] == R) {
					path_t[i - 1] = 9;
					check3 = true;
				} else if (path_t[i] == L) {
					path_t[i - 1] = 10;
					check3 = true;
				}
				if (j != 0 && path_s[j + 2] > 2 && path_t[j] == path_t[j + 1]) {
					if (path_t[j] == R) {
						path_t[j + 1] = 9;
						check2 = true;
					} else if (path_t[j] == L) {
						path_t[j + 1] = 10;
						check2 = true;
					}
					path_s[j + 1] = check + 1;
				} else {
					if (path_t[j] == R) {
						path_t[j] = 7;
					} else if (path_t[j] == L) {
						path_t[j] = 8;
					}
					path_s[j] = check + 1;
				}
			} else {
				int memory = 0;
				if (path_t[i] == R) {
					path_t[i] = 7;
					memory = R;
				} else if (path_t[i] == L) {
					path_t[i] = 8;
					memory = L;
				}
				if (j != 0 && path_s[j + 2] > 2 && path_t[j] == path_t[j + 1]) {
					if (path_t[j] == R) {
						path_t[j + 1] = 9;
						check2 = true;
					} else if (path_t[j] == L) {
						path_t[j + 1] = 10;
						check2 = true;
					}
					path_s[j + 1] = check + 1;
				} else {
					if (!a1) {
						if (path_s[j + 1] > 2) {
							if (path_t[j] == R) {
								path_t[j] = 7;
							} else if (path_t[j] == L) {
								path_t[j] = 8;
							}
							path_s[j] = check + 1;
						} else {
							path_t[i] = memory;
							check3 = false;
							check2 = false;
							i = j;
							i++;
							continue;
						}
					} else {
						if (path_t[j] == R) {
							path_t[j] = 7;
						} else if (path_t[j] == L) {
							path_t[j] = 8;
						}
						path_s[j] = check + 1;
					}
				}
			}
			if (check3) {
				for (int k = i; k < j; k++) {
					path_t[k] = 254;
				}
			} else {
				for (int k = i + 1; k < j; k++) {
					path_t[k] = 254;
				}
			}
			if (check2) {
				path_t[j] = 254;
			}
			check3 = false;
			check2 = false;
			i = j;
		}
		i++;
	}
	i = 0;

	while (path_t[i] != 0) {
		if (path_t[i] == 7 && path_t[i + 1] == 7 && path_s[i + 1] == 2) {
			path_t[i] = 11;
			path_t[i + 1] = 254;
		}
		if (path_t[i] == 8 && path_t[i + 1] == 8 && path_s[i + 1] == 2) {
			path_t[i] = 12;
			path_t[i + 1] = 254;
		}
		i++;
	}
	i = 0;
	diaMode = false;
	while (path_t[i] != 0) {
		if (!diaMode) {
			if (path_t[i] == 7 || path_t[i] == 8 || path_t[i] == 9
					|| path_t[i] == 10) {
				path_s[i] -= 1;
				diaMode = true;
			}
		} else if (diaMode) {
			if (path_t[i] == 7 || path_t[i] == 8 || path_t[i] == 9
					|| path_t[i] == 10) {
				path_s[i + 1] -= 1;
				diaMode = false;
			}
		}
		i++;
	}
	pathOffset();
//TODO APEC対応でコメントアウト中
//	if (isFull) {
//		i = 0;
//		for (i = 0; i < 255; i++) {
//			if (i > 0 && path_t[i] == 255 && path_s[i] == 1) {
//				if (path_t[i - 1] == 7 || path_t[i - 1] == 8) {
//					path_t[i - 1] = 255;
//					path_s[i - 1] += 1;
//				}
//			}
//			if (path_t[i] == 255) {
//				break;
//			}
//		}
//	}
}
void checkOtherRoot(int x, int y, int now);
void updateVectorMap(int x, int y, char isSearch, char isFull);
void vetorPathCreate(int Gx, int Gy, char isFull) {
	int next_dir = now_dir;
	int nextMotion = 0;
	int p = 0;
	int dirLog[3];
	char b1 = false;
	char b2 = false;
	deadEnd(Gx, Gy);
	pathClear();
	// updateVectorMap(goalX, goalY, false, isFull);
	updateVectorMap(Gx, Gy, false, isFull);
	path_s[0] += 1;
	while (true) {
		now_dir = next_dir;
		dirLog[2] = dirLog[1];
		dirLog[1] = dirLog[0];
		dirLog[0] = now_dir;
		Value = MAX;
		nextDirection = 255;
		if ((Gx == 7 && Gy == 7) || (Gx == 7 && Gy == 8) || (Gx == 8 && Gy == 7)
				|| (Gx == 8 && Gy == 8)) {
			if ((x == Gx && y == Gy) || (x == Gx + 1 && y == Gy)
					|| (x == Gx && y == Gy + 1)
					|| (x == Gx + 1 && y == Gy + 1)) {
				b1 = true;
			}
		} else {
			if ((x == Gx && y == Gy)) {
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
		if (nextDirection != 255) {
			nextMotion = setNextMotion(nextDirection);
		} else {
			nextMotion = Back;
		}
		checkOtherRoot(x, y, position);
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
	}
//	path_s[p] += 1;
}
#endif /* VECTORPATH_H_ */
