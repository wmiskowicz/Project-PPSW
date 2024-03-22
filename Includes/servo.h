enum ServoState {CALLIB, IDLE, IN_PROGRESS, OFFSET};

void ServoGoTo(unsigned int uiPosition);
void ServoCallib(void);
void ServoInit(unsigned int uiServoFrequency);

