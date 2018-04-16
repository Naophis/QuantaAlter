volatile void deadEnd(char x, char y);
volatile void setDefaultData();
volatile void setNextRootDirectionPath(int x, int y, int dir);
volatile void priorityStraight(int x, int y, int dir);
volatile void priorityStraight2(int x, int y, int dir);
int setNextRootDirectionPath2(int x, int y, int dir);
char setNextRootDirection(int x, int y, int dir);
volatile void setNextRootDirectionPath3(int x, int y, int dir);
int setNextRootDirectionPath4(int x, int y, int dir);
int setNextRootDirectionPath5(int x, int y, int dir);
int getWallData(int x, int y);
int getDist(int x, int y);
int getDistVector(int x, int y, int v);
int getDistVector2(int x, int y, int v);
char isDead(int x, int y);
int getWall(int x, int y);
char isStep(int x, int y, int dir);
char isStepped(int x, int y);
char isUnknown(int x, int y, int dir);
char isFullStepped(int x, int y);
char candicateDead(int x, int y);
volatile void clearVectorMap(int x, int y, char isFull);
volatile void clearVectorMap2(int x, int y);
char isProceed(int x, int y, int dir);
volatile void setNextDirection(int x, int y, int x2, int y2, int dir);

void updateDist(int x, int y, int mode, char isFull);
char notWall_isMin(int x, int y, int dir, int min);
char isMin(int x, int y, int dir, int min);
char isMax(int x, int y, int dir);
char haveVector(int x, int y, int dir);
char suggestUpd(int x1, int y1, int x2, int y2, int dir);
volatile void setVector(int x, int y, int dir, int val);
//volatile void quickVectorUpdate(int x, int y);
volatile void quickUpdate(int x, int y);
char up(int x, int y, int dir, char b, int value);
volatile void mapSum();
//volatile void step(int x, int y, int dir, char isWall);
volatile void updateWall(int x, int y, int dir);

int position = 0;
const int MIN = 0;
char block = false;
#define ILLEGAL_ARGUMENT  255
volatile void setDefaultData() {
	int i = 0;
	for (i = 0; i < 16; i++) {
		map[i][15] |= 0x11;
		map[15][i] |= 0x22;
		map[0][i] |= 0x44;
		map[i][0] |= 0x88;
	}
	map[0][0] |= 0xf0;
	map[0][0] |= 0x02;
	map[1][0] |= 0x04;
}
char existWall(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return true;
	return ((map[x][y] / dir) & 0x01) == 0x01;
}
char isStep(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return false;
	return ((map[x][y] / dir) & 0x10) == 0x10;
}
char isStepped(int x, int y) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return true;
	return (map[x][y] & 0xf0) == 0xf0;
}
volatile void step(int x, int y, int dir, char isWall) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE) {
		return;
	}
	map[x][y] |= (0x10 * dir);
	if (isWall) {
		map[x][y] |= 0x01 * dir;
	} else {
		map[x][y] = (map[x][y] & 0xf0) | (map[x][y] & (~(0x01 * dir) & 0x0f));
	}
}

int getDistVector(int x, int y, int v) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return MAX;
	if (existWall(x, y, v))
		return MAX;
	if (v == North) {
		return m[x][y].n;
	}
	if (v == East) {
		return m[x][y].e;
	}
	if (v == West) {
		return m[x][y].w;
	}
	if (v == South) {
		return m[x][y].s;
	}
	return MAX;
}
char isMin(int x, int y, int dir, int min) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return false;
	if (dir == North) {
		return m[x][y].n == min;
	} else if (dir == East) {
		return m[x][y].e == min;
	} else if (dir == West) {
		return m[x][y].w == min;
	} else if (dir == South) {
		return m[x][y].s == min;
	}
	return false;
}

char isMax(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return false;
	if (dir == North) {
		return m[x][y].n == MAX;
	} else if (dir == East) {
		return m[x][y].e == MAX;
	} else if (dir == West) {
		return m[x][y].w == MAX;
	} else if (dir == South) {
		return m[x][y].s == MAX;
	}
	return false;
}
char up(int x, int y, int dir, char b, int value) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE) {
		return !b;
	}

	if (dir == North) {
		if (m[x][y].n <= value) {
			return false;
		}
		m[x][y].n = value;
		y++;
		dir = South;
	} else if (dir == East) {
		if (m[x][y].e <= value) {
			return false;
		}
		m[x][y].e = value;
		x++;
		dir = West;
	} else if (dir == West) {
		if (m[x][y].w <= value) {
			return false;
		}
		m[x][y].w = value;
		x--;
		dir = East;
	} else if (dir == South) {
		if (m[x][y].s <= value) {
			return false;
		}
		m[x][y].s = value;
		y--;
		dir = North;
	}
	if (b) {
		return up(x, y, dir, false, value);
	}
	return true;
}

volatile void setNextRootDirectionPath(int x, int y, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MAX : getDistVector(x, y, dir);
	if (now_dir * dir == 8)
		return;
	if (!isWall && dist < Value) {
		nextDirection = dir;
		Value = dist;
	}
	if (!isWall && step && dist >= position) {
	}
}

volatile void priorityStraight(int x, int y, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MAX : getDistVector(x, y, dir);
	if (now_dir * dir == 8)
		return;
	if (!isWall && step) {
		nextDirection = dir;
		Value = dist;
	}
}

volatile void priorityStraight2(int x, int y, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MAX : getDistVector(x, y, dir);
	if (now_dir * dir == 8)
		return;
	if (!isWall && step && dist <= Value) {
		nextDirection = dir;
		Value = dist;
	}
}

int setNextRootDirectionPath2(int x, int y, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MIN : getDistVector(x, y, dir);
	if (now_dir * dir == 8)
		return 0;
	if (!isWall && dist >= Value) {
		nextDirection = dir;
		Value = dist;
		block = true;
		return 1;
	}
	return 0;
}

char setNextRootDirection(int x, int y, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MIN : getDistVector(x, y, dir);
	if (now_dir * dir == 8)
		return false;
	if (!isWall && step) {
		nextDirection = dir;
		Value = dist;
		return true;
	}
	return false;
}

volatile void setNextRootDirectionPath3(int x, int y, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MAX : getDistVector(x, y, dir);
	if (now_dir * dir == 8)
		return;
	if (!isWall && dist < Value) {
		nextDirection = dir;
		Value = dist;
		block = true;
	}
	if (!isWall && step && dist >= position) {
		// updateWall(x, y, dir);
	}
}

int setNextRootDirectionPath4(int x, int y, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MIN : getDistVector(x, y, dir);
	if (now_dir * dir == 8)
		return 0;
	if (!isWall && step) {
		block = true;
		return 1;
	}
	return 0;
}

int setNextRootDirectionPath5(int x, int y, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MIN : getDistVector(x, y, dir);
	if (now_dir * dir == 8)
		return 0;
	if (!isWall && step) {
		nextDirection = dir;
		Value = dist;
		block = true;
		return 1;
	}
	return 0;
}

int getWallData(int x, int y) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return ILLEGAL_ARGUMENT;
	return map[x][y];
}

int getDist(int x, int y) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return ILLEGAL_ARGUMENT;
	return dist[x][y];
}

char isDead(int x, int y) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return true;
	return dist[x][y] == ILLEGAL_ARGUMENT;
}

int getWall(int x, int y) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return ILLEGAL_ARGUMENT;
	return map[x][y];
}

char stepped(int x, int y) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return true;
	return (map[x][y] & 0xf0) == 0xf0;
}

char isUnknown(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return true;
	return (map[x][y] & (0x10 * dir)) == 0x00;
}

char isFullStepped(int x, int y) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return true;
	return (map[x][y] & 0xf0) == 0xf0;
}

char candicateDead(int x, int y) {
	char temp = map[x][y] & 0x0f;
	return (temp == 0x0e || temp == 0x0d || temp == 0x0b || temp == 0x07);
}

volatile void clearVectorMap(int x, int y, char isFull) {
	char i = 0;
	char j = 0;
	for (i = 0; i < MAZE_SIZE; i++) {
		for (j = 0; j < MAZE_SIZE; j++) {
			dist[i][j] = ILLEGAL_ARGUMENT;
			m[i][j].n = MAX;
			m[i][j].e = MAX;
			m[i][j].w = MAX;
			m[i][j].s = MAX;
			m[i][j].v = 0;
			m[i][j].N1 = 0;
			m[i][j].NE = 0;
			m[i][j].NW = 0;
			m[i][j].E1 = 0;
			m[i][j].SE = 0;
			m[i][j].S1 = 0;
			m[i][j].SW = 0;
			m[i][j].W1 = 0;
		}
	}

	for (i = 0; i < (isFull ? 2 : 1); i++) {
		for (j = 0; j < (isFull ? 2 : 1); j++) {
			if (!existWall(x + i, y + j, North)) {
				m[x + i][y + j].n = 0;
				if (y + j < 15) {
					m[x + i][y + 1 + j].s = 0;
				}
			}
			if (!existWall(x + i, y + j, East)) {
				m[x + i][y + j].e = 0;
				if (x + i < 15) {
					m[x + 1 + i][y + j].w = 0;
				}
			}
			if (!existWall(x + i, y + j, West)) {
				m[x + i][y + j].w = 0;
				if (x + i > 0) {
					m[x - 1 + i][y + j].e = 0;
				}
			}
			if (!existWall(x + i, y + j, South)) {
				m[x + i][y + j].s = 0;
				if (y + j > 0) {
					m[x + i][y - 1 + j].n = 0;
				}
			}
		}
	}
	dist[x][y] = 0;
}

volatile void clearVectorMap2(int x, int y) {
	char a = 1;
	char i = 0;
	char j = 0;
	for (i = 0; i < MAZE_SIZE; i++) {
		for (j = 0; j < MAZE_SIZE; j++) {
			m[i][j].n = MAX;
			m[i][j].e = MAX;
			m[i][j].w = MAX;
			m[i][j].s = MAX;
		}
	}
	a = 1;
	if ((x == 7 && y == 7) || (x == 7 && y == 8) || (x == 8 && y == 7)
			|| (x == 8 && y == 8)) {
		a = 2;
		x = 7;
		y = 7;
	} else {
		a = 1;
	}
	for (i = 0; i < a; i++) {
		for (j = 0; j < a; j++) {
			if (!existWall(x + i, y + j, North)) {
				m[x + i][y + j].n = 0;
				if (y + j < 15) {
					m[x + i][y + 1 + j].s = 0;
				}
			}
			if (!existWall(x + i, y + j, East)) {
				m[x + i][y + j].e = 0;
				if (x + i < 15) {
					m[x + 1 + i][y + j].w = 0;
				}
			}
			if (!existWall(x + i, y + j, West)) {
				m[x + i][y + j].w = 0;
				if (x + i > 0) {
					m[x - 1 + i][y + j].e = 0;
				}
			}
			if (!existWall(x + i, y + j, South)) {
				m[x + i][y + j].s = 0;
				if (y + j > 0) {
					m[x + i][y - 1 + j].n = 0;
				}
			}
		}
	}
	dist[x][y] = 0;
}

char isProceed(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return false;
	return ((map[x][y] / dir) & 0x11) == 0x10;
}

int setNextMotion(int nextMotion) {
	if (now_dir == nextMotion)
		return Straight;
	switch (now_dir) {
	case North:
		if (nextMotion == East) {
			return Right;
		} else if (nextMotion == West) {
			return Left;
		}
		break;
	case East:
		if (nextMotion == South) {
			return Right;
		} else if (nextMotion == North) {
			return Left;
		}
		break;
	case West:
		if (nextMotion == North) {
			return Right;
		} else if (nextMotion == South) {
			return Left;
		}
		break;
	case South:
		if (nextMotion == West) {
			return Right;
		} else if (nextMotion == East) {
			return Left;
		}
		break;
	}
	return Back;
}

int setNewPosition(int dir) {
	if (dir == 255) {
		if (now_dir == North) {
			dir = South;
		} else if (now_dir == East) {
			dir = West;
		} else if (now_dir == West) {
			dir = East;
		} else if (now_dir == South) {
			dir = North;
		}
	}
	if (dir == North) {
		y++;
	} else if (dir == East) {
		x++;
	} else if (dir == West) {
		x--;
	} else if (dir == South) {
		y--;
	}

	return dir;
}

volatile void setNextDirection(int x, int y, int x2, int y2, int dir) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x2, y2, dir);
	int dist = getDist(x2, y2);
	if (!isWall && !step && dist < Value) {
		nextDirection = dir;
		Value = dist;
		isKnown = false;
	} else if (!isWall && step && dist < Value) {
		nextDirection = dir;
		Value = dist;
		if (dir == now_dir) {
			isKnown = true;
		} else {
			isKnown = false;
		}
	}
}

void updateDist(int x, int y, int mode, char isFull) {
	char X = 0, Y = 0;
	int pt1;
	unsigned char q[257];
	char head, tail;
	char D = 1;
	short i = 0, j = 0;
	char b;
	q[0] = x * 16 + y;
	head = 0;
	tail = 1;
	clearMap(x, y, isFull);
	while (head != tail) {
		Y = q[head] & 0x0f;
		X = (q[head] & 0xf0) >> 4;
		head++;
		pt1 = dist[X][Y] + 1;
		D = 1;
		while (D <= 8) {
			i = 0;
			j = 0;
			if (D == North) {
				j = 1;
			} else if (D == East) {
				i = 1;
			} else if (D == West) {
				i = -1;
			} else if (D == South) {
				j = -1;
			}
			b = false;
			if (mode == 1) {
				b = isProceed(X, Y, D);
			} else {
				b = !existWall(X, Y, D);
			}
			if (b && getDist(X + i, Y + j) == ILLEGAL_ARGUMENT) {
				if (X + i < 0 || X + i >= MAZE_SIZE || Y + j < 0
						|| Y + j >= MAZE_SIZE) {
				} else {
					dist[X + i][Y + j] = pt1;
					q[tail] = ((X + i) << 4) | (Y + j);
					tail++;
				}
			}
			D *= 2;
		}
	}
}

char notWall_isMin(int x, int y, int dir, int min) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE) {
		return false;
	}
	return !existWall(x, y, dir) && isMin(x, y, dir, min);
}

char haveVector(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return false;
	return (m[x][y].v & (0x01 * dir)) == 0x01;
}

char suggestUpd(int x1, int y1, int x2, int y2, int dir) {
	if (x1 < 0 || x1 >= MAZE_SIZE || y1 < 0 || y1 >= MAZE_SIZE)
		return false;
	if (x2 < 0 || x2 >= MAZE_SIZE || y2 < 0 || y2 >= MAZE_SIZE)
		return false;
	if (dir == North) {
		return m[x2][y2].n > m[x1][y1].n;
	} else if (dir == East) {
		return m[x2][y2].e > m[x1][y1].e;
	} else if (dir == West) {
		return m[x2][y2].w > m[x1][y1].w;
	} else if (dir == South) {
		return m[x2][y2].s > m[x1][y1].s;
	}
	return false;
}

volatile void setVector(int x, int y, int dir, int val) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return;
	if (dir == North) {
		m[x][y].n = val;
	} else if (dir == East) {
		m[x][y].e = val;
	} else if (dir == West) {
		m[x][y].w = val;
	} else if (dir == South) {
		m[x][y].s = val;
	}
}

char updateVector(int x, int y, int dir, int min) {
	char b = false;
	int i = 0;
	int j = 0;
	if (dir == North) {
		j = 1;
	} else if (dir == East) {
		i = 1;
	} else if (dir == West) {
		i = -1;
	} else if (dir == South) {
		j = -1;
	}
	if (notWall_isMin(x, y, dir, min)) {
		if (dir * North != 8) {
			if (!existWall(x + i, y + j + 1, North)) {
				if (isMax(x + i, y + j, North)
						|| suggestUpd(x, y, x + i, y + j, North)) {
					b = true;
					if (haveVector(x + i, y + j, North)) {
						m[x + i][y + j].n = min + Dia;
						setVector(x + i, y + j + 1, South, m[x + i][y + j].n);
					} else {
						m[x + i][y + j].n = min + St1;
						setVector(x + i, y + j + 1, South, m[x + i][y + j].n);
					}
					m[x + i][y + j].v |= 0x01;
					m[x + i][y + j].v &= 0x07;
				}
			}
		}
		if (dir * East != 8) {
			if (!existWall(x + i + 1, y + j, East)) {
				if (isMax(x + i, y + j, East)
						|| suggestUpd(x, y, x + i, y + j, East)) {
					b = true;
					if (haveVector(x + i, y + j, East)) {
						m[x + i][y + j].e = min + Dia;
						setVector(x + i + 1, y + j, West, m[x + i][y + j].e);
					} else {
						m[x + i][y + j].e = min + St1;
						setVector(x + i + 1, y + j, West, m[x + i][y + j].e);
					}
					m[x + i][y + j].v |= 0x02;
					m[x + i][y + j].v &= 0x0b;
				}
			}
		}
		if (dir * West != 8) {
			if (!existWall(x + i - 1, y + j, East)) {
				if (isMax(x + i, y + j, West)
						|| suggestUpd(x, y, x + i, y + j, West)) {
					b = true;
					if (haveVector(x + i, y + j, West)) {
						m[x + i][y + j].w = min + Dia;
						setVector(x + i - 1, y + j, East, m[x + i][y + j].w);
					} else {
						m[x + i][y + j].w = min + St1;
						setVector(x + i - 1, y + j, East, m[x + i][y + j].w);
					}
					m[x + i][y + j].v |= 0x04;
					m[x + i][y + j].v &= 0x0d;
				}
			}
		}
		if (dir * South != 8) {
			if (!existWall(x + i, y + j - 1, South)) {
				if (isMax(x + i, y + j, South)
						|| suggestUpd(x, y, x + i, y + j, South)) {
					b = true;
					if (haveVector(x + i, y + j, South)) {
						m[x + i][y + j].s = min + Dia;
						setVector(x + i, y + j - 1, North, m[x + i][y + j].s);
					} else {
						m[x + i][y + j].s = min + St1;
						setVector(x + i, y + j - 1, North, m[x + i][y + j].s);
					}
					m[x + i][y + j].v |= 0x08;
					m[x + i][y + j].v &= 0x0e;
				}
			}
		}
	}
	return b;
}

volatile void quickUpdate(int x, int y) {
	char head = true;
	int min = 0;
	int c = 0;
	int d = 0;
	char b2 = true;
	int i = 0;
	int j = 0;
	clearVectorMap2(x, y);
	while (b2) {
		c++;
		head = false;
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				head |= updateVector(i, j, North, min);
				head |= updateVector(i, j, East, min);
				head |= updateVector(i, j, West, min);
				head |= updateVector(i, j, South, min);
			}
		}
		if (c == 100) {
			break;
		}
		if (head) {
			b2 = true;
			d = 0;
		} else {
			d++;
			if (d > 10) {
				b2 = false;
			}
		}
		min++;
	}
}

volatile void updateWall(int x, int y, int dir) {
	if (dir == North) {
		step(x, y, North, true);
		step(x, y + 1, South, true);
	} else if (dir == East) {
		step(x, y, East, true);
		step(x + 1, y, West, true);
	} else if (dir == West) {
		step(x, y, West, true);
		step(x - 1, y, East, true);
	} else if (dir == South) {
		step(x, y, South, true);
		step(x, y - 1, North, true);
	}
}

float R_WALL_EXIST = 600;  //探索時壁判定
float L_WALL_EXIST = 500;  //探索時壁判定
float FRONT_WALL_EXIST = 800; //探索時壁判定

volatile void wallJudge2(short dir, short X, short Y) {
	char wallN = 0, wallE = 0, wallW = 0, wallS = 0;
	if (dir == North) {
		wallW = LS_SEN45.now > L_WALL_EXIST;
		wallE = RS_SEN45.now > R_WALL_EXIST;
		wallN = Front_SEN.now > FRONT_WALL_EXIST;
	} else if (dir == East) {
		wallN = LS_SEN45.now > L_WALL_EXIST;
		wallS = RS_SEN45.now > R_WALL_EXIST;
		wallE = Front_SEN.now > FRONT_WALL_EXIST;
	} else if (dir == West) {
		wallS = LS_SEN45.now > L_WALL_EXIST;
		wallN = RS_SEN45.now > R_WALL_EXIST;
		wallW = Front_SEN.now > FRONT_WALL_EXIST;
	} else if (dir == South) {
		wallE = LS_SEN45.now > L_WALL_EXIST;
		wallW = RS_SEN45.now > R_WALL_EXIST;
		wallS = Front_SEN.now > FRONT_WALL_EXIST;
	}
	step(X, Y, North, wallN);
	step(X, Y + 1, South, wallN);
	step(X, Y, East, wallE);
	step(X + 1, Y, West, wallE);
	step(X, Y, West, wallW);
	step(X - 1, Y, East, wallW);
	step(X, Y, South, wallS);
	step(X, Y - 1, North, wallS);

	for (char i = 0; i < MAZE_SIZE; i++) {
		map[i][MAZE_SIZE - 1] |= 0x11;
		map[MAZE_SIZE - 1][i] |= 0x22;
		map[0][i] |= 0x44;
		map[i][0] |= 0x88;
	}
	map[0][0] |= 0x22;
	map[1][0] |= 0x44;

}

volatile void wallJudge3(short dir, short X, short Y) {
	char wallN = 0, wallE = 0, wallW = 0, wallS = 0;
	char wallN2 = 0, wallE2 = 0, wallW2 = 0, wallS2 = 0;
	frontCtrl();
	if (dir == North) {
		wallW = LS_SEN2.now > L_WALL_EXIST2;
		wallE = RS_SEN2.now > R_WALL_EXIST2;
		wallN = Front_SEN.now > FRONT_WALL_EXIST2;
		if (!wallW) {
			wallW2 = LS_SEN2.now > L_WALL_EXIST3;
			step(X - 1, Y, West, wallW2);
			step(X - 2, Y, East, wallW2);
		}
		if (!wallE) {
			wallE2 = RS_SEN2.now > R_WALL_EXIST3;
			step(X + 1, Y, East, wallE2);
			step(X + 2, Y, West, wallE2);
		}
		if (!wallN) {
			wallN2 = Front_SEN.now > FRONT_WALL_EXIST3;
			step(X, Y + 1, North, wallN2);
			step(X, Y + 2, South, wallN2);
		}

	} else if (dir == East) {
		wallN = LS_SEN2.now > L_WALL_EXIST2;
		wallS = RS_SEN2.now > R_WALL_EXIST2;
		wallE = Front_SEN.now > FRONT_WALL_EXIST2;
		if (!wallN) {
			wallN2 = LS_SEN2.now > L_WALL_EXIST3;
			step(X, Y + 1, North, wallN2);
			step(X, Y + 2, South, wallN2);
		}
		if (!wallS) {
			wallS2 = RS_SEN2.now > R_WALL_EXIST3;
			step(X, Y - 1, South, wallS2);
			step(X, Y - 2, North, wallS2);
		}
		if (!wallE) {
			wallE2 = Front_SEN.now > FRONT_WALL_EXIST3;
			step(X + 1, Y, East, wallE2);
			step(X + 2, Y, West, wallE2);
		}
	} else if (dir == West) {
		wallS = LS_SEN2.now > L_WALL_EXIST2;
		wallN = RS_SEN2.now > R_WALL_EXIST2;
		wallW = Front_SEN.now > FRONT_WALL_EXIST2;
		if (!wallS) {
			wallS2 = LS_SEN2.now > L_WALL_EXIST3;
			step(X, Y - 1, South, wallS2);
			step(X, Y - 2, North, wallS2);
		}
		if (!wallN) {
			wallN2 = RS_SEN2.now > R_WALL_EXIST3;
			step(X, Y + 1, North, wallN2);
			step(X, Y + 2, South, wallN2);
		}
		if (!wallW) {
			wallW2 = Front_SEN.now > FRONT_WALL_EXIST3;
			step(X - 1, Y, West, wallW2);
			step(X - 2, Y, East, wallW2);
		}
	} else if (dir == South) {
		wallE = LS_SEN2.now > L_WALL_EXIST2;
		wallW = RS_SEN2.now > R_WALL_EXIST2;
		wallS = Front_SEN.now > FRONT_WALL_EXIST2;
		if (!wallE) {
			wallE2 = LS_SEN2.now > L_WALL_EXIST3;
			step(X + 1, Y, East, wallE2);
			step(X + 2, Y, West, wallE2);
		}
		if (!wallW) {
			wallW2 = RS_SEN2.now > R_WALL_EXIST3;
			step(X - 1, Y, West, wallW2);
			step(X - 2, Y, East, wallW2);
		}
		if (!wallS) {
			wallS2 = Front_SEN.now > FRONT_WALL_EXIST3;
			step(X, Y - 1, South, wallS2);
			step(X, Y - 2, North, wallS2);
		}
	}
	step(X, Y, North, wallN);
	step(X, Y + 1, South, wallN);
	step(X, Y, East, wallE);
	step(X + 1, Y, West, wallE);
	step(X, Y, West, wallW);
	step(X - 1, Y, East, wallW);
	step(X, Y, South, wallS);
	step(X, Y - 1, North, wallS);

	for (char i = 0; i < MAZE_SIZE; i++) {
		map[i][MAZE_SIZE - 1] |= 0x11;
		map[MAZE_SIZE - 1][i] |= 0x22;
		map[0][i] |= 0x44;
		map[i][0] |= 0x88;
	}
	map[0][0] |= 0x22;
	map[1][0] |= 0x44;
}
float R_WALL_EXIST4 = 180;  //探索時壁判定
float L_WALL_EXIST4 = 180;  //探索時壁判定

volatile void wallJudge4(short dir, short X, short Y) {
	char wallN = 0, wallE = 0, wallW = 0, wallS = 0;
	char wallN2 = 0, wallE2 = 0, wallW2 = 0, wallS2 = 0;
	char wallN3 = 0, wallE3 = 0, wallW3 = 0, wallS3 = 0;
	frontCtrl5();
	if (dir == North) {
		wallW = LS_SEN2.now > L_WALL_EXIST2;
		wallE = RS_SEN2.now > R_WALL_EXIST2;
		wallN = Front_SEN.now > FRONT_WALL_EXIST2;
		if (!wallW) {
			wallW2 = LS_SEN2.now > L_WALL_EXIST3;
			step(X - 1, Y, West, wallW2);
			step(X - 2, Y, East, wallW2);

			wallW3 = LS_SEN45.now > L_WALL_EXIST4;
			step(X - 1, Y, North, wallW3);
			step(X - 1, Y + 1, South, wallW3);
		}
		if (!wallE) {
			wallE2 = RS_SEN2.now > R_WALL_EXIST3;
			step(X + 1, Y, East, wallE2);
			step(X + 2, Y, West, wallE2);

			wallE3 = RS_SEN45.now > R_WALL_EXIST4;
			step(X + 1, Y, North, wallE3);
			step(X + 1, Y + 1, South, wallE3);
		}
		if (!wallN) {
			wallN2 = Front_SEN.now > FRONT_WALL_EXIST3;
			step(X, Y + 1, North, wallN2);
			step(X, Y + 2, South, wallN2);
		}

	} else if (dir == East) {
		wallN = LS_SEN2.now > L_WALL_EXIST2;
		wallS = RS_SEN2.now > R_WALL_EXIST2;
		wallE = Front_SEN.now > FRONT_WALL_EXIST2;
		if (!wallN) {
			wallN2 = LS_SEN2.now > L_WALL_EXIST3;
			step(X, Y + 1, North, wallN2);
			step(X, Y + 2, South, wallN2);

			wallN3 = LS_SEN45.now > L_WALL_EXIST4;
			step(X, Y + 1, East, wallN3);
			step(X + 1, Y + 1, West, wallN3);
		}
		if (!wallS) {
			wallS2 = RS_SEN2.now > R_WALL_EXIST3;
			step(X, Y - 1, South, wallS2);
			step(X, Y - 2, North, wallS2);

			wallS3 = RS_SEN45.now > R_WALL_EXIST4;
			step(X, Y - 1, East, wallS3);
			step(X + 1, Y - 1, West, wallS3);
		}
		if (!wallE) {
			wallE2 = Front_SEN.now > FRONT_WALL_EXIST3;
			step(X + 1, Y, East, wallE2);
			step(X + 2, Y, West, wallE2);
		}
	} else if (dir == West) {
		wallS = LS_SEN2.now > L_WALL_EXIST2;
		wallN = RS_SEN2.now > R_WALL_EXIST2;
		wallW = Front_SEN.now > FRONT_WALL_EXIST2;
		if (!wallS) {
			wallS2 = LS_SEN2.now > L_WALL_EXIST3;
			step(X, Y - 1, South, wallS2);
			step(X, Y - 2, North, wallS2);

			wallS3 = LS_SEN45.now > L_WALL_EXIST4;
			step(X, Y - 1, West, wallS3);
			step(X - 1, Y - 1, East, wallS3);
		}
		if (!wallN) {
			wallN2 = RS_SEN2.now > R_WALL_EXIST3;
			step(X, Y + 1, North, wallN2);
			step(X, Y + 2, South, wallN2);

			wallS3 = RS_SEN45.now > R_WALL_EXIST4;
			step(X, Y + 1, West, wallS3);
			step(X - 1, Y + 1, East, wallS3);
		}
		if (!wallW) {
			wallW2 = Front_SEN.now > FRONT_WALL_EXIST3;
			step(X - 1, Y, West, wallW2);
			step(X - 2, Y, East, wallW2);
		}
	} else if (dir == South) {
		wallE = LS_SEN2.now > L_WALL_EXIST2;
		wallW = RS_SEN2.now > R_WALL_EXIST2;
		wallS = Front_SEN.now > FRONT_WALL_EXIST2;
		if (!wallE) {
			wallE2 = LS_SEN2.now > L_WALL_EXIST3;
			step(X + 1, Y, East, wallE2);
			step(X + 2, Y, West, wallE2);

			wallE3 = LS_SEN45.now > L_WALL_EXIST4;
			step(X + 1, Y, South, wallE3);
			step(X + 1, Y - 1, North, wallE3);
		}
		if (!wallW) {
			wallW2 = RS_SEN2.now > R_WALL_EXIST3;
			step(X - 1, Y, West, wallW2);
			step(X - 2, Y, East, wallW2);

			wallS3 = RS_SEN45.now > R_WALL_EXIST4;
			step(X - 1, Y, South, wallS3);
			step(X - 1, Y - 1, North, wallS3);
		}
		if (!wallS) {
			wallS2 = Front_SEN.now > FRONT_WALL_EXIST3;
			step(X, Y - 1, South, wallS2);
			step(X, Y - 2, North, wallS2);
		}
	}
	step(X, Y, North, wallN);
	step(X, Y + 1, South, wallN);
	step(X, Y, East, wallE);
	step(X + 1, Y, West, wallE);
	step(X, Y, West, wallW);
	step(X - 1, Y, East, wallW);
	step(X, Y, South, wallS);
	step(X, Y - 1, North, wallS);

	for (char i = 0; i < MAZE_SIZE; i++) {
		map[i][MAZE_SIZE - 1] |= 0x11;
		map[MAZE_SIZE - 1][i] |= 0x22;
		map[0][i] |= 0x44;
		map[i][0] |= 0x88;
	}
	map[0][0] |= 0x22;
	map[1][0] |= 0x44;
}

volatile void deadEnd(char x, char y) {
	char head = true;
	return;
	while (head) {
		head = false;
		for (char i = 0; i < MAZE_SIZE; i++) {
			for (char j = 0; j < MAZE_SIZE; j++) {
				int temp = map[i][j] & 0x0f;
				if (i == 0 && j == 0) {
					continue;
				}
				if (i == x && j == y) {
					continue;
				}
				if (temp == 0x07) {
					updateWall(i, j, South);
					head = true;
				}
				if (temp == 0x0b) {
					updateWall(i, j, West);
					head = true;
				}
				if (temp == 0x0d) {
					updateWall(i, j, East);
					head = true;
				}
				if (temp == 0x0e) {
					updateWall(i, j, North);
					head = true;
				}
			}
		}
	}
}

