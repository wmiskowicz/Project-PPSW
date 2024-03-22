#include <LPC21xx.H>
#include "Interrupts.h"

// TIMER
#define mCOUNTER_ENABLE 0x00000001
#define mCOUNTER_RESET  0x00000002

// CompareMatch
#define mINTERRUPT_ON_MR0 0x00000001
#define mRESET_ON_MR0     0x00000002
#define mMR0_INTERRUPT    0x00000001

#define mINTERRUPT_ON_MR1 0x00000008
#define mRESET_ON_MR1     0x00000010
#define mMR1_INTERRUPT    0x00000002
// VIC (Vector Interrupt Controller) VICIntEnable
#define VIC_TIMER0_CHANNEL_NR 4
#define VIC_TIMER1_CHANNEL_NR 5

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE 0x00000020


/**********************************************/
void (*pvTimer0InterruptFunction)();
void (*pvTimer1InterruptFunction)();


__irq void Timer0IRQHandler(){

	T0IR=mMR0_INTERRUPT; 	// skasowanie flagi przerwania 
	(*pvTimer0InterruptFunction)();		// cos do roboty
	
	VICVectAddr=0; 	// potwierdzenie wykonania procedury obslugi przerwania
}

__irq void Timer1IRQHandler(){

	T1IR=mMR1_INTERRUPT;
	(*pvTimer1InterruptFunction)();
	
	VICVectAddr=0;
}
/**********************************************/
void Timer0Interrupts_Init(unsigned int uiPeriod, void *pvInterruptFunction){ // microseconds

        // interrupts

	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);            // Enable Timer 0 interrupt channel 
	VICVectCntl2  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;  // Enable Slot 1 and assign it to Timer 0 interrupt channel
	VICVectAddr2  =(unsigned long)Timer0IRQHandler; 	   // Set to Slot 1 Address of Interrupt Service Routine 

  
	pvTimer0InterruptFunction = pvInterruptFunction;
	
	
	
	// match module

	T0MR0 = 15 * uiPeriod;                 	      // value 
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0); // action 

        // timer

	T0TCR |=  mCOUNTER_ENABLE; // start 

}


void Timer1Interrupts_Init(unsigned int uiPeriod, void *pvInterruptFunction){

        // interrupts

	VICIntEnable |= (0x1 << VIC_TIMER1_CHANNEL_NR);
	VICVectCntl3  = mIRQ_SLOT_ENABLE | VIC_TIMER1_CHANNEL_NR; 
	VICVectAddr3  =(unsigned long)Timer1IRQHandler;

  
	pvTimer1InterruptFunction = pvInterruptFunction;
	
	
	
	// match module

	T1MR1 = 15 * uiPeriod;
	T1MCR |= (mINTERRUPT_ON_MR1 | mRESET_ON_MR1); 

        // timer

	T1TCR |=  mCOUNTER_ENABLE; // start 

}

