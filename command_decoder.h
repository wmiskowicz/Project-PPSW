#ifndef COMMAND_DECODER_H
#define COMMAND_DECODER_H

#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 10 
#define MAX_KEYWORD_NR 4

enum TokenType {KEYWORD, NUMBER, STRING};
enum KeywordCode {CAL, GOTO, CALC, ID};

union TokenValue{
	enum KeywordCode eKeyword; 
	unsigned int uiNumber; 
	char* pcString;
};

struct Token{
	enum TokenType eType; 
	union TokenValue uValue;
};

void DecodeMsg(char *pcString);

#endif
