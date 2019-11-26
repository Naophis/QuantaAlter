/*
 * RealRun.h
 *
 *  Created on: 2014/05/23
 *      Author: Naoto
 */

#ifndef REALRUN_H_
#define REALRUN_H_

#define NULL_FILTER 0
#define SEARCH_FILTER 1
#define REAL_RUN_FILTER 2
#define DIA_RUN_FILTER 3
#define START_FILTER 4
#define OTHERS_FILTER 5


void cirquit();
char realRun(float max, float ac, float diac, float dist, float sla,
		char runtype) {
	globalState = STRAIGHT;
	sensingMode = (dia == 0) ? AtackStraight : AtackDia;
	tmpfanMode = fanMode;
	fanMode = CtrlFan4;
	char res = true;
	if (dia == 1) {
		res = orignalRunDia(max, sla, ac, diac, dist, runtype);
	} else {
		res = orignalRun(max, sla, ac, diac, dist, runtype);
	}
	fanMode = tmpfanMode;
	return res;
}

char runForPath(float max, float ac, float diac) {
	int i = 0;
	float dist = 0;
	float slaVel = 0;
	char RorL = 0;
	char turnVarys = 0;
	float slaVel2 = 0;
	char turnVarys2 = 0;
	char res = 1;
	float slalomDist = 0;
//	char oldTurnVary = 0;
	char top = false;
	float start_offset = *(float *) 1049496;

	dia = 0;
	tempVmax = max;
	getAllPram2();
	cmt_wait(100);
	gyroZeroCheck(false);
	if (pLarge.velocity >= 1200) {
		TRANSAM = true;
		startVacume2(70);
	}
	turnVarys = turnVary(path_t[0]);
	slaVel = turnVelocity(turnVarys);
	mtu_start();
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
	char transam_running = false;

	getAllPram2();

	if (activate_TRANS_AM) {
		float dist0 = 0.5 * (path_s[0] - 1) - 0.5;
		float dist1 = 0.5 * (path_s[1] - 1) - 0.5;
		char turn_type = turnVary(path_t[0]);

		// if ((dist0 > 0 && dist1 > 0)
		if ((dist0 > 0) && (turn_type == Large || turn_type == Orval)) {
			float turnVelocity1 = vs[turn_type][8];
			float turnVelocity2 = vs3[turn_type][8];
			if (turnVelocity2 > turnVelocity1) {
				RS_SEN45.ref = *(float *) 1049944;
				LS_SEN45.ref = *(float *) 1049948;
				R_WALL_OFF = *(float *) 1049952;
				FRONT_WALL_ON = *(float *) 1049956;
				transam_running = true;
				start_offset = *(float *) 1049548;
				getPrm3(Large);
				getPrm3(Orval);
			}
		}

	}

	for (i = 0; i < pathLength; i++) {
		if (i == 0) {
			wall_off_limit = 125000;
			wall_off_limit_d = 125000;
			dist = 0.5 * (path_s[i] - 1) - 0.5;
			if (dist >= 0.5) {
				const float tempdist1 = *(float *) 1049960;
				wall_off_limit = wall_off_limit_d = tempdist1;
			}
		} else {
			const float tempdist1 = *(float *) 1049960;
			wall_off_limit = wall_off_limit_d = tempdist1;
			dist = 0.5 * path_s[i] - 1;
		}
		if (dist <= 0) {
			dist = 0;
		}
		if (i > 0) {
			slalomDist = slalomBackDistance;
			slalomBackDistance = 0;
		}
		if (transam_running) {
			if (dist > 0 && !top && i > 0) {
				getAllPram();
				top = true;
			}
		} else {
			if (dist > 0 && !top) {
				getAllPram();
				top = true;
			}
		}
		turnVarys = turnVary(path_t[i]);
		slaVel = turnVelocity(turnVarys);
		RorL = turnRoL(path_t[i]);

		if (i == 0) {
			if (dist > 0) {
				float tmpDist = (dist) * 180 + start_offset;
				res = realRun(max, ac, diac, tmpDist, slaVel, START_FILTER);
			} else {
				float tmpDist = getFirstFront(turnVarys) + start_offset;
				float tmpAccel = slaVel * slaVel / 2 / tmpDist;
				if (tmpAccel > ac) {
					tmpAccel += 1000;
					res = realRun(max, tmpAccel, tmpAccel, tmpDist, slaVel,
					START_FILTER);
				} else {
					res = realRun(max, ac, diac, tmpDist, slaVel,
					START_FILTER);
				}

				globalSkipFront = true;
			}
		} else if (dist > 0 || i == 0) {
			if (dia == 0) {
				float tmpDist = dist * 180 + slalomDist;
				res = realRun(max, ac, diac, tmpDist, slaVel, REAL_RUN_FILTER);
			} else {
				float tmpDist = dist * ROOT2 * 180 + slalomDist;
				res = realRun(max * 0.75, ac * 0.75, diac * 0.75, tmpDist,
						slaVel, DIA_RUN_FILTER);
			}
		}
		if (!res) {
			mtu_stop2();
			fastMode = 0;
			return 0;
		}
		if (path_t[i] == 255) {
			break;
		}
		if (wallOff(RorL, true)) {
			float next_dist = 0.5 * path_s[i + 1] - 1;
			if (next_dist <= 0) {
				next_dist = 0;
			}
			if (next_dist == 0) {
				turnVarys2 = turnVary(path_t[i + 1]);
				slaVel2 = turnVelocity(turnVarys2);
				if (transam_running) {
					slaVel2 = turnVelocity_transam(turnVarys2);
				}
				if (slaVel2 == slaVel) {
					res = slalom(RorL, turnVarys, slaVel, slaVel2, ac * 0.8);
				} else if (slaVel2 > slaVel) {
					res = slalom(RorL, turnVarys, slaVel, slaVel2, ac * 0.8);
				} else if (slaVel2 < slaVel) {
					res = slalom(RorL, turnVarys, slaVel, slaVel2, -diac * 0.8);
				}
			} else {
				res = slalom(RorL, turnVarys, slaVel, slaVel, 0);
			}
		} else {
			mtu_stop2();
			fastMode = 0;
			return 0;
		}
		// i>=1でトランザム終了
		if (transam_running) {
			RS_SEN45.ref = *(float *) 1049600;
			LS_SEN45.ref = *(float *) 1049604;
			R_WALL_OFF = *(float *) 1049856;
			FRONT_WALL_ON = *(float *) 1049896;
			transam_running = false;
			getAllPram();
		}
		// RS_SEN45.ref = *(float *) 1049600;
		// LS_SEN45.ref = *(float *) 1049604;
		// R_WALL_OFF = *(float *) 1049856;
		// FRONT_WALL_ON = *(float *) 1049896;
		// transam_running = false;
		globalSkipFront = false;

		if (!res) {
			mtu_stop2();
			fastMode = 0;
			return 0;
		}

		gyroErrResetEnable = false;
	}
	cc = 0;

	if (!dia) {
		frontCtrlDash(slaVel, 18000);
		// frontCtrl();
	}
	running(150, -diac, 90, 1);

	if (!dia) {
//		 frontCtrl2();
		frontCtrl3();
	}

	mtu_stop2();
	fastMode = 0;
//	gyroRollTest(R, 180, 60, 100);
//	back(-100, -1000, 65, 1);

//	if (now_dir == North) {
//		now_dir = South;
//	} else if (now_dir == East) {
//		now_dir = West;
//	} else if (now_dir == West) {
//		now_dir = East;
//	} else if (now_dir == South) {
//		now_dir = North;
//	}
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
		if (i == 0) {
			wall_off_limit = 125000;
			wall_off_limit_d = 125000;
			if (dist >= 0.5) {
				const float tempdist1 = *(float *) 1049960;
				wall_off_limit = wall_off_limit_d = tempdist1;
			}
		} else {
			const float tempdist1 = *(float *) 1049960;
			wall_off_limit = wall_off_limit_d = tempdist1;
		}

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
		if (dia == 0 && dist == 1) {
			check = runForWallOff(slaVelocity, 0, 180.0, 1);
		} else if (dist > 0) {
			if (dia == 0) {
				if (path_t[i] == 255 && tmp) {
					cmtMusic(C2_, 500);
					check = realRun(max, ac, diac, dist * 180, slaVelocity,
					NULL_FILTER);
				} else if (path_t[i] != 255
						&& !(path_t[i] == 1 || path_t[i] == 2)) {
					cmtMusic(C2_, 500);
					check = realRun(max, ac, diac, dist * 180, slaVelocity,
					NULL_FILTER);
					tmp = true;
				} else if (path_t[i] == 1 || path_t[i] == 2) {
					if (tmp) {
						// if (dist >= 1) {
						check = realRun(max, ac, diac, dist * 180, slaVelocity,
						NULL_FILTER);
						// }
						// check = runForWallOff(slaVelocity, ac, 90, 1);
						tmp = false;
					} else {
						check = realRun(max, ac, diac, dist * 180, slaVelocity,
						NULL_FILTER);
					}
				} else {
					if (dist >= 1) {
						check = realRun(max, ac, diac, dist * 180 - 90,
								slaVelocity, NULL_FILTER);
						check = runForWallOff(slaVelocity, ac, 90, 1,
						NULL_FILTER);
					} else {
						check = realRun(max, ac, diac, dist * 180, slaVelocity,
						NULL_FILTER);
					}
				}
			} else {
				check = realRun(max, ac * 0.8, diac * 0.8, dist * ROOT2 * 180,
						slaVelocity, NULL_FILTER);
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
		if (path_t[i] == 1 || path_t[i] == 2 || wallOff(RorL, dist > 0) == 1) {
			if (dist == 0) {
				turnVarys2 = turnVary(path_t[i + 1]);
				slaVelocity2 = turnVelocitySlow(turnVarys2);
				if (slaVelocity2 == slaVelocity) {
					check = slalom(RorL, turnVarys, slaVelocity, slaVelocity2,
							ac * 0.8);
				} else if (slaVelocity2 > slaVelocity) {
					check = slalom(RorL, turnVarys, slaVelocity, slaVelocity2,
							ac * 0.8);
				} else if (slaVelocity2 < slaVelocity) {
					check = slalom(RorL, turnVarys, slaVelocity, slaVelocity2,
							-diac * 0.8);
				}
			} else {
				check = slalom(RorL, turnVarys, slaVelocity, slaVelocity, 0);
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
#endif /* REALRUN_H_ */
