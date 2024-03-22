#include "string.h"

void CopyString(char pcSource[], char pcDestination[]){
	unsigned char ucCharCount;
		
	for(ucCharCount = 0; pcSource[ucCharCount] != NULL; ucCharCount++){
		pcDestination[ucCharCount] = pcSource[ucCharCount];
	}
	pcDestination[ucCharCount] = pcSource[ucCharCount];
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
	unsigned char ucCharCount;
	
	for(ucCharCount = 0; pcStr1[ucCharCount] != NULL; ucCharCount++){
		
		if(pcStr1[ucCharCount] != pcStr2[ucCharCount]){
			return DIFFERENT;
		}
	}
	return EQUAL;
}

void AppendString (char pcSourceStr[],char pcDestinationStr[]){
	unsigned char ucCharCount;
	
	for(ucCharCount = 0; pcDestinationStr[ucCharCount] != NULL; ucCharCount++){}
	CopyString(pcSourceStr, pcDestinationStr + ucCharCount);
}


void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){
	unsigned char ucCharCount;
	
	for(ucCharCount = 0; pcString[ucCharCount] != NULL; ucCharCount++){
		if(pcString[ucCharCount] == cOldChar){
			
			pcString[ucCharCount] = cNewChar;
		}
	}		
}



enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
	
	unsigned char ucCharCount;
	unsigned char ucCurrChar;
	*puiValue=0;
	
	if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==NULL)){
		return ERROR;
	}
	
	for(ucCharCount=2; pcStr[ucCharCount]!=NULL; ucCharCount++){
		ucCurrChar = pcStr[ucCharCount];
		if(ucCharCount==6){
			return ERROR;
		}
		
		*puiValue = *puiValue << 4;
		if((ucCurrChar <= '9') && (ucCurrChar >= '0')){
			*puiValue = (*puiValue) | ucCurrChar-'0';
		}
		else if((ucCurrChar <= 'F') && (ucCurrChar >= 'A')){
			*puiValue = (*puiValue) | ucCurrChar-'A'+10;
		}
		else{
			return ERROR;
		}
	}
	return OK;
}

void UIntToHexStr (unsigned int uiValue, char pcStr[]){

	unsigned char ucTetradCount;
	unsigned char ucCurrTetrad;

	pcStr[0] = '0';
	pcStr[1] = 'x';
	pcStr[6] = NULL;
	
	for(ucTetradCount=0; ucTetradCount<4; ucTetradCount++){
		ucCurrTetrad=(uiValue >> (ucTetradCount*4))&0x0F;
		if(ucCurrTetrad<10){
			pcStr[5-ucTetradCount] = '0'+ucCurrTetrad;
		} 
		else{
		pcStr[5-ucTetradCount] = 'A'+(ucCurrTetrad-10);
		}
	}
}

void CreateMessage(unsigned char ucCtrVal, char cPrefix[], char pcMessage[]){
	char cCtrValStr[7];
	char cMessage[13] = "";
	

	CopyString(cPrefix, cMessage);
	UIntToHexStr(ucCtrVal, cCtrValStr);
	AppendString(cCtrValStr, cMessage);
	CopyString(cMessage, pcMessage);
	
}
