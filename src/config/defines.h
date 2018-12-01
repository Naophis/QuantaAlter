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

float sen_r_dia_img[255] = { 1434.2531, 1336.205, 1173.0216, 1048.3785,
		954.5954, 885.5453, 836.78465, 797.79435, 770.42975, 750.10215,
		731.3159, 717.89495, 705.7453, 696.10585, 688.2942, 685.3383, 682.50585,
		675.48005, 672.84575, 664.0832, 659.36645, 654.47065, 654.49525,
		647.93915, 650.1557, 647.5807, 650.2427, 648.67945, 647.02385, 645.0427,
		645.29795, 646.81695, 647.13255, 646.4824, 647.35015, 651.8325,
		654.91295, 656.35915, 656.26185, 657.42985, 663.87365, 664.19985,
		667.7021, 667.6735, 668.42835, 674.3854, 677.87815, 681.211, 684.1296,
		689.47795, 692.6948, 694.40835, 697.6562, 704.20705, 712.8891,
		713.37695, 716.6862, 720.0338, 725.1036, 728.13695, 734.01325, 741.2036,
		743.5508, 752.78975, 757.36665, 759.05755, 763.7931, 767.15975, 771.383,
		775.5445, 781.04895, 787.66425, 792.7912, 791.1003, 788.1202, 793.42625,
		799.5735, 805.1159, 809.5176, 813.22625, 816.0677, 821.7242, 826.55345,
		831.74145, 838.8851, 843.3356, 845.3356, 851.0432, 858.2747, 864.7612,
		867.963, 872.4181, 879.3813, 885.1312, 893.928, 900.6615, 908.6278,
		916.1343, 923.681, 931.9007, 934.9406, 940.975, 948.7515, 954.141,
		956.9142, 964.3076, 967.3206, 972.9944, 977.8437, 986.3187, 995.4125,
		1002.0224, 1007.3912, 1016.5984, 1027.0728, 1035.5841, 1044.0817,
		1051.7976, 1060.2982, 1069.4089, 1081.085, 1090.1964, 1100.795,
		1107.3508, 1117.6423, 1127.7391, 1136.772, 1144.6915, 1156.6067,
		1163.6509, 1173.224, 1186.2383, 1201.4518, 1205.2058, 1213.871,
		1222.0265, 1234.2473, 1242.4323, 1252.9225, 1264.3346, 1276.0543,
		1286.4354, 1303.106, 1316.8967, 1329.0277, 1340.1976, 1352.7839,
		1366.7814, 1382.9874, 1396.9635, 1411.4348, 1428.7939, 1439.7781,
		1454.0137, 1479.318, 1487.0875, 1503.8743, 1520.7935, 1540.3831,
		1560.8251, 1578.3855, 1594.8273, 1617.71, 1636.0492, 1654.8818,
		1676.9473, 1694.3768, 1714.1836, 1733.7314, 1759.4434, 1767.0892,
		1781.3842, 1797.658, 1804.823, 1817.7114, 1830.9264, 1844.444,
		1859.1446, 1873.2336, 1889.7072, 1908.2308, 1930.3658, 1949.657,
		1968.6224, 1990.366, 2012.5668, 2034.1562, 2058.8868, 2082.1552,
		2104.465, 2124.0334, 2146.7338, 2163.1252, 2184.3144, 2203.0884,
		2221.3414, 2239.007, 2258.753, 2282.1416, 2303.4778, 2326.3732,
		2353.6826, 2383.2344, 2414.6146, 2443.5726, 2477.6036, 2511.565,
		2548.5572, 2582.773, 2617.6316, 2656.5984, 2695.2796, 2735.393,
		2775.8454, 2814.9426, 2852.2678, 2892.7602, 2930.384, 2968.027,
		3002.7312, 3040.299, 3076.58, 3112.2828, 3150.4688, 3188.4688,
		3225.9252, 3262.259, 3297.5086, 3325.6394, 3351.9086, 3370.6668,
		3381.484, 3379.7408, 3365.8312, 3342.8356, 3306.5904, 3263.8758,
		3234.342, 3212.6878, 3209.5224, 3221.3628, 3238.4416, 3257.6102,
		3280.2356, 3303.5416, 3335.2234, 3370.8432, 3403.778, 3415.5448,
		3381.598, 3295.5036, 3142.6922, 2933.3128, 2674.9678, 2384.4622, };

float sen_l_dia_img[255] = { 1486.694, 1322.2089, 1188.4581, 1079.8156, 991.054,
		954.2137, 892.8586, 844.4062, 809.488, 770.9901, 755.81145, 745.7472,
		727.04735, 717.19975, 713.086, 704.1726, 703.1498, 700.2808, 695.7655,
		691.5906, 682.47445, 679.16145, 672.17065, 673.16075, 668.6345,
		665.84355, 660.95845, 662.0866, 660.96325, 656.02465, 655.34905,
		656.1437, 659.2676, 658.1521, 654.17485, 655.13405, 652.47355, 650.3954,
		652.99965, 655.66865, 659.2758, 664.5833, 668.0107, 668.1687, 666.8722,
		668.6267, 670.3535, 680.06385, 682.9895, 683.23275, 686.0851, 691.18535,
		690.6901, 687.8869, 693.7583, 696.9815, 698.135, 698.32655, 704.0678,
		707.27205, 709.2738, 717.3454, 716.73895, 722.1911, 727.1762, 731.75415,
		737.6966, 741.1511, 744.2738, 748.1096, 748.1641, 751.32375, 757.76365,
		763.05835, 770.78845, 774.0686, 777.125, 782.43425, 778.1578, 786.39685,
		790.39015, 791.1206, 797.4914, 806.9055, 807.4908, 817.4052, 823.43755,
		825.0044, 830.46965, 838.48835, 844.2504, 848.6815, 853.3121, 859.0575,
		863.7293, 869.11, 875.2753, 877.5775, 887.7031, 893.0446, 896.8731,
		907.1811, 909.9009, 919.0151, 926.428, 934.977, 945.0071, 953.2332,
		961.3306, 971.2973, 977.6815, 985.2368, 989.665, 993.8942, 1000.8425,
		1006.7726, 1011.387, 1014.8738, 1025.2643, 1028.6265, 1036.0312,
		1040.0507, 1048.3085, 1051.0398, 1061.9133, 1071.2098, 1078.0845,
		1079.4283, 1087.1476, 1099.4199, 1103.1646, 1105.912, 1113.6614,
		1117.2611, 1129.0728, 1132.7515, 1140.8683, 1143.2031, 1156.5264,
		1161.6901, 1173.9373, 1180.6375, 1191.152, 1193.9653, 1205.7245,
		1215.0167, 1226.4158, 1235.3102, 1244.5686, 1254.2227, 1268.8375,
		1282.1814, 1292.903, 1295.348, 1311.4122, 1326.002, 1339.642, 1355.653,
		1369.4916, 1380.2665, 1392.496, 1412.3043, 1427.3643, 1436.6293,
		1445.0996, 1469.4758, 1480.7107, 1493.5626, 1512.9603, 1526.452,
		1540.754, 1549.0691, 1567.605, 1580.9661, 1598.105, 1609.5364,
		1620.4222, 1632.5981, 1645.6343, 1661.5457, 1672.3678, 1685.6384,
		1704.637, 1718.0532, 1736.22, 1751.8686, 1764.7014, 1784.9482,
		1806.6512, 1823.8614, 1850.7158, 1867.8612, 1888.1552, 1909.0412,
		1928.3656, 1938.3362, 1973.2258, 1994.1722, 2007.3194, 2026.9536,
		2051.0354, 2070.1108, 2093.47, 2114.2032, 2133.7456, 2151.863,
		2174.9268, 2199.6164, 2224.6148, 2259.3548, 2280.5358, 2304.1982,
		2324.2048, 2347.2376, 2368.0422, 2392.2722, 2404.1104, 2430.4942,
		2453.1866, 2490.9018, 2515.0788, 2537.5622, 2555.9692, 2577.9756,
		2596.7866, 2614.7674, 2629.8628, 2628.4114, 2630.153, 2623.9892,
		2598.0672, 2579.7908, 2556.0494, 2537.4764, 2529.6268, 2539.6442,
		2551.9046, 2564.5518, 2579.9948, 2595.8558, 2619.2632, 2648.8042,
		2681.452, 2703.1456, 2695.069, 2647.8554, 2557.4328, 2425.1756,
		2253.9912, 2071.0728, 1875.882, 1690.1006, 1519.6666, 1366.2686,
		1235.1483, };

float sen_r90_dia[255] = { 989.8058, 997.4826, 1011.1075, 1026.0576, 1038.4607,
		1051.2078, 1063.7848, 1075.131, 1089.2975, 1099.9296, 1109.0483,
		1127.8314, 1137.2076, 1147.0029, 1157.307, 1168.0114, 1180.9908,
		1192.8063, 1203.2728, 1214.8275, 1227.4194, 1239.0709, 1255.3346,
		1268.4252, 1282.757, 1292.8804, 1303.0667, 1313.649, 1320.0343,
		1330.9421, 1350.7922, 1379.0731, 1403.1483, 1435.765, 1467.5352,
		1499.4114, 1526.3792, 1543.2271, 1539.299, 1524.1617, 1507.8722,
		1487.4337, 1480.7661, 1477.4038, 1481.6956, 1479.8373, 1464.6172,
		1444.1729, 1410.6187, 1384.947, 1360.5538, 1339.489, 1319.8599,
		1303.8164, 1291.1033, 1277.0275, 1266.1865, 1253.0214, 1243.7,
		1231.5042, 1220.8186, 1210.5039, 1197.7955, 1187.8235, 1174.0271,
		1166.2543, 1155.3717, 1143.468, 1133.6538, 1122.2058, 1111.1176,
		1098.2201, 1083.9137, 1070.8058, 1057.5327, 1047.9863, 1037.8093,
		1027.3422, 1014.3693, 998.177, 986.8112, 976.5807, 965.7857, 953.2486,
		940.6226, 928.2889, 917.5887, 902.3806, 888.193, 877.5806, 866.3099,
		855.541, 844.6602, 837.0578, 828.64515, 819.5991, 808.77205, 797.20545,
		783.9308, 772.42305, 762.23315, 750.8354, 742.82375, 733.5522,
		724.77375, 718.6971, 711.1438, 702.5682, 694.77275, 685.50005,
		675.04165, 668.831, 659.66465, 655.78535, 647.9159, 640.53715, 632.0155,
		623.25665, 618.6018, 611.8646, 605.23645, 599.4884, 593.5066, 584.09245,
		578.49805, 570.46145, 564.1924, 558.85875, 550.5338, 544.8611,
		536.92495, 534.0301, 526.9506, 523.55, 517.7968, 516.417, 512.9745,
		505.27425, 500.8138, 496.7763, 491.72115, 487.88655, 484.7574,
		478.74865, 476.97155, 474.6665, 468.39625, 467.15345, 467.65725,
		465.89655, 466.571, 466.3968, 468.8225, 470.7941, 472.6531, 475.369,
		477.0497, 481.03205, 488.55275, 491.4835, 501.4403, 508.3935, 513.80355,
		520.09595, 523.6169, 528.97565, 532.51335, 534.48, 536.98545, 535.63445,
		532.34385, 530.145, 518.24415, 515.8377, 512.749, 508.01775, 503.47905,
		499.3841, 491.5022, 485.98665, 484.1518, 483.8279, 481.4552, 477.4099,
		477.663, 475.99175, 477.83615, 482.48845, 482.56845, 485.7855,
		488.16955, 493.5196, 493.5559, 496.8508, 500.2752, 502.10265, 509.681,
		514.9672, 518.6744, 520.818, 527.6137, 530.31525, 537.8005, 543.12505,
		545.2149, 552.0562, 556.50055, 558.57245, 568.1681, 572.97695,
		578.99145, 587.9164, 594.1204, 598.4833, 605.77985, 613.52985, 621.942,
		627.5108, 633.76245, 640.6881, 650.01805, 655.8648, 662.93025,
		672.33015, 680.9354, 687.54365, 697.9139, 708.722, 715.7553, 722.7773,
		729.1574, 739.3089, 748.80865, 754.97915, 766.11695, 775.78515,
		785.16345, 796.8211, 805.4359, 816.1062, 826.8975, 835.8167, 849.3455,
		857.9853, 867.5852, 877.4487, 886.3052, 899.3576, 915.0441, 929.1641,
		942.3218, 955.3388, 967.3975, 978.9822, 991.4064, };

float sen_l90_dia[255] = { 1428.9812, 1446.6605, 1471.6587, 1492.4585,
		1513.4087, 1522.531, 1547.0304, 1562.7205, 1583.6357, 1612.5229,
		1638.2137, 1653.1329, 1682.4184, 1699.1092, 1718.1406, 1733.4018,
		1739.0354, 1754.7332, 1770.5158, 1784.1114, 1803.2046, 1819.8166,
		1833.5322, 1844.382, 1855.7942, 1867.8618, 1875.6566, 1888.0596,
		1896.673, 1915.5964, 1935.3876, 1966.8242, 1995.525, 2006.643,
		1993.4986, 1969.6944, 1940.7382, 1919.2416, 1919.7886, 1936.7356,
		1960.6578, 1976.0184, 1971.6462, 1947.8302, 1923.1976, 1896.9056,
		1873.5498, 1855.1174, 1835.6474, 1822.957, 1813.6866, 1808.016,
		1804.4328, 1791.9918, 1770.9726, 1757.7712, 1753.9246, 1741.5402,
		1723.8576, 1709.6298, 1697.0588, 1675.4233, 1654.4312, 1639.3293,
		1620.7341, 1599.24, 1578.2052, 1544.525, 1519.1124, 1504.2521,
		1481.2644, 1461.0393, 1437.6368, 1415.4246, 1397.5286, 1388.088,
		1366.4968, 1343.1184, 1310.3285, 1294.0679, 1276.0939, 1257.6833,
		1237.1588, 1224.35, 1204.1412, 1187.4524, 1169.8582, 1158.035,
		1145.4335, 1120.4009, 1107.9336, 1090.0142, 1073.4108, 1051.7537,
		1038.6758, 1027.1277, 1011.9811, 997.1381, 983.7358, 968.3168, 957.7646,
		945.6376, 937.3595, 921.9118, 913.0612, 903.9587, 891.26, 881.2734,
		865.5571, 853.175, 849.6056, 841.4937, 832.27425, 819.29725, 814.2855,
		805.66515, 797.85095, 789.4208, 775.63125, 771.2317, 766.08875,
		757.52405, 749.3583, 749.02015, 743.3089, 730.57115, 722.5736,
		720.18455, 717.2394, 713.2884, 704.9693, 696.4002, 687.13775, 686.63465,
		681.3316, 674.11145, 667.00415, 658.5633, 652.3916, 647.5189, 642.69575,
		635.9347, 636.4261, 631.21315, 630.4037, 632.6828, 630.351, 625.69535,
		628.48945, 630.8557, 635.20305, 634.1945, 635.33665, 641.0912, 643.4078,
		650.1613, 660.7509, 667.0376, 674.41095, 682.98035, 687.5758, 692.1906,
		692.4196, 694.76185, 693.6371, 695.9432, 688.30805, 684.2985, 684.7166,
		682.256, 676.51775, 675.78575, 672.40745, 668.8775, 660.64575, 659.3799,
		656.07655, 649.38045, 648.7223, 649.24475, 647.1092, 642.73195,
		646.9474, 648.7616, 646.9063, 652.1419, 655.5562, 660.276, 660.17965,
		667.63415, 672.4342, 672.507, 676.9699, 682.1429, 686.17375, 685.57075,
		696.28045, 703.31425, 709.20455, 712.92735, 716.2451, 723.4439, 732.519,
		737.4137, 741.91035, 747.0204, 752.8007, 765.3023, 772.52395, 782.5504,
		794.1256, 800.94875, 805.94115, 816.5802, 822.2853, 832.7845, 838.37545,
		844.727, 856.1432, 872.9695, 884.1326, 888.3817, 898.2504, 907.0082,
		916.5198, 926.9537, 944.2369, 954.8656, 961.181, 974.2742, 988.1484,
		996.948, 1010.1608, 1024.5315, 1033.6342, 1045.8903, 1054.2715,
		1069.4618, 1088.3489, 1102.8879, 1117.6716, 1133.1125, 1146.1526,
		1166.8129, 1184.8942, 1204.0856, 1223.334, 1235.9131, 1253.2114,
		1272.2322, 1287.2727, 1304.3896, 1320.1633, 1335.8348, 1357.6918, };

#endif /* DEFINES_H_ */
