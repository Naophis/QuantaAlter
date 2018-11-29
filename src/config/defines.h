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
float fastRunFanV2 = 3.0f;	//5.0

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
#define FastRun2 6

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

float sen_r_dia_img[255] = { 1477.9171, 1393.0927, 1170.5577, 1109.7517,
		1010.4222, 937.2798, 875.7908, 835.8973, 809.07775, 786.6711, 770.1015,
		754.8784, 740.06315, 736.55095, 730.63175, 724.52455, 717.14995,
		715.724, 708.5731, 707.7268, 705.78005, 703.3089, 697.79915, 695.54665,
		693.2401, 692.1253, 688.1446, 690.9766, 686.5281, 687.01875, 686.6706,
		687.86945, 687.4983, 689.3725, 686.54315, 684.6316, 685.3867, 690.31,
		688.60765, 693.4355, 693.7796, 694.0671, 694.78575, 702.7049, 704.76935,
		704.47625, 707.82085, 707.7953, 708.86565, 711.2176, 712.67115,
		721.74815, 725.73695, 726.36675, 727.5703, 725.25035, 729.0428,
		730.9096, 731.0435, 734.4892, 737.1027, 739.8307, 747.46, 750.8633,
		761.2715, 764.5863, 764.17975, 769.67655, 770.29015, 777.61005, 777.533,
		781.76665, 784.27055, 787.4858, 794.35835, 795.6543, 796.4699, 800.4947,
		803.9303, 805.2407, 808.08895, 816.5006, 823.4906, 821.57165, 832.78245,
		835.67375, 837.91795, 844.3932, 851.9844, 858.9226, 862.8973, 871.3486,
		875.8707, 879.0823, 887.1522, 892.3885, 897.8337, 902.596, 902.1127,
		907.2079, 918.9109, 924.9577, 928.5505, 934.2402, 938.1918, 944.6367,
		950.4288, 954.4219, 956.8445, 968.4979, 970.4125, 975.7441, 981.4018,
		988.223, 992.4916, 999.6068, 1009.6296, 1013.3348, 1018.5192, 1025.9598,
		1027.5675, 1036.4939, 1036.3674, 1043.4844, 1049.5615, 1051.4805,
		1063.7633, 1064.7157, 1072.3594, 1081.4198, 1090.2964, 1103.0526,
		1110.5974, 1115.6047, 1124.884, 1135.1323, 1141.5447, 1152.0715,
		1155.4579, 1163.3361, 1169.2871, 1180.9125, 1195.2579, 1202.4423,
		1205.8983, 1219.1064, 1229.6154, 1248.4835, 1258.0032, 1261.9827,
		1273.2321, 1281.0568, 1289.7474, 1299.9514, 1307.77, 1325.8253,
		1340.4349, 1353.4044, 1360.3744, 1373.9371, 1383.9076, 1394.533,
		1408.1748, 1421.3165, 1433.5605, 1445.4645, 1457.8906, 1469.6992,
		1483.3184, 1495.7205, 1510.7959, 1529.1405, 1535.5637, 1546.7933,
		1562.5807, 1578.1925, 1591.4547, 1607.1698, 1619.8986, 1633.8636,
		1647.5004, 1664.5286, 1679.5338, 1690.3432, 1707.0774, 1722.767,
		1740.3404, 1760.364, 1776.7704, 1796.4616, 1812.2524, 1828.5914,
		1841.564, 1854.8812, 1870.8724, 1890.0534, 1904.9172, 1920.612,
		1937.5252, 1957.6664, 1975.549, 1993.2862, 2009.126, 2029.3588,
		2050.9126, 2075.1806, 2096.25, 2116.7046, 2142.5598, 2170.5684,
		2195.5036, 2232.3174, 2260.0564, 2289.9122, 2317.4282, 2342.4072,
		2371.4048, 2396.0584, 2422.7458, 2449.0686, 2472.8108, 2495.6508,
		2508.8372, 2530.7364, 2551.2856, 2569.6772, 2584.9322, 2605.7698,
		2626.3474, 2645.076, 2666.2492, 2682.15, 2694.5122, 2699.4146,
		2703.2614, 2692.625, 2679.9592, 2670.9986, 2667.2444, 2667.1274,
		2663.8946, 2658.4378, 2658.3332, 2671.4348, 2705.4592, 2753.804,
		2804.2234, 2834.4948, 2822.7148, 2763.7158, 2648.5132, 2472.4272,
		2250.8488, 2007.6872, 1766.387 };

float sen_l_dia_img[256] =
		{ 1499.5525, 1334.7101, 1197.0748, 1087.1545, 995.1116, 920.0004,
				865.8986, 830.8704, 803.2996, 783.3008, 768.6031, 758.96065,
				749.9103, 742.5073, 737.65465, 727.8022, 722.5761, 716.4405,
				710.6053, 705.31965, 701.572, 699.11045, 692.7759, 684.0918,
				682.01085, 682.9255, 679.39515, 678.6154, 676.9138, 676.93325,
				677.74205, 676.69465, 678.21745, 677.1291, 675.99915, 680.3935,
				680.5272, 680.7882, 678.9936, 675.66825, 682.4284, 689.65985,
				691.04255, 693.4892, 698.0226, 696.89325, 697.5696, 702.34635,
				701.4463, 700.62695, 700.48395, 705.71985, 710.709, 711.53965,
				711.4283, 716.18785, 720.82915, 725.67345, 727.71045, 730.21855,
				741.17, 738.9139, 743.84425, 749.88395, 750.06875, 755.76545,
				763.40425, 765.33565, 774.0365, 778.1233, 781.9872, 785.58085,
				791.2015, 797.25695, 798.43305, 801.99025, 805.1932, 807.04915,
				808.92625, 810.201, 817.217, 815.06965, 815.3123, 818.9785,
				821.77285, 825.21865, 828.63045, 831.61475, 834.89705, 840.6337,
				848.9537, 848.0787, 851.6627, 855.412, 858.4691, 864.8912,
				870.4851, 875.7134, 882.9431, 887.6882, 894.6201, 902.1433,
				905.7567, 909.6551, 912.8198, 918.4048, 923.8776, 928.7205,
				936.2852, 942.0576, 951.6772, 957.7548, 959.3848, 968.5164,
				975.8198, 982.4662, 989.8933, 996.9722, 999.4432, 1003.2395,
				1014.5689, 1021.5179, 1021.9866, 1028.912, 1034.1511, 1042.0046,
				1050.7009, 1061.5327, 1070.3552, 1075.0653, 1086.2434,
				1092.6688, 1100.6868, 1109.6023, 1116.0935, 1122.6057,
				1130.3845, 1134.9614, 1144.6268, 1147.2111, 1154.4131,
				1159.1812, 1172.8844, 1183.0404, 1193.2177, 1207.3784,
				1220.1536, 1229.0869, 1238.4081, 1250.34, 1254.8052, 1262.6121,
				1275.0734, 1280.5618, 1293.9301, 1303.5006, 1315.7661,
				1325.2018, 1334.4127, 1349.9164, 1361.1516, 1366.7227,
				1380.6226, 1388.3048, 1401.2317, 1416.7278, 1432.5077,
				1444.4286, 1456.6219, 1468.1791, 1476.6051, 1488.6826,
				1499.4188, 1514.9177, 1520.7338, 1534.2428, 1548.158, 1558.5721,
				1567.146, 1578.9772, 1592.394, 1604.1326, 1612.1228, 1626.8636,
				1635.9725, 1649.7758, 1666.0203, 1678.436, 1690.0942, 1702.1186,
				1714.7802, 1734.8864, 1752.7502, 1774.0506, 1791.431, 1804.3392,
				1826.445, 1842.3492, 1860.5438, 1879.2606, 1899.168, 1914.0024,
				1925.4052, 1941.692, 1957.5852, 1974.971, 1994.788, 2011.4542,
				2028.1976, 2047.8106, 2070.6126, 2089.379, 2108.3118, 2132.7166,
				2155.2886, 2176.7548, 2197.4166, 2222.1954, 2239.998, 2261.0418,
				2282.1074, 2298.239, 2307.783, 2324.8552, 2340.5332, 2346.3298,
				2355.6652, 2356.7014, 2354.0168, 2350.533, 2338.5074, 2318.1534,
				2290.2498, 2263.1832, 2237.791, 2223.0144, 2219.8958, 2230.31,
				2242.8752, 2253.721, 2272.6186, 2289.3706, 2306.2344, 2324.2714,
				2339.2006, 2340.1618, 2319.2076, 2270.9942, 2204.7996, 2107.858,
				1985.6086, 1848.9068, 1707.9968, 1554.587, 1407.2469, 1339.12 };

float sen_r90_dia[255] = { 1544.9874, 1558.3297, 1606.0225, 1626.7682,
		1657.2747, 1690.7496, 1726.8776, 1764.2822, 1799.023, 1838.4622,
		1879.3082, 1919.2496, 1959.8984, 2001.02, 2040.6626, 2080.282, 2128.128,
		2173.1084, 2222.826, 2268.1086, 2311.035, 2350.2732, 2390.0432,
		2434.5958, 2474.1762, 2514.8356, 2556.113, 2596.124, 2633.2056,
		2668.3276, 2709.6076, 2757.434, 2814.7758, 2877.7392, 2939.4348,
		3001.0212, 3061.4498, 3101.4528, 3091.6434, 3057.999, 3021.2988,
		3004.371, 2997.532, 3012.2032, 3042.428, 3072.4858, 3068.7276,
		3022.8476, 2965.6416, 2900.5062, 2847.5186, 2793.5656, 2752.7554,
		2720.1648, 2688.375, 2659.2186, 2644.3168, 2616.8226, 2582.7954,
		2551.291, 2515.941, 2480.2924, 2441.7254, 2408.388, 2356.539, 2318.3396,
		2287.996, 2257.1276, 2226.2088, 2193.7976, 2163.5618, 2133.1688,
		2097.2664, 2062.8342, 2028.341, 1996.2546, 1980.4662, 1947.9366,
		1917.6352, 1883.972, 1852.6022, 1816.6714, 1787.3902, 1751.7244,
		1707.212, 1691.4216, 1656.0303, 1625.4751, 1576.7189, 1551.4119,
		1537.3435, 1508.3136, 1479.0757, 1445.4304, 1422.0551, 1400.484,
		1372.2087, 1351.3029, 1336.2052, 1313.5546, 1277.8781, 1264.2412,
		1242.8593, 1224.4076, 1203.29, 1188.8, 1173.1348, 1150.2922, 1133.4131,
		1115.1624, 1090.9231, 1084.6576, 1063.1106, 1046.3311, 1035.0859,
		1017.1367, 1002.5916, 991.0036, 976.267, 960.6631, 955.8471, 945.4407,
		925.0206, 911.7807, 902.2155, 889.7479, 881.7255, 868.3334, 857.4988,
		848.7603, 841.8129, 825.98235, 814.92585, 810.2699, 799.5548, 789.197,
		782.4773, 766.59905, 763.4753, 754.929, 749.15025, 738.6131, 727.39625,
		719.20675, 715.5074, 709.22085, 700.90835, 698.5957, 695.992, 692.23345,
		685.57855, 672.87895, 670.7685, 668.7528, 670.5349, 664.62055,
		660.17975, 664.3135, 663.33165, 662.81635, 666.5374, 670.46995,
		671.2345, 678.7022, 685.3612, 691.45335, 698.63765, 706.55735,
		713.88605, 717.8155, 728.2453, 733.03945, 730.5919, 728.5522, 724.78385,
		719.7371, 710.3911, 703.52685, 694.4071, 684.8469, 674.59205, 663.28125,
		656.36835, 647.3974, 636.8857, 630.69255, 626.41265, 621.6559,
		621.34325, 618.4947, 619.50855, 623.46105, 629.1251, 631.00865,
		641.17065, 646.85255, 657.0404, 659.45925, 666.99965, 673.2087, 677.755,
		683.52735, 689.80665, 699.7733, 707.61285, 709.63175, 719.31645,
		727.07055, 733.82405, 741.2707, 747.52755, 760.20965, 775.33265,
		787.5865, 794.29065, 804.64085, 818.15265, 828.8227, 838.9972, 849.6585,
		859.5467, 873.2026, 876.7841, 891.8585, 908.7025, 921.2382, 935.5069,
		954.5303, 962.6627, 975.7672, 993.5031, 1004.373, 1024.6389, 1039.8865,
		1052.6711, 1072.8624, 1092.4625, 1112.6553, 1132.2195, 1153.3219,
		1177.9523, 1199.5966, 1217.7299, 1239.9431, 1267.1278, 1290.9088,
		1318.6989, 1342.6476, 1366.2838, 1388.5636, 1414.7665, 1442.8126,
		1472.9504, 1500.6013, 1527.8159 };

float sen_l90_dia[256] = { 1237.4436, 1261.0645, 1277.0439, 1297.5236,
		1316.0726, 1339.392, 1359.3407, 1377.8588, 1397.4397, 1415.3284,
		1435.4017, 1457.8901, 1481.7954, 1499.4746, 1519.1339, 1544.7693,
		1565.0156, 1585.7158, 1608.6946, 1624.9001, 1640.9845, 1662.6211,
		1686.8592, 1699.9074, 1714.6814, 1735.8046, 1752.8196, 1761.8964,
		1771.058, 1785.637, 1800.8884, 1824.637, 1845.279, 1870.7072, 1905.6516,
		1945.9544, 1973.5692, 1987.33, 1985.03, 1970.8748, 1948.317, 1939.103,
		1941.0806, 1959.5152, 1981.4922, 1995.9324, 1998.7252, 1988.6862,
		1973.4172, 1953.1828, 1923.1796, 1889.2864, 1860.4472, 1836.361,
		1813.9538, 1793.565, 1778.5624, 1754.2972, 1739.8294, 1721.8218,
		1706.022, 1689.6086, 1669.2024, 1649.4052, 1633.9801, 1614.9224,
		1594.4426, 1568.2012, 1545.7668, 1527.4398, 1506.7267, 1486.4261,
		1468.7151, 1444.0271, 1421.3805, 1398.3907, 1375.5031, 1353.8232,
		1332.3721, 1316.957, 1295.9043, 1272.1879, 1254.8367, 1238.0336,
		1214.8488, 1199.5426, 1173.587, 1156.7462, 1140.1001, 1121.2944,
		1100.4658, 1083.3629, 1066.3005, 1051.4807, 1035.1707, 1030.1157,
		1017.0283, 997.5819, 982.3973, 971.5359, 955.3693, 941.9874, 932.4002,
		916.2738, 903.1234, 895.4004, 884.9133, 876.2831, 863.6743, 854.6248,
		845.2374, 830.67155, 814.8792, 803.3139, 793.2362, 785.3518, 772.8854,
		760.5172, 753.10005, 745.03575, 731.7407, 723.95295, 718.8371,
		708.81505, 702.4551, 691.94075, 688.46965, 679.3194, 670.8742,
		665.75905, 654.001, 649.8514, 645.58565, 644.6433, 642.93935, 634.7808,
		627.727, 620.9488, 619.30165, 614.63435, 609.07055, 609.4396, 604.91895,
		598.4529, 595.0093, 586.40885, 586.31605, 586.7368, 580.2442, 586.9138,
		584.16015, 585.73415, 585.85515, 586.33635, 592.6898, 594.55175,
		600.90565, 603.55415, 616.1432, 615.8856, 618.249, 622.5017, 631.59155,
		637.638, 637.25545, 648.60515, 655.80745, 656.03215, 658.21485,
		655.05225, 654.7221, 654.25625, 654.992, 640.786, 632.67995, 625.57665,
		618.43805, 611.79285, 610.31335, 606.1942, 595.61315, 593.2801,
		594.69215, 592.2204, 595.2754, 596.08415, 595.06215, 592.80365,
		597.56175, 602.90405, 606.60615, 605.6031, 607.7224, 614.38155,
		616.8195, 617.0156, 629.43145, 631.48945, 631.6139, 638.19325, 645.8988,
		651.7826, 662.13105, 663.7628, 666.3573, 675.77845, 682.50585, 689.3182,
		697.00885, 702.3578, 705.47825, 715.6939, 724.79865, 734.6704,
		737.14635, 741.23115, 755.14055, 760.24495, 768.0436, 777.05615,
		784.7271, 792.01905, 805.93105, 817.4436, 824.8617, 831.89405, 845.0488,
		850.1555, 861.8048, 871.5287, 881.7252, 892.4852, 905.4945, 915.8635,
		934.9506, 944.8026, 956.4738, 963.3995, 979.6505, 993.8286, 1004.3665,
		1019.3762, 1033.3167, 1047.5751, 1058.2839, 1072.2484, 1090.4825,
		1106.8112, 1125.088, 1139.9291, 1155.1742, 1167.8324, 1186.4839,
		1205.5826, 1230.0781, 1232.9834 };

#endif /* DEFINES_H_ */
