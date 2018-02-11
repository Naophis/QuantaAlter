/*
 * RealRun.h
 *
 *  Created on: 2014/05/23
 *      Author: Naoto
 */

#ifndef REALRUN_H_
#define REALRUN_H_

void cirquit();
char realRun(float max, float ac, float diac, float dist, float sla) {
	if (dia == 0) {
		sensingMode = AtackStraight;
	} else {
		sensingMode = AtackDia;
	}
	return orignalRun(max, sla, ac, diac, dist);
}

char runForPath(float max, float ac, float diac) {
	int i = 0;
	float dist = 0;
	float slaVelocity = 0;
	char RorL = 0;
	char turnVarys = 0;
	float slaVelocity2 = 0;
	char turnVarys2 = 0;
	char check = 0;
	float slalomDist = 0;
	char oldTurnVary = 0;
	char top = false;
	dia = 0;
	tempVmax = max;
	getAllPram2();
	cmt_wait(100);
//	back(-100, -1000, 50, 0);
	gyroZeroCheck(true);
	if (pLarge.velocity >= 1200) {
		TRANSAM = true;
//		LED_R = true;
//		LED_L = true;
		startVacume2(70);
	}
	turnVarys = turnVary(path_t[0]);
	slaVelocity = turnVelocity(turnVarys);
//	getAllPram();
	mtu_start();
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
	for (i = 0; i < pathLength; i++) {
		if (i == 0) {
			wall_off_limit = 125000;
			wall_off_limit_d = 125000;
			dist = 0.5 * (path_s[i] - 1) - 1;
		} else {
			wall_off_limit = 30;
			wall_off_limit_d = 25;

			dist = 0.5 * path_s[i] - 1;
		}
		if (dist <= 0) {
			dist = 0;
		}
		if (i > 0) {
			slalomDist = slalomBackDistance;
			slalomBackDistance = 0;
		}
		if (dist > 0 && !top) {
			getAllPram();
			top = true;
		}
		turnVarys = turnVary(path_t[i]);
		slaVelocity = turnVelocity(turnVarys);
		RorL = turnRoL(path_t[i]);
//		myprintf("%d	%f	%f\r\n", i, dist, slaVelocity);
		if (dist > 0 || i == 0) {
			if (dia == 0) {
				if (i == 0) {
					check = realRun(max, ac, diac, (dist) * 180 + 41,
							slaVelocity);
				} else {
					check = realRun(max, ac, diac, dist * 180 + slalomDist,
							slaVelocity);
				}
			} else {
				if (oldTurnVary == Dia135 || oldTurnVary == Dia90) {
//					slalomDist -= 20;
				}
				check = realRun(max, ac * 0.8, diac * 0.8,
						dist * ROOT2 * 180 + slalomDist, slaVelocity);
			}
		}
		if (!check) {
			mtu_stop();
			fastMode = 0;
			return 0;
		}
		if (path_t[i] == 255) {
			break;
		}
		if (wallOff(RorL) == 1) {
			if (dist == 0) {
				turnVarys2 = turnVary(path_t[i + 1]);
				slaVelocity2 = turnVelocity(turnVarys2);
				if (slaVelocity2 == slaVelocity) {
					check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
							ac * 0.8);
				} else if (slaVelocity2 > slaVelocity) {
					check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
							ac * 0.8);
				} else if (slaVelocity2 < slaVelocity) {
					check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
							-diac * 0.8);
				}
			} else {
				check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity, 0);
			}
		} else {
			mtu_stop();
			fastMode = 0;
			return 0;
		}
		if (!check) {
			mtu_stop();
			fastMode = 0;
			return 0;
		}
	}
	cc = 0;

	running(150, -diac, 90, 1);

	if (!dia) {
		frontCtrl2();
	}

	mtu_stop2();
//	logOutPut();
	fastMode = 0;
	return 1;
}

char runForPath_v2(float max, float ac, float diac) {
	int i = 0;
	float dist = 0;
	float slaVelocity = 0;
	char RorL = 0;
	char turnVarys = 0;
	float slaVelocity2 = 0;
	char turnVarys2 = 0;
	char check = 0;
	float slalomDist = 0;
	char oldTurnVary = 0;
	char top = false;
	dia = 0;
	tempVmax = max;
	getAllPram2();
	cmt_wait(100);
//	back(-100, -1000, 50, 0);
	gyroZeroCheck(true);
	if (pLarge.velocity >= 1200) {
		TRANSAM = true;
//		LED_R = true;
//		LED_L = true;
		startVacume2(70);
	}
	turnVarys = turnVary(path_t[0]);
	slaVelocity = turnVelocity(turnVarys);
//	getAllPram();
	mtu_start();
	for (i = 0; i < pathLength; i++) {
		if (i == 0) {
			dist = 0.5 * (path_s[i] - 1) - 1;
		} else {
			dist = 0.5 * path_s[i] - 1;
		}
		if (dist <= 0) {
			dist = 0;
		}
		if (i > 0) {
			slalomDist = slalomBackDistance;
			slalomBackDistance = 0;
		}
		if (dist > 0 && !top) {
			getAllPram();
			top = true;
		}
		turnVarys = turnVary(path_t[i]);
		slaVelocity = turnVelocity(turnVarys);
		RorL = turnRoL(path_t[i]);
		if (dist > 0 || i == 0) {
			if (dia == 0) {
				if (i == 0) {
					check = realRun(max, ac, diac, (dist) * 180 + 41,
							slaVelocity);
				} else {
					check = realRun(max, ac, diac, dist * 180 + slalomDist,
							slaVelocity);
				}
			} else {
				check = realRun(max, ac * 0.8, diac * 0.8,
						dist * ROOT2 * 180 + slalomDist, slaVelocity);
			}
		}
		if (!check) {
			mtu_stop();
			fastMode = 0;
			return 0;
		}
		if (path_t[i] == 255) {
			break;
		}
		if (dist == 0) {
			turnVarys2 = turnVary(path_t[i + 1]);
			slaVelocity2 = turnVelocity(turnVarys2);
			if (slaVelocity2 == slaVelocity) {
				check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
						ac * 0.8);
			} else if (slaVelocity2 > slaVelocity) {
				check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
						ac * 0.8);
			} else if (slaVelocity2 < slaVelocity) {
				check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
						-diac * 0.8);
			}
		} else {
			check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity, 0);
		}
		if (!check) {
			mtu_stop();
			fastMode = 0;
			return 0;
		}
	}
	running(150, -diac, 120, 1);

	if (!dia) {
		frontCtrl2();
	}

	mtu_stop2();
	fastMode = 0;
	return 1;
}

char runForKnownPath(float max, float ac, float diac) {
	int i = 0;
	float dist = 0;
	float slaVelocity = 0;
	char RorL = 0;
	char turnVarys = 0;
	float slaVelocity2 = 0;
	char turnVarys2 = 0;
	char check = 1;
	dia = 0;
	tempVmax = max;
	getAllPram();
	turnVarys = turnVary(path_t[0]);
	slaVelocity = turnVelocitySlow(turnVarys);
	char tmp = false;
	for (i = 0; i < pathLength; i++) {
		if (i == 0/* || path_t[i] == 255 || path_t[i] == 0*/) {
			dist = 0.5 * (path_s[i] - 1) - 0.5;
		} else {
			dist = 0.5 * path_s[i] - 1;
		}
		if (dist <= 0) {
			dist = 0;
		}

		turnVarys = turnVary(path_t[i]);

		slaVelocity = turnVelocitySlow(turnVarys);
		RorL = turnRoL(path_t[i]);
		if (dist > 0) {
			if (dia == 0) {
				if (path_t[i] == 255 && tmp) {
					cmtMusic(C2_, 500);
					check = realRun(max, ac, diac, dist * 180, slaVelocity);
				} else if (path_t[i] != 255
						&& !(path_t[i] == 1 || path_t[i] == 2)) {
					cmtMusic(C2_, 500);
					check = realRun(max, ac, diac, dist * 180, slaVelocity);
					tmp = true;
				} else if (path_t[i] == 1 || path_t[i] == 2) {
					if (tmp) {
						if (dist >= 1) {
							check = realRun(max, ac, diac, dist * 180 - 90,
									slaVelocity);
						}
						check = running2(slaVelocity, ac, 90, 1);
						tmp = false;
					} else {
						check = realRun(max, ac, diac, dist * 180, slaVelocity);
					}
				} else {
					if (dist >= 1) {
						check = realRun(max, ac, diac, dist * 180 - 90,
								slaVelocity);
						check = running2(slaVelocity, ac, 90, 1);
					} else {
						check = realRun(max, ac, diac, dist * 180, slaVelocity);
					}
				}
			} else {
				check = realRun(max, ac * 0.8, diac * 0.8, dist * ROOT2 * 180,
						slaVelocity);
			}
		}
		if (!check) {
			mtu_stop();
			fastMode = 0;
			return 0;
		}
		if (path_t[i] == 255 || path_t[i] == 0) {
			break;
		}
		if (path_t[i] == 1 || path_t[i] == 2 || wallOff(RorL) == 1) {
			if (dist == 0) {
				turnVarys2 = turnVary(path_t[i + 1]);
				slaVelocity2 = turnVelocitySlow(turnVarys2);
				if (slaVelocity2 == slaVelocity) {
					check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
							ac * 0.8);
				} else if (slaVelocity2 > slaVelocity) {
					check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
							ac * 0.8);
				} else if (slaVelocity2 < slaVelocity) {
					check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity2,
							-diac * 0.8);
				}
			} else {
				check = slalom3(RorL, turnVarys, slaVelocity, slaVelocity, 0);
			}
		} else {
			mtu_stop();
			fastMode = 0;
			return 0;
		}
		if (!check) {
			mtu_stop();
			fastMode = 0;
			return 0;
		}
	}
	fastMode = 0;
	return 1;
}
char realRun3(float max, float ac, float diac, float dist, float sla) {
	float M = 0;
	float M2 = 0;
	float max2 = sla;
	sensingMode = SearchMode;
	for (max2 = sla; M + M2 < dist; max2 += 50) {
		M = (max2 + V_now) * (max2 - V_now) / (2.0f * ac);
		M2 = (max2 + sla) * (max2 - sla) / (2.0f * diac);
	}
	for (max2 = max2 - 50; M + M2 < dist; max2 += 5) {
		M = (max2 + V_now) * (max2 - V_now) / (2.0f * ac);
		M2 = (max2 + sla) * (max2 - sla) / (2.0f * diac);
	}
	for (max2 = max2 - 5; M + M2 < dist; max2 += 1) {
		M = (max2 + V_now) * (max2 - V_now) / (2.0f * ac);
		M2 = (max2 + sla) * (max2 - sla) / (2.0f * diac);
	}
	if (max2 > max) {
		max2 = max;
	}
	gyroOn = 1;
	M2 = (max2 + sla) * (max2 - sla) / (2.0f * diac);
	M = dist - M2;
	if (running(max2, ac, M, 1)) {
		if (running(sla, -diac, M2, 1)) {
			gyroOn = 0;
			return 1;
		} else {
			gyroOn = 0;
			return 0;
		}
	}
	return 0;
}
#endif /* REALRUN_H_ */
