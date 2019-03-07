/*
 * Adachi.h
 *
 *  Created on: 2015/10/25
 *      Author: Naoto
 */
char saveFcu(uint32_t flash_addr);
//char saveFcuBlock(uint8_t brock);
char setNextRootDirectionPathUnKnown(int x, int y, int dir, int now) {
	char isWall = existWall(x, y, dir);
	char step = isStep(x, y, dir);
	int dist = isWall ? MAX : getDistVector(x, y, dir);
	if (now * dir == 8)
		return false;
	if (!isWall && dist < Value) {
		nextDirection = dir;
		Value = dist;
	}
	if (!isWall && step && dist >= position) {
	}
	return false;
}
void makeDesitiny(int x, int y) {
	char head = true;
	int min = 0;
	int c = 0;
	int d = 0;
	char bool2 = true;
	int val = 0;
	char i, j;
	clearVectorMap(x, y, false);
	while (bool2) {
		head = false;
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 16; j++) {
				if (m[0][0].n != MAX) {
					return;
				}
				c++;
				if (m[i][j].n == min) {
					head = true;
					if (!existWall(i, j + 1, North)) {
						val = m[i][j].N1 == 0 ? min + St1 : min + St2;
						val = m[i][j].N1 >= strBias ? min + St3 : val;
						if (up(i, j + 1, North, true, val)) {
							m[i][j + 1].N1 = m[i][j].N1 + 1;
						}
					}
					if (!existWall(i, j + 1, East)) {
						val = m[i][j].NE <= bias ? min + Dia : min + Dia2;
						val = m[i][j].NE > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, West)
								&& up(i, j + 1, East, true, val)) {
							m[i][j + 1].NE = m[i][j].NE + 1;
						} else if (up(i, j + 1, East, true, val)) {
							m[i][j + 1].NE = +1;
						}
					}
					if (!existWall(i, j + 1, West)) {
						val = m[i][j].NW <= bias ? min + Dia : min + Dia2;
						val = m[i][j].NW > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, East)
								&& up(i, j + 1, West, true, val)) {
							m[i][j + 1].NW = m[i][j].NW + 1;
						} else if (up(i, j + 1, West, true, val)) {
							m[i][j + 1].NW = +1;
						}
					}
				}
				if (m[i][j].e == min) {
					head = true;
					if (!existWall(i + 1, j, East)) {
						val = m[i][j].E1 == 0 ? min + St1 : min + St2;
						val = m[i][j].E1 >= strBias ? min + St3 : val;
						if (up(i + 1, j, East, true, val)) {
							m[i + 1][j].E1 = m[i][j].E1 + 1;
						}
					}
					if (!existWall(i + 1, j, South)) {
						val = m[i][j].SE <= bias ? min + Dia : min + Dia2;
						val = m[i][j].SE > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, North)
								&& up(i + 1, j, South, true, val)) {
							m[i + 1][j].SE = m[i][j].SE + 1;
						} else if (up(i + 1, j, South, true, val)) {
							m[i + 1][j].SE = +1;
						}
					}
					if (!existWall(i + 1, j, North)) {
						val = m[i][j].NE <= bias ? min + Dia : min + Dia2;
						val = m[i][j].NE > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, South)
								&& up(i + 1, j, North, true, val)) {
							m[i + 1][j].NE = m[i][j].NE + 1;
						} else if (up(i + 1, j, North, true, val)) {
							m[i + 1][j].NE = +1;
						}
					}
				}
				if (m[i][j].w == min) {
					head = true;
					if (!existWall(i - 1, j, West)) {
						val = m[i][j].W1 == 0 ? min + St1 : min + St2;
						val = m[i][j].W1 >= strBias ? min + St3 : val;
						if (up(i - 1, j, West, true, val)) {
							m[i - 1][j].W1 = m[i][j].W1 + 1;
						}
					}
					if (!existWall(i - 1, j, North)) {
						val = m[i][j].NW <= bias ? min + Dia : min + Dia2;
						val = m[i][j].NW > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, South)
								&& up(i - 1, j, North, true, val)) {
							m[i - 1][j].NW = m[i][j].NW + 1;
						} else if (up(i - 1, j, North, true, val)) {
							m[i - 1][j].NW = +1;
						}
					}
					if (!existWall(i - 1, j, South)) {
						val = m[i][j].SW <= bias ? min + Dia : min + Dia2;
						val = m[i][j].SW > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, North)
								&& up(i - 1, j, South, true, val)) {
							m[i - 1][j].SW = m[i][j].SW + 1;
						} else if (up(i - 1, j, South, true, val)) {
							m[i - 1][j].SW = +1;
						}
					}
				}
				if (m[i][j].s == min) {
					head = true;
					if (!existWall(i, j - 1, South)) {
						val = m[i][j].S1 == 0 ? min + St1 : min + St2;
						val = m[i][j].S1 >= strBias ? min + St3 : val;
						if (up(i, j - 1, South, true, val)) {
							m[i][j - 1].S1 = m[i][j].S1 + 1;
						}
					}
					if (!existWall(i, j - 1, West)) {
						val = m[i][j].SW <= bias ? min + Dia : min + Dia2;
						val = m[i][j].SW > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, East)
								&& up(i, j - 1, West, true, val)) {
							m[i][j - 1].SW = m[i][j].SW + 1;
						} else if (up(i, j - 1, West, true, val)) {
							m[i][j - 1].SW = +1;
						}
					}
					if (!existWall(i, j - 1, East)) {
						val = m[i][j].SE <= bias ? min + Dia : min + Dia2;
						val = m[i][j].SE > diaBias ? min + Dia3 : val;
						if (!existWall(i, j, West)
								&& up(i, j - 1, East, true, val)) {
							m[i][j - 1].SE = m[i][j].SE + 1;
						} else if (up(i, j - 1, East, true, val)) {
							m[i][j - 1].SE = +1;
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
void addVector(int x, int y, int dir, int val) {
	if (val < 15)
		val++;
	if (dir == North) {
		m[x][y].N1 = val;
	} else if (dir == NorthEast) {
		m[x][y].NE = val;
	} else if (dir == East) {
		m[x][y].E1 = val;
	} else if (dir == SouthEast) {
		m[x][y].SE = val;
	} else if (dir == South) {
		m[x][y].S1 = val;
	} else if (dir == SouthWest) {
		m[x][y].SW = val;
	} else if (dir == West) {
		m[x][y].W1 = val;
	} else if (dir == NorthWest) {
		m[x][y].NW = val;
	}
}
int borderLv1 = 0;
int borderLv2 = 2;
int borderLv1d = 0;
int borderLv2d = 2;

int haveVectorLv(int x, int y, int dir) {
	if (dir == North) {
		if (m[x][y].N1 > borderLv2) {
			return 2;
		} else if (m[x][y].N1 > borderLv1) {
			return 1;
		}
	} else if (dir == NorthEast) {
		if (m[x][y].NE > borderLv2d) {
			return 2;
		} else if (m[x][y].NE > borderLv1d) {
			return 1;
		}
	} else if (dir == East) {
		if (m[x][y].E1 > borderLv2) {
			return 2;
		} else if (m[x][y].E1 > borderLv1) {
			return 1;
		}
	} else if (dir == SouthEast) {
		if (m[x][y].SE > borderLv2d) {
			return 2;
		} else if (m[x][y].SE > borderLv1d) {
			return 1;
		}
	} else if (dir == South) {
		if (m[x][y].S1 > borderLv2) {
			return 2;
		} else if (m[x][y].S1 > borderLv1) {
			return 1;
		}
	} else if (dir == SouthWest) {
		if (m[x][y].SW > borderLv2d) {
			return 2;
		} else if (m[x][y].SW > borderLv1d) {
			return 1;
		}
	} else if (dir == West) {
		if (m[x][y].W1 > borderLv2) {
			return 2;
		} else if (m[x][y].W1 > borderLv1) {
			return 1;
		}
	} else if (dir == NorthWest) {
		if (m[x][y].NW > borderLv2d) {
			return 2;
		} else if (m[x][y].NW > borderLv1d) {
			return 1;
		}
	}
	return 0;
}
void simplesort(int tail) {
	for (int i = tail; i >= 0; i--) {
		if (que[i][2] < que[i - 1][2]) {
			int temp[3];
			temp[0] = que[i][0];
			temp[1] = que[i][1];
			temp[2] = que[i][2];
			que[i][0] = que[i - 1][0];
			que[i][1] = que[i - 1][1];
			que[i][2] = que[i - 1][2];
			que[i - 1][0] = temp[0];
			que[i - 1][1] = temp[1];
			que[i - 1][2] = temp[2];
		} else {
			break;
		}
	}
}
int MAX_VALUE = 8096;
int getDistV(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return MAX_VALUE;
	if (dir == North) {
		return m[x][y].n;
	} else if (dir == East) {
		return m[x][y].e;
	} else if (dir == West) {
		return m[x][y].w;
	} else if (dir == South) {
		return m[x][y].s;
	}
	return MAX_VALUE;
}
char isUpdated(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return true;
	if (dir == North) {
		return (updateMap[x][y] & 0x01) == 0x01;
	} else if (dir == East) {
		return (updateMap[x][y] & 0x02) == 0x02;
	} else if (dir == West) {
		return (updateMap[x][y] & 0x04) == 0x04;
	} else if (dir == South) {
		return (updateMap[x][y] & 0x08) == 0x08;
	} else if (dir == NorthEast) {
		return (updateMap[x][y] & 0x10) == 0x10;
	} else if (dir == SouthEast) {
		return (updateMap[x][y] & 0x20) == 0x20;
	} else if (dir == SouthWest) {
		return (updateMap[x][y] & 0x40) == 0x40;
	} else if (dir == NorthWest) {
		return (updateMap[x][y] & 0x80) == 0x80;
	}
	return false;
}
void setDistV(int x, int y, int dir, int val) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE) {
	}
	if (dir == North) {
		m[x][y].n = val;
		if (y < MAZE_SIZE - 1) {
			m[x][y + 1].s = val;
		}
	} else if (dir == East) {
		m[x][y].e = val;
		if (x < MAZE_SIZE - 1) {
			m[x + 1][y].w = val;
		}
	} else if (dir == West) {
		m[x][y].w = val;
		if (x > 0) {
			m[x - 1][y].e = val;
		}
	} else if (dir == South) {
		m[x][y].s = val;
		if (y > 0) {
			m[x][y - 1].n = val;
		}
	}
}
void updateMapCheck(int x, int y, int dir) {
	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE)
		return;
	if (dir == North) {
		updateMap[x][y] |= 0x01;
	} else if (dir == East) {
		updateMap[x][y] |= 0x02;
	} else if (dir == West) {
		updateMap[x][y] |= 0x04;
	} else if (dir == South) {
		updateMap[x][y] |= 0x08;
	} else if (dir == NorthEast) {
		updateMap[x][y] |= 0x10;
	} else if (dir == SouthEast) {
		updateMap[x][y] |= 0x20;
	} else if (dir == SouthWest) {
		updateMap[x][y] |= 0x40;
	} else if (dir == NorthWest) {
		updateMap[x][y] |= 0x80;
	}
}
int getVector(int x, int y, int dir) {
	if (dir == North) {
		return m[x][y].N1;
	} else if (dir == NorthEast) {
		return m[x][y].NE;
	} else if (dir == East) {
		return m[x][y].E1;
	} else if (dir == SouthEast) {
		return m[x][y].SE;
	} else if (dir == South) {
		return m[x][y].S1;
	} else if (dir == SouthWest) {
		return m[x][y].SW;
	} else if (dir == West) {
		return m[x][y].W1;
	} else if (dir == NorthWest) {
		return m[x][y].NW;
	}
	return 0;
}
void updateVectorMap(int x, int y, char isSearch, char isFull) {
	int head = 0;
	int tail = clearMap(x, y, isFull);
	int c = 0;
	while (head != tail) {
		int X = (que[head][0] & 0xf0) >> 4;
		int Y = (que[head][0] & 0x0f);
		int dir = que[head][1];
		int i = 0;
		int j = 0;
		int d[3];
		int d2[3];
		int now = getDistV(X, Y, dir);
		if (dir == North) {
			j = 1;
			d[0] = North; // N
			d[1] = NorthEast; // NE
			d[2] = NorthWest; // NW
			d2[0] = North; // N
			d2[1] = East; // E
			d2[2] = West; // W
		} else if (dir == East) {
			i = 1;
			d[0] = East; // E
			d[1] = SouthEast; // SE
			d[2] = NorthEast; // NE
			d2[0] = East; // E
			d2[1] = South; // S
			d2[2] = North; // N
		} else if (dir == West) {
			i = -1;
			d[0] = West; // W
			d[1] = NorthWest; // NW
			d[2] = SouthWest; // SW
			d2[0] = West; // W
			d2[1] = North; // N
			d2[2] = South; // S
		} else if (dir == South) {
			j = -1;
			d[0] = South; // S
			d[1] = SouthWest; // SW
			d[2] = SouthEast; // SE
			d2[0] = South; // S
			d2[1] = West; // W
			d2[2] = East; // E
		}
		// c++;
		for (int k = 0; k < 3; k++) {
			c++;
			if (!existWall(X + i, Y + j, d2[k])
					&& (isSearch || isStep(X + i, Y + j, d2[k]))) {
				int v = haveVectorLv(X, Y, d[k]);
				int tmp = now;
				if (dir == d2[k]) {
					if (v >= 2) {
						tmp += St3;
					} else if (v == 1) {
						tmp += St2;
					} else {
						tmp += St1;
					}
					if (tmp <= getDistV(X + i, Y + j, d2[k])) {
						if (!isUpdated(X + i, Y + j, d2[k])) {
							setDistV(X + i, Y + j, d2[k], tmp);
							que[tail][0] = (X + i) * 16 + (Y + j);
							que[tail][1] = d2[k];
							que[tail][2] = tmp;
							simplesort(tail);
							tail++;
							updateMapCheck(X + i, Y + j, d2[k]);
						}
					}
					addVector(X + i, Y + j, d[k], getVector(X, Y, d[k]));
				} else {
					if (v == 2) {
						tmp += Dia3;
					} else if (v == 1) {
						tmp += Dia2;
					} else {
						tmp += Dia;
					}
					if (tmp <= getDistV(X + i, Y + j, d2[k])) {
						if (!isUpdated(X + i, Y + j, d2[k])) {
							setDistV(X + i, Y + j, d2[k], tmp);
							que[tail][0] = (X + i) * 16 + (Y + j);
							que[tail][1] = d2[k];
							que[tail][2] = tmp;
							simplesort(tail);
							tail++;
							updateMapCheck(X + i, Y + j, d2[k]);
						}
					}
					addVector(X + i, Y + j, d[k], getVector(X, Y, d[k]));
				}
			}
		}
		head++;
	}
}
int searchGoalPosition(int Gx, int Gy, char isSearch, char isFull) {
	int next_dir = North;
	int now_dir = North;
	int x = 0;
	int y = 0;
	int goal = 0;
	char mode = false;
	updateVectorMap(Gx, Gy, isSearch, isFull);
	while (true) {
		now_dir = next_dir;
		Value = MAX;
		nextDirection = 255;
		if ((x == Gx && y == Gy)) {
			return goal;
		}
		if (isFull) {
			if ((x == Gx + 1 && y == Gy + 1)) {
				return goal;
			}
			if ((x == Gx + 0 && y == Gy + 1)) {
				return goal;
			}
			if ((x == Gx + 1 && y == Gy + 0)) {
				return goal;
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
		setNextRootDirectionPathUnKnown(x, y, North, now_dir);
		setNextRootDirectionPathUnKnown(x, y, East, now_dir);
		setNextRootDirectionPathUnKnown(x, y, West, now_dir);
		setNextRootDirectionPathUnKnown(x, y, South, now_dir);
		if (mode) {
			if (nextDirection == North) {
				if (!isStepped(x, y + 1))
					goal = x << 4 | (y + 1);
			} else if (nextDirection == East) {
				if (!isStepped(x + 1, y))
					goal = (x + 1) << 4 | y;
			} else if (nextDirection == West) {
				if (!isStepped(x - 1, y))
					goal = (x - 1) << 4 | y;
			} else if (nextDirection == South) {
				if (!isStepped(x, y - 1))
					goal = x << 4 | (y - 1);
			}
		} else {
			if (nextDirection == North) {
				if (isUnknown(x, y, North))
					goal = x << 4 | (y + 1);
			} else if (nextDirection == East) {
				if (isUnknown(x, y, East))
					goal = (x + 1) << 4 | y;
			} else if (nextDirection == West) {
				if (isUnknown(x, y, West))
					goal = (x - 1) << 4 | y;
			} else if (nextDirection == South) {
				if (isUnknown(x, y, South))
					goal = x << 4 | (y - 1);
			}
		}
		if (nextDirection == North) {
			y++;
		} else if (nextDirection == East) {
			x++;
		} else if (nextDirection == West) {
			x--;
		} else if (nextDirection == South) {
			y--;
		}
		next_dir = nextDirection;
	}
}

int distiny2(int x, int y, char isFull) {
	short X = 0, Y = 0;
	unsigned char q[257];
	short head, tail;
	short pt1;
	char D = 1;
	short i = 0, j = 0;
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
		i = 0, j = 0;
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
			if (!existWall(X, Y, D) && isDead(X + i, Y + j)) {
				if (X + i < 0 || X + i >= MAZE_SIZE || Y + j < 0
						|| Y + j >= MAZE_SIZE) {
				} else {
					dist[X + i][Y + j] = pt1;
					q[tail] = ((X + i) << 4) | (Y + j);
					tail++;
					if (isUnknown(X + i, Y + j, D) && !isDead(X + i, Y + j)) {
//					if (isFullStepped(X + i, Y + j) && !isDead(X + i, Y + j)) {
						return ((X + i) << 4) | (Y + j);
					}
				}
			}
			D *= 2;
		}
	}
	return 0;
}
char setNewPositionDummy(int x, int y, int dir) {
//	return false;
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
		return false;
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
	return isStepped(x, y);
}
char checkSearchVector(int Gx, int Gy, int dir) {
	if (Gx < 0 || Gx >= MAZE_SIZE || Gy < 0 || Gy >= MAZE_SIZE) {
		return false;
	}
	if (dir == North) {
		return y < Gy;
	} else if (dir == East) {
		return x < Gx;
	} else if (dir == West) {
		return x > Gx;
	} else if (dir == South) {
		return y > Gy;
	}
	return false;
}

volatile int motionLog[motionLogLength][5];

volatile int motionLogCount = 0;

void pushMotionLog(int x, int y, int dist, int wall, int dir) {
	motionLog[motionLogCount][0] = x;
	motionLog[motionLogCount][1] = y;
	motionLog[motionLogCount][2] = dist;
	motionLog[motionLogCount][3] = wall;
	motionLog[motionLogCount][4] = dir;
	motionLogCount++;
}

volatile void showMotionLog() {
	int x = 0, y = 0, dist = 0, wall = 0, dir = 0;
	for (int i = 0; i < motionLogLength; i++) {
		x = motionLog[i][0];
		y = motionLog[i][1];
		dist = motionLog[i][2];
		wall = motionLog[i][3];
		dir = motionLog[i][4];
		myprintf("(%d,%d)\t%d\t%d\t%d\t%d\r\n", x, y, dist, wall, dir);
	}
}

char Adachi2(int GoalX, int GoalY, char Zen, char isFull, char Mode) {
	char known = false;
	char next_dir = now_dir;
	char nextMotion = 0;
	char check = 1;
	char backFlg = 0;
	char goal = 0;
	char firstGoalX = GoalX;
	char firstGoalY = GoalY;
	char limit = 16;
	char lock = false;
	char skip = false;
	char lastMotion = Straight;
	char oflg = true;
	char tmpSave = false;
	char goaled = false;
	int p = 0;

	float velocity = *(float *) 1049320;
	float velocity2 = *(float *) 1049332;
	float acc = *(float *) 1049324;
	float diac = *(float *) 1049328;

	if (Mode == true) {
		velocity = 1000;
		velocity2 = 1500;
		acc = 5000;
		diac = 6000;
	} else {
		velocity = 500;
		velocity2 = 1500;
		acc = 5000;
		diac = 6000;
	}

	map[0][0] |= 0xf0;
	updateDist(GoalX, GoalY, 0, isFull);
//	back(-100, -2000, 60, 0);
	gyroZeroCheck(false);
	if (velocity >= 1000) {
		sensingMode = SearchMode;
		startVacume2(70);
	}
	mtu_start();

	runForWallOff(velocity, acc, 90.0 + 56, 1);

	next_dir = direction(now_dir, Straight);
	while (true) {
		now_dir = next_dir;
		if (known == false) {
			wallJudge4(now_dir, x, y);
			map[x][y] |= 0xf0;
			time = 0;
			updateDist(GoalX, GoalY, 0, isFull);
		}
		Value = 255;
		nextDirection = 255;
		if (Zen == Kata) {
			lock = true;
			if (GoalX == x && GoalY == y) {
				goaled = true;
			}
		} else if (Zen == Oufuku) {
			if (oflg) {
				if (firstGoalX == x && firstGoalY == y) {
					GoalX = 0;
					GoalY = 0;
					oflg = false;
				}
			} else {
				lock = true;
				if (GoalX == x && GoalY == y) {
					goaled = true;
				}
			}
		} else {
			if (GoalX == 0 && GoalY == 0) {
				Zen = Oufuku;
				oflg = false;
//				lock = true;
				if (GoalX == x && GoalY == y) {
					goaled = true;
				}
			}
			if (!skip && isStepped(firstGoalX, firstGoalY) && !known) {
				oflg = false;
				if (lock) {
					if ((isStepped(GoalX, GoalY) || candicateDead(GoalX, GoalY))) {
						lock = false;
//						goal = distiny2(x, y, isFull);
						goal = searchGoalPosition(firstGoalX, firstGoalY, true,
								isFull);
						GoalX = (goal & 0xf0) >> 4;
						GoalY = goal & 0x0f;
						updateDist(GoalX, GoalY, 0, isFull);
						if (GoalX == 0 && GoalY == 0) {
							lock = true;
//							break;
							continue;
						}
					}
				} else {
					if (lastMotion == Back && !lock) {
					} else {
						if ((isStepped(GoalX, GoalY)
								|| candicateDead(GoalX, GoalY)
								|| dist[x][y] > limit)) {
							lock = false;
//							goal = distiny2(x, y, isFull);
							goal = searchGoalPosition(firstGoalX, firstGoalY,
									true, isFull);
							GoalX = (goal & 0xf0) >> 4;
							GoalY = goal & 0x0f;
							updateDist(GoalX, GoalY, 0, isFull);
							if (GoalX == 0 && GoalY == 0) {
								lock = true;
								continue;
							}
						}
					}
				}
			}
		}

		if (goaled) {
//			break;
		}
		skip = false;

		if ((checkSearchVector(GoalX, GoalY, now_dir) || dist[x][y] > 15)) {
			if (now_dir == North) {
				setNextDirection(x, y, x, y + 1, North);
				setNextDirection(x, y, x + 1, y, East);
				setNextDirection(x, y, x - 1, y, West);
				setNextDirection(x, y, x, y - 1, South);
			} else if (now_dir == East) {
				setNextDirection(x, y, x + 1, y, East);
				setNextDirection(x, y, x, y - 1, South);
				setNextDirection(x, y, x, y + 1, North);
				setNextDirection(x, y, x - 1, y, West);
			} else if (now_dir == West) {
				setNextDirection(x, y, x - 1, y, West);
				setNextDirection(x, y, x, y + 1, North);
				setNextDirection(x, y, x, y - 1, South);
				setNextDirection(x, y, x + 1, y, East);
			} else if (now_dir == South) {
				setNextDirection(x, y, x, y - 1, South);
				setNextDirection(x, y, x - 1, y, West);
				setNextDirection(x, y, x + 1, y, East);
				setNextDirection(x, y, x, y + 1, North);
			}
		} else {
			if (now_dir == North) {
				setNextDirection(x, y, x, y + 1, North);
				setNextDirection(x, y, x + 1, y, East);
				setNextDirection(x, y, x - 1, y, West);
				setNextDirection(x, y, x, y - 1, South);
			} else if (now_dir == East) {
				setNextDirection(x, y, x + 1, y, East);
				setNextDirection(x, y, x, y - 1, South);
				setNextDirection(x, y, x, y + 1, North);
				setNextDirection(x, y, x - 1, y, West);
			} else if (now_dir == West) {
				setNextDirection(x, y, x - 1, y, West);
				setNextDirection(x, y, x, y + 1, North);
				setNextDirection(x, y, x, y - 1, South);
				setNextDirection(x, y, x + 1, y, East);
			} else if (now_dir == South) {
				setNextDirection(x, y, x, y - 1, South);
				setNextDirection(x, y, x - 1, y, West);
				setNextDirection(x, y, x + 1, y, East);
				setNextDirection(x, y, x, y + 1, North);
			}
		}
		if (nextDirection != 255) {
			nextMotion = setNextMotion(nextDirection);
		} else {
			nextMotion = Back;
		}
//		goaled = false;
		if (goaled) {
			cmtMusic(F3_, 1000);
		}
		if (!goaled && setNewPositionDummy(x, y, nextDirection)
				&& nextMotion != Back) {
			known = true;
			if (p == 0 && path_s[0] == 0) {
				path_s[0] += 2;
			}
			switch (nextMotion) {
			case Straight:
				path_s[p] += 2;
				break;
			case Right:
				path_t[p] = 1;
				p++;
				path_s[p] = 2;
				break;
			case Left:
				path_t[p] = 2;
				p++;
				path_s[p] = 2;
				break;
			}
			next_dir = setNewPosition(nextDirection);
			continue;
		} else {
			if (known) {
				known = false;
				int flag = (int) (*(float *) 1049768);
				if (flag) {
					largePath(false);
					diagonalPath(false, false);
				}
				check = runForKnownPath(velocity2, acc, diac);
				pathClear();
				p = 0;
				if (check == 0) {
					mtu_stop();
					return false;
				}
				if (goaled) {
					break;
				}
				continue;
			}
			lastMotion = nextMotion;
			switch (nextMotion) {
			case Straight:
				check = runForWallOff(velocity, 0, 180.0, 1);
				backFlg = 0;
				break;
			case Right:
				check = slalom(R, Normal, velocity, velocity, 0);
				backFlg = 0;
				break;
			case Left:
				check = slalom(L, Normal, velocity, velocity, 0);
				backFlg = 0;
				break;
			case Back:
				if (Front_SEN.now > wallhosei) {
					fanMode = CtrlFan2;
					frontCtrl();
					realRun(velocity, acc, diac, 100, 100);
					mtu_stop();
					gyroRollTest(R, 180, 60, 100);
					if (isStepped(firstGoalX, firstGoalY)) {
						if (nextMotion == Back && !lock
								&& !(isStepped(GoalX, GoalY)
										|| candicateDead(GoalX, GoalY))) {
							goal = searchGoalPosition(firstGoalX, firstGoalY,
									true, isFull);
							lock = true;
							GoalX = (goal & 0xf0) >> 4;
							GoalY = goal & 0x0f;
							updateDist(GoalX, GoalY, 0, isFull);
							skip = true;
						}
					}
					if (tmpSave == false && oflg == false) {
						char res = saveFcuBlock(FLASH_DF_BLOCK_4);
						if (res == true) {
							oneUp(100);
						}
						tmpSave = true;
						gyroZeroCheck(false);
					}
					fanMode = SearchRun;
					mtu_start();
					check = runForWallOff(velocity, acc, 115, 1);
				} else {
					realRun(velocity, acc, diac, 115, 25);
					mtu_stop();
					gyroRoll(R, 180, 60, 80);
					if (isStepped(firstGoalX, firstGoalY)) {
						if (nextMotion == Back && !lock
								&& !(isStepped(GoalX, GoalY)
										|| candicateDead(GoalX, GoalY))) {
							goal = searchGoalPosition(firstGoalX, firstGoalY,
									true, isFull);
							lock = true;
							GoalX = (goal & 0xf0) >> 4;
							GoalY = goal & 0x0f;
							updateDist(GoalX, GoalY, 0, isFull);
							skip = true;
						}
					}
					gyroZeroCheck(false);
					mtu_start();
					check = runForWallOff(velocity, acc, 115.0, 1);
				}
				backFlg++;
				break;
			}
		}
		if (check == 0) {
			mtu_stop();
			return false;
		}
		next_dir = setNewPosition(nextDirection);
		if (backFlg == 4) {
			mtu_stop();
			return false;
		}
	}
	fanMode = CtrlFan2;
	frontCtrl();
	realRun(velocity, acc, diac, 100, 50);
	frontCtrl3();
	mtu_stop();

	const int frontCtrlMode = (int) (*(float *) 1049988);
	if (frontCtrlMode) {
		calibrateRun(R);
	} else {
		gyroRollTest(R, 180, 60, 100);
		back(-100, -diac / 500, 30, 1);
	}

	V_now = 0;
	cmt_wait(500);
	mtu_stop2();
	if (saveFcuBlock(FLASH_DF_BLOCK_4)) {
		oneUp(100);
	}
	return true;
}

void inputNaiperTurnAll1000();
