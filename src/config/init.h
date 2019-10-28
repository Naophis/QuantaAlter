/*
 * init.h
 *
 *  Created on: 2017/07/26
 *      Author: Naoto
 */

#ifndef INIT_H_
#define INIT_H_

volatile void cmt_wait(int t) {
	timer = 0;
	while (timer != (CMT_CYCLE / 1000) * t) {
	}
}

void initLED() {
	PORTE.PDR.BIT.B2 = 1;
	PORTA.PDR.BIT.B7 = 1;
	PORTB.PDR.BIT.B6 = 1;
	PORTB.PDR.BIT.B7 = 1;
	PORTB.PDR.BIT.B5 = 1;
	PORT2.PDR.BIT.B3 = 1;

}

void initSensorLED() {
	PORTE.PDR.BIT.B0 = 1; //Right45
	PORTE.PDR.BIT.B1 = 1; //Right
	PORT2.PDR.BIT.B5 = 1; //Left45
	PORT2.PDR.BIT.B4 = 1; //Left
	PORTD.PDR.BIT.B6 = 1; //Front
}

void initMotorDriverRotate() {

	PORTB.PDR.BIT.B1 = 1;	// CW/CCW
	PORTB.PDR.BIT.B2 = 1;	// CW/CCW
	PORTB.PDR.BIT.B3 = 1;	// CW/CCW
	PORTB.PDR.BIT.B4 = 1;	// CW/CCW

	PORTA.PDR.BIT.B5 = 1;	// vacume
	PORTA.PDR.BIT.B2 = 1;	// pwm
	PORTE.PDR.BIT.B3 = 1;	// pwm

	PORTD.PDR.BIT.B7 = 1;	//Buzzer
}

void initS12AD() {
	SYSTEM.PRCR.WORD = 0xA503;
	MSTP (S12AD) = 0;
	MSTP (S12AD1) = 0;
	S12AD.ADCSR.BIT.ADCS = 0; // single scan
	S12AD1.ADCSR.BIT.ADCS = 0; // single scan
	S12AD.ADANSA0.BIT.ANSA0 = 0x01;
	S12AD1.ADANSA1.BIT.ANSA1 = 0x01;
	// sampring time
//	S12AD.ADSSTR1 = 20;
//	S12AD1.ADSSTR6 = 20;
//	S12AD1.ADSSTR7 = 20;
//	S12AD1.ADSSTRL = 20;
	SYSTEM.PRCR.WORD = 0xA500;
}

void initClock() {
	SYSTEM.PRCR.WORD = 0xA503;
	SYSTEM.SOSCCR.BIT.SOSTP = 0x01; //sub_clock disable
	SYSTEM.MOSCCR.BIT.MOSTP = 0x00; // main clock start
	SYSTEM.PLLCR.BIT.PLIDIV = 0x00; //PLL入力分周比選択ビット
	SYSTEM.PLLCR.BIT.STC = 19; //周波数逓倍率設定ビット
	SYSTEM.PLLCR2.BYTE = 0x00; //PLL動作
	for (int i = 0; i < 1000; i++) {
	}
	SYSTEM.MEMWAIT.BIT.MEMWAIT = 1;
	SYSTEM.SCKCR.BIT.ICK = 0; //システムクロック　RAM,　コードフラッシュ
	SYSTEM.SCKCR.BIT.PCKA = 2; //MTU3, GPT,RSPI, unit1
	SYSTEM.SCKCR.BIT.PCKB = 2; //CMT,TPU, unit1
	SYSTEM.SCKCR.BIT.PCKC = 2; //S12AD unit0
	SYSTEM.SCKCR.BIT.PCKD = 2; //S12AD unit1
	SYSTEM.SCKCR.BIT.BCK = 1; //BSC, I/O
	SYSTEM.SCKCR.BIT.FCK = 2; //データフラッシュ
	SYSTEM.SCKCR3.WORD = 0x0400;
}

void initSci1() {
	SYSTEM.PRCR.WORD = 0xA503;
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MSTP (SCI1) = 0;
	SCI1.SMR.BYTE = 0;
	SCI1.SCR.BYTE = 0;
	SCI1.SEMR.BIT.BGDM = 0;
	SCI1.SEMR.BIT.ABCS = 0;
	SCI1.BRR = 7; // 230400  baurate.xlsx 参照
	SCI1.SCR.BIT.RIE = 1; // 受信割込み:許可(1)/禁止(0)
	SCI1.SCR.BIT.TE = 1; //送信許可
	SCI1.SCR.BIT.RE = 1; //受信許可
	PORT3.PMR.BIT.B0 = 1; //PD5をRXD1に
	PORT2.PMR.BIT.B6 = 1; //入力バッファ設定
	MPC.P30PFS.BIT.PSEL = 10; //RXD1 or SMSO1 or SSCL
	MPC.P26PFS.BIT.PSEL = 10; //TXD1 or SMOSI1 or SSDA1
	IEN(SCI1, RXI1) = 1; //割り込み許可
	IPR(SCI1, RXI1) = 3; //割り込み優先度設定
	SYSTEM.PRCR.WORD = 0xA500;
	MPC.PWPR.BIT.B0WI = 1;
	MPC.PWPR.BIT.PFSWE = 0;
}

void initCmt0() {
	//クロックプロテクト解除
	SYSTEM.PRCR.WORD = 0xA503;
	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;
	MSTP (CMT0) = 0;
	IEN(CMT0, CMI0) = 1;
	IPR(CMT0, CMI0) = 9;
	SYSTEM.PRCR.BIT.PRC1 = 0;
	CMT0.CMCR.BIT.CKS = 0;
	CMT0.CMCR.BIT.CMIE = 1;
	CMT0.CMCNT = 0;
	CMT0.CMCOR = _PCLKB / 8 / CMT_CYCLE - 1;
	CMT.CMSTR0.BIT.STR0 = 1;
	SYSTEM.PRCR.WORD = 0xA500;
}
void initCmt1() {
	//クロックプロテクト解除
	SYSTEM.PRCR.WORD = 0xA503;
	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;
	MSTP (CMT1) = 0;
	IEN(CMT1, CMI1) = 1;
	IPR(CMT1, CMI1) = 8;
	SYSTEM.PRCR.BIT.PRC1 = 0;
	CMT1.CMCR.BIT.CKS = 0;
	CMT1.CMCR.BIT.CMIE = 1;
	SYSTEM.PRCR.WORD = 0xA500;
}

void initIsouKeisu() {
	SYSTEM.PRCR.WORD = 0xA503;
	MTU.TSTRA.BIT.CST1 = 0;
	MTU.TSTRA.BIT.CST2 = 0;
	MSTP (MTU) = 0;
	MSTP (MTU1) = 0;
	MSTP (MTU2) = 0;
	//PMR = 0
	PORTA.PMR.BIT.B1 = 0;
	PORTA.PMR.BIT.B3 = 0;
	PORTA.PMR.BIT.B4 = 0;
	PORTA.PMR.BIT.B6 = 0;
	//protect off
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	// MTU.TCNT is readable
	MTU.TRWERA.BIT.RWE = 1;
	// pin mode assign
	MPC.PA1PFS.BIT.PSEL = 2;	//MTU2 MTCLK-C
	MPC.PA3PFS.BIT.PSEL = 2;	//MTU2 MTCLK-D
	MPC.PA4PFS.BIT.PSEL = 2; //MTU1 MTCLK-A
	MPC.PA6PFS.BIT.PSEL = 2; //MTU1 MTCLK-B
	//protect on
	MPC.PWPR.BIT.B0WI = 1;
	MPC.PWPR.BIT.PFSWE = 0;
	//PMR = 1
	PORTA.PMR.BIT.B1 = 1;
	PORTA.PMR.BIT.B3 = 1;
	PORTA.PMR.BIT.B4 = 1;
	PORTA.PMR.BIT.B6 = 1;
	// PCR = 1
	PORTA.PCR.BIT.B1 = 1;
	PORTA.PCR.BIT.B3 = 1;
	PORTA.PCR.BIT.B4 = 1;
	PORTA.PCR.BIT.B6 = 1;
	MTU1.TMDR1.BIT.MD = 4;
	MTU2.TMDR1.BIT.MD = 4;
	MTU1.TCNT = 30000;
	MTU2.TCNT = 30000;
	SYSTEM.PRCR.WORD = 0xA500;	// protext off
	//start
	MTU.TSTRA.BIT.CST1 = 1;
	MTU.TSTRA.BIT.CST2 = 1;
}

void initGPT01() {
	SYSTEM.PRCR.WORD = 0xA503;
	MSTP (GPT) = 0;
	MSTP (GPT0) = 0;
	MSTP (GPT1) = 0;
	MSTP (GPT2) = 0;
	MSTP (GPT3) = 0;

	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;

	GPT0.GTCNT = 0;
	GPT0.GTCR.BIT.MD = 0;
	GPT0.GTUDC.WORD = 0;
	GPT0.GTCR.BIT.TPCS = 0;
	GPT0.GTIOR.BIT.GTIOA = 6;
	PORTA.PMR.BIT.B2 = 1;
	MPC.PA2PFS.BIT.PSEL = 0x1E; //GPT0 GTIOC0A
	GPT0.GTONCR.BIT.OAE = 1;
	GPT0.GTBER.BIT.CCRA = 1;
	GPT0.GTPR = M_CYCLE;
	GPT0.GTCCRA = M_CYCLE / 2;
	GPT0.GTCCRC = M_CYCLE / 2;

	GPT1.GTCNT = 0;
	GPT1.GTCR.BIT.MD = 0;
	GPT1.GTUDC.WORD = 0;
	GPT1.GTCR.BIT.TPCS = 0;
	GPT1.GTIOR.BIT.GTIOA = 6;
	PORTA.PMR.BIT.B5 = 1;
	MPC.PA5PFS.BIT.PSEL = 0x1E; //GPT1 GTIOC1B
	GPT1.GTONCR.BIT.OAE = 1;
	GPT1.GTBER.BIT.CCRA = 1;
	GPT1.GTPR = M_CYCLE;
	GPT1.GTCCRA = M_CYCLE / 2;
	GPT1.GTCCRC = M_CYCLE / 2;

	GPT2.GTCNT = 0;
	GPT2.GTCR.BIT.MD = 0;
	GPT2.GTUDC.WORD = 0;
	GPT2.GTCR.BIT.TPCS = 0;
	GPT2.GTIOR.BIT.GTIOA = 6;
	PORTE.PMR.BIT.B3 = 1;
	MPC.PE3PFS.BIT.PSEL = 0x1E; //GPT1 GTIOC2A
	GPT2.GTONCR.BIT.OAE = 1;
	GPT2.GTBER.BIT.CCRA = 1;
	GPT2.GTPR = FAN_CYCLE;
	GPT2.GTCCRA = FAN_CYCLE / 4;
	GPT2.GTCCRC = FAN_CYCLE / 4;

//	GPT3.GTCNT = 0;
//	GPT3.GTCR.BIT.MD = 0;
//	GPT3.GTUDC.WORD = 0;
//	GPT3.GTCR.BIT.TPCS = 0;
//	GPT3.GTIOR.BIT.GTIOB = 6;
//	PORTC.PMR.BIT.B6 = 1;
//	MPC.PC6PFS.BIT.PSEL = 0x1E; //GPT1 GTIOC2A
////	GPT3.GTONCR.BIT.OAE = 1;
//	GPT3.GTONCR.BIT.OBE = 1;
//	GPT3.GTBER.BIT.CCRA = 1;
//	GPT3.GTPR = M_CYCLE;
//	GPT3.GTCCRA = M_CYCLE / 2;
//	GPT3.GTCCRC = M_CYCLE / 2;

	//protect on
	MPC.PWPR.BIT.B0WI = 1;
	MPC.PWPR.BIT.PFSWE = 0;

	SYSTEM.PRCR.WORD = 0xA500;	// protext off
}

void stopVacume() {
	GPT2.GTCCRA = GPT2.GTCCRC = 0;
	fanStart = false;
	cmt_wait(1);
	GPT.GTSTR.BIT.CST2 = 0;
}

void init_Mtu4() {
	SYSTEM.PRCR.WORD = 0xA503; // Protect off
	/*	P257でベクタテーブルの説明	*/
	MSTP (MTU4) = 0;
	MTU4.TCR.BIT.TPSC = 0;
	MTU4.TCR.BIT.CCLR = 2;				// TGRBコンペアマッチでTCNTクリア
	MTU4.TIER.BIT.TGIEA = 1;				// TGRAの割り込み許可
	MTU4.TGRA = (int) (_PCLKA / MTU_CYCLE) - 1900 - 1;// TGRB - TGRA = 発光時間 3840= 40us
	MTU4.TIER.BIT.TGIEB = 1;				// TGRBの割り込み許可
	MTU4.TGRB = (int) (_PCLKA / MTU_CYCLE) - 1;	// 96MHz 1/96M =0.0104166us 0.0104166*19200=0.2ms
	//割り込み許可
	IEN(PERIA, INTA210) = 1;
	ICU.SLIAR210.BYTE = 0x15U;
	IPR(PERIA, INTA210) = 13;

	ICU.SLIAR211.BYTE = 0x16U;
	IEN(PERIA, INTA211) = 1;
	IPR(PERIA, INTA211) = 12;

	MTU.TSTRA.BIT.CST4 = 1;				//MTU0のカウントスタート p460
	SYSTEM.PRCR.WORD = 0xA500; // Protect off

}

void init_Mtu6() {
	SYSTEM.PRCR.WORD = 0xA503; // Protect of//f

	MSTP (MTU6) = 0;
	MTU6.TCR.BIT.TPSC = 0;
	MTU6.TCR.BIT.CCLR = 2;		// TGRBコンペアマッチでTCNTクリア

	MTU6.TIER.BIT.TGIEA = 1;	// TGRAの割り込み許可
	MTU6.TIER.BIT.TGIEB = 1;	// TGRBの割り込み許可

	//割り込み許可
	ICU.SLIAR212.BYTE = 30;
	ICU.SLIAR213.BYTE = 31;

	IEN(PERIA, INTA212) = 1;
	IPR(PERIA, INTA212) = 6;
	IEN(PERIA, INTA213) = 1;
	IPR(PERIA, INTA213) = 7;

	SYSTEM.PRCR.WORD = 0xA500; // Protect off
}

void startVacume2(int duty) {
	GPT2.GTPR = M_CYCLE2;
	GPT2.GTCCRA = GPT2.GTCCRC = M_CYCLE2 * duty / 100;
	fanStart = true;
	GPT.GTSTR.BIT.CST2 = 1;
	cmt_wait(1500);
}
void startVacume() {
	GPT2.GTPR = M_CYCLE2;
	GPT2.GTCCRA = GPT2.GTCCRC = M_CYCLE2 / 2;
	fanStart = true;
	GPT.GTSTR.BIT.CST2 = 1;
	cmt_wait(1000);
}

void getSensorData() {

	if (RS_SEN45.on > RS_SEN45.off) {
		RS_SEN45.now = 0.1 * (RS_SEN45.on - RS_SEN45.off) + 0.9 * RS_SEN45.old;
	} else {
		RS_SEN45.now = 0;
	}
	if (LS_SEN45.on > LS_SEN45.off) {
		LS_SEN45.now = 0.1 * (LS_SEN45.on - LS_SEN45.off) + 0.9 * LS_SEN45.old;
	} else {
		LS_SEN45.now = 0;
	}

	if (RS_SEN2.on > RS_SEN2.off) {
		RS_SEN2.now = 0.1 * (RS_SEN2.on - RS_SEN2.off) + 0.9 * RS_SEN2.old;
	} else {
		RS_SEN2.now = 0;
	}
	if (LS_SEN2.on > LS_SEN2.off) {
		LS_SEN2.now = 0.1 * (LS_SEN2.on - LS_SEN2.off) + 0.9 * LS_SEN2.old;
	} else {
		LS_SEN2.now = 0;
	}

	if (Front_SEN.on > Front_SEN.off) {
		Front_SEN.now = 0.1 * (Front_SEN.on - Front_SEN.off)
				+ 0.9 * Front_SEN.old;
	} else {
		Front_SEN.now = 0;
	}
}
#endif /* INIT_H_ */
