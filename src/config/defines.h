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
	LED4 = false;
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

float pathVmax=0;
float pathAcc=0;
float pathDiac=0;

#endif /* DEFINES_H_ */
