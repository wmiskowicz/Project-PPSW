#define RECIEVER_SIZE 19
#define TRANSMITER_SIZE 19

void UART_InitWithInt(unsigned int uiBaudRate);

enum eRecieverStatus {EMPTY, READY, OVERFLOW};
enum eRecieverStatus eReciever_GetStatus(void);
void Reciever_GetStringCopy(char *ucDestination);

void Transmiter_SendString(char cString[]);
enum eTransmiterStatus Transmiter_GetStatus(void);

enum eTransmiterStatus {FREE, BUSY};


