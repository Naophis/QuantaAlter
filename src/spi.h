/*
 * spi.h
 *
 *  Created on: 2016/05/17
 *      Author: Naoto
 */

#ifndef SPI_H_
#define SPI_H_

volatile int buff1, buff2, buff3;
volatile long timeCounter = 0;

// SPI用 //
static volatile unsigned char rx_buff[3];
static volatile unsigned char tx_buff[3];
static volatile unsigned char flag_spi;
static volatile unsigned char flag_spi2;

extern void Init_SPI(void);
extern void interrpt_spi_tx(void);
extern void interrpt_spi_rx(void);
extern void interrpt_spi_end(void);
extern unsigned char MPU6500_Read_1byte(unsigned char addr);
extern void MPU6000_Read_1byte_v2(unsigned char addr);
extern signed short MPU6500_Read_2byte(unsigned char addr);
extern signed short MPU6500_Read_2byte_v2(unsigned char addr);
extern void MPU6500_Write_1byte(unsigned char addr, unsigned char write_date);
volatile int temp = 0;
void spi10MbpsMode() {
	// 転送フォーマットの設定 //
	RSPI1.SPBR = 5;
	RSPI1.SPCMD0.BIT.BRDV = 1;
}
void spi1MbpsMode() {
	// 転送フォーマットの設定 //
	RSPI1.SPBR = 5;
	RSPI1.SPCMD0.BIT.BRDV = 3;
}
volatile char setupMpu6500() {
//	return true;
	mpu = false;
	cmt_wait(200);
	MPU6500_Write_1byte(0x6B, 0x80); //スリープ解除?
	cmt_wait(200);
	MPU6500_Write_1byte(0x68, 0x04); //ジャイロリセット
	cmt_wait(200);
	MPU6500_Write_1byte(0x6A, 0x10); //uercontrol i2c=disable
	cmt_wait(200);
	MPU6500_Write_1byte(0x1B, 0x18); //gyro config ジャイロのフルスケールを±2000°/s
	cmt_wait(200);
	short result = MPU6500_Read_1byte(117);
	myprintf("%d	%d\r\n", result, result == 152);
	mpu = true;
	cmt_wait(5);
	return result;
}

void Init_SPI(void) {

	SYSTEM.PRCR.WORD = 0xA503;
	//protect off
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;

	MSTP (RSPI1) = 0;

	// 通信形式の設定 //
	RSPI1.SSLP.BIT.SSL0P = 0;		//SSLB0-BはアクティブLow
	RSPI1.SPPCR.BIT.MOIFV = 1;
	RSPI1.SPPCR.BIT.MOIFE = 1;
	RSPI1.SPBR = 5;
	RSPI1.SPDCR.BIT.SPFC = 2;	//3frame SPCMD0~2まで使用する
	RSPI1.SSLND.BIT.SLNDL = 0;
	RSPI1.SPND.BIT.SPNDL = 0;
	RSPI1.SPCR2.BIT.SPPE = 0;	//No parity
	RSPI1.SPSCR.BIT.SPSLN = 2;

	// データフォーマットの設定 //
	RSPI1.SPCMD0.BIT.SSLKP = 1;	//1//キープ
	RSPI1.SPCMD0.BIT.SPB = 4;		//8bit data
	RSPI1.SPCMD0.BIT.CPOL = 1;		//クロック極性設定
	RSPI1.SPCMD0.BIT.CPHA = 1;		//データタイミング設定
	RSPI1.SPCMD0.BIT.BRDV = 0;	//データタイミング設定
	RSPI1.SPCMD1.WORD = RSPI1.SPCMD0.WORD;
	RSPI1.SPCMD2.WORD = RSPI1.SPCMD0.WORD;
	RSPI1.SPCMD2.BIT.SSLKP = 0;	//CSをnegativeにする

	RSPI1.SPBR = 4;
	;
	RSPI1.SPCMD0.BIT.BRDV = 2;

	IEN(RSPI1, SPTI1) = 1;
	IEN(RSPI1, SPRI1) = 1;
	IPR(RSPI1, SPTI1) = 14;
	IPR(RSPI1, SPRI1) = 15;
	IR(RSPI1, SPTI1) = 0;		//送信割り込み要求の初期化
	IR(RSPI1, SPRI1) = 0;		//受信割り込み要求の初期化

	RSPI1.SPCR.BIT.SPTIE = 0;	//送信割り込み要求不許可
	RSPI1.SPCR.BIT.SPRIE = 0;	//受信割り込み要求許可
	RSPI1.SPCR2.BIT.SPIIE = 0;	//通信終了割り込み要求不許可

	MPC.PE4PFS.BIT.PSEL = 13; //MOSI
	MPC.PE5PFS.BIT.PSEL = 13; //MSOI
	MPC.PE6PFS.BIT.PSEL = 13; //SSLA
	MPC.PE7PFS.BIT.PSEL = 13; //RSPCKA

	PORTE.PMR.BIT.B4 = 1;
	PORTE.PMR.BIT.B5 = 1;
	PORTE.PMR.BIT.B6 = 1;
	PORTE.PMR.BIT.B7 = 1;

//	RSPI1.SPCKD.BIT.SCKDL = 1;	//0:SPI動作(4線式)

	RSPI1.SPCR.BIT.SPMS = 0;	//0:SPI動作(4線式)
	RSPI1.SPCR.BIT.TXMD = 0;	//0:全二重同期式シリアル通信
	RSPI1.SPCR.BIT.MODFEN = 0;	//0:モードフォルトエラー検出を禁止
	RSPI1.SPCR.BIT.MSTR = 1;	//1:マスタモード

//	RSPI1.SPCR.BIT.SPE = 1;

	SYSTEM.PRCR.WORD = 0xA500;

	while (setupMpu6500() != 152)
		;
}

void interrpt_spi_tx(void) {
	IR(RSPI1, SPTI1) = 0;
	RSPI1.SPDR.WORD.H = tx_buff[0];
	RSPI1.SPDR.WORD.H = tx_buff[1];
	RSPI1.SPDR.WORD.H = tx_buff[2];
	RSPI1.SPCR.BIT.SPTIE = 0;	//送信割り込み要求不許可
	RSPI1.SPCR2.BIT.SPIIE = 1;	//通信終了割り込み要求許可
	RSPI1.SPCR.BIT.SPRIE = 1;	//受信割り込み要求許可
}

void interrpt_spi_rx(void) {
	IR(RSPI1, SPRI1) = 0;
	if (RSPI1.SPSR.BIT.SPRF == 1) {
		RSPI1.SPSR.BIT.SPRF = 0;
		rx_buff[0] = RSPI1.SPDR.WORD.H;
		rx_buff[1] = RSPI1.SPDR.WORD.H;
		rx_buff[2] = RSPI1.SPDR.WORD.H;
	}
	flag_spi2 = 1;
	interrpt_spi_end();
}

void interrpt_spi_end(void) {
//	IR(RSPI1, SPII1) = 0;
	RSPI1.SPCR.BIT.SPE = 0;
	RSPI1.SPCR2.BIT.SPIIE = 0;	//通信終了割り込み要求不許可
	RSPI1.SPCR.BIT.SPRIE = 0;	//受信割り込み要求許可
	flag_spi = 1;
}
#define USE 1
#define FREE 0
volatile char spiFlg = FREE;
volatile char global_spi_data = 0;

char recvByteSCI1(void) {
	char receivedByte;              // 受信データ
	while (!SCI1.SSR.BIT.RDRF)
		;    // RDRFフラグのチェック
	receivedByte = SCI1.RDR;      // 受信データの読み出し
	SCI1.SSR.BIT.RDRF = 0;        // RDRFフラグを0にクリア
	return receivedByte;            // 受信したデータを返す
}
void MPU6000_Read_1byte_mtuA(unsigned char addr) {
	global_spi_data = 0;
	tx_buff[0] = (addr | 0x80);
	tx_buff[1] = 0;
	tx_buff[2] = 0;
	RSPI1.SPCR.BIT.SPTIE = 1;	//送信割り込み要求許可
	RSPI1.SPCR.BIT.SPE = 1;		//機能動作
}

void MPU6000_Read_1byte_mtuB() {
	if (flag_spi == 1) {
		global_spi_data = rx_buff[1];
	}
}
void mpu6500_MTUA(char addr) {
//	global_spi_data = 0;
	tx_buff[0] = (addr | 0x80);
	tx_buff[1] = 0;
	tx_buff[2] = 0;
// SPIスタート //
	RSPI1.SPCR.BIT.SPRIE = 1;	//受信割り込み要求許可
	RSPI1.SPCR.BIT.SPE = 1;		//機能動作
}
void mtuB() {
	if (flag_spi == 1) {
		global_spi_data = (((unsigned short) rx_buff[1] << 8)
				| ((unsigned short) rx_buff[2] & 0xff));
	}
}

volatile char A = 0, B = 0;

void MPU6000_Read_1byte_v2(unsigned char addr) {
	if (spiFlg == USE) {
		//SPIに実行中のデータ有
		if (flag_spi == 1) {
			global_spi_data = rx_buff[1];
			spiFlg = FREE;
		}
	} else {
		//SPIに実行中のデータ無
		tx_buff[0] = (addr | 0x80);
		tx_buff[1] = 0;
		tx_buff[2] = 0;
		RSPI1.SPCR.BIT.SPTIE = 1;	//送信割り込み要求許可
		RSPI1.SPCR.BIT.SPE = 1;		//機能動作
		spiFlg = USE;
	}
}

unsigned char MPU6500_Read_1byte(unsigned char addr) {
// spiフラグクリア //
	flag_spi = 0;
// 送信配列に代入 //
	tx_buff[0] = (addr | 0x80);
	tx_buff[1] = 0;
	tx_buff[2] = 0;
// SPIスタート //
	RSPI1.SPCR.BIT.SPTIE = 1;	//送信割り込み要求許可
	RSPI1.SPCR.BIT.SPE = 1;		//機能動作
// SPIが終わるまで待つ //
	while (flag_spi == 0)
		;
// 返値
	return rx_buff[1];
}

#define GYRO_Z 0x47
void startReadGyro() {
	flag_spi = 0;
	tx_buff[0] = (GYRO_Z | 0x80);
	tx_buff[1] = 0;
	tx_buff[2] = 0;
	RSPI1.SPCR.BIT.SPTIE = 1;	//送信割り込み要求許可
	RSPI1.SPCR.BIT.SPE = 1;		//機能動作
}
void callMpu(unsigned char addr) {
// spiフラグクリア //
	flag_spi = 0;
// 送信配列に代入 //
	tx_buff[0] = (addr | 0x80);
	tx_buff[1] = 0;
	tx_buff[2] = 0;
// SPIスタート //
	RSPI1.SPCR.BIT.SPTIE = 1;	//送信割り込み要求許可
	RSPI1.SPCR.BIT.SPE = 1;		//機能動作
}
signed short getMpu() {
	if (flag_spi == 0) {
		return gyroData;	//まだなら前回のデータ
	}
// 返値
	return (((unsigned short) rx_buff[1] << 8)
			| ((unsigned short) rx_buff[2] & 0xff));
}
signed short getWhoAmI() {
	if (flag_spi == 0) {
		return gyroData;	//まだなら前回のデータ
	}
// 返値
	return (unsigned short) rx_buff[1];
}
signed short MPU6500_Read_2byte(unsigned char addr) {
// spiフラグクリア //
	flag_spi = 0;
// 送信配列に代入 //
	tx_buff[0] = (addr | 0x80);
	tx_buff[1] = 0;
	tx_buff[2] = 0;
// SPIスタート //
	RSPI1.SPCR.BIT.SPTIE = 1;	//送信割り込み要求許可
	RSPI1.SPCR.BIT.SPE = 1;		//機能動作
// SPIが終わるまで待つ //
	while (flag_spi == 0)
		;
// 返値
	return (((unsigned short) rx_buff[1] << 8)
			| ((unsigned short) rx_buff[2] & 0xff));
}

signed short MPU6500_Read_2byte_v2(unsigned char addr) {
// spiフラグクリア //
	flag_spi2 = 0;
// SPIスタート //
	RSPI1.SPCR.BIT.SPRIE = 1;	//受信割り込み要求許可
	RSPI1.SPCR.BIT.SPE = 1;		//機能動作
// 送信配列に代入 //
	RSPI1.SPDR.WORD.H = (addr | 0x80);
	RSPI1.SPDR.WORD.H = 0;
	RSPI1.SPDR.WORD.H = 0;
	while (flag_spi2 == 0)
		;
	RSPI1.SPCR.BIT.SPRIE = 0;	//受信割り込み要求許可
// 返値
	return (((unsigned short) rx_buff[1] << 8)
			| ((unsigned short) rx_buff[2] & 0xff));

}

signed short mpuData = 0;
signed short getMpuData() {
	mpuData = (((unsigned short) rx_buff[1] << 8)
			| ((unsigned short) rx_buff[2] & 0xff));
	return mpuData;
}
void MPU6500Read2byte(unsigned char addr) {
	if (spiFlg == USE) {
		global_spi_data = (((unsigned short) rx_buff[1] << 8)
				| ((unsigned short) rx_buff[2] & 0xff));
	} else {
		// 送信配列に代入 //
		tx_buff[0] = (addr | 0x80);
		tx_buff[1] = 0;
		tx_buff[2] = 0;
		// SPIスタート //
		RSPI1.SPCR.BIT.SPRIE = 1;	//受信割り込み要求許可
		RSPI1.SPCR.BIT.SPE = 1;		//機能動作
		spiFlg = USE;
	}
}
void MPU6500_Write_1byte(unsigned char addr, unsigned char write_date) {
// spiフラグクリア //
	flag_spi = 0;
// 送信配列に代入 //
	tx_buff[0] = addr;
	tx_buff[1] = write_date;
	tx_buff[2] = 0;
// SPIスタート //
	RSPI1.SPCR.BIT.SPTIE = 1;	//送信割り込み要求許可
	RSPI1.SPCR.BIT.SPE = 1;		//機能動作
// SPIが終わるまで待つ //
	while (flag_spi == 0)
		;
}

#endif /* SPI_H_ */
