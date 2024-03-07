#include <LPC21xx.H>
#include "led.h"
#include "Interrupts.h"
#include "servo.h"

#define mPIN10 1<<10





struct Servo{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
	unsigned int uiOffsetWanted;
};

enum DetectorState {ACTIVE, INACTIVE};

enum DetectorState eReadDetector(){
	if((IO0PIN & mPIN10) == 0){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
}

enum DetectorState eDetectorState;
struct Servo sServo;


void ServoGoTo(unsigned int uiPosition) {
	sServo.uiDesiredPosition=uiPosition;
}

void DetectorInit(){
	IO0DIR &= ~mPIN10;
	
	if(eReadDetector()==INACTIVE){
		LedStepLeft();
		sServo.eState=CALLIB;
	}
	else{
		sServo.eState=OFFSET;
	}
}


void ServoCallib(void){
	sServo.eState=CALLIB;
}

void Automat_servo(){
		switch (sServo.eState){
			case CALLIB:{
				DetectorInit();
				sServo.uiCurrentPosition=0;
				sServo.uiDesiredPosition=0;
				sServo.uiOffsetWanted = 0;
			}
			break;
			case OFFSET:{
				if(sServo.uiCurrentPosition<sServo.uiOffsetWanted){
					LedStepRight();
					sServo.uiCurrentPosition++;
				}
				else{
					sServo.uiCurrentPosition=0;
					sServo.eState = IDLE;
				}
			}
			break;
			case IDLE:{
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
					sServo.eState=IN_PROGRESS;
				}
				else{
					sServo.eState=IDLE;
				}
			}
			break;
			case IN_PROGRESS:{
				if(sServo.uiDesiredPosition != sServo.uiCurrentPosition){
					sServo.eState=IN_PROGRESS;
					
					if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
						sServo.uiCurrentPosition++;
						LedStepRight();
					}
					else{
						sServo.uiCurrentPosition--;
						LedStepLeft();
					}
					
				}
				else{
					sServo.eState=IDLE;
				}
			}
			break;
		}
}

void ServoInit(unsigned int uiServoFrequency){
	unsigned int uiServoPeriod=(1000000/uiServoFrequency);
	
	LedInit();
	Timer0Interrupts_Init(uiServoPeriod, &Automat_servo);
	ServoCallib();
}

