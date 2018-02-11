/*
 * flash.h
 *
 *  Created on: 2016/05/19
 *      Author: Naoto
 */

#ifndef FLASH_H_
#define FLASH_H_

#define PROGRAM_SIZE 1024

char saveFcu(uint32_t flash_addr);

void initFcu() {
	R_FLASH_Open();
}
//void readMap(uint32_t flash_addr) {
//	initFcu();
//	unsigned char wall[16][16];
//	uint32_t address;
//	address = flash_addr;
//	myprintf("\r\n");
//	for (int i = 0; i < 16; i++) {
//		for (int j = 0; j < 16; j++) {
//			wall[i][j] = *(unsigned char *) (address + 16 * i + j);
////			myprintf("%2x,", (char) (wall[i][j]));
//			cmt_wait(1);
//		}
//		myprintf("\r\n");
//	}
//	printMap();
//}
/**
 * 指定アドレスを32byte単位でループ削除
 * @param flash_addr
 * @return
 */
char eraseFlashAddr(uint32_t flash_addr) {
//	char bool1 = false;
//	uint8_t brank;
	flash_res_t result;
	R_FLASH_BlankCheck((uint32_t) flash_addr, 4, &result);
	uint8_t ret = R_FLASH_Erase(flash_addr, 4);
	if (ret != 0) {
//		bool1 = true;
	}
	return 0;
}
/**
 * ブロック単位で削除
 * @param brock
 * @return
 */
char eraseFlashBrock(uint32_t brock) {
//	eraseFlashAddr(brock);
	uint8_t ret = R_FLASH_Erase(brock, 4);
	return ret;
}
/**
 * 全部ブロック削除
 */
void eraseAllFlashBlock() {

	uint8_t ret = R_FLASH_Erase(FLASH_DF_BLOCK_0, 128);
	myprintf("result all flash erase", ret);
}

char writeMap(uint32_t flash_addr) {
	unsigned char wall[16][16] = { { 14, 6, 6, 5, 14, 7, 12, 6, 5, 12, 6, 4, 6,
			6, 6, 5 },
			{ 12, 5, 15, 10, 6, 6, 3, 15, 8, 1, 15, 11, 14, 7, 12, 1 }, { 9, 10,
					6, 6, 6, 4, 4, 6, 3, 8, 4, 6, 6, 6, 3, 9 }, { 9, 12, 6, 6,
					4, 1, 9, 12, 7, 9, 10, 4, 6, 6, 5, 9 }, { 9, 10, 6, 4, 3, 9,
					9, 11, 15, 9, 15, 10, 4, 6, 3, 9 }, { 9, 13, 12, 2, 6, 3,
					10, 6, 6, 2, 6, 6, 2, 5, 13, 9 }, { 9, 11, 9, 12, 5, 12, 4,
					7, 14, 4, 5, 12, 5, 9, 11, 9 }, { 10, 5, 9, 9, 9, 9, 9, 12,
					5, 9, 9, 9, 9, 9, 12, 3 }, { 15, 9, 8, 3, 9, 9, 11, 8, 3,
					11, 9, 9, 10, 1, 9, 15 }, { 12, 1, 9, 15, 8, 3, 13, 9, 15,
					13, 10, 1, 15, 11, 10, 5 }, { 9, 9, 9, 12, 3, 13, 9, 8, 5,
					9, 13, 10, 4, 6, 4, 1 }, { 9, 10, 2, 2, 5, 11, 11, 9, 9, 11,
					11, 12, 3, 15, 9, 9 }, { 8, 7, 12, 5, 9, 12, 5, 9, 9, 13,
					13, 9, 12, 5, 10, 1 }, { 9, 15, 9, 9, 9, 9, 9, 8, 1, 8, 1,
					9, 9, 9, 15, 9 }, { 8, 6, 1, 10, 3, 9, 9, 9, 9, 9, 9, 10, 3,
					8, 6, 1 }, { 10, 6, 2, 6, 6, 3, 10, 3, 10, 3, 10, 6, 6, 2,
					6, 3 } };
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			map[i][j] = wall[i][j];
		}
	}
	return saveFcu(flash_addr);
}
char writeMap2(uint32_t flash_addr) {
	unsigned char wall[16][16] = { { 14, 6, 4, 6, 4, 6, 6, 4, 5, 12, 4, 6, 4, 6,
			4, 7 }, { 12, 5, 9, 12, 2, 4, 7, 9, 8, 3, 10, 7, 10, 7, 10, 5 }, {
			9, 10, 3, 8, 7, 10, 7, 11, 10, 5, 12, 6, 6, 6, 4, 3 }, { 10, 4, 7,
			8, 7, 12, 5, 12, 5, 9, 10, 4, 6, 4, 0, 7 }, { 14, 0, 7, 10, 5, 9, 9,
			9, 9, 9, 12, 2, 4, 1, 8, 7 }, { 12, 2, 4, 7, 9, 9, 10, 3, 9, 9, 9,
			12, 3, 11, 11, 13 }, { 8, 4, 0, 7, 9, 9, 14, 6, 2, 3, 10, 2, 6, 6,
			6, 1 }, { 11, 11, 8, 5, 9, 10, 5, 12, 4, 4, 7, 12, 6, 6, 5, 9 }, {
			12, 4, 3, 10, 2, 7, 9, 10, 3, 10, 6, 1, 13, 12, 3, 9 }, { 9, 8, 5,
			12, 6, 5, 9, 12, 6, 6, 6, 3, 8, 3, 12, 1 }, { 9, 11, 11, 9, 12, 3,
			9, 9, 12, 6, 6, 4, 3, 12, 3, 9 }, { 9, 12, 5, 9, 8, 6, 3, 9, 9, 14,
			4, 3, 12, 3, 12, 3 }, { 9, 9, 10, 3, 9, 12, 6, 3, 9, 12, 3, 12, 0,
			7, 10, 5 },
			{ 9, 9, 12, 6, 3, 9, 12, 7, 8, 3, 12, 3, 11, 13, 14, 1 }, { 8, 3, 9,
					14, 5, 8, 1, 12, 3, 12, 3, 14, 4, 2, 5, 9 }, { 11, 14, 2, 6,
					2, 3, 11, 10, 6, 2, 6, 6, 2, 7, 10, 3 } };
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			map[i][j] = wall[i][j];
		}
	}
	return saveFcu(flash_addr);
}

char saveFcu(uint32_t flash_addr) {
	unsigned char wall[16][16];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			wall[i][j] = map[i][j];
		}
	}
	eraseFlashAddr(flash_addr);
	uint8_t ret2 = R_FLASH_Write((uint32_t) wall, flash_addr, sizeof(wall));
	myprintf("result saveFcu :%d \r\n", ret2);
	if (FLASH_SUCCESS == ret2) {
		return true;
	}
	return false;
}
char saveFcuBlock(uint32_t addr) {
	return saveFcu(addr);
}
void readMaze() {
	initFcu();
	uint32_t address = FLASH_DF_BLOCK_4;
	for (char i = 0; i < MAZE_SIZE; i++) {
		for (char j = 0; j < MAZE_SIZE; j++) {
			map[i][j] = *(unsigned char *) (address + 16 * i + j);
		}
	}
	printMap();
}
void readMaze2() {
	initFcu();
	uint32_t address = FLASH_DF_BLOCK_4;
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			map[i][j] = *(unsigned char *) (address + 16 * i + j);
		}
	}
	printMap();
}

void resetMap() {
	uint32_t flash_addr = FLASH_DF_BLOCK_0;
	eraseFlashBrock(0);
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			map[i][j] = 0;
		}
	}
	uint8_t ret2 = R_FLASH_Write((uint32_t) map, flash_addr, sizeof(map));
	if (FLASH_SUCCESS == ret2) {
		oneUp(100);
	} else {
		coin(100);
	}
}

char printBrankCheck() {
//	uint8_t ch;
	char b = false;
//	myprintf("=====%d=====\r\n", FLASH.FSTATR0.BIT.ILGLERR);
//	for (int i = BLOCK_DB0; i <= BLOCK_DB15; i++) {
//		ch = R_FlashDataAreaBlankCheck(g_flash_BlockAddresses[i],
//				BLANK_CHECK_2_BYTE);
////		myprintf("brank check result = %d @%d \r\n", ch, i);
//		if (ch != 0) {
//			b = true;
//		}
//	}
	return !b;
}
void resetFull() {
	uint32_t flash_addr = FLASH_DF_BLOCK_4;
	printBrankCheck();
	eraseAllFlashBlock();
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			map[i][j] = 0;
		}
	}
	uint8_t ret2 = R_FLASH_Write((uint32_t) map, flash_addr, sizeof(map));
	if (FLASH_SUCCESS == ret2) {
		myprintf("write success\r\n");
		oneUp(100);
		oneUp(100);
		oneUp(100);
	} else {
		myprintf("error %d\r\n", ret2);
		coin(50);
		coin(50);
		coin(50);
		coin(50);
		coin(50);
	}
}
char encorderOperation();
void testFcu() {
//	R_FlashDataAreaAccess(0xffff, 0xffff);

//	uint32_t flash_addr = g_flash_BlockAddresses[BLOCK_DB0];
	cmt_wait(1000);

	while (1) {
		int mode = encorderOperation() + 1;
		if (mode >= 5) {
//			break;
		}
		if ((mode) == 0x01) {
			writeMap(FLASH_DF_BLOCK_0);
		} else if ((mode) == 0x02) {
			readMaze();
		} else if ((mode) == 0x03) {
			writeMap2(FLASH_DF_BLOCK_4);
		} else if ((mode) == 0x04) {
			readMaze2();
		} else if ((mode) == 0x05) {
			resetFull();
		}
//		readMaze();
	}
}

#endif /* FLASH_H_ */
