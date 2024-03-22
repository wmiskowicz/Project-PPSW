#include "command_decoder.h"
#include "string.h"

struct Keyword{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1]; 
};


struct Token asToken[MAX_TOKEN_NR];
union TokenValue uTokenValue;
unsigned char ucTokenNr;

struct Keyword asKeywordList[MAX_KEYWORD_NR]={
	{CAL,"callib"},
	{GOTO, "goto" },
	{CALC, "calc"},
	{ID, "id"}
};


enum Stan{TOKEN, DELIMITER};

unsigned char ucFindTokensInString(char *pcString){
	
	unsigned char ucCharCount;
	unsigned char ucTokenNr=0;
	unsigned char ucCurrChar;
	enum Stan eStan=DELIMITER;

	for(ucCharCount=0;;ucCharCount++){
		ucCurrChar=pcString[ucCharCount];
		
		switch(eStan){
			case TOKEN:
			{
				if(ucTokenNr==MAX_TOKEN_NR){
					return ucTokenNr;
				}
				else if(ucCurrChar==NULL){
					return ucTokenNr;
				}
				else if(ucCurrChar!=' '){
					eStan=TOKEN;
				}
				else{
					eStan=DELIMITER;
				}
				break;
			}
			case DELIMITER:
			{
				if(ucCurrChar==NULL){
					return ucTokenNr;
				}
				else if(ucCurrChar==' '){
					eStan=DELIMITER;
				}
				else{
					eStan=TOKEN;
					asToken[ucTokenNr].uValue.pcString=pcString+ucCharCount;
					ucTokenNr++;
				}
				break;
			}
		}
	}
}



enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode){

	unsigned char ucKeywordCounter;

	for(ucKeywordCounter=0; ucKeywordCounter< MAX_KEYWORD_NR; ucKeywordCounter++){
		
		if(EQUAL == eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr)){
			*peKeywordCode= asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}


void DecodeTokens(void){

	unsigned char ucTokenCounter;
	struct Token *psCurrentToken;
	unsigned int uiTokenValue;
	enum KeywordCode eTokenCode;

	for(ucTokenCounter= 0; ucTokenCounter< ucTokenNr; ucTokenCounter++){
		psCurrentToken= &asToken[ucTokenCounter];
		
		if(OK== eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue)){
			psCurrentToken->eType= NUMBER;
			psCurrentToken->uValue.uiNumber= uiTokenValue;
		}	
		else if(OK== eStringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode)){
			psCurrentToken->eType=KEYWORD;
			psCurrentToken->uValue.eKeyword=eTokenCode;
		}
		else{
			psCurrentToken->eType=STRING;
		}
	}
}

void DecodeMsg(char *pcString){
	ucTokenNr=ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, ' ', NULL);
	DecodeTokens();
} 




