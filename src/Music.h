/*
 * Music.h
 *
 *  Created on: 2016/05/19
 *      Author: Naoto
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#define G_1_ 195.99771799087463
#define G_1s_ 207.65234878997256
#define A_1_ 220
#define A_1s_ 233.08188075904496
#define B_1_ 246.94165062806206
#define C_ 261.6255653005986
#define Cs_ 277.1826309768721
#define D_ 293.6647679174076
#define Ds_ 311.12698372208087
#define E_ 329.6275569128699
#define F_ 349.2282314330039
#define Fs_ 369.9944227116344
#define G_ 391.99543598174927
#define Gs_ 415.3046975799451
#define A_ 440
#define As_ 466.1637615180899
#define B_ 493.8833012561241
#define C2_ 523.2511306011972

#define C2s_ 554.3652619537442
#define D2_ 587.3295358348151
#define D2s_ 622.2539674441618
#define E2_ 659.2551138257398
#define F2_ 698.4564628660078
#define F2s_ 739.9888454232688
#define G2_ 783.9908719634985
#define G2s_ 830.6093951598903
#define A2_ 880
#define A2s_ 932.3275230361799
#define B2_ 987.7666025122483
#define C3_ 1046.5022612023945
#define C3s_ 1108.73
#define D3_ 1174.6590716696303
#define D3s_ 1244.51
#define E3_ 1318.5102276514797
#define F3_ 1396.9129257320155
#define G3_ 1567.981743926997
#define G3s_ 1661.22
#define A3_ 1760
#define A3s_ 1864.66
#define B3_ 1975.533205024496
#define C4_ 2093.0

#define MUSIC_CYCLE 60000000.0f
volatile int m_time = 0;
volatile unsigned int melodyTime = 0;

volatile char singing = false;
//void startCmt1(int T) {
//	if (singing == false) {
//		CMT1.CMCNT = 0;
//		CMT1.CMCOR = T;
//		buzzerTimer = 0;
//		CMT.CMSTR0.BIT.STR1 = 1;
//	}
//	singing = true;
//}
//void stopCmt1() {
//	singing = false;
//	PORTC.PODR.BIT.B6 = 0;
//	CMT.CMSTR0.BIT.STR1 = 0;
//}

volatile int musicTimeout = 0;
void startCmt1(int T) {
	buzzerTimer = 0;
	singing = true;
}

void stopCmt1() {
	singing = false;
	PORTC.PODR.BIT.B6 = 0;
}
void makeMusic(float melo, int meloTime) {
	m_time = 0;
	startCmt1((int) (MUSIC_CYCLE / melo / 2));
	cmt_wait((int) meloTime);
	stopCmt1();
	m_time = 0;
}

void cmtMusic(float melo, int meloTime) {
	stopCmt1();
	startCmt1((int) (MUSIC_CYCLE / melo / 2));
	m_time = meloTime;
}

void mazeStartMusic(int te) {
	int temp = (int) (te / 1.0);
	makeMusic(E2_, temp - 10);
	cmt_wait(10);
	makeMusic(E2_, temp);
	cmt_wait(temp);
	makeMusic(E2_, temp);
	cmt_wait(temp);
	makeMusic(C2_, temp);
	makeMusic(E2_, temp);
	cmt_wait(temp);
	makeMusic(G2_, temp);
	cmt_wait(temp * 3);
	makeMusic(G_, temp);
	cmt_wait(temp * 3);
}

void mazefinishMusic(int te) {
	int temp = (int) (te / 1.1);
	makeMusic(G_1_, temp);
	makeMusic(C_, temp);
	makeMusic(E_, temp);

	makeMusic(G_, temp);
	makeMusic(C2_, temp);
	makeMusic(E2_, temp);

	makeMusic(G2_, temp * 3);
	makeMusic(E2_, temp * 3);
/////////////////////////////////
	makeMusic(G_1s_, temp);
	makeMusic(C_, temp);
	makeMusic(Ds_, temp);

	makeMusic(Gs_, temp);
	makeMusic(C2_, temp);
	makeMusic(D2s_, temp);

	makeMusic(G2s_, temp * 3);
	makeMusic(D2s_, temp * 3);
////////////////////////////////
	makeMusic(A_1s_, temp);
	makeMusic(C_, temp);
	makeMusic(D_, temp);

	makeMusic(As_, temp);
	makeMusic(D2_, temp);
	makeMusic(F2_, temp);

	makeMusic(A2s_, temp * 3 - 5);
	cmt_wait(5);
	makeMusic(A2s_, temp - 5);
	cmt_wait(5);
	makeMusic(A2s_, temp - 5);
	cmt_wait(5);
	makeMusic(A2s_, temp - 5);
	cmt_wait(5);
	makeMusic(C3_, temp * 6);
}

void coin(int temp) {
	makeMusic(B2_, temp - 10);
	cmt_wait(10);
	makeMusic(E3_, temp - 10);
}

void oneUp(int temp) {
	makeMusic(E2_, temp - 10);
	cmt_wait(10);
	makeMusic(G2_, temp - 10);
	cmt_wait(10);
	makeMusic(E3_, temp - 10);
	cmt_wait(10);
	makeMusic(C3_, temp - 10);
	cmt_wait(10);
	makeMusic(E3_, temp - 10);
	cmt_wait(10);
	makeMusic(G3_, temp - 10);
}

void decide2(int temp) {
	makeMusic(G_1_, temp - 10);
	cmt_wait(10);
	makeMusic(G_1_, temp - 10);
	cmt_wait(10);
	makeMusic(G_1_, temp - 10);
	cmt_wait(10);
}

void decide(int temp) {
	makeMusic(G2_, temp - 10);
	cmt_wait(10);
	makeMusic(A2_, temp - 10);
	cmt_wait(10);
	makeMusic(B2_, temp - 10);
}
void startTransam(int tmp) {
	makeMusic(B3_, tmp - 10);
	cmt_wait(10);
	makeMusic(B3_, tmp - 10);
	cmt_wait(10);
	makeMusic(B3_, tmp - 10);
	cmt_wait(10);
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);
	makeMusic(B3_, tmp - 10);
	cmt_wait(tmp);
	makeMusic(F3_, 2 * (tmp - 10));
	cmt_wait(10);
	makeMusic(E3_, tmp - 10);
	cmt_wait(10);
	makeMusic(D3_, tmp - 10);
}

void quoria(int tmp2) {
	double tmp = tmp2;
	makeMusic(D2s_, tmp / 2 - 10);
	cmt_wait(10);
	makeMusic(C3_, 1.5 * tmp - 10);
	cmt_wait(10);
	makeMusic(C3s_, tmp / 4 - 10);
	cmt_wait(10);
	makeMusic(C3_, 3 * tmp - 10);
	cmt_wait(10);
	makeMusic(A2s_, tmp / 4 - 10);
	cmt_wait(10);
	makeMusic(G2s_, 3.0 * tmp / 4 - 10);
	cmt_wait(10);
	makeMusic(A3s_, 3.0 * tmp / 4 - 10);
	cmt_wait(10);
	makeMusic(G3s_, tmp / 2 - 10);
	cmt_wait(10);
	makeMusic(G3s_, tmp / 4 - 10);
	cmt_wait(10);
	makeMusic(G3s_, tmp / 2 - 10);
	cmt_wait(10);
}

void ashLikeSnow(int tmp) {
	makeMusic(G3_, tmp - 10);
	cmt_wait(10);
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);

	makeMusic(G3_, tmp - 10);
	cmt_wait(10);
	makeMusic(G3_, tmp - 10);
	cmt_wait(10);
	cmt_wait(tmp);

	makeMusic(E3_, tmp / 1 - 10);
	cmt_wait(10);
	makeMusic(F3_, tmp / 1 - 10);
	cmt_wait(10);
	makeMusic(G3_, tmp / 1 - 10);
	cmt_wait(10);
	makeMusic(G3_, tmp / 1 - 10);
	cmt_wait(10);

	makeMusic(A3_, tmp / 1 - 10);
	cmt_wait(10);
	makeMusic(B3_, tmp / 1 - 10);
	cmt_wait(10);

	makeMusic(C4_, 1 * tmp - 10);
	cmt_wait(10);
	makeMusic(B3_, 2 * tmp - 10);
	cmt_wait(10);
	makeMusic(G3_, 1 * tmp - 10);
	cmt_wait(10);
}

void aheadTears(int tmp) {
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);
	makeMusic(A3_, 3 * tmp - 10);
	cmt_wait(tmp);
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);
	makeMusic(A3_, tmp - 10);
	cmt_wait(10);
	makeMusic(C4_, 1.5 * tmp - 10);
	cmt_wait(tmp / 4);
	makeMusic(G3_, 2 * tmp - 10);
	cmt_wait(10);
	makeMusic(F3_, 2 * tmp - 10);
	cmt_wait(10);
	makeMusic(G3_, 2 * tmp - 10);
	cmt_wait(10);

}
/*makeMusic(C_, 500);
 cmtMusic(Cs_, 500);
 cmtMusic(D_, 500);
 cmtMusic(Ds_, 500);
 cmtMusic(E_, 500);
 cmtMusic(F_, 500);
 cmtMusic(Fs_, 500);
 cmtMusic(G_, 500);
 cmtMusic(Gs_, 500);
 cmtMusic(A_, 500);
 cmtMusic(As_, 500);
 cmtMusic(B_, 500);
 cmtMusic(C2_, 500);*/

#endif /* MUSIC_H_ */
