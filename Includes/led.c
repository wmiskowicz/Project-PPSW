#include <LPC21xx.H>
#include "led.h"

#define LED0_bm 1<<16 
#define LED1_bm 1<<17 
#define LED2_bm 1<<18 
#define LED3_bm 1<<19 

#define BUTTON0_bm 1<<4
#define BUTTON1_bm 1<<6
#define BUTTON2_bm 1<<5
#define BUTTON3_bm 1<<7

enum Step {LEFT, RIGHT};

void LedInit(){
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks){

	IO1CLR = IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	
	switch(ucLedIndeks){
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
		default:
			break;
	}
}


void eLedStep(enum Step Direction){

	static unsigned int uiStepCtr;
	
	if(Direction == LEFT){
		uiStepCtr++;
		}
	else{
		uiStepCtr--;
		}
	LedOn(uiStepCtr % 4);
}


void LedStepLeft(void){
		eLedStep(LEFT);
}

void LedStepRight(void){
		eLedStep(RIGHT);
}
