struct Watch {
	unsigned char ucMinutes;
	unsigned char ucSeconds;
	unsigned char fSeccondsValueChanged;
	unsigned char fMinutesValueChanged;
	unsigned char fSendingTime;
};

void ClearMinutesFlag(void);
void ClearSecondsFlag(void);

unsigned char GetSecondsFlag(void);
unsigned char GetMinutesFlag(void);

void CreateMessage(unsigned char ucCtrVal, char cUnits[], char pcMessage[]);
void WatchUpdate(void);
