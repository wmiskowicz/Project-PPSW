struct Watch {
	unsigned char ucMinutes;
	unsigned char ucSeconds;
	unsigned char fSeccondsValueChanged;
	unsigned char fMinutesValueChanged;
	unsigned char fSendingTime;
};



void WatchUpdate(void);
