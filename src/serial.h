/*
 * serial.h
 *
 *  Created on: 2016/06/02
 *      Author: Naoto
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdio.h>
#include <stdarg.h>
#include "iodefine.h"

#define BUFFER_LENGTH 1024
#define QUEUE_SIZE 1024
unsigned char res_buffer[BUFFER_LENGTH];
#define true 1
#define false 0

int queue_head = 0, queue_num = 0;

void putnbyte(char *buf, int len);
int myprintf(const char *fmt, ...);
void sci_recv(void);
char INT_RXI1(void);
int dequeue();
int enqueue(char enq_data);

void queClear() {
	for (int i = 0; i < BUFFER_LENGTH; i++) {
		res_buffer[i] = 0;
	}
	queue_head = 0;
	queue_num = 0;
}
int enqueue(char enq_data) {
	myprintf("%d %d\r\n", queue_head, queue_num, enq_data);
	if (enq_data == 92) {
		return 999;
	}
	if (queue_head + queue_num < QUEUE_SIZE) {
		res_buffer[queue_head + queue_num] = enq_data;
		queue_num++;
		return true;
	} else {
		return false;
	}
}

//シリアル通信の受信動作を開始
void SERIAL_EnableSerialRecive(void) {
	SCI1.SCR.BIT.RIE = 1;   // 受信割込み許可(RXI,ERI)
	SCI1.SCR.BIT.RE = 1;    // 受信を許可
}

// シリアル通信の受信動作を終了
void SERIAL_DisableSerialRecive(void) {
	SCI1.SCR.BIT.RIE = 0;   // 受信割込み許可(RXI,ERI)
	SCI1.SCR.BIT.RE = 0;    // 受信を許可
}

void put1byte(char c) {
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0;
}
char INT_RXI1(void) {      // 正常に受信できた場合の処理
	SCI1.SSR.BIT.RDRF = 0;  // 受信フラグを解除
	int res = enqueue(SCI1.RDR);
	if (res == 999) {
		return true;
	}
	return false;
}
int get1byte(void) {
	int ch;
	SERIAL_EnableSerialRecive();
	while ((SCI1.SSR.BYTE & 0x78) == 0)
		;
	while (((ch = SCI1.SSR.BYTE) & 0x78) == 0)
		;
	if ((ch & 0x40) == 0) {
//		ch = -((ch & SSR_ERR) >> 3);          // error
		SCI1.SSR.BYTE = 0x80;
	} else {
		ch = SCI1.RDR & 0xff;
		SCI1.SSR.BIT.RDRF = 0;
	}
	return (ch);

}
void putnbyte(char *buf, int len) {    //nbyte
	int c;
	unsigned long i = 0;
	char flag = 0;
// 送信バッファが解放されるのをポーリングで待機
// タイムアウトあり
	for (c = 0; c < len; c++) {
		flag = 0;
		for (i = 0; i < 0x00200000; i++) {
			if (SCI1.SSR.BIT.TDRE) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			put1byte(buf[c]);
		}
	}
}

int myprintf(const char *fmt, ...) {    //可変長引数・・・データ値が違っても使える
	static char buffer[100];
	int len;
	va_list ap;
	va_start(ap, fmt);          //(stdarg.h)
	len = vsprintf(buffer, fmt, ap);    //データの長さを識別(stdio.h)
	putnbyte(buffer, len);          //(stdarg.h)
	va_end(ap);
	return len;
}

#define SCI_RX_BUF_SHIFT   4
#define SCI_RX_BUF_SIZE   (1<<SCI_RX_BUF_SHIFT)
#define SCI_RX_BUF_MASK   (SCI_RX_BUF_SIZE-1)

volatile static struct stSCI_RX {
	unsigned short rdptr;                // リードポインタ
	unsigned short wrptr;                // ライトポインタ
	unsigned short dataNum;              // バッファ内データ数
	unsigned char buf[SCI_RX_BUF_SIZE];  // 受信バッファ
} SCI_RX;

void intprg_rxi0(void) {
	unsigned char c;
	PORT1.PODR.BIT.B4 = 1;
	SCI1.SSR.BIT.ORER = 0;     // オーバーランエラー
	SCI1.SSR.BIT.FER = 0;     // フレーミングエラー
	SCI1.SSR.BIT.PER = 0;     // パリティエラー

	// 受信バッファにデータ格納
	if (SCI1.SSR.BIT.RDRF) {                      // 受信フラグチェック
		SCI1.SSR.BIT.RDRF = 0;                  // 受信フラグクリア
		c = SCI1.RDR;                           // 受信データ取得
		if (SCI_RX.dataNum != SCI_RX_BUF_SIZE) {    // 受信バッファの空きチェック
			SCI_RX.buf[SCI_RX.wrptr] = c;         // 受信バッファに格納
			SCI_RX.wrptr = (SCI_RX.wrptr + 1) & SCI_RX_BUF_MASK;  // ライトポインタの更新
			SCI_RX.dataNum++;                     // データ数のインクリメント
		}
	}
}

// --------------------------------------------------------
// SCI 1バイト受信
//   引数   - unsigned char *c : 受信データ(ポインタ渡し)
//   戻り値 - 0:受信なし、1:受信成功
// --------------------------------------------------------
short SCI_read(unsigned char *c) {
	// 受信バッファからデータ取り出し
	if (SCI_RX.dataNum != 0) {                    // データ数チェック
		*c = SCI_RX.buf[SCI_RX.rdptr];          // 受信バッファからデータ取得
		SCI_RX.rdptr = (SCI_RX.rdptr + 1) & SCI_RX_BUF_MASK;  // リードポインタの更新
		SCI_RX.dataNum--;                       // データ数のデクリメント
		return 1;
	}
	*c = 0;
	return 0;
}

int dequeue() {
	if (queue_num > 0 && queue_num < BUFFER_LENGTH) {
		char res = res_buffer[queue_head];
		queue_num--;
		queue_head++;
		return res;
	} else {
		return 999;
	}
}

char charget(void) {
	char data;
	data = SCI1.RDR;
	ICU.IR[VECT_SCI1_RXI1].BIT.IR = 0;
	return data;
}

#endif /* SERIAL_H_ */
