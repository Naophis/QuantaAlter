/*
 * defines.h
 *
 *  Created on: 2017/07/30
 *      Author: Naoto
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define STR(var) #var   //引数にした変数を変数名を示す文字列リテラルとして返すマクロ関数

#define true 1
#define false 0
volatile char setupCmt = false;
volatile int tpu_count = 0;
#define M_CYCLE 450
#define FAN_CYCLE 450

#define FRONT_AD S12AD.ADDR3 //front P43
#define RS2 S12AD.ADDR5	 //P45
#define RS45 S12AD.ADDR4 //P44
#define LS45 S12AD.ADDR1 //P41
#define LS2 S12AD.ADDR2	//P42

#define LF S12AD.ADDR6	//P46
#define BATTERY S12AD.ADDR7	//P47

#define LED1 PORTA.PODR.BIT.B7
#define LED2 PORTB.PODR.BIT.B5
#define LED3 PORTB.PODR.BIT.B6
#define LED4 PORTB.PODR.BIT.B7
#define LED_RIGHT PORTE.PODR.BIT.B2
#define LED_LEFT PORT2.PODR.BIT.B3

float settleGyro2, settleGyroOld, settleGyro;

volatile char adEnable = 1;

volatile char enableMPU = false;
float battery, batteryOld;
char fanStart = false;
char fanStart2 = false;
//#define FAN_AMP2 10.50
//#define FAN_AMP 10.50

float FAN_AMP = 9.0f;	//11.35
float FAN_AMP2 = 6.5f;	//5.0
float FAN_AMP3 = 0.0f;	//5.0
float FAN_AMP4 = 4.0f;	//5.0
float FAN_AMP5 = 3.0f;	//5.0

volatile float myVacumeDuty = 6.5;
//#define FAN_AMP 11.0	//11.35
const float PI = 3.141592653589793;

char TRANSAM = false;
double dt = 0.001 / 4;
#define ABS(IN) ((IN) < 0 ? - (IN) : (IN))
#define Vo 0.0f				//初速度
#define Wo 0.5f			//初期角速度
#define W_max 25.0f
//#define W_max 5.5f
volatile double W_now = 0;
volatile double alpha = 0.0;			//	[rad/s^2]
volatile double ang = 0.0;				//角度 rad
volatile double distance = 0.0;		//距離 mm
volatile double img_distance = 0.0;		//距離 mm
volatile double img_dist_r = 0.0;		//距離 mm
volatile double img_dist_l = 0.0;		//距離 mm
volatile char diaStrwallCount_r = 0;
volatile char diaStrwallCount_l = 0;
#define North 1
#define East 2
#define West 4
#define South 8
#define NorthEast 3
#define SouthEast 5
#define NorthWest 6
#define SouthWest 7
#define true 1
#define false 0

#define R 1					//探索時ターン　右フラグ
#define L 2					//探索時ターン　左フラグ
#define ROOT2 1.41421356f
#define pathLength 256

volatile float V_r = 0;
volatile float V_l = 0;
volatile float V_max = 600.0;	//最高速度
volatile float acc = 4000;		//加速度
volatile float V_now = Vo;		//現在速度
volatile float V_old = 0;
volatile float W_old = 0;
volatile unsigned short x = 0, y = 0;		//座標保持変数
volatile unsigned char path_s[pathLength];	//直進パス
volatile unsigned char path_t[pathLength];	//ターンパス

volatile unsigned int Value = 255;	//最小の評価値
volatile unsigned char next_move = North;
volatile unsigned char next_dir = North;
volatile unsigned char now_dir = North;

volatile char stop = 0;
volatile float v_sla[8];

volatile char os_escape;
volatile char fail = 0;
volatile unsigned int sinCount = 0;
volatile unsigned char sw;
volatile unsigned int time = 0;
volatile short gyro_temp[5];
volatile float gyro = 0;
volatile float tempGyro = 0;
volatile int temp_max = 0, temp_min = 5000;
volatile float oldGyroData = 0;
volatile float settlegyroData = 0;
volatile int tempGyro2 = 0;
volatile float settleGyro3 = 0;
volatile float controlSensour = 0;
volatile float controlGyro = 0;
volatile float w_r, w_l;
volatile float w_now;
volatile char positionControlValueFlg;
volatile char dia = 0;
volatile float Duty_r, Duty_l;
volatile unsigned long gra_r, gra_l;

volatile unsigned int meloTimer = 0;
volatile int DutyR, DutyL;
volatile float rpmR = 0, rpmL = 0;
volatile float rpmR_old = 0, rpmL_old = 0;

volatile float logterm = 5;
volatile float isouratio = 0;
volatile float isouzure = 0;
volatile float searchrange = 0;
volatile float angle = 0;
volatile char gyroErrResetEnable = false;
volatile unsigned int cc = 0;
volatile unsigned int logs = 0;
volatile float ffR, ffL;
volatile float angle_enc;
volatile char slaFLG = 0;
volatile char gyroOn = 0;
volatile float W_now2 = 0;
volatile int EtCheck = 0;
volatile int ledOn = 0;
volatile int logData = 0;
volatile char cirquitMode = 0;
#define NAPIER 0.7632146182405746f
#define NAPIER2 0.6034501613134686f
volatile char goalChangeFlg = 0;
volatile char modeFlg = 0;
volatile char allow = 1;
volatile char weightMode = 1;
volatile char wallCut_R = 0;
volatile char wallCut_L = 0;
volatile char mode_FF = 0;
volatile char fastMode = 0;
volatile float slalomBackDistance = 0;
volatile char pathMode = 1;
volatile float tempVmax = 0;
volatile char alphaMode = 0;
volatile float alphaTemp = 0;
volatile float omegaTemp = 0;
volatile float slaTerm = 0;
volatile char runFlg = 0;
volatile char errorFlg = 0;
volatile char globalError = 0;

volatile char frontWallCtrl = 0;

volatile char isKnown = 0;

volatile float tmpData = 0;
#define MAZE_SIZE  16
volatile char dist[MAZE_SIZE][MAZE_SIZE];

volatile unsigned int c = 0;
volatile unsigned int timer = 0;
#define Swich	PORTC.PIDR.BIT.B4
#define CW_R();  PORTB.PODR.BIT.B1 = 1; PORTB.PODR.BIT.B2 = 0;
#define CCW_R(); PORTB.PODR.BIT.B1 = 0; PORTB.PODR.BIT.B2 = 1;
#define CCW_L();  PORTB.PODR.BIT.B3 = 1; PORTB.PODR.BIT.B4 = 0;
#define CW_L(); PORTB.PODR.BIT.B3 = 0; PORTB.PODR.BIT.B4 = 1;

#define PushTop PORTC.PIDR.BIT.B5
#define PushCenter PORTC.PIDR.BIT.B4
#define PushLeft PORTC.PIDR.BIT.B3
#define PushRight PORTC.PIDR.BIT.B0
#define PushBottom PORTC.PIDR.BIT.B2

#define ALL 0
#define SearchMode 1
#define AtackStraight 2
#define AtackDia 3
#define AtackDia2 4
#define CtrlMode 5
volatile char sensingMode = AtackStraight;
volatile char enablePWM = false;
#define  ESC    0x1B

#define checkQlength 256
int checkQDuality[100];
int checkQ[checkQlength];
unsigned char checkMap[16][16];
unsigned char checkTurningPoint = false;
char checkPoint = false;
#define MAX 1023

char globalSkipFront = false;

void ledHex(int v) {
	char a = (v & 0x01);
	char b = (v & 0x02);
	char c = (v & 0x04);
	char d = (v & 0x08);
	LED1 = a > 0;
	LED2 = b > 0;
	LED3 = c > 0;
	LED4 = d > 0;
	LED_RIGHT = false;
	LED_LEFT = false;
}
void led(char a, char b, char c, char d) {
	LED1 = a > 0;
	LED2 = b > 0;
	LED3 = c > 0;
	LED4 = d > 0;
	LED_RIGHT = false;
	LED_LEFT = false;
}
void LED(char i) {
	LED1 = i & 0x01;
	LED2 = i & 0x02;
	LED3 = i & 0x04;
	LED4 = i & 0x08;
	LED_RIGHT = false;
	LED_LEFT = false;
}
void F_SEN_LED() {
	PORTC.PODR.BIT.B3 = 1;
}
void S1_SEN_LED() {
	PORTC.PODR.BIT.B2 = 1;
}
void S2_SEN_LED() {
//	return;
	PORT1.PODR.BIT.B5 = 1;
}
void SEN_LEDOFF() {
	PORTC.PODR.BIT.B2 = 0;
	PORTC.PODR.BIT.B3 = 0;
	PORT1.PODR.BIT.B5 = 0;
}
int gyroData = 0;
#define GYRO_Z 0x47
volatile int buzzerTimer = 0;

#define BUFSIZE		100
volatile float etN = 4; //	ネイピアべき乗数
// ｸﾞﾛｰﾊﾞﾙ変数

// SCI ﾊﾞｯﾌｧ
unsigned char g_uchBuf1[BUFSIZE];
volatile char originalDiaMode = false;
volatile char mpu = false;
// SCI ﾘﾝｸﾞﾊﾞｯﾌｧ ｲﾝﾃﾞｯｸｽ
int g_nIdx1Read;
int g_nIdx1Write;

volatile float vs[10][12];
volatile float vs2[10][12];

volatile float tmpDiac;
volatile float targetVelocity;
#define Kata 0
#define Zentansaku 1
#define Oufuku 2
unsigned char recieved_data;

#define SCI_RX_BUF_SHIFT   4
#define SCI_RX_BUF_SIZE   (1<<SCI_RX_BUF_SHIFT)
#define SCI_RX_BUF_MASK   (SCI_RX_BUF_SIZE-1)

#define motionLogLength 2048

int nextDirection = 0;
volatile unsigned char map[MAZE_SIZE][MAZE_SIZE];

typedef struct {
	unsigned int n :10;
	unsigned int e :10;
	unsigned int w :10;
	unsigned int s :10;
	unsigned int v :8;
	unsigned int N1 :4;
	unsigned int NE :4;
	unsigned int E1 :4;
	unsigned int SE :4;
	unsigned int S1 :4;
	unsigned int SW :4;
	unsigned int W1 :4;
	unsigned int NW :4;
	unsigned int step :4;

} vector_map;
volatile vector_map m[MAZE_SIZE][MAZE_SIZE];

#define Q_LENGTH 2048
int que[Q_LENGTH][3];
#define L_Length 3000
volatile int log1[L_Length];
volatile float logs2[L_Length];
volatile float log3[L_Length];
volatile float log4[L_Length];
volatile float log5[L_Length];
volatile float log6[L_Length];
volatile float log7[L_Length];
volatile float log8[L_Length];
volatile float log9[L_Length];
volatile float logs10[L_Length];
volatile float log11[L_Length];
volatile float log12[L_Length];
volatile float log13[L_Length];
volatile float log14[L_Length];
volatile float log15[L_Length];
volatile float log16[L_Length];
volatile float log17[L_Length];
volatile float log18[L_Length];
volatile float log19[L_Length];
volatile float log20[L_Length];
volatile float log21[L_Length];
volatile float log22[L_Length];
volatile float log23[L_Length];
volatile float log24[L_Length];
volatile float log25[L_Length];
volatile float log26[L_Length];
volatile float log27[L_Length];
volatile float log28[L_Length];
volatile float log29[L_Length];
volatile float log30[L_Length];
volatile float log31[L_Length];
volatile float log32[L_Length];
volatile float log33[L_Length];
volatile float log34[L_Length];
volatile float log35[L_Length];
volatile float log36[L_Length];

volatile char enableSystemIdentification = false;
volatile float sysIdDutyR = 0;
volatile float sysIdDutyL = 0;

#define DETECT_SYS_ID_Length 20
volatile float vrlist[DETECT_SYS_ID_Length];
volatile float vllist[DETECT_SYS_ID_Length];
volatile float gyrolist[DETECT_SYS_ID_Length];
volatile float dutylist[DETECT_SYS_ID_Length];

#define Cycle 24000000.0f
#define MTU_CYCLE 16000.0f	//4khz
#define _ICLK 240000000 //240MHz
#define _PCLKA 60000000.0f //60MHz
#define _PCLKB 60000000.0f //60MHz
#define CMT_CYCLE 4000 // 4kHz
#define CMT_CYCLE2 2000 // 2kHz
#define M_CYCLE2 500

#define FastRun 0
#define SearchRun 1
#define TestRun 2
#define CtrlFan 3
#define CtrlFan2 4
#define CtrlFan3 5

volatile char fanMode = SearchRun;

volatile char rotate_r = true;
volatile char rotate_l = true;

volatile char friction_str = true;
volatile char friction_roll = false;

volatile char RecvDat, ComFlag;
volatile char enableSciUpdate = false;

volatile char swTop, swBottom, swLeft, swRight, swCenter;

volatile unsigned int globalState = 0;
#define NONE 0
#define STRAIGHT 1
#define PIVOT 2
//#define SLA_TURN 2
#define SLA_TURN 3
#define SLA_BEFORE 4
#define SLA_AFTER 5
#define WALL_OFF 6
#define FRONT_ctrl 7
#define PARAREL 8
//#define DIA_STRAIGHT 2
#define DIA_STRAIGHT 9
#define WALL_OFF_WAIT 10
#define MODE_SELECT 11
#define START_WAIT 12
#define IMPORT_PARM 13

char testRunMode = false;

#define SEN_R RS_SEN45.now
#define SEN_L LS_SEN45.now
#define SEN_R2 RS_SEN2.now
#define SEN_L2 LS_SEN2.now
#define SEN_FRONT Front_SEN.now

char testMode = true;

float R_WALL_EXIST = 1900;
float L_WALL_EXIST = 1500;

float R_WALL_EXIST2 = 1600;  //探索時壁判定
float L_WALL_EXIST2 = 1500;  //探索時壁判定
float FRONT_WALL_EXIST2 = 740; //探索時壁判定

float R_WALL_EXIST3 = 420;  //探索時壁判定
float L_WALL_EXIST3 = 300;  //探索時壁判定
float FRONT_WALL_EXIST3 = 300; //探索時壁判定

float px = 0, py = 0;
float px2 = 0, py2 = 0;

float FRONT_WALL_EXIST = 800; //探索時壁判定
float R_WALL_EXIST4 = 220;  //探索時壁判定
float L_WALL_EXIST4 = 220;  //探索時壁判定

float pathVmax = 0;
float pathAcc = 0;
float pathDiac = 0;

volatile char motionDir = R;

float sen_r_dia_img[257] = { 1488.4326, 1376.7888, 1191.6425, 1052.9584,
		950.8019, 883.5596, 831.38195, 793.6073, 775.65435, 760.06765,
		746.72065, 737.4793, 729.35035, 724.2422, 718.4085, 711.68815, 705.128,
		701.985, 699.28295, 691.3585, 688.7582, 685.8697, 684.06895, 682.8786,
		684.19005, 677.17165, 674.26495, 675.26795, 675.242, 668.48055,
		672.90625, 672.36715, 677.01835, 675.83125, 678.6222, 679.21135,
		680.1012, 685.8926, 683.9983, 685.92285, 688.0695, 696.3763, 698.46165,
		699.8991, 699.5071, 703.52055, 704.5624, 710.9409, 714.32445, 719.5438,
		722.6277, 725.2677, 726.0677, 731.2166, 733.13105, 734.4301, 737.8949,
		737.6877, 737.4068, 737.65625, 739.38415, 744.4019, 748.2558, 753.1132,
		754.1947, 757.7254, 758.9503, 763.3943, 770.17045, 768.46815, 774.8846,
		777.19935, 781.17095, 783.55425, 787.7263, 792.8029, 795.6287,
		802.48535, 806.14205, 807.50415, 808.71875, 811.2923, 816.395,
		820.41215, 820.933, 826.795, 828.9912, 834.1782, 840.3005, 850.0543,
		852.4594, 859.9472, 861.7919, 865.7968, 872.9502, 879.0332, 886.4179,
		894.709, 899.7939, 905.4139, 912.6427, 917.1358, 923.1602, 927.1995,
		936.417, 940.5223, 946.4211, 952.7184, 958.8568, 966.0534, 968.672,
		973.8681, 979.15, 981.9894, 991.1655, 998.0931, 999.4421, 1005.0665,
		1011.4629, 1016.9093, 1023.3561, 1029.2998, 1030.9075, 1038.5593,
		1043.8654, 1055.7596, 1062.8573, 1070.3765, 1071.6417, 1079.4404,
		1082.816, 1093.2584, 1104.1937, 1114.5131, 1118.0724, 1124.8311,
		1134.8147, 1143.1162, 1149.5117, 1156.0144, 1161.9449, 1168.2502,
		1173.0494, 1179.4392, 1189.589, 1197.0809, 1202.1066, 1212.3324,
		1216.4021, 1224.9564, 1237.6897, 1247.5264, 1256.866, 1269.819,
		1282.4821, 1293.7498, 1308.4586, 1321.1151, 1332.8657, 1341.5605,
		1355.5591, 1367.559, 1375.5061, 1389.4176, 1394.1912, 1403.9244,
		1413.9906, 1421.7214, 1433.2542, 1442.5909, 1452.5594, 1464.3387,
		1474.6307, 1486.804, 1498.9758, 1513.3231, 1528.488, 1540.7234,
		1556.978, 1575.2739, 1591.2291, 1608.5935, 1625.1725, 1642.4111,
		1661.5696, 1679.1458, 1700.4836, 1723.3672, 1744.0768, 1765.3498,
		1788.4064, 1803.5514, 1819.0334, 1831.1988, 1838.2192, 1852.0274,
		1866.5422, 1870.7376, 1879.239, 1891.3474, 1907.423, 1915.8418,
		1930.3098, 1944.2244, 1957.8638, 1972.233, 1993.788, 2016.8952,
		2039.3522, 2064.58, 2092.1894, 2118.5796, 2145.0452, 2175.3724,
		2202.8592, 2231.842, 2256.628, 2281.9034, 2307.2812, 2335.9244,
		2357.5656, 2385.2812, 2410.9856, 2437.0586, 2465.5428, 2492.6696,
		2520.2054, 2547.071, 2570.867, 2594.6916, 2620.4426, 2641.2238,
		2645.9876, 2648.1072, 2632.379, 2602.8804, 2562.9712, 2516.9002,
		2484.968, 2475.6468, 2495.173, 2516.7058, 2533.382, 2545.9128,
		2550.0122, 2570.248, 2609.3672, 2669.5638, 2736.3464, 2789.9704,
		2794.9484, 2729.665, 2597.1806, 2393.3384, 2136.1216, 1858.3742,
		1598.1533 };

float sen_l_dia_img[254] = { 1469.5535, 1371.8575, 1197.4623, 1054.1172,
		951.5433, 876.5651, 826.021, 797.12815, 778.55555, 773.99595, 767.59325,
		761.34505, 753.42385, 750.6354, 745.97535, 739.91835, 734.70025,
		736.66285, 727.1601, 722.6848, 722.15925, 719.77915, 715.32155,
		713.26195, 713.88875, 714.09655, 712.50805, 708.34575, 705.0913,
		704.0104, 705.1714, 703.762, 703.56685, 704.0617, 703.22615, 706.85015,
		709.0935, 711.69215, 711.60545, 710.6285, 707.0531, 711.4954, 709.47465,
		712.62605, 714.03595, 718.1665, 720.30645, 723.29225, 724.86565,
		725.16145, 728.98065, 731.697, 737.4784, 740.45115, 744.2895, 743.42865,
		748.7986, 749.89585, 753.9087, 755.0913, 763.1914, 768.8654, 771.52325,
		776.21685, 779.1447, 785.6097, 786.7928, 786.15525, 789.39705,
		789.56575, 792.6823, 792.545, 798.40455, 808.249, 817.6108, 820.02205,
		823.4962, 826.70495, 833.27245, 838.51725, 848.9503, 852.2815, 859.65,
		861.892, 866.9688, 870.7848, 875.8876, 883.6679, 884.3265, 888.9118,
		893.6114, 898.2788, 903.2271, 909.973, 918.0959, 921.9121, 925.7886,
		932.7894, 938.0989, 942.2859, 946.244, 948.9405, 954.2139, 961.9986,
		976.101, 982.3061, 987.3876, 988.0215, 992.4952, 997.5516, 1007.8094,
		1017.2706, 1017.5635, 1023.2796, 1030.1205, 1031.1727, 1036.8459,
		1045.3069, 1050.3713, 1056.2708, 1064.2675, 1072.1101, 1076.4049,
		1080.2441, 1090.6083, 1105.4014, 1107.6, 1116.2881, 1125.9008,
		1138.6295, 1145.0331, 1156.0282, 1162.2473, 1171.4933, 1175.6462,
		1185.3257, 1196.3086, 1200.4712, 1210.199, 1215.2358, 1224.483,
		1238.1078, 1244.3313, 1251.5238, 1258.2566, 1271.7322, 1281.2892,
		1294.4629, 1302.0704, 1314.0874, 1324.7371, 1334.8219, 1348.299,
		1358.0605, 1363.9529, 1370.3999, 1383.6097, 1395.875, 1408.8553,
		1419.6602, 1434.2601, 1442.2286, 1452.0841, 1465.433, 1479.928,
		1496.2188, 1509.213, 1520.2695, 1535.4641, 1551.5977, 1563.9409,
		1573.3331, 1583.8785, 1592.8596, 1600.0846, 1606.3287, 1619.0348,
		1633.0208, 1639.7032, 1654.0951, 1666.3815, 1677.5736, 1692.8172,
		1702.2314, 1720.2638, 1735.0162, 1753.0238, 1770.9152, 1791.9976,
		1807.4432, 1825.5358, 1840.5332, 1860.5412, 1881.3684, 1905.654,
		1924.6882, 1943.3512, 1960.829, 1976.4118, 1993.5642, 2012.0248,
		2035.0368, 2045.8406, 2060.9804, 2073.5926, 2089.3066, 2110.1792,
		2128.78, 2140.3096, 2154.7102, 2172.7942, 2188.6988, 2207.211,
		2222.7188, 2248.2674, 2274.6154, 2290.1712, 2313.2016, 2335.6396,
		2359.461, 2381.3174, 2403.1626, 2425.7524, 2451.7626, 2473.5606,
		2506.382, 2526.0644, 2543.2476, 2557.4622, 2565.1746, 2565.4318,
		2552.1482, 2511.544, 2470.4126, 2398.7442, 2325.6564, 2263.6882,
		2231.7234, 2240.3022, 2262.332, 2302.439, 2344.1172, 2376.0452,
		2395.1752, 2400.0278, 2392.4294, 2359.262, 2317.8228, 2243.655,
		2149.0718, 2036.0034, 1896.2626, 1746.8044, 1583.8131

};
float sen_r90_dia[257] = { 1451.7867, 1466.9568, 1493.6873, 1526.1481,
		1559.0367, 1589.2045, 1622.2448, 1661.1637, 1688.1292, 1720.826,
		1755.9686, 1791.038, 1831.2238, 1865.528, 1909.8424, 1949.6768,
		1993.774, 2032.9148, 2075.8792, 2115.1426, 2153.0236, 2194.6224,
		2239.1458, 2276.3242, 2327.528, 2368.5044, 2401.7246, 2441.1298,
		2474.8086, 2509.4282, 2549.007, 2590.8772, 2637.176, 2690.856,
		2754.9236, 2826.507, 2890.5146, 2945.3328, 3001.5972, 3035.4902,
		3019.8862, 2949.8956, 2865.784, 2804.3194, 2797.4566, 2824.8242,
		2871.3718, 2919.028, 2934.2198, 2905.324, 2851.0774, 2775.5142,
		2723.7912, 2674.762, 2638.8824, 2605.9222, 2587.598, 2563.5214,
		2529.6766, 2505.9182, 2489.0622, 2458.7354, 2426.805, 2394.122,
		2359.0686, 2322.1106, 2282.0042, 2245.1894, 2209.1708, 2169.8798,
		2133.1638, 2096.7806, 2058.6866, 2027.1556, 1994.9516, 1953.5718,
		1918.422, 1890.3846, 1856.1336, 1820.8626, 1782.4608, 1755.2634,
		1714.793, 1682.7822, 1662.9988, 1624.3738, 1603.8306, 1576.3201,
		1546.2738, 1515.2374, 1487.4797, 1463.3041, 1437.8706, 1411.566,
		1391.2688, 1367.8254, 1344.524, 1323.0227, 1297.0641, 1270.5007,
		1248.0391, 1233.7577, 1205.7817, 1189.3612, 1169.9572, 1151.2805,
		1134.7286, 1117.7209, 1099.76, 1078.5488, 1066.4985, 1050.3972,
		1034.2345, 1022.237, 1010.3303, 991.4749, 979.1057, 965.2435, 952.2012,
		944.829, 931.144, 917.0866, 907.8356, 896.8597, 884.7964, 872.4882,
		862.6037, 848.1546, 838.69625, 826.98485, 824.6271, 811.32615, 802.9691,
		792.8917, 783.50245, 773.64685, 766.99395, 756.4676, 750.9956,
		743.49715, 735.74, 728.0578, 721.38445, 713.33775, 708.29, 700.04485,
		695.30255, 688.11725, 682.2335, 676.99535, 670.461, 664.9486, 655.8991,
		652.6307, 647.2677, 647.55915, 642.7802, 639.748, 636.5774, 638.8863,
		638.66705, 639.5519, 643.0046, 650.84375, 657.3749, 661.56145, 669.4746,
		678.88045, 689.3339, 696.1544, 704.19975, 708.685, 713.0425, 719.3485,
		725.14025, 721.17425, 717.54755, 712.7925, 701.59045, 690.9291, 681.356,
		666.0523, 653.5895, 644.557, 635.643, 627.0912, 616.28095, 611.97145,
		609.01695, 606.558, 604.666, 603.5954, 608.5072, 612.6654, 616.13965,
		622.07365, 626.9823, 628.59315, 637.08415, 641.731, 646.68275, 652.2239,
		656.09275, 663.95855, 672.14335, 676.29285, 682.11085, 687.1695,
		700.96645, 708.19195, 715.34845, 726.9314, 736.0681, 740.59625,
		747.0353, 759.0288, 770.05815, 779.78825, 789.5918, 797.26665, 810.2043,
		820.7804, 832.87695, 842.4494, 854.6407, 867.5917, 881.9277, 893.3129,
		909.1147, 922.5057, 937.3904, 952.3091, 968.3463, 982.7366, 999.2814,
		1016.8615, 1031.6536, 1046.069, 1063.7614, 1082.5778, 1096.3004,
		1114.8876, 1134.7747, 1151.3108, 1168.9657, 1189.4231, 1213.6216,
		1232.6357, 1259.3879, 1280.5258, 1306.3323, 1335.6052, 1364.1475,
		1393.0664, 1423.0026, 1453.3689, 1484.3302 };

float sen_l90_dia[255] = { 1295.3419, 1302.5625, 1319.7819, 1337.7126,
		1361.2255, 1379.9602, 1398.4242, 1419.0623, 1437.2531, 1455.4978,
		1475.3768, 1498.4155, 1512.7012, 1536.6752, 1555.5255, 1576.8003,
		1602.3257, 1623.0458, 1645.6764, 1662.811, 1683.6932, 1699.0762,
		1716.9036, 1736.4956, 1753.336, 1772.2818, 1787.9124, 1802.1686,
		1819.5498, 1838.51, 1858.6926, 1881.9302, 1906.513, 1944.0112,
		1987.2276, 2047.225, 2093.9212, 2107.205, 2077.4892, 2020.2088,
		1960.7718, 1907.0808, 1886.8156, 1903.7958, 1942.2038, 1976.9542,
		1985.158, 1962.4606, 1929.1952, 1897.0844, 1864.2292, 1837.3994,
		1817.9376, 1795.9146, 1781.7342, 1767.9676, 1754.4554, 1738.3286,
		1718.8242, 1699.0232, 1680.65, 1668.2588, 1651.807, 1629.5057,
		1611.1855, 1586.0032, 1565.7483, 1547.698, 1523.3599, 1501.7166,
		1484.6755, 1461.0729, 1443.9822, 1417.1611, 1390.0125, 1368.2736,
		1349.7533, 1329.5425, 1310.4642, 1291.0767, 1268.9304, 1246.5089,
		1232.1432, 1215.0984, 1196.2516, 1177.9067, 1156.4102, 1138.653,
		1121.4259, 1104.5747, 1089.4399, 1070.0417, 1059.7854, 1047.3018,
		1027.425, 1013.3107, 998.303, 983.2471, 966.8149, 957.7534, 945.2347,
		936.0819, 917.8949, 902.8374, 889.4238, 879.2582, 875.6908, 861.0577,
		846.3307, 837.8443, 827.046, 821.42535, 808.82775, 799.14785, 789.22805,
		780.6547, 768.6463, 758.2807, 752.8466, 743.92515, 742.3449, 730.84385,
		721.0717, 714.3536, 706.9074, 697.92555, 685.9797, 682.32015, 678.7655,
		665.2794, 661.44515, 654.0729, 648.674, 645.19695, 642.76335, 640.217,
		635.60085, 628.67695, 622.05015, 622.60015, 614.95025, 607.38445,
		603.718, 599.99635, 600.83915, 592.955, 592.4492, 588.4975, 582.81675,
		586.57005, 584.8377, 586.5906, 591.2935, 596.11505, 593.9845, 596.47345,
		605.49425, 615.71845, 620.7597, 626.4876, 631.91805, 636.37835,
		643.4995, 653.4963, 656.975, 663.62495, 664.0848, 665.02955, 660.36395,
		656.4396, 657.2268, 651.8744, 647.33065, 642.33435, 632.55255, 631.2196,
		621.4438, 613.9329, 610.19155, 610.47625, 599.62385, 600.64775,
		597.15265, 596.477, 599.35335, 597.33515, 597.93725, 603.0583,
		601.35865, 601.11155, 600.30945, 601.0967, 608.95565, 612.73865,
		616.2998, 622.84595, 628.4076, 630.6535, 635.61605, 640.5796, 646.8552,
		653.74635, 661.0464, 668.26485, 668.50655, 683.9022, 689.3797,
		698.64895, 701.97795, 711.4478, 722.83075, 725.85065, 729.9009,
		734.71565, 744.78485, 757.4148, 763.74895, 767.40605, 775.2898,
		790.1714, 799.84395, 806.5251, 815.5989, 825.899, 827.6797, 843.4819,
		858.821, 869.0251, 874.5046, 887.0385, 896.7977, 908.0111, 922.6475,
		929.6217, 942.9455, 953.635, 961.0397, 982.6588, 997.8577, 1009.6786,
		1019.9977, 1027.641, 1041.4908, 1059.374, 1073.5001, 1083.0258,
		1101.6931, 1117.0525, 1134.4152, 1152.5303, 1167.5642, 1189.9386,
		1206.3325, 1221.8966 };

#endif /* DEFINES_H_ */
