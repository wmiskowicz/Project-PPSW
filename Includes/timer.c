#include <LPC21xx.H>
#include "timer.h"


#define mCOUNTER_ENABLE 1<<0
#define mCOUNTER_RESET 1<<1

#define mMR0_INTERRUPT_FLAG (1<<0)
#define mMR0_INTERRUPT_MATCH (1<<0)
#define mMR0_INTERRUPT_RESET (1<<1)


void InitTimer0(void){
	T0TCR = mCOUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= mCOUNTER_RESET;
	T0TCR &= ~(mCOUNTER_RESET);
	while ((uiTime*15) > T0TC){}
}

void InitTimer0Match0(unsigned int uiDelayTime){
	T0MR0 = uiDelayTime*15;
	T0TCR |= mCOUNTER_RESET;
	T0TCR &= ~(mCOUNTER_RESET);
	T0TCR |= mCOUNTER_ENABLE;
	T0MCR |= mMR0_INTERRUPT_MATCH;
	T0MCR |= mMR0_INTERRUPT_RESET;
}

void WaitOnTimer0Match0(){

	while ((T0IR & mMR0_INTERRUPT_FLAG) == 0){}
	T0IR = mMR0_INTERRUPT_FLAG;
}
