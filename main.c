#include "./Includes/uart.h"
#include "./Includes/servo.h"
#include "./Includes/command_decoder.h"
#include "./Includes/Interrupts.h"
#include "./Includes/watch.h"
#include "./Includes/string.h"

extern struct Token asToken[MAX_TOKEN_NR];
extern struct Watch sWatch;

struct TransmitterFlags sTransmitterFlags;

int main(){
	
	char cBuffDataCopy[RECIEVER_SIZE];
	char cWatchMessage[TRANSMITER_SIZE];
	char cCalcMessage[TRANSMITER_SIZE];
	
	ServoInit(25);
	Timer0Interrupts_Init(1000000, &WatchUpdate);
	UART_InitWithInt(9600);	
	Transmiter_SendString("Init");
	
	while(1){
		
		if(Transmiter_GetStatus() == FREE){
			
      if(sWatch.fMinutesValueChanged){

				CreateMessage(sWatch.ucMinutes, "min ", cWatchMessage);	
				Transmiter_SendString(cWatchMessage);
				sWatch.fMinutesValueChanged=0;
			}
			else if(sWatch.fSeccondsValueChanged){

				CreateMessage(sWatch.ucSeconds, "sec ", cWatchMessage);
				Transmiter_SendString(cWatchMessage);
				sWatch.fSeccondsValueChanged=0;
			}
			else if(sTransmitterFlags.fId){
				
				Transmiter_SendString("Servo LPC");
				sTransmitterFlags.fId = 0;
			}
			else if(sTransmitterFlags.fUnknown){
				
				Transmiter_SendString("Unknown command");
				sTransmitterFlags.fUnknown = 0;
			}
			else if(sTransmitterFlags.fCalc){
				
				CreateMessage(asToken[1].uValue.uiNumber << 1, "calc ", cCalcMessage);
				Transmiter_SendString(cCalcMessage);
				sTransmitterFlags.fCalc = 0;
			}
		}
		
		
		if(eReciever_GetStatus() == READY){
			
			Reciever_GetStringCopy(cBuffDataCopy);
			DecodeMsg(cBuffDataCopy);
			
			if(asToken[0].eType == KEYWORD){
				
				if(asToken[0].uValue.eKeyword == CAL){
					ServoCallib();
				}
				else if(asToken[0].uValue.eKeyword == GOTO && asToken[1].eType == NUMBER){
					ServoGoTo(asToken[1].uValue.uiNumber);
				}
				else if(asToken[0].uValue.eKeyword == CALC && asToken[1].eType == NUMBER){
					sTransmitterFlags.fCalc = 1;
				}	
				else if(asToken[0].uValue.eKeyword == ID){
					sTransmitterFlags.fId = 1;
				}
			}
			else{
				sTransmitterFlags.fUnknown = 1;
			}
		}
	}
}
