/*
 * SerialMapper.h
 *
 *  Created on: 2017/08/17
 *      Author: Naoto
 */

#ifndef SERIALMAPPER_H_
#define SERIALMAPPER_H_

#include "string.h"
#include <stdlib.h>

#define STAY 0
#define KEY 1
#define VALUE 2
#define END 3
volatile int recieveMode = STAY;
volatile char lastData = 0;
#define MAX_BUFFER 20
typedef struct {
	int index;
	int length;
	char buffer[MAX_BUFFER];
} s_key;
s_key keys, values;

void pushKey(char key) {
	if (keys.length < MAX_BUFFER) {
		keys.buffer[keys.length] = key;
		keys.length++;
	}
}
void pushValue(char val) {
	if (values.length < MAX_BUFFER) {
		values.buffer[values.length] = val;
		values.length++;
	}
}
void flushData() {
	for (int i = 0; i < MAX_BUFFER; i++) {
		keys.buffer[i] = values.buffer[i] = 0;
	}
	keys.index = keys.length = values.index = values.length = 0;
}

char writeParam(int key, float val);
void assing(long id, float val);
void setA(long key, long id, float val);
void mapping() {
	const char *keyBuffer = &(keys.buffer);
	const char *valueBuffer = &(values.buffer);
	long key = atoi(keyBuffer);
	double value = atof(valueBuffer);
	assing(key, value);
}
void applyRecieveData(char type, char data) {
	if (type == KEY) {
		pushKey(data);
	} else if (type == VALUE) {
		pushValue(data);
	} else if (type == END) {
		mapping();
	} else if (type == STAY) {
	}
}
void detectChar() {
	SCI1.SSR.BIT.RDRF = 0; // 受信フラグを解除
	char recieveData = SCI1.RDR;
	lastData = recieveData;
	if (!enableSciUpdate) {
		return;
	}
	skipPrint = true;
	switch (recieveData) {
	case '{':
		recieveMode = KEY;
		flushData();
		break;
	case '}':
		recieveMode = END;
		applyRecieveData(recieveMode, recieveData);
		break;
	case ':':
		recieveMode = VALUE;
		break;
	default:
		applyRecieveData(recieveMode, recieveData);
		break;
	}
	skipPrint = false;
}

void setA(long key, long id, float val) {
	float backup[16];
	uint32_t address = key;
	while (true) {
		for (char i = 0; i < 16; i++) {
			backup[i] = *(float *) (address + 4 * i);
			if (id == address + 4 * i) {
				backup[i] = val;
			}
		}
		flash_err_t ret = R_FLASH_Erase((flash_block_address_t) address, 1);
		flash_err_t ret2 = R_FLASH_Write((uint32_t) backup, key,
				sizeof(backup));
		char check = true;
		for (char i = 0; i < 16; i++) {
			if (backup[i] != *(float *) (address + 4 * i)) {
				check = false;
			}
		}
		break;
		cmt_wait(10);
	}
	cmtMusic(C3_, 20);
}
void assing(long id, float val) {
	if (id >= 1114048) {
		setA(FLASH_DF_BLOCK_1023, id, val);
	} else if (id >= 1113984) {
		setA(FLASH_DF_BLOCK_1022, id, val);
	} else if (id >= 1113920) {
		setA(FLASH_DF_BLOCK_1021, id, val);
	} else if (id >= 1113856) {
		setA(FLASH_DF_BLOCK_1020, id, val);
	} else if (id >= 1113792) {
		setA(FLASH_DF_BLOCK_1019, id, val);
	} else if (id >= 1113728) {
		setA(FLASH_DF_BLOCK_1018, id, val);
	} else if (id >= 1113664) {
		setA(FLASH_DF_BLOCK_1017, id, val);
	} else if (id >= 1113600) {
		setA(FLASH_DF_BLOCK_1016, id, val);
	} else if (id >= 1113536) {
		setA(FLASH_DF_BLOCK_1015, id, val);
	} else if (id >= 1113472) {
		setA(FLASH_DF_BLOCK_1014, id, val);
	} else if (id >= 1113408) {
		setA(FLASH_DF_BLOCK_1013, id, val);
	} else if (id >= 1113344) {
		setA(FLASH_DF_BLOCK_1012, id, val);
	} else if (id >= 1113280) {
		setA(FLASH_DF_BLOCK_1011, id, val);
	} else if (id >= 1113216) {
		setA(FLASH_DF_BLOCK_1010, id, val);
	} else if (id >= 1113152) {
		setA(FLASH_DF_BLOCK_1009, id, val);
	} else if (id >= 1113088) {
		setA(FLASH_DF_BLOCK_1008, id, val);
	} else if (id >= 1113024) {
		setA(FLASH_DF_BLOCK_1007, id, val);
	} else if (id >= 1112960) {
		setA(FLASH_DF_BLOCK_1006, id, val);
	} else if (id >= 1112896) {
		setA(FLASH_DF_BLOCK_1005, id, val);
	} else if (id >= 1112832) {
		setA(FLASH_DF_BLOCK_1004, id, val);
	} else if (id >= 1112768) {
		setA(FLASH_DF_BLOCK_1003, id, val);
	} else if (id >= 1112704) {
		setA(FLASH_DF_BLOCK_1002, id, val);
	} else if (id >= 1112640) {
		setA(FLASH_DF_BLOCK_1001, id, val);
	} else if (id >= 1112576) {
		setA(FLASH_DF_BLOCK_1000, id, val);
	} else if (id >= 1112512) {
		setA(FLASH_DF_BLOCK_999, id, val);
	} else if (id >= 1112448) {
		setA(FLASH_DF_BLOCK_998, id, val);
	} else if (id >= 1112384) {
		setA(FLASH_DF_BLOCK_997, id, val);
	} else if (id >= 1112320) {
		setA(FLASH_DF_BLOCK_996, id, val);
	} else if (id >= 1112256) {
		setA(FLASH_DF_BLOCK_995, id, val);
	} else if (id >= 1112192) {
		setA(FLASH_DF_BLOCK_994, id, val);
	} else if (id >= 1112128) {
		setA(FLASH_DF_BLOCK_993, id, val);
	} else if (id >= 1112064) {
		setA(FLASH_DF_BLOCK_992, id, val);
	} else if (id >= 1112000) {
		setA(FLASH_DF_BLOCK_991, id, val);
	} else if (id >= 1111936) {
		setA(FLASH_DF_BLOCK_990, id, val);
	} else if (id >= 1111872) {
		setA(FLASH_DF_BLOCK_989, id, val);
	} else if (id >= 1111808) {
		setA(FLASH_DF_BLOCK_988, id, val);
	} else if (id >= 1111744) {
		setA(FLASH_DF_BLOCK_987, id, val);
	} else if (id >= 1111680) {
		setA(FLASH_DF_BLOCK_986, id, val);
	} else if (id >= 1111616) {
		setA(FLASH_DF_BLOCK_985, id, val);
	} else if (id >= 1111552) {
		setA(FLASH_DF_BLOCK_984, id, val);
	} else if (id >= 1111488) {
		setA(FLASH_DF_BLOCK_983, id, val);
	} else if (id >= 1111424) {
		setA(FLASH_DF_BLOCK_982, id, val);
	} else if (id >= 1111360) {
		setA(FLASH_DF_BLOCK_981, id, val);
	} else if (id >= 1111296) {
		setA(FLASH_DF_BLOCK_980, id, val);
	} else if (id >= 1111232) {
		setA(FLASH_DF_BLOCK_979, id, val);
	} else if (id >= 1111168) {
		setA(FLASH_DF_BLOCK_978, id, val);
	} else if (id >= 1111104) {
		setA(FLASH_DF_BLOCK_977, id, val);
	} else if (id >= 1111040) {
		setA(FLASH_DF_BLOCK_976, id, val);
	} else if (id >= 1110976) {
		setA(FLASH_DF_BLOCK_975, id, val);
	} else if (id >= 1110912) {
		setA(FLASH_DF_BLOCK_974, id, val);
	} else if (id >= 1110848) {
		setA(FLASH_DF_BLOCK_973, id, val);
	} else if (id >= 1110784) {
		setA(FLASH_DF_BLOCK_972, id, val);
	} else if (id >= 1110720) {
		setA(FLASH_DF_BLOCK_971, id, val);
	} else if (id >= 1110656) {
		setA(FLASH_DF_BLOCK_970, id, val);
	} else if (id >= 1110592) {
		setA(FLASH_DF_BLOCK_969, id, val);
	} else if (id >= 1110528) {
		setA(FLASH_DF_BLOCK_968, id, val);
	} else if (id >= 1110464) {
		setA(FLASH_DF_BLOCK_967, id, val);
	} else if (id >= 1110400) {
		setA(FLASH_DF_BLOCK_966, id, val);
	} else if (id >= 1110336) {
		setA(FLASH_DF_BLOCK_965, id, val);
	} else if (id >= 1110272) {
		setA(FLASH_DF_BLOCK_964, id, val);
	} else if (id >= 1110208) {
		setA(FLASH_DF_BLOCK_963, id, val);
	} else if (id >= 1110144) {
		setA(FLASH_DF_BLOCK_962, id, val);
	} else if (id >= 1110080) {
		setA(FLASH_DF_BLOCK_961, id, val);
	} else if (id >= 1110016) {
		setA(FLASH_DF_BLOCK_960, id, val);
	} else if (id >= 1109952) {
		setA(FLASH_DF_BLOCK_959, id, val);
	} else if (id >= 1109888) {
		setA(FLASH_DF_BLOCK_958, id, val);
	} else if (id >= 1109824) {
		setA(FLASH_DF_BLOCK_957, id, val);
	} else if (id >= 1109760) {
		setA(FLASH_DF_BLOCK_956, id, val);
	} else if (id >= 1109696) {
		setA(FLASH_DF_BLOCK_955, id, val);
	} else if (id >= 1109632) {
		setA(FLASH_DF_BLOCK_954, id, val);
	} else if (id >= 1109568) {
		setA(FLASH_DF_BLOCK_953, id, val);
	} else if (id >= 1109504) {
		setA(FLASH_DF_BLOCK_952, id, val);
	} else if (id >= 1109440) {
		setA(FLASH_DF_BLOCK_951, id, val);
	} else if (id >= 1109376) {
		setA(FLASH_DF_BLOCK_950, id, val);
	} else if (id >= 1109312) {
		setA(FLASH_DF_BLOCK_949, id, val);
	} else if (id >= 1109248) {
		setA(FLASH_DF_BLOCK_948, id, val);
	} else if (id >= 1109184) {
		setA(FLASH_DF_BLOCK_947, id, val);
	} else if (id >= 1109120) {
		setA(FLASH_DF_BLOCK_946, id, val);
	} else if (id >= 1109056) {
		setA(FLASH_DF_BLOCK_945, id, val);
	} else if (id >= 1108992) {
		setA(FLASH_DF_BLOCK_944, id, val);
	} else if (id >= 1108928) {
		setA(FLASH_DF_BLOCK_943, id, val);
	} else if (id >= 1108864) {
		setA(FLASH_DF_BLOCK_942, id, val);
	} else if (id >= 1108800) {
		setA(FLASH_DF_BLOCK_941, id, val);
	} else if (id >= 1108736) {
		setA(FLASH_DF_BLOCK_940, id, val);
	} else if (id >= 1108672) {
		setA(FLASH_DF_BLOCK_939, id, val);
	} else if (id >= 1108608) {
		setA(FLASH_DF_BLOCK_938, id, val);
	} else if (id >= 1108544) {
		setA(FLASH_DF_BLOCK_937, id, val);
	} else if (id >= 1108480) {
		setA(FLASH_DF_BLOCK_936, id, val);
	} else if (id >= 1108416) {
		setA(FLASH_DF_BLOCK_935, id, val);
	} else if (id >= 1108352) {
		setA(FLASH_DF_BLOCK_934, id, val);
	} else if (id >= 1108288) {
		setA(FLASH_DF_BLOCK_933, id, val);
	} else if (id >= 1108224) {
		setA(FLASH_DF_BLOCK_932, id, val);
	} else if (id >= 1108160) {
		setA(FLASH_DF_BLOCK_931, id, val);
	} else if (id >= 1108096) {
		setA(FLASH_DF_BLOCK_930, id, val);
	} else if (id >= 1108032) {
		setA(FLASH_DF_BLOCK_929, id, val);
	} else if (id >= 1107968) {
		setA(FLASH_DF_BLOCK_928, id, val);
	} else if (id >= 1107904) {
		setA(FLASH_DF_BLOCK_927, id, val);
	} else if (id >= 1107840) {
		setA(FLASH_DF_BLOCK_926, id, val);
	} else if (id >= 1107776) {
		setA(FLASH_DF_BLOCK_925, id, val);
	} else if (id >= 1107712) {
		setA(FLASH_DF_BLOCK_924, id, val);
	} else if (id >= 1107648) {
		setA(FLASH_DF_BLOCK_923, id, val);
	} else if (id >= 1107584) {
		setA(FLASH_DF_BLOCK_922, id, val);
	} else if (id >= 1107520) {
		setA(FLASH_DF_BLOCK_921, id, val);
	} else if (id >= 1107456) {
		setA(FLASH_DF_BLOCK_920, id, val);
	} else if (id >= 1107392) {
		setA(FLASH_DF_BLOCK_919, id, val);
	} else if (id >= 1107328) {
		setA(FLASH_DF_BLOCK_918, id, val);
	} else if (id >= 1107264) {
		setA(FLASH_DF_BLOCK_917, id, val);
	} else if (id >= 1107200) {
		setA(FLASH_DF_BLOCK_916, id, val);
	} else if (id >= 1107136) {
		setA(FLASH_DF_BLOCK_915, id, val);
	} else if (id >= 1107072) {
		setA(FLASH_DF_BLOCK_914, id, val);
	} else if (id >= 1107008) {
		setA(FLASH_DF_BLOCK_913, id, val);
	} else if (id >= 1106944) {
		setA(FLASH_DF_BLOCK_912, id, val);
	} else if (id >= 1106880) {
		setA(FLASH_DF_BLOCK_911, id, val);
	} else if (id >= 1106816) {
		setA(FLASH_DF_BLOCK_910, id, val);
	} else if (id >= 1106752) {
		setA(FLASH_DF_BLOCK_909, id, val);
	} else if (id >= 1106688) {
		setA(FLASH_DF_BLOCK_908, id, val);
	} else if (id >= 1106624) {
		setA(FLASH_DF_BLOCK_907, id, val);
	} else if (id >= 1106560) {
		setA(FLASH_DF_BLOCK_906, id, val);
	} else if (id >= 1106496) {
		setA(FLASH_DF_BLOCK_905, id, val);
	} else if (id >= 1106432) {
		setA(FLASH_DF_BLOCK_904, id, val);
	} else if (id >= 1106368) {
		setA(FLASH_DF_BLOCK_903, id, val);
	} else if (id >= 1106304) {
		setA(FLASH_DF_BLOCK_902, id, val);
	} else if (id >= 1106240) {
		setA(FLASH_DF_BLOCK_901, id, val);
	} else if (id >= 1106176) {
		setA(FLASH_DF_BLOCK_900, id, val);
	} else if (id >= 1106112) {
		setA(FLASH_DF_BLOCK_899, id, val);
	} else if (id >= 1106048) {
		setA(FLASH_DF_BLOCK_898, id, val);
	} else if (id >= 1105984) {
		setA(FLASH_DF_BLOCK_897, id, val);
	} else if (id >= 1105920) {
		setA(FLASH_DF_BLOCK_896, id, val);
	} else if (id >= 1105856) {
		setA(FLASH_DF_BLOCK_895, id, val);
	} else if (id >= 1105792) {
		setA(FLASH_DF_BLOCK_894, id, val);
	} else if (id >= 1105728) {
		setA(FLASH_DF_BLOCK_893, id, val);
	} else if (id >= 1105664) {
		setA(FLASH_DF_BLOCK_892, id, val);
	} else if (id >= 1105600) {
		setA(FLASH_DF_BLOCK_891, id, val);
	} else if (id >= 1105536) {
		setA(FLASH_DF_BLOCK_890, id, val);
	} else if (id >= 1105472) {
		setA(FLASH_DF_BLOCK_889, id, val);
	} else if (id >= 1105408) {
		setA(FLASH_DF_BLOCK_888, id, val);
	} else if (id >= 1105344) {
		setA(FLASH_DF_BLOCK_887, id, val);
	} else if (id >= 1105280) {
		setA(FLASH_DF_BLOCK_886, id, val);
	} else if (id >= 1105216) {
		setA(FLASH_DF_BLOCK_885, id, val);
	} else if (id >= 1105152) {
		setA(FLASH_DF_BLOCK_884, id, val);
	} else if (id >= 1105088) {
		setA(FLASH_DF_BLOCK_883, id, val);
	} else if (id >= 1105024) {
		setA(FLASH_DF_BLOCK_882, id, val);
	} else if (id >= 1104960) {
		setA(FLASH_DF_BLOCK_881, id, val);
	} else if (id >= 1104896) {
		setA(FLASH_DF_BLOCK_880, id, val);
	} else if (id >= 1104832) {
		setA(FLASH_DF_BLOCK_879, id, val);
	} else if (id >= 1104768) {
		setA(FLASH_DF_BLOCK_878, id, val);
	} else if (id >= 1104704) {
		setA(FLASH_DF_BLOCK_877, id, val);
	} else if (id >= 1104640) {
		setA(FLASH_DF_BLOCK_876, id, val);
	} else if (id >= 1104576) {
		setA(FLASH_DF_BLOCK_875, id, val);
	} else if (id >= 1104512) {
		setA(FLASH_DF_BLOCK_874, id, val);
	} else if (id >= 1104448) {
		setA(FLASH_DF_BLOCK_873, id, val);
	} else if (id >= 1104384) {
		setA(FLASH_DF_BLOCK_872, id, val);
	} else if (id >= 1104320) {
		setA(FLASH_DF_BLOCK_871, id, val);
	} else if (id >= 1104256) {
		setA(FLASH_DF_BLOCK_870, id, val);
	} else if (id >= 1104192) {
		setA(FLASH_DF_BLOCK_869, id, val);
	} else if (id >= 1104128) {
		setA(FLASH_DF_BLOCK_868, id, val);
	} else if (id >= 1104064) {
		setA(FLASH_DF_BLOCK_867, id, val);
	} else if (id >= 1104000) {
		setA(FLASH_DF_BLOCK_866, id, val);
	} else if (id >= 1103936) {
		setA(FLASH_DF_BLOCK_865, id, val);
	} else if (id >= 1103872) {
		setA(FLASH_DF_BLOCK_864, id, val);
	} else if (id >= 1103808) {
		setA(FLASH_DF_BLOCK_863, id, val);
	} else if (id >= 1103744) {
		setA(FLASH_DF_BLOCK_862, id, val);
	} else if (id >= 1103680) {
		setA(FLASH_DF_BLOCK_861, id, val);
	} else if (id >= 1103616) {
		setA(FLASH_DF_BLOCK_860, id, val);
	} else if (id >= 1103552) {
		setA(FLASH_DF_BLOCK_859, id, val);
	} else if (id >= 1103488) {
		setA(FLASH_DF_BLOCK_858, id, val);
	} else if (id >= 1103424) {
		setA(FLASH_DF_BLOCK_857, id, val);
	} else if (id >= 1103360) {
		setA(FLASH_DF_BLOCK_856, id, val);
	} else if (id >= 1103296) {
		setA(FLASH_DF_BLOCK_855, id, val);
	} else if (id >= 1103232) {
		setA(FLASH_DF_BLOCK_854, id, val);
	} else if (id >= 1103168) {
		setA(FLASH_DF_BLOCK_853, id, val);
	} else if (id >= 1103104) {
		setA(FLASH_DF_BLOCK_852, id, val);
	} else if (id >= 1103040) {
		setA(FLASH_DF_BLOCK_851, id, val);
	} else if (id >= 1102976) {
		setA(FLASH_DF_BLOCK_850, id, val);
	} else if (id >= 1102912) {
		setA(FLASH_DF_BLOCK_849, id, val);
	} else if (id >= 1102848) {
		setA(FLASH_DF_BLOCK_848, id, val);
	} else if (id >= 1102784) {
		setA(FLASH_DF_BLOCK_847, id, val);
	} else if (id >= 1102720) {
		setA(FLASH_DF_BLOCK_846, id, val);
	} else if (id >= 1102656) {
		setA(FLASH_DF_BLOCK_845, id, val);
	} else if (id >= 1102592) {
		setA(FLASH_DF_BLOCK_844, id, val);
	} else if (id >= 1102528) {
		setA(FLASH_DF_BLOCK_843, id, val);
	} else if (id >= 1102464) {
		setA(FLASH_DF_BLOCK_842, id, val);
	} else if (id >= 1102400) {
		setA(FLASH_DF_BLOCK_841, id, val);
	} else if (id >= 1102336) {
		setA(FLASH_DF_BLOCK_840, id, val);
	} else if (id >= 1102272) {
		setA(FLASH_DF_BLOCK_839, id, val);
	} else if (id >= 1102208) {
		setA(FLASH_DF_BLOCK_838, id, val);
	} else if (id >= 1102144) {
		setA(FLASH_DF_BLOCK_837, id, val);
	} else if (id >= 1102080) {
		setA(FLASH_DF_BLOCK_836, id, val);
	} else if (id >= 1102016) {
		setA(FLASH_DF_BLOCK_835, id, val);
	} else if (id >= 1101952) {
		setA(FLASH_DF_BLOCK_834, id, val);
	} else if (id >= 1101888) {
		setA(FLASH_DF_BLOCK_833, id, val);
	} else if (id >= 1101824) {
		setA(FLASH_DF_BLOCK_832, id, val);
	} else if (id >= 1101760) {
		setA(FLASH_DF_BLOCK_831, id, val);
	} else if (id >= 1101696) {
		setA(FLASH_DF_BLOCK_830, id, val);
	} else if (id >= 1101632) {
		setA(FLASH_DF_BLOCK_829, id, val);
	} else if (id >= 1101568) {
		setA(FLASH_DF_BLOCK_828, id, val);
	} else if (id >= 1101504) {
		setA(FLASH_DF_BLOCK_827, id, val);
	} else if (id >= 1101440) {
		setA(FLASH_DF_BLOCK_826, id, val);
	} else if (id >= 1101376) {
		setA(FLASH_DF_BLOCK_825, id, val);
	} else if (id >= 1101312) {
		setA(FLASH_DF_BLOCK_824, id, val);
	} else if (id >= 1101248) {
		setA(FLASH_DF_BLOCK_823, id, val);
	} else if (id >= 1101184) {
		setA(FLASH_DF_BLOCK_822, id, val);
	} else if (id >= 1101120) {
		setA(FLASH_DF_BLOCK_821, id, val);
	} else if (id >= 1101056) {
		setA(FLASH_DF_BLOCK_820, id, val);
	} else if (id >= 1100992) {
		setA(FLASH_DF_BLOCK_819, id, val);
	} else if (id >= 1100928) {
		setA(FLASH_DF_BLOCK_818, id, val);
	} else if (id >= 1100864) {
		setA(FLASH_DF_BLOCK_817, id, val);
	} else if (id >= 1100800) {
		setA(FLASH_DF_BLOCK_816, id, val);
	} else if (id >= 1100736) {
		setA(FLASH_DF_BLOCK_815, id, val);
	} else if (id >= 1100672) {
		setA(FLASH_DF_BLOCK_814, id, val);
	} else if (id >= 1100608) {
		setA(FLASH_DF_BLOCK_813, id, val);
	} else if (id >= 1100544) {
		setA(FLASH_DF_BLOCK_812, id, val);
	} else if (id >= 1100480) {
		setA(FLASH_DF_BLOCK_811, id, val);
	} else if (id >= 1100416) {
		setA(FLASH_DF_BLOCK_810, id, val);
	} else if (id >= 1100352) {
		setA(FLASH_DF_BLOCK_809, id, val);
	} else if (id >= 1100288) {
		setA(FLASH_DF_BLOCK_808, id, val);
	} else if (id >= 1100224) {
		setA(FLASH_DF_BLOCK_807, id, val);
	} else if (id >= 1100160) {
		setA(FLASH_DF_BLOCK_806, id, val);
	} else if (id >= 1100096) {
		setA(FLASH_DF_BLOCK_805, id, val);
	} else if (id >= 1100032) {
		setA(FLASH_DF_BLOCK_804, id, val);
	} else if (id >= 1099968) {
		setA(FLASH_DF_BLOCK_803, id, val);
	} else if (id >= 1099904) {
		setA(FLASH_DF_BLOCK_802, id, val);
	} else if (id >= 1099840) {
		setA(FLASH_DF_BLOCK_801, id, val);
	} else if (id >= 1099776) {
		setA(FLASH_DF_BLOCK_800, id, val);
	} else if (id >= 1099712) {
		setA(FLASH_DF_BLOCK_799, id, val);
	} else if (id >= 1099648) {
		setA(FLASH_DF_BLOCK_798, id, val);
	} else if (id >= 1099584) {
		setA(FLASH_DF_BLOCK_797, id, val);
	} else if (id >= 1099520) {
		setA(FLASH_DF_BLOCK_796, id, val);
	} else if (id >= 1099456) {
		setA(FLASH_DF_BLOCK_795, id, val);
	} else if (id >= 1099392) {
		setA(FLASH_DF_BLOCK_794, id, val);
	} else if (id >= 1099328) {
		setA(FLASH_DF_BLOCK_793, id, val);
	} else if (id >= 1099264) {
		setA(FLASH_DF_BLOCK_792, id, val);
	} else if (id >= 1099200) {
		setA(FLASH_DF_BLOCK_791, id, val);
	} else if (id >= 1099136) {
		setA(FLASH_DF_BLOCK_790, id, val);
	} else if (id >= 1099072) {
		setA(FLASH_DF_BLOCK_789, id, val);
	} else if (id >= 1099008) {
		setA(FLASH_DF_BLOCK_788, id, val);
	} else if (id >= 1098944) {
		setA(FLASH_DF_BLOCK_787, id, val);
	} else if (id >= 1098880) {
		setA(FLASH_DF_BLOCK_786, id, val);
	} else if (id >= 1098816) {
		setA(FLASH_DF_BLOCK_785, id, val);
	} else if (id >= 1098752) {
		setA(FLASH_DF_BLOCK_784, id, val);
	} else if (id >= 1098688) {
		setA(FLASH_DF_BLOCK_783, id, val);
	} else if (id >= 1098624) {
		setA(FLASH_DF_BLOCK_782, id, val);
	} else if (id >= 1098560) {
		setA(FLASH_DF_BLOCK_781, id, val);
	} else if (id >= 1098496) {
		setA(FLASH_DF_BLOCK_780, id, val);
	} else if (id >= 1098432) {
		setA(FLASH_DF_BLOCK_779, id, val);
	} else if (id >= 1098368) {
		setA(FLASH_DF_BLOCK_778, id, val);
	} else if (id >= 1098304) {
		setA(FLASH_DF_BLOCK_777, id, val);
	} else if (id >= 1098240) {
		setA(FLASH_DF_BLOCK_776, id, val);
	} else if (id >= 1098176) {
		setA(FLASH_DF_BLOCK_775, id, val);
	} else if (id >= 1098112) {
		setA(FLASH_DF_BLOCK_774, id, val);
	} else if (id >= 1098048) {
		setA(FLASH_DF_BLOCK_773, id, val);
	} else if (id >= 1097984) {
		setA(FLASH_DF_BLOCK_772, id, val);
	} else if (id >= 1097920) {
		setA(FLASH_DF_BLOCK_771, id, val);
	} else if (id >= 1097856) {
		setA(FLASH_DF_BLOCK_770, id, val);
	} else if (id >= 1097792) {
		setA(FLASH_DF_BLOCK_769, id, val);
	} else if (id >= 1097728) {
		setA(FLASH_DF_BLOCK_768, id, val);
	} else if (id >= 1097664) {
		setA(FLASH_DF_BLOCK_767, id, val);
	} else if (id >= 1097600) {
		setA(FLASH_DF_BLOCK_766, id, val);
	} else if (id >= 1097536) {
		setA(FLASH_DF_BLOCK_765, id, val);
	} else if (id >= 1097472) {
		setA(FLASH_DF_BLOCK_764, id, val);
	} else if (id >= 1097408) {
		setA(FLASH_DF_BLOCK_763, id, val);
	} else if (id >= 1097344) {
		setA(FLASH_DF_BLOCK_762, id, val);
	} else if (id >= 1097280) {
		setA(FLASH_DF_BLOCK_761, id, val);
	} else if (id >= 1097216) {
		setA(FLASH_DF_BLOCK_760, id, val);
	} else if (id >= 1097152) {
		setA(FLASH_DF_BLOCK_759, id, val);
	} else if (id >= 1097088) {
		setA(FLASH_DF_BLOCK_758, id, val);
	} else if (id >= 1097024) {
		setA(FLASH_DF_BLOCK_757, id, val);
	} else if (id >= 1096960) {
		setA(FLASH_DF_BLOCK_756, id, val);
	} else if (id >= 1096896) {
		setA(FLASH_DF_BLOCK_755, id, val);
	} else if (id >= 1096832) {
		setA(FLASH_DF_BLOCK_754, id, val);
	} else if (id >= 1096768) {
		setA(FLASH_DF_BLOCK_753, id, val);
	} else if (id >= 1096704) {
		setA(FLASH_DF_BLOCK_752, id, val);
	} else if (id >= 1096640) {
		setA(FLASH_DF_BLOCK_751, id, val);
	} else if (id >= 1096576) {
		setA(FLASH_DF_BLOCK_750, id, val);
	} else if (id >= 1096512) {
		setA(FLASH_DF_BLOCK_749, id, val);
	} else if (id >= 1096448) {
		setA(FLASH_DF_BLOCK_748, id, val);
	} else if (id >= 1096384) {
		setA(FLASH_DF_BLOCK_747, id, val);
	} else if (id >= 1096320) {
		setA(FLASH_DF_BLOCK_746, id, val);
	} else if (id >= 1096256) {
		setA(FLASH_DF_BLOCK_745, id, val);
	} else if (id >= 1096192) {
		setA(FLASH_DF_BLOCK_744, id, val);
	} else if (id >= 1096128) {
		setA(FLASH_DF_BLOCK_743, id, val);
	} else if (id >= 1096064) {
		setA(FLASH_DF_BLOCK_742, id, val);
	} else if (id >= 1096000) {
		setA(FLASH_DF_BLOCK_741, id, val);
	} else if (id >= 1095936) {
		setA(FLASH_DF_BLOCK_740, id, val);
	} else if (id >= 1095872) {
		setA(FLASH_DF_BLOCK_739, id, val);
	} else if (id >= 1095808) {
		setA(FLASH_DF_BLOCK_738, id, val);
	} else if (id >= 1095744) {
		setA(FLASH_DF_BLOCK_737, id, val);
	} else if (id >= 1095680) {
		setA(FLASH_DF_BLOCK_736, id, val);
	} else if (id >= 1095616) {
		setA(FLASH_DF_BLOCK_735, id, val);
	} else if (id >= 1095552) {
		setA(FLASH_DF_BLOCK_734, id, val);
	} else if (id >= 1095488) {
		setA(FLASH_DF_BLOCK_733, id, val);
	} else if (id >= 1095424) {
		setA(FLASH_DF_BLOCK_732, id, val);
	} else if (id >= 1095360) {
		setA(FLASH_DF_BLOCK_731, id, val);
	} else if (id >= 1095296) {
		setA(FLASH_DF_BLOCK_730, id, val);
	} else if (id >= 1095232) {
		setA(FLASH_DF_BLOCK_729, id, val);
	} else if (id >= 1095168) {
		setA(FLASH_DF_BLOCK_728, id, val);
	} else if (id >= 1095104) {
		setA(FLASH_DF_BLOCK_727, id, val);
	} else if (id >= 1095040) {
		setA(FLASH_DF_BLOCK_726, id, val);
	} else if (id >= 1094976) {
		setA(FLASH_DF_BLOCK_725, id, val);
	} else if (id >= 1094912) {
		setA(FLASH_DF_BLOCK_724, id, val);
	} else if (id >= 1094848) {
		setA(FLASH_DF_BLOCK_723, id, val);
	} else if (id >= 1094784) {
		setA(FLASH_DF_BLOCK_722, id, val);
	} else if (id >= 1094720) {
		setA(FLASH_DF_BLOCK_721, id, val);
	} else if (id >= 1094656) {
		setA(FLASH_DF_BLOCK_720, id, val);
	} else if (id >= 1094592) {
		setA(FLASH_DF_BLOCK_719, id, val);
	} else if (id >= 1094528) {
		setA(FLASH_DF_BLOCK_718, id, val);
	} else if (id >= 1094464) {
		setA(FLASH_DF_BLOCK_717, id, val);
	} else if (id >= 1094400) {
		setA(FLASH_DF_BLOCK_716, id, val);
	} else if (id >= 1094336) {
		setA(FLASH_DF_BLOCK_715, id, val);
	} else if (id >= 1094272) {
		setA(FLASH_DF_BLOCK_714, id, val);
	} else if (id >= 1094208) {
		setA(FLASH_DF_BLOCK_713, id, val);
	} else if (id >= 1094144) {
		setA(FLASH_DF_BLOCK_712, id, val);
	} else if (id >= 1094080) {
		setA(FLASH_DF_BLOCK_711, id, val);
	} else if (id >= 1094016) {
		setA(FLASH_DF_BLOCK_710, id, val);
	} else if (id >= 1093952) {
		setA(FLASH_DF_BLOCK_709, id, val);
	} else if (id >= 1093888) {
		setA(FLASH_DF_BLOCK_708, id, val);
	} else if (id >= 1093824) {
		setA(FLASH_DF_BLOCK_707, id, val);
	} else if (id >= 1093760) {
		setA(FLASH_DF_BLOCK_706, id, val);
	} else if (id >= 1093696) {
		setA(FLASH_DF_BLOCK_705, id, val);
	} else if (id >= 1093632) {
		setA(FLASH_DF_BLOCK_704, id, val);
	} else if (id >= 1093568) {
		setA(FLASH_DF_BLOCK_703, id, val);
	} else if (id >= 1093504) {
		setA(FLASH_DF_BLOCK_702, id, val);
	} else if (id >= 1093440) {
		setA(FLASH_DF_BLOCK_701, id, val);
	} else if (id >= 1093376) {
		setA(FLASH_DF_BLOCK_700, id, val);
	} else if (id >= 1093312) {
		setA(FLASH_DF_BLOCK_699, id, val);
	} else if (id >= 1093248) {
		setA(FLASH_DF_BLOCK_698, id, val);
	} else if (id >= 1093184) {
		setA(FLASH_DF_BLOCK_697, id, val);
	} else if (id >= 1093120) {
		setA(FLASH_DF_BLOCK_696, id, val);
	} else if (id >= 1093056) {
		setA(FLASH_DF_BLOCK_695, id, val);
	} else if (id >= 1092992) {
		setA(FLASH_DF_BLOCK_694, id, val);
	} else if (id >= 1092928) {
		setA(FLASH_DF_BLOCK_693, id, val);
	} else if (id >= 1092864) {
		setA(FLASH_DF_BLOCK_692, id, val);
	} else if (id >= 1092800) {
		setA(FLASH_DF_BLOCK_691, id, val);
	} else if (id >= 1092736) {
		setA(FLASH_DF_BLOCK_690, id, val);
	} else if (id >= 1092672) {
		setA(FLASH_DF_BLOCK_689, id, val);
	} else if (id >= 1092608) {
		setA(FLASH_DF_BLOCK_688, id, val);
	} else if (id >= 1092544) {
		setA(FLASH_DF_BLOCK_687, id, val);
	} else if (id >= 1092480) {
		setA(FLASH_DF_BLOCK_686, id, val);
	} else if (id >= 1092416) {
		setA(FLASH_DF_BLOCK_685, id, val);
	} else if (id >= 1092352) {
		setA(FLASH_DF_BLOCK_684, id, val);
	} else if (id >= 1092288) {
		setA(FLASH_DF_BLOCK_683, id, val);
	} else if (id >= 1092224) {
		setA(FLASH_DF_BLOCK_682, id, val);
	} else if (id >= 1092160) {
		setA(FLASH_DF_BLOCK_681, id, val);
	} else if (id >= 1092096) {
		setA(FLASH_DF_BLOCK_680, id, val);
	} else if (id >= 1092032) {
		setA(FLASH_DF_BLOCK_679, id, val);
	} else if (id >= 1091968) {
		setA(FLASH_DF_BLOCK_678, id, val);
	} else if (id >= 1091904) {
		setA(FLASH_DF_BLOCK_677, id, val);
	} else if (id >= 1091840) {
		setA(FLASH_DF_BLOCK_676, id, val);
	} else if (id >= 1091776) {
		setA(FLASH_DF_BLOCK_675, id, val);
	} else if (id >= 1091712) {
		setA(FLASH_DF_BLOCK_674, id, val);
	} else if (id >= 1091648) {
		setA(FLASH_DF_BLOCK_673, id, val);
	} else if (id >= 1091584) {
		setA(FLASH_DF_BLOCK_672, id, val);
	} else if (id >= 1091520) {
		setA(FLASH_DF_BLOCK_671, id, val);
	} else if (id >= 1091456) {
		setA(FLASH_DF_BLOCK_670, id, val);
	} else if (id >= 1091392) {
		setA(FLASH_DF_BLOCK_669, id, val);
	} else if (id >= 1091328) {
		setA(FLASH_DF_BLOCK_668, id, val);
	} else if (id >= 1091264) {
		setA(FLASH_DF_BLOCK_667, id, val);
	} else if (id >= 1091200) {
		setA(FLASH_DF_BLOCK_666, id, val);
	} else if (id >= 1091136) {
		setA(FLASH_DF_BLOCK_665, id, val);
	} else if (id >= 1091072) {
		setA(FLASH_DF_BLOCK_664, id, val);
	} else if (id >= 1091008) {
		setA(FLASH_DF_BLOCK_663, id, val);
	} else if (id >= 1090944) {
		setA(FLASH_DF_BLOCK_662, id, val);
	} else if (id >= 1090880) {
		setA(FLASH_DF_BLOCK_661, id, val);
	} else if (id >= 1090816) {
		setA(FLASH_DF_BLOCK_660, id, val);
	} else if (id >= 1090752) {
		setA(FLASH_DF_BLOCK_659, id, val);
	} else if (id >= 1090688) {
		setA(FLASH_DF_BLOCK_658, id, val);
	} else if (id >= 1090624) {
		setA(FLASH_DF_BLOCK_657, id, val);
	} else if (id >= 1090560) {
		setA(FLASH_DF_BLOCK_656, id, val);
	} else if (id >= 1090496) {
		setA(FLASH_DF_BLOCK_655, id, val);
	} else if (id >= 1090432) {
		setA(FLASH_DF_BLOCK_654, id, val);
	} else if (id >= 1090368) {
		setA(FLASH_DF_BLOCK_653, id, val);
	} else if (id >= 1090304) {
		setA(FLASH_DF_BLOCK_652, id, val);
	} else if (id >= 1090240) {
		setA(FLASH_DF_BLOCK_651, id, val);
	} else if (id >= 1090176) {
		setA(FLASH_DF_BLOCK_650, id, val);
	} else if (id >= 1090112) {
		setA(FLASH_DF_BLOCK_649, id, val);
	} else if (id >= 1090048) {
		setA(FLASH_DF_BLOCK_648, id, val);
	} else if (id >= 1089984) {
		setA(FLASH_DF_BLOCK_647, id, val);
	} else if (id >= 1089920) {
		setA(FLASH_DF_BLOCK_646, id, val);
	} else if (id >= 1089856) {
		setA(FLASH_DF_BLOCK_645, id, val);
	} else if (id >= 1089792) {
		setA(FLASH_DF_BLOCK_644, id, val);
	} else if (id >= 1089728) {
		setA(FLASH_DF_BLOCK_643, id, val);
	} else if (id >= 1089664) {
		setA(FLASH_DF_BLOCK_642, id, val);
	} else if (id >= 1089600) {
		setA(FLASH_DF_BLOCK_641, id, val);
	} else if (id >= 1089536) {
		setA(FLASH_DF_BLOCK_640, id, val);
	} else if (id >= 1089472) {
		setA(FLASH_DF_BLOCK_639, id, val);
	} else if (id >= 1089408) {
		setA(FLASH_DF_BLOCK_638, id, val);
	} else if (id >= 1089344) {
		setA(FLASH_DF_BLOCK_637, id, val);
	} else if (id >= 1089280) {
		setA(FLASH_DF_BLOCK_636, id, val);
	} else if (id >= 1089216) {
		setA(FLASH_DF_BLOCK_635, id, val);
	} else if (id >= 1089152) {
		setA(FLASH_DF_BLOCK_634, id, val);
	} else if (id >= 1089088) {
		setA(FLASH_DF_BLOCK_633, id, val);
	} else if (id >= 1089024) {
		setA(FLASH_DF_BLOCK_632, id, val);
	} else if (id >= 1088960) {
		setA(FLASH_DF_BLOCK_631, id, val);
	} else if (id >= 1088896) {
		setA(FLASH_DF_BLOCK_630, id, val);
	} else if (id >= 1088832) {
		setA(FLASH_DF_BLOCK_629, id, val);
	} else if (id >= 1088768) {
		setA(FLASH_DF_BLOCK_628, id, val);
	} else if (id >= 1088704) {
		setA(FLASH_DF_BLOCK_627, id, val);
	} else if (id >= 1088640) {
		setA(FLASH_DF_BLOCK_626, id, val);
	} else if (id >= 1088576) {
		setA(FLASH_DF_BLOCK_625, id, val);
	} else if (id >= 1088512) {
		setA(FLASH_DF_BLOCK_624, id, val);
	} else if (id >= 1088448) {
		setA(FLASH_DF_BLOCK_623, id, val);
	} else if (id >= 1088384) {
		setA(FLASH_DF_BLOCK_622, id, val);
	} else if (id >= 1088320) {
		setA(FLASH_DF_BLOCK_621, id, val);
	} else if (id >= 1088256) {
		setA(FLASH_DF_BLOCK_620, id, val);
	} else if (id >= 1088192) {
		setA(FLASH_DF_BLOCK_619, id, val);
	} else if (id >= 1088128) {
		setA(FLASH_DF_BLOCK_618, id, val);
	} else if (id >= 1088064) {
		setA(FLASH_DF_BLOCK_617, id, val);
	} else if (id >= 1088000) {
		setA(FLASH_DF_BLOCK_616, id, val);
	} else if (id >= 1087936) {
		setA(FLASH_DF_BLOCK_615, id, val);
	} else if (id >= 1087872) {
		setA(FLASH_DF_BLOCK_614, id, val);
	} else if (id >= 1087808) {
		setA(FLASH_DF_BLOCK_613, id, val);
	} else if (id >= 1087744) {
		setA(FLASH_DF_BLOCK_612, id, val);
	} else if (id >= 1087680) {
		setA(FLASH_DF_BLOCK_611, id, val);
	} else if (id >= 1087616) {
		setA(FLASH_DF_BLOCK_610, id, val);
	} else if (id >= 1087552) {
		setA(FLASH_DF_BLOCK_609, id, val);
	} else if (id >= 1087488) {
		setA(FLASH_DF_BLOCK_608, id, val);
	} else if (id >= 1087424) {
		setA(FLASH_DF_BLOCK_607, id, val);
	} else if (id >= 1087360) {
		setA(FLASH_DF_BLOCK_606, id, val);
	} else if (id >= 1087296) {
		setA(FLASH_DF_BLOCK_605, id, val);
	} else if (id >= 1087232) {
		setA(FLASH_DF_BLOCK_604, id, val);
	} else if (id >= 1087168) {
		setA(FLASH_DF_BLOCK_603, id, val);
	} else if (id >= 1087104) {
		setA(FLASH_DF_BLOCK_602, id, val);
	} else if (id >= 1087040) {
		setA(FLASH_DF_BLOCK_601, id, val);
	} else if (id >= 1086976) {
		setA(FLASH_DF_BLOCK_600, id, val);
	} else if (id >= 1086912) {
		setA(FLASH_DF_BLOCK_599, id, val);
	} else if (id >= 1086848) {
		setA(FLASH_DF_BLOCK_598, id, val);
	} else if (id >= 1086784) {
		setA(FLASH_DF_BLOCK_597, id, val);
	} else if (id >= 1086720) {
		setA(FLASH_DF_BLOCK_596, id, val);
	} else if (id >= 1086656) {
		setA(FLASH_DF_BLOCK_595, id, val);
	} else if (id >= 1086592) {
		setA(FLASH_DF_BLOCK_594, id, val);
	} else if (id >= 1086528) {
		setA(FLASH_DF_BLOCK_593, id, val);
	} else if (id >= 1086464) {
		setA(FLASH_DF_BLOCK_592, id, val);
	} else if (id >= 1086400) {
		setA(FLASH_DF_BLOCK_591, id, val);
	} else if (id >= 1086336) {
		setA(FLASH_DF_BLOCK_590, id, val);
	} else if (id >= 1086272) {
		setA(FLASH_DF_BLOCK_589, id, val);
	} else if (id >= 1086208) {
		setA(FLASH_DF_BLOCK_588, id, val);
	} else if (id >= 1086144) {
		setA(FLASH_DF_BLOCK_587, id, val);
	} else if (id >= 1086080) {
		setA(FLASH_DF_BLOCK_586, id, val);
	} else if (id >= 1086016) {
		setA(FLASH_DF_BLOCK_585, id, val);
	} else if (id >= 1085952) {
		setA(FLASH_DF_BLOCK_584, id, val);
	} else if (id >= 1085888) {
		setA(FLASH_DF_BLOCK_583, id, val);
	} else if (id >= 1085824) {
		setA(FLASH_DF_BLOCK_582, id, val);
	} else if (id >= 1085760) {
		setA(FLASH_DF_BLOCK_581, id, val);
	} else if (id >= 1085696) {
		setA(FLASH_DF_BLOCK_580, id, val);
	} else if (id >= 1085632) {
		setA(FLASH_DF_BLOCK_579, id, val);
	} else if (id >= 1085568) {
		setA(FLASH_DF_BLOCK_578, id, val);
	} else if (id >= 1085504) {
		setA(FLASH_DF_BLOCK_577, id, val);
	} else if (id >= 1085440) {
		setA(FLASH_DF_BLOCK_576, id, val);
	} else if (id >= 1085376) {
		setA(FLASH_DF_BLOCK_575, id, val);
	} else if (id >= 1085312) {
		setA(FLASH_DF_BLOCK_574, id, val);
	} else if (id >= 1085248) {
		setA(FLASH_DF_BLOCK_573, id, val);
	} else if (id >= 1085184) {
		setA(FLASH_DF_BLOCK_572, id, val);
	} else if (id >= 1085120) {
		setA(FLASH_DF_BLOCK_571, id, val);
	} else if (id >= 1085056) {
		setA(FLASH_DF_BLOCK_570, id, val);
	} else if (id >= 1084992) {
		setA(FLASH_DF_BLOCK_569, id, val);
	} else if (id >= 1084928) {
		setA(FLASH_DF_BLOCK_568, id, val);
	} else if (id >= 1084864) {
		setA(FLASH_DF_BLOCK_567, id, val);
	} else if (id >= 1084800) {
		setA(FLASH_DF_BLOCK_566, id, val);
	} else if (id >= 1084736) {
		setA(FLASH_DF_BLOCK_565, id, val);
	} else if (id >= 1084672) {
		setA(FLASH_DF_BLOCK_564, id, val);
	} else if (id >= 1084608) {
		setA(FLASH_DF_BLOCK_563, id, val);
	} else if (id >= 1084544) {
		setA(FLASH_DF_BLOCK_562, id, val);
	} else if (id >= 1084480) {
		setA(FLASH_DF_BLOCK_561, id, val);
	} else if (id >= 1084416) {
		setA(FLASH_DF_BLOCK_560, id, val);
	} else if (id >= 1084352) {
		setA(FLASH_DF_BLOCK_559, id, val);
	} else if (id >= 1084288) {
		setA(FLASH_DF_BLOCK_558, id, val);
	} else if (id >= 1084224) {
		setA(FLASH_DF_BLOCK_557, id, val);
	} else if (id >= 1084160) {
		setA(FLASH_DF_BLOCK_556, id, val);
	} else if (id >= 1084096) {
		setA(FLASH_DF_BLOCK_555, id, val);
	} else if (id >= 1084032) {
		setA(FLASH_DF_BLOCK_554, id, val);
	} else if (id >= 1083968) {
		setA(FLASH_DF_BLOCK_553, id, val);
	} else if (id >= 1083904) {
		setA(FLASH_DF_BLOCK_552, id, val);
	} else if (id >= 1083840) {
		setA(FLASH_DF_BLOCK_551, id, val);
	} else if (id >= 1083776) {
		setA(FLASH_DF_BLOCK_550, id, val);
	} else if (id >= 1083712) {
		setA(FLASH_DF_BLOCK_549, id, val);
	} else if (id >= 1083648) {
		setA(FLASH_DF_BLOCK_548, id, val);
	} else if (id >= 1083584) {
		setA(FLASH_DF_BLOCK_547, id, val);
	} else if (id >= 1083520) {
		setA(FLASH_DF_BLOCK_546, id, val);
	} else if (id >= 1083456) {
		setA(FLASH_DF_BLOCK_545, id, val);
	} else if (id >= 1083392) {
		setA(FLASH_DF_BLOCK_544, id, val);
	} else if (id >= 1083328) {
		setA(FLASH_DF_BLOCK_543, id, val);
	} else if (id >= 1083264) {
		setA(FLASH_DF_BLOCK_542, id, val);
	} else if (id >= 1083200) {
		setA(FLASH_DF_BLOCK_541, id, val);
	} else if (id >= 1083136) {
		setA(FLASH_DF_BLOCK_540, id, val);
	} else if (id >= 1083072) {
		setA(FLASH_DF_BLOCK_539, id, val);
	} else if (id >= 1083008) {
		setA(FLASH_DF_BLOCK_538, id, val);
	} else if (id >= 1082944) {
		setA(FLASH_DF_BLOCK_537, id, val);
	} else if (id >= 1082880) {
		setA(FLASH_DF_BLOCK_536, id, val);
	} else if (id >= 1082816) {
		setA(FLASH_DF_BLOCK_535, id, val);
	} else if (id >= 1082752) {
		setA(FLASH_DF_BLOCK_534, id, val);
	} else if (id >= 1082688) {
		setA(FLASH_DF_BLOCK_533, id, val);
	} else if (id >= 1082624) {
		setA(FLASH_DF_BLOCK_532, id, val);
	} else if (id >= 1082560) {
		setA(FLASH_DF_BLOCK_531, id, val);
	} else if (id >= 1082496) {
		setA(FLASH_DF_BLOCK_530, id, val);
	} else if (id >= 1082432) {
		setA(FLASH_DF_BLOCK_529, id, val);
	} else if (id >= 1082368) {
		setA(FLASH_DF_BLOCK_528, id, val);
	} else if (id >= 1082304) {
		setA(FLASH_DF_BLOCK_527, id, val);
	} else if (id >= 1082240) {
		setA(FLASH_DF_BLOCK_526, id, val);
	} else if (id >= 1082176) {
		setA(FLASH_DF_BLOCK_525, id, val);
	} else if (id >= 1082112) {
		setA(FLASH_DF_BLOCK_524, id, val);
	} else if (id >= 1082048) {
		setA(FLASH_DF_BLOCK_523, id, val);
	} else if (id >= 1081984) {
		setA(FLASH_DF_BLOCK_522, id, val);
	} else if (id >= 1081920) {
		setA(FLASH_DF_BLOCK_521, id, val);
	} else if (id >= 1081856) {
		setA(FLASH_DF_BLOCK_520, id, val);
	} else if (id >= 1081792) {
		setA(FLASH_DF_BLOCK_519, id, val);
	} else if (id >= 1081728) {
		setA(FLASH_DF_BLOCK_518, id, val);
	} else if (id >= 1081664) {
		setA(FLASH_DF_BLOCK_517, id, val);
	} else if (id >= 1081600) {
		setA(FLASH_DF_BLOCK_516, id, val);
	} else if (id >= 1081536) {
		setA(FLASH_DF_BLOCK_515, id, val);
	} else if (id >= 1081472) {
		setA(FLASH_DF_BLOCK_514, id, val);
	} else if (id >= 1081408) {
		setA(FLASH_DF_BLOCK_513, id, val);
	} else if (id >= 1081344) {
		setA(FLASH_DF_BLOCK_512, id, val);
	} else if (id >= 1081280) {
		setA(FLASH_DF_BLOCK_511, id, val);
	} else if (id >= 1081216) {
		setA(FLASH_DF_BLOCK_510, id, val);
	} else if (id >= 1081152) {
		setA(FLASH_DF_BLOCK_509, id, val);
	} else if (id >= 1081088) {
		setA(FLASH_DF_BLOCK_508, id, val);
	} else if (id >= 1081024) {
		setA(FLASH_DF_BLOCK_507, id, val);
	} else if (id >= 1080960) {
		setA(FLASH_DF_BLOCK_506, id, val);
	} else if (id >= 1080896) {
		setA(FLASH_DF_BLOCK_505, id, val);
	} else if (id >= 1080832) {
		setA(FLASH_DF_BLOCK_504, id, val);
	} else if (id >= 1080768) {
		setA(FLASH_DF_BLOCK_503, id, val);
	} else if (id >= 1080704) {
		setA(FLASH_DF_BLOCK_502, id, val);
	} else if (id >= 1080640) {
		setA(FLASH_DF_BLOCK_501, id, val);
	} else if (id >= 1080576) {
		setA(FLASH_DF_BLOCK_500, id, val);
	} else if (id >= 1080512) {
		setA(FLASH_DF_BLOCK_499, id, val);
	} else if (id >= 1080448) {
		setA(FLASH_DF_BLOCK_498, id, val);
	} else if (id >= 1080384) {
		setA(FLASH_DF_BLOCK_497, id, val);
	} else if (id >= 1080320) {
		setA(FLASH_DF_BLOCK_496, id, val);
	} else if (id >= 1080256) {
		setA(FLASH_DF_BLOCK_495, id, val);
	} else if (id >= 1080192) {
		setA(FLASH_DF_BLOCK_494, id, val);
	} else if (id >= 1080128) {
		setA(FLASH_DF_BLOCK_493, id, val);
	} else if (id >= 1080064) {
		setA(FLASH_DF_BLOCK_492, id, val);
	} else if (id >= 1080000) {
		setA(FLASH_DF_BLOCK_491, id, val);
	} else if (id >= 1079936) {
		setA(FLASH_DF_BLOCK_490, id, val);
	} else if (id >= 1079872) {
		setA(FLASH_DF_BLOCK_489, id, val);
	} else if (id >= 1079808) {
		setA(FLASH_DF_BLOCK_488, id, val);
	} else if (id >= 1079744) {
		setA(FLASH_DF_BLOCK_487, id, val);
	} else if (id >= 1079680) {
		setA(FLASH_DF_BLOCK_486, id, val);
	} else if (id >= 1079616) {
		setA(FLASH_DF_BLOCK_485, id, val);
	} else if (id >= 1079552) {
		setA(FLASH_DF_BLOCK_484, id, val);
	} else if (id >= 1079488) {
		setA(FLASH_DF_BLOCK_483, id, val);
	} else if (id >= 1079424) {
		setA(FLASH_DF_BLOCK_482, id, val);
	} else if (id >= 1079360) {
		setA(FLASH_DF_BLOCK_481, id, val);
	} else if (id >= 1079296) {
		setA(FLASH_DF_BLOCK_480, id, val);
	} else if (id >= 1079232) {
		setA(FLASH_DF_BLOCK_479, id, val);
	} else if (id >= 1079168) {
		setA(FLASH_DF_BLOCK_478, id, val);
	} else if (id >= 1079104) {
		setA(FLASH_DF_BLOCK_477, id, val);
	} else if (id >= 1079040) {
		setA(FLASH_DF_BLOCK_476, id, val);
	} else if (id >= 1078976) {
		setA(FLASH_DF_BLOCK_475, id, val);
	} else if (id >= 1078912) {
		setA(FLASH_DF_BLOCK_474, id, val);
	} else if (id >= 1078848) {
		setA(FLASH_DF_BLOCK_473, id, val);
	} else if (id >= 1078784) {
		setA(FLASH_DF_BLOCK_472, id, val);
	} else if (id >= 1078720) {
		setA(FLASH_DF_BLOCK_471, id, val);
	} else if (id >= 1078656) {
		setA(FLASH_DF_BLOCK_470, id, val);
	} else if (id >= 1078592) {
		setA(FLASH_DF_BLOCK_469, id, val);
	} else if (id >= 1078528) {
		setA(FLASH_DF_BLOCK_468, id, val);
	} else if (id >= 1078464) {
		setA(FLASH_DF_BLOCK_467, id, val);
	} else if (id >= 1078400) {
		setA(FLASH_DF_BLOCK_466, id, val);
	} else if (id >= 1078336) {
		setA(FLASH_DF_BLOCK_465, id, val);
	} else if (id >= 1078272) {
		setA(FLASH_DF_BLOCK_464, id, val);
	} else if (id >= 1078208) {
		setA(FLASH_DF_BLOCK_463, id, val);
	} else if (id >= 1078144) {
		setA(FLASH_DF_BLOCK_462, id, val);
	} else if (id >= 1078080) {
		setA(FLASH_DF_BLOCK_461, id, val);
	} else if (id >= 1078016) {
		setA(FLASH_DF_BLOCK_460, id, val);
	} else if (id >= 1077952) {
		setA(FLASH_DF_BLOCK_459, id, val);
	} else if (id >= 1077888) {
		setA(FLASH_DF_BLOCK_458, id, val);
	} else if (id >= 1077824) {
		setA(FLASH_DF_BLOCK_457, id, val);
	} else if (id >= 1077760) {
		setA(FLASH_DF_BLOCK_456, id, val);
	} else if (id >= 1077696) {
		setA(FLASH_DF_BLOCK_455, id, val);
	} else if (id >= 1077632) {
		setA(FLASH_DF_BLOCK_454, id, val);
	} else if (id >= 1077568) {
		setA(FLASH_DF_BLOCK_453, id, val);
	} else if (id >= 1077504) {
		setA(FLASH_DF_BLOCK_452, id, val);
	} else if (id >= 1077440) {
		setA(FLASH_DF_BLOCK_451, id, val);
	} else if (id >= 1077376) {
		setA(FLASH_DF_BLOCK_450, id, val);
	} else if (id >= 1077312) {
		setA(FLASH_DF_BLOCK_449, id, val);
	} else if (id >= 1077248) {
		setA(FLASH_DF_BLOCK_448, id, val);
	} else if (id >= 1077184) {
		setA(FLASH_DF_BLOCK_447, id, val);
	} else if (id >= 1077120) {
		setA(FLASH_DF_BLOCK_446, id, val);
	} else if (id >= 1077056) {
		setA(FLASH_DF_BLOCK_445, id, val);
	} else if (id >= 1076992) {
		setA(FLASH_DF_BLOCK_444, id, val);
	} else if (id >= 1076928) {
		setA(FLASH_DF_BLOCK_443, id, val);
	} else if (id >= 1076864) {
		setA(FLASH_DF_BLOCK_442, id, val);
	} else if (id >= 1076800) {
		setA(FLASH_DF_BLOCK_441, id, val);
	} else if (id >= 1076736) {
		setA(FLASH_DF_BLOCK_440, id, val);
	} else if (id >= 1076672) {
		setA(FLASH_DF_BLOCK_439, id, val);
	} else if (id >= 1076608) {
		setA(FLASH_DF_BLOCK_438, id, val);
	} else if (id >= 1076544) {
		setA(FLASH_DF_BLOCK_437, id, val);
	} else if (id >= 1076480) {
		setA(FLASH_DF_BLOCK_436, id, val);
	} else if (id >= 1076416) {
		setA(FLASH_DF_BLOCK_435, id, val);
	} else if (id >= 1076352) {
		setA(FLASH_DF_BLOCK_434, id, val);
	} else if (id >= 1076288) {
		setA(FLASH_DF_BLOCK_433, id, val);
	} else if (id >= 1076224) {
		setA(FLASH_DF_BLOCK_432, id, val);
	} else if (id >= 1076160) {
		setA(FLASH_DF_BLOCK_431, id, val);
	} else if (id >= 1076096) {
		setA(FLASH_DF_BLOCK_430, id, val);
	} else if (id >= 1076032) {
		setA(FLASH_DF_BLOCK_429, id, val);
	} else if (id >= 1075968) {
		setA(FLASH_DF_BLOCK_428, id, val);
	} else if (id >= 1075904) {
		setA(FLASH_DF_BLOCK_427, id, val);
	} else if (id >= 1075840) {
		setA(FLASH_DF_BLOCK_426, id, val);
	} else if (id >= 1075776) {
		setA(FLASH_DF_BLOCK_425, id, val);
	} else if (id >= 1075712) {
		setA(FLASH_DF_BLOCK_424, id, val);
	} else if (id >= 1075648) {
		setA(FLASH_DF_BLOCK_423, id, val);
	} else if (id >= 1075584) {
		setA(FLASH_DF_BLOCK_422, id, val);
	} else if (id >= 1075520) {
		setA(FLASH_DF_BLOCK_421, id, val);
	} else if (id >= 1075456) {
		setA(FLASH_DF_BLOCK_420, id, val);
	} else if (id >= 1075392) {
		setA(FLASH_DF_BLOCK_419, id, val);
	} else if (id >= 1075328) {
		setA(FLASH_DF_BLOCK_418, id, val);
	} else if (id >= 1075264) {
		setA(FLASH_DF_BLOCK_417, id, val);
	} else if (id >= 1075200) {
		setA(FLASH_DF_BLOCK_416, id, val);
	} else if (id >= 1075136) {
		setA(FLASH_DF_BLOCK_415, id, val);
	} else if (id >= 1075072) {
		setA(FLASH_DF_BLOCK_414, id, val);
	} else if (id >= 1075008) {
		setA(FLASH_DF_BLOCK_413, id, val);
	} else if (id >= 1074944) {
		setA(FLASH_DF_BLOCK_412, id, val);
	} else if (id >= 1074880) {
		setA(FLASH_DF_BLOCK_411, id, val);
	} else if (id >= 1074816) {
		setA(FLASH_DF_BLOCK_410, id, val);
	} else if (id >= 1074752) {
		setA(FLASH_DF_BLOCK_409, id, val);
	} else if (id >= 1074688) {
		setA(FLASH_DF_BLOCK_408, id, val);
	} else if (id >= 1074624) {
		setA(FLASH_DF_BLOCK_407, id, val);
	} else if (id >= 1074560) {
		setA(FLASH_DF_BLOCK_406, id, val);
	} else if (id >= 1074496) {
		setA(FLASH_DF_BLOCK_405, id, val);
	} else if (id >= 1074432) {
		setA(FLASH_DF_BLOCK_404, id, val);
	} else if (id >= 1074368) {
		setA(FLASH_DF_BLOCK_403, id, val);
	} else if (id >= 1074304) {
		setA(FLASH_DF_BLOCK_402, id, val);
	} else if (id >= 1074240) {
		setA(FLASH_DF_BLOCK_401, id, val);
	} else if (id >= 1074176) {
		setA(FLASH_DF_BLOCK_400, id, val);
	} else if (id >= 1074112) {
		setA(FLASH_DF_BLOCK_399, id, val);
	} else if (id >= 1074048) {
		setA(FLASH_DF_BLOCK_398, id, val);
	} else if (id >= 1073984) {
		setA(FLASH_DF_BLOCK_397, id, val);
	} else if (id >= 1073920) {
		setA(FLASH_DF_BLOCK_396, id, val);
	} else if (id >= 1073856) {
		setA(FLASH_DF_BLOCK_395, id, val);
	} else if (id >= 1073792) {
		setA(FLASH_DF_BLOCK_394, id, val);
	} else if (id >= 1073728) {
		setA(FLASH_DF_BLOCK_393, id, val);
	} else if (id >= 1073664) {
		setA(FLASH_DF_BLOCK_392, id, val);
	} else if (id >= 1073600) {
		setA(FLASH_DF_BLOCK_391, id, val);
	} else if (id >= 1073536) {
		setA(FLASH_DF_BLOCK_390, id, val);
	} else if (id >= 1073472) {
		setA(FLASH_DF_BLOCK_389, id, val);
	} else if (id >= 1073408) {
		setA(FLASH_DF_BLOCK_388, id, val);
	} else if (id >= 1073344) {
		setA(FLASH_DF_BLOCK_387, id, val);
	} else if (id >= 1073280) {
		setA(FLASH_DF_BLOCK_386, id, val);
	} else if (id >= 1073216) {
		setA(FLASH_DF_BLOCK_385, id, val);
	} else if (id >= 1073152) {
		setA(FLASH_DF_BLOCK_384, id, val);
	} else if (id >= 1073088) {
		setA(FLASH_DF_BLOCK_383, id, val);
	} else if (id >= 1073024) {
		setA(FLASH_DF_BLOCK_382, id, val);
	} else if (id >= 1072960) {
		setA(FLASH_DF_BLOCK_381, id, val);
	} else if (id >= 1072896) {
		setA(FLASH_DF_BLOCK_380, id, val);
	} else if (id >= 1072832) {
		setA(FLASH_DF_BLOCK_379, id, val);
	} else if (id >= 1072768) {
		setA(FLASH_DF_BLOCK_378, id, val);
	} else if (id >= 1072704) {
		setA(FLASH_DF_BLOCK_377, id, val);
	} else if (id >= 1072640) {
		setA(FLASH_DF_BLOCK_376, id, val);
	} else if (id >= 1072576) {
		setA(FLASH_DF_BLOCK_375, id, val);
	} else if (id >= 1072512) {
		setA(FLASH_DF_BLOCK_374, id, val);
	} else if (id >= 1072448) {
		setA(FLASH_DF_BLOCK_373, id, val);
	} else if (id >= 1072384) {
		setA(FLASH_DF_BLOCK_372, id, val);
	} else if (id >= 1072320) {
		setA(FLASH_DF_BLOCK_371, id, val);
	} else if (id >= 1072256) {
		setA(FLASH_DF_BLOCK_370, id, val);
	} else if (id >= 1072192) {
		setA(FLASH_DF_BLOCK_369, id, val);
	} else if (id >= 1072128) {
		setA(FLASH_DF_BLOCK_368, id, val);
	} else if (id >= 1072064) {
		setA(FLASH_DF_BLOCK_367, id, val);
	} else if (id >= 1072000) {
		setA(FLASH_DF_BLOCK_366, id, val);
	} else if (id >= 1071936) {
		setA(FLASH_DF_BLOCK_365, id, val);
	} else if (id >= 1071872) {
		setA(FLASH_DF_BLOCK_364, id, val);
	} else if (id >= 1071808) {
		setA(FLASH_DF_BLOCK_363, id, val);
	} else if (id >= 1071744) {
		setA(FLASH_DF_BLOCK_362, id, val);
	} else if (id >= 1071680) {
		setA(FLASH_DF_BLOCK_361, id, val);
	} else if (id >= 1071616) {
		setA(FLASH_DF_BLOCK_360, id, val);
	} else if (id >= 1071552) {
		setA(FLASH_DF_BLOCK_359, id, val);
	} else if (id >= 1071488) {
		setA(FLASH_DF_BLOCK_358, id, val);
	} else if (id >= 1071424) {
		setA(FLASH_DF_BLOCK_357, id, val);
	} else if (id >= 1071360) {
		setA(FLASH_DF_BLOCK_356, id, val);
	} else if (id >= 1071296) {
		setA(FLASH_DF_BLOCK_355, id, val);
	} else if (id >= 1071232) {
		setA(FLASH_DF_BLOCK_354, id, val);
	} else if (id >= 1071168) {
		setA(FLASH_DF_BLOCK_353, id, val);
	} else if (id >= 1071104) {
		setA(FLASH_DF_BLOCK_352, id, val);
	} else if (id >= 1071040) {
		setA(FLASH_DF_BLOCK_351, id, val);
	} else if (id >= 1070976) {
		setA(FLASH_DF_BLOCK_350, id, val);
	} else if (id >= 1070912) {
		setA(FLASH_DF_BLOCK_349, id, val);
	} else if (id >= 1070848) {
		setA(FLASH_DF_BLOCK_348, id, val);
	} else if (id >= 1070784) {
		setA(FLASH_DF_BLOCK_347, id, val);
	} else if (id >= 1070720) {
		setA(FLASH_DF_BLOCK_346, id, val);
	} else if (id >= 1070656) {
		setA(FLASH_DF_BLOCK_345, id, val);
	} else if (id >= 1070592) {
		setA(FLASH_DF_BLOCK_344, id, val);
	} else if (id >= 1070528) {
		setA(FLASH_DF_BLOCK_343, id, val);
	} else if (id >= 1070464) {
		setA(FLASH_DF_BLOCK_342, id, val);
	} else if (id >= 1070400) {
		setA(FLASH_DF_BLOCK_341, id, val);
	} else if (id >= 1070336) {
		setA(FLASH_DF_BLOCK_340, id, val);
	} else if (id >= 1070272) {
		setA(FLASH_DF_BLOCK_339, id, val);
	} else if (id >= 1070208) {
		setA(FLASH_DF_BLOCK_338, id, val);
	} else if (id >= 1070144) {
		setA(FLASH_DF_BLOCK_337, id, val);
	} else if (id >= 1070080) {
		setA(FLASH_DF_BLOCK_336, id, val);
	} else if (id >= 1070016) {
		setA(FLASH_DF_BLOCK_335, id, val);
	} else if (id >= 1069952) {
		setA(FLASH_DF_BLOCK_334, id, val);
	} else if (id >= 1069888) {
		setA(FLASH_DF_BLOCK_333, id, val);
	} else if (id >= 1069824) {
		setA(FLASH_DF_BLOCK_332, id, val);
	} else if (id >= 1069760) {
		setA(FLASH_DF_BLOCK_331, id, val);
	} else if (id >= 1069696) {
		setA(FLASH_DF_BLOCK_330, id, val);
	} else if (id >= 1069632) {
		setA(FLASH_DF_BLOCK_329, id, val);
	} else if (id >= 1069568) {
		setA(FLASH_DF_BLOCK_328, id, val);
	} else if (id >= 1069504) {
		setA(FLASH_DF_BLOCK_327, id, val);
	} else if (id >= 1069440) {
		setA(FLASH_DF_BLOCK_326, id, val);
	} else if (id >= 1069376) {
		setA(FLASH_DF_BLOCK_325, id, val);
	} else if (id >= 1069312) {
		setA(FLASH_DF_BLOCK_324, id, val);
	} else if (id >= 1069248) {
		setA(FLASH_DF_BLOCK_323, id, val);
	} else if (id >= 1069184) {
		setA(FLASH_DF_BLOCK_322, id, val);
	} else if (id >= 1069120) {
		setA(FLASH_DF_BLOCK_321, id, val);
	} else if (id >= 1069056) {
		setA(FLASH_DF_BLOCK_320, id, val);
	} else if (id >= 1068992) {
		setA(FLASH_DF_BLOCK_319, id, val);
	} else if (id >= 1068928) {
		setA(FLASH_DF_BLOCK_318, id, val);
	} else if (id >= 1068864) {
		setA(FLASH_DF_BLOCK_317, id, val);
	} else if (id >= 1068800) {
		setA(FLASH_DF_BLOCK_316, id, val);
	} else if (id >= 1068736) {
		setA(FLASH_DF_BLOCK_315, id, val);
	} else if (id >= 1068672) {
		setA(FLASH_DF_BLOCK_314, id, val);
	} else if (id >= 1068608) {
		setA(FLASH_DF_BLOCK_313, id, val);
	} else if (id >= 1068544) {
		setA(FLASH_DF_BLOCK_312, id, val);
	} else if (id >= 1068480) {
		setA(FLASH_DF_BLOCK_311, id, val);
	} else if (id >= 1068416) {
		setA(FLASH_DF_BLOCK_310, id, val);
	} else if (id >= 1068352) {
		setA(FLASH_DF_BLOCK_309, id, val);
	} else if (id >= 1068288) {
		setA(FLASH_DF_BLOCK_308, id, val);
	} else if (id >= 1068224) {
		setA(FLASH_DF_BLOCK_307, id, val);
	} else if (id >= 1068160) {
		setA(FLASH_DF_BLOCK_306, id, val);
	} else if (id >= 1068096) {
		setA(FLASH_DF_BLOCK_305, id, val);
	} else if (id >= 1068032) {
		setA(FLASH_DF_BLOCK_304, id, val);
	} else if (id >= 1067968) {
		setA(FLASH_DF_BLOCK_303, id, val);
	} else if (id >= 1067904) {
		setA(FLASH_DF_BLOCK_302, id, val);
	} else if (id >= 1067840) {
		setA(FLASH_DF_BLOCK_301, id, val);
	} else if (id >= 1067776) {
		setA(FLASH_DF_BLOCK_300, id, val);
	} else if (id >= 1067712) {
		setA(FLASH_DF_BLOCK_299, id, val);
	} else if (id >= 1067648) {
		setA(FLASH_DF_BLOCK_298, id, val);
	} else if (id >= 1067584) {
		setA(FLASH_DF_BLOCK_297, id, val);
	} else if (id >= 1067520) {
		setA(FLASH_DF_BLOCK_296, id, val);
	} else if (id >= 1067456) {
		setA(FLASH_DF_BLOCK_295, id, val);
	} else if (id >= 1067392) {
		setA(FLASH_DF_BLOCK_294, id, val);
	} else if (id >= 1067328) {
		setA(FLASH_DF_BLOCK_293, id, val);
	} else if (id >= 1067264) {
		setA(FLASH_DF_BLOCK_292, id, val);
	} else if (id >= 1067200) {
		setA(FLASH_DF_BLOCK_291, id, val);
	} else if (id >= 1067136) {
		setA(FLASH_DF_BLOCK_290, id, val);
	} else if (id >= 1067072) {
		setA(FLASH_DF_BLOCK_289, id, val);
	} else if (id >= 1067008) {
		setA(FLASH_DF_BLOCK_288, id, val);
	} else if (id >= 1066944) {
		setA(FLASH_DF_BLOCK_287, id, val);
	} else if (id >= 1066880) {
		setA(FLASH_DF_BLOCK_286, id, val);
	} else if (id >= 1066816) {
		setA(FLASH_DF_BLOCK_285, id, val);
	} else if (id >= 1066752) {
		setA(FLASH_DF_BLOCK_284, id, val);
	} else if (id >= 1066688) {
		setA(FLASH_DF_BLOCK_283, id, val);
	} else if (id >= 1066624) {
		setA(FLASH_DF_BLOCK_282, id, val);
	} else if (id >= 1066560) {
		setA(FLASH_DF_BLOCK_281, id, val);
	} else if (id >= 1066496) {
		setA(FLASH_DF_BLOCK_280, id, val);
	} else if (id >= 1066432) {
		setA(FLASH_DF_BLOCK_279, id, val);
	} else if (id >= 1066368) {
		setA(FLASH_DF_BLOCK_278, id, val);
	} else if (id >= 1066304) {
		setA(FLASH_DF_BLOCK_277, id, val);
	} else if (id >= 1066240) {
		setA(FLASH_DF_BLOCK_276, id, val);
	} else if (id >= 1066176) {
		setA(FLASH_DF_BLOCK_275, id, val);
	} else if (id >= 1066112) {
		setA(FLASH_DF_BLOCK_274, id, val);
	} else if (id >= 1066048) {
		setA(FLASH_DF_BLOCK_273, id, val);
	} else if (id >= 1065984) {
		setA(FLASH_DF_BLOCK_272, id, val);
	} else if (id >= 1065920) {
		setA(FLASH_DF_BLOCK_271, id, val);
	} else if (id >= 1065856) {
		setA(FLASH_DF_BLOCK_270, id, val);
	} else if (id >= 1065792) {
		setA(FLASH_DF_BLOCK_269, id, val);
	} else if (id >= 1065728) {
		setA(FLASH_DF_BLOCK_268, id, val);
	} else if (id >= 1065664) {
		setA(FLASH_DF_BLOCK_267, id, val);
	} else if (id >= 1065600) {
		setA(FLASH_DF_BLOCK_266, id, val);
	} else if (id >= 1065536) {
		setA(FLASH_DF_BLOCK_265, id, val);
	} else if (id >= 1065472) {
		setA(FLASH_DF_BLOCK_264, id, val);
	} else if (id >= 1065408) {
		setA(FLASH_DF_BLOCK_263, id, val);
	} else if (id >= 1065344) {
		setA(FLASH_DF_BLOCK_262, id, val);
	} else if (id >= 1065280) {
		setA(FLASH_DF_BLOCK_261, id, val);
	} else if (id >= 1065216) {
		setA(FLASH_DF_BLOCK_260, id, val);
	} else if (id >= 1065152) {
		setA(FLASH_DF_BLOCK_259, id, val);
	} else if (id >= 1065088) {
		setA(FLASH_DF_BLOCK_258, id, val);
	} else if (id >= 1065024) {
		setA(FLASH_DF_BLOCK_257, id, val);
	} else if (id >= 1064960) {
		setA(FLASH_DF_BLOCK_256, id, val);
	} else if (id >= 1064896) {
		setA(FLASH_DF_BLOCK_255, id, val);
	} else if (id >= 1064832) {
		setA(FLASH_DF_BLOCK_254, id, val);
	} else if (id >= 1064768) {
		setA(FLASH_DF_BLOCK_253, id, val);
	} else if (id >= 1064704) {
		setA(FLASH_DF_BLOCK_252, id, val);
	} else if (id >= 1064640) {
		setA(FLASH_DF_BLOCK_251, id, val);
	} else if (id >= 1064576) {
		setA(FLASH_DF_BLOCK_250, id, val);
	} else if (id >= 1064512) {
		setA(FLASH_DF_BLOCK_249, id, val);
	} else if (id >= 1064448) {
		setA(FLASH_DF_BLOCK_248, id, val);
	} else if (id >= 1064384) {
		setA(FLASH_DF_BLOCK_247, id, val);
	} else if (id >= 1064320) {
		setA(FLASH_DF_BLOCK_246, id, val);
	} else if (id >= 1064256) {
		setA(FLASH_DF_BLOCK_245, id, val);
	} else if (id >= 1064192) {
		setA(FLASH_DF_BLOCK_244, id, val);
	} else if (id >= 1064128) {
		setA(FLASH_DF_BLOCK_243, id, val);
	} else if (id >= 1064064) {
		setA(FLASH_DF_BLOCK_242, id, val);
	} else if (id >= 1064000) {
		setA(FLASH_DF_BLOCK_241, id, val);
	} else if (id >= 1063936) {
		setA(FLASH_DF_BLOCK_240, id, val);
	} else if (id >= 1063872) {
		setA(FLASH_DF_BLOCK_239, id, val);
	} else if (id >= 1063808) {
		setA(FLASH_DF_BLOCK_238, id, val);
	} else if (id >= 1063744) {
		setA(FLASH_DF_BLOCK_237, id, val);
	} else if (id >= 1063680) {
		setA(FLASH_DF_BLOCK_236, id, val);
	} else if (id >= 1063616) {
		setA(FLASH_DF_BLOCK_235, id, val);
	} else if (id >= 1063552) {
		setA(FLASH_DF_BLOCK_234, id, val);
	} else if (id >= 1063488) {
		setA(FLASH_DF_BLOCK_233, id, val);
	} else if (id >= 1063424) {
		setA(FLASH_DF_BLOCK_232, id, val);
	} else if (id >= 1063360) {
		setA(FLASH_DF_BLOCK_231, id, val);
	} else if (id >= 1063296) {
		setA(FLASH_DF_BLOCK_230, id, val);
	} else if (id >= 1063232) {
		setA(FLASH_DF_BLOCK_229, id, val);
	} else if (id >= 1063168) {
		setA(FLASH_DF_BLOCK_228, id, val);
	} else if (id >= 1063104) {
		setA(FLASH_DF_BLOCK_227, id, val);
	} else if (id >= 1063040) {
		setA(FLASH_DF_BLOCK_226, id, val);
	} else if (id >= 1062976) {
		setA(FLASH_DF_BLOCK_225, id, val);
	} else if (id >= 1062912) {
		setA(FLASH_DF_BLOCK_224, id, val);
	} else if (id >= 1062848) {
		setA(FLASH_DF_BLOCK_223, id, val);
	} else if (id >= 1062784) {
		setA(FLASH_DF_BLOCK_222, id, val);
	} else if (id >= 1062720) {
		setA(FLASH_DF_BLOCK_221, id, val);
	} else if (id >= 1062656) {
		setA(FLASH_DF_BLOCK_220, id, val);
	} else if (id >= 1062592) {
		setA(FLASH_DF_BLOCK_219, id, val);
	} else if (id >= 1062528) {
		setA(FLASH_DF_BLOCK_218, id, val);
	} else if (id >= 1062464) {
		setA(FLASH_DF_BLOCK_217, id, val);
	} else if (id >= 1062400) {
		setA(FLASH_DF_BLOCK_216, id, val);
	} else if (id >= 1062336) {
		setA(FLASH_DF_BLOCK_215, id, val);
	} else if (id >= 1062272) {
		setA(FLASH_DF_BLOCK_214, id, val);
	} else if (id >= 1062208) {
		setA(FLASH_DF_BLOCK_213, id, val);
	} else if (id >= 1062144) {
		setA(FLASH_DF_BLOCK_212, id, val);
	} else if (id >= 1062080) {
		setA(FLASH_DF_BLOCK_211, id, val);
	} else if (id >= 1062016) {
		setA(FLASH_DF_BLOCK_210, id, val);
	} else if (id >= 1061952) {
		setA(FLASH_DF_BLOCK_209, id, val);
	} else if (id >= 1061888) {
		setA(FLASH_DF_BLOCK_208, id, val);
	} else if (id >= 1061824) {
		setA(FLASH_DF_BLOCK_207, id, val);
	} else if (id >= 1061760) {
		setA(FLASH_DF_BLOCK_206, id, val);
	} else if (id >= 1061696) {
		setA(FLASH_DF_BLOCK_205, id, val);
	} else if (id >= 1061632) {
		setA(FLASH_DF_BLOCK_204, id, val);
	} else if (id >= 1061568) {
		setA(FLASH_DF_BLOCK_203, id, val);
	} else if (id >= 1061504) {
		setA(FLASH_DF_BLOCK_202, id, val);
	} else if (id >= 1061440) {
		setA(FLASH_DF_BLOCK_201, id, val);
	} else if (id >= 1061376) {
		setA(FLASH_DF_BLOCK_200, id, val);
	} else if (id >= 1061312) {
		setA(FLASH_DF_BLOCK_199, id, val);
	} else if (id >= 1061248) {
		setA(FLASH_DF_BLOCK_198, id, val);
	} else if (id >= 1061184) {
		setA(FLASH_DF_BLOCK_197, id, val);
	} else if (id >= 1061120) {
		setA(FLASH_DF_BLOCK_196, id, val);
	} else if (id >= 1061056) {
		setA(FLASH_DF_BLOCK_195, id, val);
	} else if (id >= 1060992) {
		setA(FLASH_DF_BLOCK_194, id, val);
	} else if (id >= 1060928) {
		setA(FLASH_DF_BLOCK_193, id, val);
	} else if (id >= 1060864) {
		setA(FLASH_DF_BLOCK_192, id, val);
	} else if (id >= 1060800) {
		setA(FLASH_DF_BLOCK_191, id, val);
	} else if (id >= 1060736) {
		setA(FLASH_DF_BLOCK_190, id, val);
	} else if (id >= 1060672) {
		setA(FLASH_DF_BLOCK_189, id, val);
	} else if (id >= 1060608) {
		setA(FLASH_DF_BLOCK_188, id, val);
	} else if (id >= 1060544) {
		setA(FLASH_DF_BLOCK_187, id, val);
	} else if (id >= 1060480) {
		setA(FLASH_DF_BLOCK_186, id, val);
	} else if (id >= 1060416) {
		setA(FLASH_DF_BLOCK_185, id, val);
	} else if (id >= 1060352) {
		setA(FLASH_DF_BLOCK_184, id, val);
	} else if (id >= 1060288) {
		setA(FLASH_DF_BLOCK_183, id, val);
	} else if (id >= 1060224) {
		setA(FLASH_DF_BLOCK_182, id, val);
	} else if (id >= 1060160) {
		setA(FLASH_DF_BLOCK_181, id, val);
	} else if (id >= 1060096) {
		setA(FLASH_DF_BLOCK_180, id, val);
	} else if (id >= 1060032) {
		setA(FLASH_DF_BLOCK_179, id, val);
	} else if (id >= 1059968) {
		setA(FLASH_DF_BLOCK_178, id, val);
	} else if (id >= 1059904) {
		setA(FLASH_DF_BLOCK_177, id, val);
	} else if (id >= 1059840) {
		setA(FLASH_DF_BLOCK_176, id, val);
	} else if (id >= 1059776) {
		setA(FLASH_DF_BLOCK_175, id, val);
	} else if (id >= 1059712) {
		setA(FLASH_DF_BLOCK_174, id, val);
	} else if (id >= 1059648) {
		setA(FLASH_DF_BLOCK_173, id, val);
	} else if (id >= 1059584) {
		setA(FLASH_DF_BLOCK_172, id, val);
	} else if (id >= 1059520) {
		setA(FLASH_DF_BLOCK_171, id, val);
	} else if (id >= 1059456) {
		setA(FLASH_DF_BLOCK_170, id, val);
	} else if (id >= 1059392) {
		setA(FLASH_DF_BLOCK_169, id, val);
	} else if (id >= 1059328) {
		setA(FLASH_DF_BLOCK_168, id, val);
	} else if (id >= 1059264) {
		setA(FLASH_DF_BLOCK_167, id, val);
	} else if (id >= 1059200) {
		setA(FLASH_DF_BLOCK_166, id, val);
	} else if (id >= 1059136) {
		setA(FLASH_DF_BLOCK_165, id, val);
	} else if (id >= 1059072) {
		setA(FLASH_DF_BLOCK_164, id, val);
	} else if (id >= 1059008) {
		setA(FLASH_DF_BLOCK_163, id, val);
	} else if (id >= 1058944) {
		setA(FLASH_DF_BLOCK_162, id, val);
	} else if (id >= 1058880) {
		setA(FLASH_DF_BLOCK_161, id, val);
	} else if (id >= 1058816) {
		setA(FLASH_DF_BLOCK_160, id, val);
	} else if (id >= 1058752) {
		setA(FLASH_DF_BLOCK_159, id, val);
	} else if (id >= 1058688) {
		setA(FLASH_DF_BLOCK_158, id, val);
	} else if (id >= 1058624) {
		setA(FLASH_DF_BLOCK_157, id, val);
	} else if (id >= 1058560) {
		setA(FLASH_DF_BLOCK_156, id, val);
	} else if (id >= 1058496) {
		setA(FLASH_DF_BLOCK_155, id, val);
	} else if (id >= 1058432) {
		setA(FLASH_DF_BLOCK_154, id, val);
	} else if (id >= 1058368) {
		setA(FLASH_DF_BLOCK_153, id, val);
	} else if (id >= 1058304) {
		setA(FLASH_DF_BLOCK_152, id, val);
	} else if (id >= 1058240) {
		setA(FLASH_DF_BLOCK_151, id, val);
	} else if (id >= 1058176) {
		setA(FLASH_DF_BLOCK_150, id, val);
	} else if (id >= 1058112) {
		setA(FLASH_DF_BLOCK_149, id, val);
	} else if (id >= 1058048) {
		setA(FLASH_DF_BLOCK_148, id, val);
	} else if (id >= 1057984) {
		setA(FLASH_DF_BLOCK_147, id, val);
	} else if (id >= 1057920) {
		setA(FLASH_DF_BLOCK_146, id, val);
	} else if (id >= 1057856) {
		setA(FLASH_DF_BLOCK_145, id, val);
	} else if (id >= 1057792) {
		setA(FLASH_DF_BLOCK_144, id, val);
	} else if (id >= 1057728) {
		setA(FLASH_DF_BLOCK_143, id, val);
	} else if (id >= 1057664) {
		setA(FLASH_DF_BLOCK_142, id, val);
	} else if (id >= 1057600) {
		setA(FLASH_DF_BLOCK_141, id, val);
	} else if (id >= 1057536) {
		setA(FLASH_DF_BLOCK_140, id, val);
	} else if (id >= 1057472) {
		setA(FLASH_DF_BLOCK_139, id, val);
	} else if (id >= 1057408) {
		setA(FLASH_DF_BLOCK_138, id, val);
	} else if (id >= 1057344) {
		setA(FLASH_DF_BLOCK_137, id, val);
	} else if (id >= 1057280) {
		setA(FLASH_DF_BLOCK_136, id, val);
	} else if (id >= 1057216) {
		setA(FLASH_DF_BLOCK_135, id, val);
	} else if (id >= 1057152) {
		setA(FLASH_DF_BLOCK_134, id, val);
	} else if (id >= 1057088) {
		setA(FLASH_DF_BLOCK_133, id, val);
	} else if (id >= 1057024) {
		setA(FLASH_DF_BLOCK_132, id, val);
	} else if (id >= 1056960) {
		setA(FLASH_DF_BLOCK_131, id, val);
	} else if (id >= 1056896) {
		setA(FLASH_DF_BLOCK_130, id, val);
	} else if (id >= 1056832) {
		setA(FLASH_DF_BLOCK_129, id, val);
	} else if (id >= 1056768) {
		setA(FLASH_DF_BLOCK_128, id, val);
	} else if (id >= 1056704) {
		setA(FLASH_DF_BLOCK_127, id, val);
	} else if (id >= 1056640) {
		setA(FLASH_DF_BLOCK_126, id, val);
	} else if (id >= 1056576) {
		setA(FLASH_DF_BLOCK_125, id, val);
	} else if (id >= 1056512) {
		setA(FLASH_DF_BLOCK_124, id, val);
	} else if (id >= 1056448) {
		setA(FLASH_DF_BLOCK_123, id, val);
	} else if (id >= 1056384) {
		setA(FLASH_DF_BLOCK_122, id, val);
	} else if (id >= 1056320) {
		setA(FLASH_DF_BLOCK_121, id, val);
	} else if (id >= 1056256) {
		setA(FLASH_DF_BLOCK_120, id, val);
	} else if (id >= 1056192) {
		setA(FLASH_DF_BLOCK_119, id, val);
	} else if (id >= 1056128) {
		setA(FLASH_DF_BLOCK_118, id, val);
	} else if (id >= 1056064) {
		setA(FLASH_DF_BLOCK_117, id, val);
	} else if (id >= 1056000) {
		setA(FLASH_DF_BLOCK_116, id, val);
	} else if (id >= 1055936) {
		setA(FLASH_DF_BLOCK_115, id, val);
	} else if (id >= 1055872) {
		setA(FLASH_DF_BLOCK_114, id, val);
	} else if (id >= 1055808) {
		setA(FLASH_DF_BLOCK_113, id, val);
	} else if (id >= 1055744) {
		setA(FLASH_DF_BLOCK_112, id, val);
	} else if (id >= 1055680) {
		setA(FLASH_DF_BLOCK_111, id, val);
	} else if (id >= 1055616) {
		setA(FLASH_DF_BLOCK_110, id, val);
	} else if (id >= 1055552) {
		setA(FLASH_DF_BLOCK_109, id, val);
	} else if (id >= 1055488) {
		setA(FLASH_DF_BLOCK_108, id, val);
	} else if (id >= 1055424) {
		setA(FLASH_DF_BLOCK_107, id, val);
	} else if (id >= 1055360) {
		setA(FLASH_DF_BLOCK_106, id, val);
	} else if (id >= 1055296) {
		setA(FLASH_DF_BLOCK_105, id, val);
	} else if (id >= 1055232) {
		setA(FLASH_DF_BLOCK_104, id, val);
	} else if (id >= 1055168) {
		setA(FLASH_DF_BLOCK_103, id, val);
	} else if (id >= 1055104) {
		setA(FLASH_DF_BLOCK_102, id, val);
	} else if (id >= 1055040) {
		setA(FLASH_DF_BLOCK_101, id, val);
	} else if (id >= 1054976) {
		setA(FLASH_DF_BLOCK_100, id, val);
	} else if (id >= 1054912) {
		setA(FLASH_DF_BLOCK_99, id, val);
	} else if (id >= 1054848) {
		setA(FLASH_DF_BLOCK_98, id, val);
	} else if (id >= 1054784) {
		setA(FLASH_DF_BLOCK_97, id, val);
	} else if (id >= 1054720) {
		setA(FLASH_DF_BLOCK_96, id, val);
	} else if (id >= 1054656) {
		setA(FLASH_DF_BLOCK_95, id, val);
	} else if (id >= 1054592) {
		setA(FLASH_DF_BLOCK_94, id, val);
	} else if (id >= 1054528) {
		setA(FLASH_DF_BLOCK_93, id, val);
	} else if (id >= 1054464) {
		setA(FLASH_DF_BLOCK_92, id, val);
	} else if (id >= 1054400) {
		setA(FLASH_DF_BLOCK_91, id, val);
	} else if (id >= 1054336) {
		setA(FLASH_DF_BLOCK_90, id, val);
	} else if (id >= 1054272) {
		setA(FLASH_DF_BLOCK_89, id, val);
	} else if (id >= 1054208) {
		setA(FLASH_DF_BLOCK_88, id, val);
	} else if (id >= 1054144) {
		setA(FLASH_DF_BLOCK_87, id, val);
	} else if (id >= 1054080) {
		setA(FLASH_DF_BLOCK_86, id, val);
	} else if (id >= 1054016) {
		setA(FLASH_DF_BLOCK_85, id, val);
	} else if (id >= 1053952) {
		setA(FLASH_DF_BLOCK_84, id, val);
	} else if (id >= 1053888) {
		setA(FLASH_DF_BLOCK_83, id, val);
	} else if (id >= 1053824) {
		setA(FLASH_DF_BLOCK_82, id, val);
	} else if (id >= 1053760) {
		setA(FLASH_DF_BLOCK_81, id, val);
	} else if (id >= 1053696) {
		setA(FLASH_DF_BLOCK_80, id, val);
	} else if (id >= 1053632) {
		setA(FLASH_DF_BLOCK_79, id, val);
	} else if (id >= 1053568) {
		setA(FLASH_DF_BLOCK_78, id, val);
	} else if (id >= 1053504) {
		setA(FLASH_DF_BLOCK_77, id, val);
	} else if (id >= 1053440) {
		setA(FLASH_DF_BLOCK_76, id, val);
	} else if (id >= 1053376) {
		setA(FLASH_DF_BLOCK_75, id, val);
	} else if (id >= 1053312) {
		setA(FLASH_DF_BLOCK_74, id, val);
	} else if (id >= 1053248) {
		setA(FLASH_DF_BLOCK_73, id, val);
	} else if (id >= 1053184) {
		setA(FLASH_DF_BLOCK_72, id, val);
	} else if (id >= 1053120) {
		setA(FLASH_DF_BLOCK_71, id, val);
	} else if (id >= 1053056) {
		setA(FLASH_DF_BLOCK_70, id, val);
	} else if (id >= 1052992) {
		setA(FLASH_DF_BLOCK_69, id, val);
	} else if (id >= 1052928) {
		setA(FLASH_DF_BLOCK_68, id, val);
	} else if (id >= 1052864) {
		setA(FLASH_DF_BLOCK_67, id, val);
	} else if (id >= 1052800) {
		setA(FLASH_DF_BLOCK_66, id, val);
	} else if (id >= 1052736) {
		setA(FLASH_DF_BLOCK_65, id, val);
	} else if (id >= 1052672) {
		setA(FLASH_DF_BLOCK_64, id, val);
	} else if (id >= 1052608) {
		setA(FLASH_DF_BLOCK_63, id, val);
	} else if (id >= 1052544) {
		setA(FLASH_DF_BLOCK_62, id, val);
	} else if (id >= 1052480) {
		setA(FLASH_DF_BLOCK_61, id, val);
	} else if (id >= 1052416) {
		setA(FLASH_DF_BLOCK_60, id, val);
	} else if (id >= 1052352) {
		setA(FLASH_DF_BLOCK_59, id, val);
	} else if (id >= 1052288) {
		setA(FLASH_DF_BLOCK_58, id, val);
	} else if (id >= 1052224) {
		setA(FLASH_DF_BLOCK_57, id, val);
	} else if (id >= 1052160) {
		setA(FLASH_DF_BLOCK_56, id, val);
	} else if (id >= 1052096) {
		setA(FLASH_DF_BLOCK_55, id, val);
	} else if (id >= 1052032) {
		setA(FLASH_DF_BLOCK_54, id, val);
	} else if (id >= 1051968) {
		setA(FLASH_DF_BLOCK_53, id, val);
	} else if (id >= 1051904) {
		setA(FLASH_DF_BLOCK_52, id, val);
	} else if (id >= 1051840) {
		setA(FLASH_DF_BLOCK_51, id, val);
	} else if (id >= 1051776) {
		setA(FLASH_DF_BLOCK_50, id, val);
	} else if (id >= 1051712) {
		setA(FLASH_DF_BLOCK_49, id, val);
	} else if (id >= 1051648) {
		setA(FLASH_DF_BLOCK_48, id, val);
	} else if (id >= 1051584) {
		setA(FLASH_DF_BLOCK_47, id, val);
	} else if (id >= 1051520) {
		setA(FLASH_DF_BLOCK_46, id, val);
	} else if (id >= 1051456) {
		setA(FLASH_DF_BLOCK_45, id, val);
	} else if (id >= 1051392) {
		setA(FLASH_DF_BLOCK_44, id, val);
	} else if (id >= 1051328) {
		setA(FLASH_DF_BLOCK_43, id, val);
	} else if (id >= 1051264) {
		setA(FLASH_DF_BLOCK_42, id, val);
	} else if (id >= 1051200) {
		setA(FLASH_DF_BLOCK_41, id, val);
	} else if (id >= 1051136) {
		setA(FLASH_DF_BLOCK_40, id, val);
	} else if (id >= 1051072) {
		setA(FLASH_DF_BLOCK_39, id, val);
	} else if (id >= 1051008) {
		setA(FLASH_DF_BLOCK_38, id, val);
	} else if (id >= 1050944) {
		setA(FLASH_DF_BLOCK_37, id, val);
	} else if (id >= 1050880) {
		setA(FLASH_DF_BLOCK_36, id, val);
	} else if (id >= 1050816) {
		setA(FLASH_DF_BLOCK_35, id, val);
	} else if (id >= 1050752) {
		setA(FLASH_DF_BLOCK_34, id, val);
	} else if (id >= 1050688) {
		setA(FLASH_DF_BLOCK_33, id, val);
	} else if (id >= 1050624) {
		setA(FLASH_DF_BLOCK_32, id, val);
	} else if (id >= 1050560) {
		setA(FLASH_DF_BLOCK_31, id, val);
	} else if (id >= 1050496) {
		setA(FLASH_DF_BLOCK_30, id, val);
	} else if (id >= 1050432) {
		setA(FLASH_DF_BLOCK_29, id, val);
	} else if (id >= 1050368) {
		setA(FLASH_DF_BLOCK_28, id, val);
	} else if (id >= 1050304) {
		setA(FLASH_DF_BLOCK_27, id, val);
	} else if (id >= 1050240) {
		setA(FLASH_DF_BLOCK_26, id, val);
	} else if (id >= 1050176) {
		setA(FLASH_DF_BLOCK_25, id, val);
	} else if (id >= 1050112) {
		setA(FLASH_DF_BLOCK_24, id, val);
	} else if (id >= 1050048) {
		setA(FLASH_DF_BLOCK_23, id, val);
	} else if (id >= 1049984) {
		setA(FLASH_DF_BLOCK_22, id, val);
	} else if (id >= 1049920) {
		setA(FLASH_DF_BLOCK_21, id, val);
	} else if (id >= 1049856) {
		setA(FLASH_DF_BLOCK_20, id, val);
	} else if (id >= 1049792) {
		setA(FLASH_DF_BLOCK_19, id, val);
	} else if (id >= 1049728) {
		setA(FLASH_DF_BLOCK_18, id, val);
	} else if (id >= 1049664) {
		setA(FLASH_DF_BLOCK_17, id, val);
	} else if (id >= 1049600) {
		setA(FLASH_DF_BLOCK_16, id, val);
	} else if (id >= 1049536) {
		setA(FLASH_DF_BLOCK_15, id, val);
	} else if (id >= 1049472) {
		setA(FLASH_DF_BLOCK_14, id, val);
	} else if (id >= 1049408) {
		setA(FLASH_DF_BLOCK_13, id, val);
	} else if (id >= 1049344) {
		setA(FLASH_DF_BLOCK_12, id, val);
	} else if (id >= 1049280) {
		setA(FLASH_DF_BLOCK_11, id, val);
	} else if (id >= 1049216) {
		setA(FLASH_DF_BLOCK_10, id, val);
	}

}

#endif /* SERIALMAPPER_H_ */
