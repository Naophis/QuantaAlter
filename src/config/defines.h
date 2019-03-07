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

volatile double settleGyro2, settleGyroOld, settleGyro;

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
volatile char gyroKeepZero;
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

volatile char enableSensorCtrl = false;

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
#define BACK_STRAIGHT 13

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

float sen_l_dia_img[255] = {1293.425,1210.8843,1135.7661,1008.823,955.5166,836.5296,783.18105,743.8963,714.664,693.29405,676.1793,668.94525,652.12715,643.95195,640.4311,631.22795,628.75465,623.8162,618.7018,613.19415,610.01885,606.65455,605.4801,603.10115,600.7924,599.64295,596.8709,596.2242,596.6167,597.43345,597.7011,597.7221,600.63055,601.23565,603.92675,604.7606,606.553,608.5119,610.70015,611.2271,612.2887,613.17375,614.7182,615.2639,617.13975,617.5764,618.58275,619.41205,621.6349,622.93075,625.239,626.71825,628.402,630.823,633.36485,635.5873,638.8108,641.53615,644.5971,647.6978,652.29845,655.80945,659.20245,662.92485,667.17695,669.6333,676.5238,680.1264,682.03235,687.6086,689.123,692.52965,696.0114,700.45325,703.52915,706.2304,708.30665,712.40015,713.494,719.3578,722.2307,726.54945,729.8015,734.2947,738.4291,741.9312,747.51955,749.63075,757.1695,761.22725,766.3173,774.82845,780.18135,783.20685,788.5556,793.85645,800.1884,808.0622,811.13035,818.5978,824.2588,831.86865,838.53135,846.7772,853.5398,860.2202,862.9783,871.9979,875.1482,885.6731,889.0452,895.4882,901.8729,911.8428,916.4441,923.1066,925.4363,931.1076,941.1588,943.7686,952.4422,959.5319,966.3939,972.3128,980.0164,986.8832,993.747,1001.8177,1008.9377,1016.4706,1025.1676,1033.4277,1041.8962,1051.0002,1060.5038,1070.1813,1075.6868,1085.6309,1101.3566,1112.9902,1118.832,1129.8921,1140.6868,1151.8188,1166.9427,1177.5868,1187.6045,1197.7212,1207.6027,1213.0582,1229.9946,1240.5227,1251.5413,1262.3602,1272.9257,1277.1398,1291.5065,1295.8303,1308.2495,1311.972,1318.9601,1329.5967,1338.272,1347.0271,1352.0818,1363.4648,1375.1041,1387.5071,1400.1943,1421.7542,1429.8108,1452.8494,1468.2041,1484.3549,1500.4773,1516.8674,1533.7242,1543.0665,1567.5796,1583.443,1599.0035,1613.5599,1620.1935,1633.2784,1646.4689,1667.6991,1682.1634,1697.6872,1706.4064,1724.9968,1744.3892,1775.44,1796.4034,1817.8606,1840.1354,1850.3496,1870.9122,1902.0228,1922.3448,1942.6536,1963.0058,1984.3138,2004.2042,2024.3726,2044.409,2064.9384,2086.636,2106.2426,2127.7832,2139.2944,2175.9864,2203.6866,2216.716,2261.1072,2289.4958,2314.612,2338.2856,2361.4412,2381.5078,2401.249,2417.5698,2426.2814,2451.0654,2467.3378,2484.35,2501.3558,2510.5278,2539.1064,2560.3292,2583.7164,2595.6004,2624.8696,2632.5478,2625.8548,2603.8738,2570.8222,2536.2068,2522.7974,2514.9204,2525.3754,2593.9268,2656.456,2719.1832,2768.3824,2795.926,2802.17,2793.8868,2784.228,2758.6038,2726.7138,2640.1044,2593.1746,2461.6294,2284.2198,2068.7554};
float sen_r_dia_img[255] = {1443.1941,1363.9072,1233.5751,1134.4966,1058.9006,1000.7628,955.701,920.2824,891.858,868.1755,849.2639,832.7414,819.245,807.57375,797.74255,788.663,780.96395,773.99695,768.7776,763.5962,759.95415,756.63805,753.15955,751.27015,750.03355,749.0052,748.6657,748.69875,749.50825,750.81605,752.5597,754.11525,755.66105,758.10415,760.6303,763.63,766.7183,770.74595,773.208,777.56405,780.58605,783.81255,787.3565,790.69995,794.3315,797.97355,801.6945,806.32435,810.93745,815.76485,819.8998,823.8322,828.2051,832.6469,836.87925,842.1702,847.6259,851.3854,857.1417,861.6259,865.9317,870.6367,875.9075,880.9637,885.4659,890.2762,894.8133,899.4123,904.2761,909.3076,913.4837,918.3462,924.5844,930.0241,935.3185,941.7905,949.009,955.7778,963.1461,971.4315,979.7808,987.8974,995.4678,1003.8256,1012.2764,1020.2417,1027.4436,1034.9471,1041.8231,1048.6648,1055.8711,1062.4717,1069.7213,1075.9895,1083.9363,1091.4803,1098.3823,1105.2657,1112.8624,1120.7023,1129.4181,1137.8894,1146.1703,1156.05,1165.5536,1176.1135,1185.9397,1195.8795,1206.8646,1217.667,1226.949,1236.1692,1245.2017,1254.452,1263.8625,1272.4508,1282.1958,1291.7738,1301.3358,1311.4115,1321.5422,1331.6833,1342.0059,1352.2113,1361.6071,1371.1467,1380.9039,1390.2404,1400.5552,1411.7625,1422.7765,1435.1379,1448.1293,1461.1823,1475.7178,1490.4207,1503.4958,1516.7546,1531.2814,1545.5586,1559.6755,1572.448,1586.1852,1599.8389,1613.2407,1627.3857,1641.4902,1654.4757,1669.1371,1684.425,1699.426,1715.8944,1734.8594,1752.0394,1770.6058,1789.9874,1808.0822,1826.2424,1844.9802,1862.9172,1881.3586,1900.3392,1920.278,1940.691,1959.2044,1975.8988,1992.4474,2008.6498,2026.1574,2043.7304,2061.6534,2081.5162,2101.5352,2121.8172,2143.398,2166.1846,2190.6794,2215.2872,2240.8448,2266.0398,2290.8876,2315.7678,2340.603,2366.9488,2394.3714,2422.5428,2451.6128,2482.731,2513.196,2542.3936,2571.2544,2600.7834,2630.268,2660.988,2692.231,2722.7866,2752.4404,2782.996,2813.538,2844.2612,2876.3166,2908.472,2940.1888,2971.3304,3001.3028,3029.167,3054.1888,3077.7062,3099.004,3118.5916,3136.6404,3153.0732,3169.6396,3193.1,3200.441,3215.0108,3227.7496,3240.1088,3250.7792,3260.7908,3270.2182,3278.316,3285.8088,3293.3124,3299.258,3304.8414,3309.7134,3314.0188,3317.2776,3319.4074,3319.022,3317.0596,3313.6188,3306.8462,3299.8908,3299.6314,3300.4,3303.0124,3305.5512,3306.231,3304.5506,3301.346,3299.3292,3299.686,3302.2082,3303.51,3298.827,3281.606,3225.4304,3047.9434,2737.4532,2341.7708,1927.56,1541.6047,1210.0009};
float sen_r90_dia[255] = {1099.6818,1106.6722,1121.4918,1135.9309,1150.2549,1163.6145,1177.3979,1192.0773,1205.4341,1220.0649,1232.8645,1246.5844,1260.1837,1274.5699,1288.0984,1302.2729,1314.9117,1326.9231,1337.5674,1346.1141,1355.1675,1363.2904,1370.9025,1377.9932,1383.8999,1389.1949,1394.0326,1397.0625,1397.6396,1397.621,1397.3455,1396.8918,1399.0609,1405.5359,1417.8872,1437.963,1466.7534,1500.3447,1522.6307,1523.0869,1513.1262,1505.0763,1499.3197,1497.5914,1504.2903,1520.9595,1533.3031,1528.3391,1512.5854,1495.925,1486.4944,1483.2185,1482.9624,1486.3091,1491.8412,1498.2582,1504.5277,1510.6075,1515.3568,1519.1158,1520.7234,1520.2836,1519.6545,1516.3302,1512.533,1506.4749,1499.7129,1491.6483,1482.906,1472.8198,1462.0635,1452.6936,1441.8007,1431.0851,1420.3361,1409.3438,1396.7371,1383.9714,1371.7124,1358.1818,1344.8511,1331.2654,1317.5452,1303.0519,1288.4253,1273.991,1259.3087,1244.3423,1230.1501,1215.6936,1202.5175,1188.6466,1173.4629,1159.819,1146.1893,1132.4585,1119.7354,1106.4236,1094.0814,1081.8374,1068.8965,1055.5662,1042.6936,1030.6718,1018.0159,1005.4662,994.5358,982.1946,971.0966,959.5809,946.8894,935.5713,924.1516,913.8295,903.3278,893.5106,884.2032,875.2825,865.5629,856.1913,846.7777,837.1452,827.5935,817.8985,807.75275,797.5024,787.8188,777.5815,768.1978,759.08325,750.78545,742.08785,735.3062,728.44965,721.7528,715.68435,710.22875,704.59635,699.63955,694.6956,689.4146,684.3583,678.5505,673.0233,668.0473,662.8103,657.4709,652.67785,647.802,642.9012,638.7073,634.43605,630.0583,625.96745,621.66985,618.588,615.1935,612.3966,609.83605,607.5119,606.2411,605.35155,605.9823,607.33625,609.68215,613.9832,618.11605,623.63485,629.0702,636.072,643.27745,649.6425,656.011,661.23695,665.2722,668.1368,668.8553,667.46905,664.3301,658.4681,652.1001,644.01145,634.38575,624.93035,615.00045,605.6346,596.9256,588.67915,581.6872,576.58915,571.66435,568.04445,566.86415,566.13485,565.80495,566.0971,567.92445,570.0038,572.73315,576.24,579.8128,584.17765,588.68525,592.1415,595.8199,601.63915,605.7542,610.5623,615.54535,621.27795,626.64805,633.0063,640.6662,650.17725,653.7935,659.9197,666.018,672.54325,680.03065,687.26935,694.3999,702.05555,710.1264,718.54205,726.92625,734.89635,743.2306,752.5279,761.15315,769.7282,779.61255,789.4914,799.15985,808.8947,824.05745,829.55645,840.88,851.6625,862.233,872.6432,883.5082,895.2724,907.2208,919.5267,931.3268,944.4739,957.1826,970.1338,982.9864,995.864,1009.5525,1022.6744,1036.8013,1051.536,1066.0652};
float sen_l90_dia[255] = {1237.9973,1247.9777,1258.0018,1277.787,1287.2474,1318.0392,1337.9668,1357.5813,1378.1138,1399.3673,1420.9507,1433.04,1467.1144,1489.3527,1500.7856,1534.1735,1545.3804,1568.5892,1590.8744,1625.3418,1647.7162,1667.3965,1676.7611,1695.7156,1712.695,1729.8304,1752.4538,1766.31,1778.9736,1791.0566,1796.8758,1809.1812,1829.3774,1844.9702,1864.5618,1877.055,1906.0982,1951.796,1967.9096,1968.0268,1931.9854,1912.538,1871.9838,1835.5192,1837.6254,1852.3214,1867.4708,1872.4112,1865.4604,1849.1404,1830.1424,1810.739,1793.315,1780.0988,1769.6284,1760.26,1751.2326,1739.87,1728.914,1717.6336,1703.4986,1687.8426,1671.5509,1654.4554,1636.4124,1626.854,1598.4741,1579.1276,1569.0831,1539.0448,1528.9662,1507.3053,1473.833,1451.861,1429.702,1407.9764,1397.7007,1366.1042,1355.8844,1326.2462,1305.2379,1284.2498,1263.5887,1243.6742,1223.7661,1204.2294,1185.7826,1176.0839,1150.0297,1142.9039,1124.0781,1098.3632,1080.6609,1072.2352,1055.8597,1040.3179,1025.0914,1002.6303,995.1705,981.1038,967.009,953.3248,940.6151,920.7749,907.5147,895.2296,889.1359,871.9614,865.7888,849.3605,844.0319,832.9528,821.70545,806.2838,796.23535,786.2697,780.8184,771.0356,757.40515,752.47815,739.3211,730.45995,722.38985,713.99395,706.2729,698.03505,690.73915,683.6577,675.32055,669.28615,662.2287,655.9859,650.51705,644.49645,638.2443,633.23145,630.34745,624.73515,616.75285,610.82055,608.0846,602.635,597.6469,593.04695,585.84755,581.33825,577.4192,573.998,571.2313,569.57735,565.69575,564.15275,563.93025,563.9813,563.788,564.02825,567.12805,568.5337,574.05625,576.5055,581.3633,589.6,595.91735,602.5163,605.67815,611.0735,616.49665,621.8008,625.4876,628.9416,629.14265,628.78105,625.89705,622.75785,617.64655,612.49025,606.484,603.312,593.61065,587.8479,582.0611,576.87255,574.34675,570.4366,567.8395,565.42955,564.6202,563.8282,564.1808,565.2604,566.5099,570.6755,574.17065,578.0048,582.3384,584.6541,588.99815,595.80085,600.76605,605.2725,611.07055,616.3651,622.067,628.03925,634.1767,639.96165,646.1567,652.77205,659.18225,662.4776,673.1225,679.71275,683.6773,695.7651,703.1429,711.2218,718.78675,727.2743,735.226,742.8997,751.74815,755.726,768.7132,777.9806,786.7172,796.525,801.7152,815.97685,825.67595,837.0637,842.4116,857.9429,869.1855,880.6714,891.3278,903.6808,916.3763,923.1149,942.6888,949.4379,969.3726,983.4555,997.5073,1011.8933,1026.1184,1033.2258,1055.3696,1062.7294,1077.863,1093.0209,1116.9001,1124.999,1142.6277,1159.2091,1177.2224};

#endif /* DEFINES_H_ */
