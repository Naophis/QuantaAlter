#ifndef CONFIG_PARAMUARTIMPORTER_H_
#define CONFIG_PARAMUARTIMPORTER_H_
void setNormalParam500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050432 + 4 * i);
	}
	setPrms(Normal, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Normal, p[9], p[10], p[11]);
}
void setLargeParam500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050496 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050560 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050624 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050688 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050752 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setNormalParam1000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050816 + 4 * i);
	}
	setPrms(Normal, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Normal, p[9], p[10], p[11]);
}
void setLargeParam1000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050880 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam1000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1050944 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param1000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051008 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param1000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051072 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param1000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051136 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam1500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051200 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam1500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051264 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param1500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051328 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param1500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051392 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param1500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051456 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam1700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051520 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam1700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051584 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param1700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051648 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param1700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051712 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param1700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051776 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam1800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051840 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam1800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051904 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param1800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1051968 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param1800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052032 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param1800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052096 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam1900() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052160 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam1900() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052224 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param1900() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052288 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param1900() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052352 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param1900() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052416 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam1950() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052480 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam1950() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052544 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param1950() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052608 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param1950() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052672 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param1950() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052736 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052800 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052864 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052928 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1052992 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053056 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2050() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053120 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2050() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053184 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2050() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053248 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2050() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053312 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2050() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053376 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2100() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053440 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2100() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053504 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2100() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053568 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2100() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053632 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2100() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053696 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2200() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053760 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2200() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053824 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2200() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053888 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2200() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1053952 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2200() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054016 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2300() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054080 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2300() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054144 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2300() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054208 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2300() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054272 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2300() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054336 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2400() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054400 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2400() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054464 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2400() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054528 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2400() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054592 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2400() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054656 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054720 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054784 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054848 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054912 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2500() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1054976 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2600() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055040 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2600() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055104 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2600() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055168 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2600() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055232 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2600() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055296 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055360 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055424 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055488 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055552 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2700() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055616 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam2800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055680 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
void setOrvalParam2800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055744 + 4 * i);
	}
	setPrms(Orval, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Orval, p[9], p[10], p[11]);
}
void setDia45Param2800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055808 + 4 * i);
	}
	setPrms(Dia45, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia45, p[9], p[10], p[11]);
}
void setDia135Param2800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055872 + 4 * i);
	}
	setPrms(Dia135, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia135, p[9], p[10], p[11]);
}
void setDia90Param2800() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1055936 + 4 * i);
	}
	setPrms(Dia90, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Dia90, p[9], p[10], p[11]);
}
void setLargeParam3000() {
	float p[12];
	for (char i = 0; i < 12; i++) {
		p[i] = *(float *) (1056000 + 4 * i);
	}
	setPrms(Large, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
	setPrms3(Large, p[9], p[10], p[11]);
}
#endif
