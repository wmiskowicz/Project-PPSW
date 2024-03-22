#include "watch.h"



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




