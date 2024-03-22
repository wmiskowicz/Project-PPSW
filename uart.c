#include <LPC210X.H>
#include "uart.h"
#include "servo.h"
#include "string.h"

/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020



//=========Reciever===========
char cOdebranyZnak;

struct RecieverBuffer{
	char cData[RECIEVER_SIZE];
	unsigned char ucCharCtr;
	enum eRecieverStatus eStatus;
};
struct RecieverBuffer sRxBuffer;


void Reciever_PutCharacterToBuffer(char cCharacter){
	
  if(sRxBuffer.ucCharCtr == RECIEVER_SIZE){
		
		sRxBuffer.eStatus = OVERFLOW;
		sRxBuffer.ucCharCtr = 0;
	}  
	else if(cCharacter == TERMINATOR){
		
		sRxBuffer.eStatus = READY;
		sRxBuffer.cData[sRxBuffer.ucCharCtr] = NULL;
		sRxBuffer.ucCharCtr = 0;
  }
	else{
		
		sRxBuffer.cData[sRxBuffer.ucCharCtr] = cCharacter;
		sRxBuffer.ucCharCtr++;
	}
}

enum eRecieverStatus eReciever_GetStatus(void){
    return sRxBuffer.eStatus;
}

void Reciever_GetStringCopy(char *ucDestination){
    CopyString(sRxBuffer.cData, ucDestination);
    sRxBuffer.eStatus = EMPTY;
}

//=========Transmitter===========
char cKomunikat[TRANSMITER_SIZE];

struct TransmiterBuffer{
	char cData[TRANSMITER_SIZE];
	enum eTransmiterStatus eStatus;
	unsigned char fLastCharacter;
	unsigned char cCharCtr;
};
struct TransmiterBuffer sTransmiterBuffer;

char Transmiter_GetCharacterFromBuffer(){
	char cCurrChar;
	
	if(sTransmiterBuffer.fLastCharacter){
		
		sTransmiterBuffer.cCharCtr = 0;
		sTransmiterBuffer.fLastCharacter = 0;
		sTransmiterBuffer.eStatus = FREE;
		return NULL;
	}
	else if(sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr] == NULL){
		
		sTransmiterBuffer.fLastCharacter = 1;
		return TERMINATOR;
	}
	else{
		cCurrChar = sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr];
		sTransmiterBuffer.cCharCtr++;
		return cCurrChar;		
	}
	
}

void Transmiter_SendString(char cString[]){
	
	CopyString(cString, sTransmiterBuffer.cData);
	sTransmiterBuffer.eStatus = BUSY;
	U0THR = Transmiter_GetCharacterFromBuffer();
}

enum eTransmiterStatus Transmiter_GetStatus(void){
	return sTransmiterBuffer.eStatus;
}


__irq void UART0_Interrupt (void) {
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
      cOdebranyZnak = U0RBR;
			Reciever_PutCharacterToBuffer(cOdebranyZnak);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
		 if(Transmiter_GetStatus() == BUSY){
      U0THR = Transmiter_GetCharacterFromBuffer();
		 }
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | 0x00000005;                                     // ustawic pina na tx i rx uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // długosc słowa, DLAB = 1
   U0DLL   = ((15000000)/16)/uiBaudRate;                      // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE | mTHRE_INTERRUPT_ENABLE; // enable interrupt Rx data

   // INT
   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}


