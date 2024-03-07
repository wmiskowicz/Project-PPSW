#include "watch.h"
#include "string.h"



struct Watch sWatch;

void WatchUpdate(void){
	
	if(sWatch.ucSeconds < 60){
		sWatch.ucSeconds++;
	}
	else{
		sWatch.ucSeconds=0;
		sWatch.ucMinutes++;
		sWatch.fMinutesValueChanged=1;
	}
	sWatch.fSeccondsValueChanged=1;
}

void ClearMinutesFlag(void){
	sWatch.fMinutesValueChanged=0;
}

void ClearSecondsFlag(void){
	sWatch.fSeccondsValueChanged=0;
}

unsigned char GetSecondsFlag(void){
	return sWatch.fSeccondsValueChanged;
}

unsigned char GetMinutesFlag(void){
	return sWatch.fMinutesValueChanged;
}

void CreateMessage(unsigned char ucCtrVal, char cPrefix[], char pcMessage[]){
	char cCtrValStr[7];
	char cMessage[13] = "";
	

	CopyString(cPrefix, cMessage);
	UIntToHexStr(ucCtrVal, cCtrValStr);
	AppendString(cCtrValStr, cMessage);
	CopyString(cMessage, pcMessage);
	
}
