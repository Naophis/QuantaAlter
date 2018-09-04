/*
 * ParamImporter.h
 *
 *  Created on: 2017/09/02
 *      Author: Naoto
 */

#ifndef PARAMIMPORTER_H_
#define PARAMIMPORTER_H_

#define FLOAT_SIZE 4	//32byte
#define BASE_PARAM_KEY1 82	//基本パラメータ1
#define BASE_PARAM_KEY2 81	//基本パラメータ2
#define BASE_PARAM_KEY3 82	//基本パラメータ2
#define RUN_PARAM_KEY1 84	//ターンパラメータ1
#define RUN_PARAM_KEY2 86	//ターンパラメータ2

/**
 *   0~ 99	->	BASE_PARAM_KEY1
 * 100~199	->	BASE_PARAM_KEY2
 * 201~299	->	RUN_PARAM_KEY1
 * 301~399	->	RUN_PARAM_KEY2
 */

float getDataFlashData(long addr, int key) {
//	FLASH.FENTRYR.WORD = 0xAA00;
//	trans_farm_ = false;
	uint32_t address = 0; //g_flash_BlockAddresses[addr];
	return *(float *) (address + 4 * key);
}

/**
 * 1つだけの更新でも、配列すべてを書き換える必要がある。
 * @param key
 * @param val
 * @return
 */


#endif /* PARAMIMPORTER_H_ */
