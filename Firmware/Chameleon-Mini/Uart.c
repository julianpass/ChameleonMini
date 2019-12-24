#include "Uart.h"

void initUart(void) {
  // config pin
  PORTE.OUTSET = 0x08;//0b00001000;
  PORTE.DIRSET = 0x08;// = 0b00001000;


  // Baud rate selection
  USARTE0.BAUDCTRLB = 0; //Just to be sure that BSCALE is 0

  USARTE0.BAUDCTRLA = 0xB0 & 0xFF;
  USARTE0.BAUDCTRLB = ((0xB0 & 0xF00) >> 0x08);


  //USARTE0.BAUDCTRLA = 0xB0; // 176

  //Disable interrupts, just for safety
  USARTE0.CTRLA = 0;
  //8 data bits, no parity and 1 stop bit
  USARTE0.CTRLC = USART_CHSIZE_8BIT_gc;

  //Enable receive and transmit
  USARTE0.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // And enable high speed mode
  char string[] = "UART READY!";
  sendUartStr(string);
}

uint8_t readUartByte(void) {
  if (USARTE0_STATUS & USART_RXCIF_bm){//Interesting DRIF didn't work.
    return USARTE0_DATA;
  }
  else {
    return 0;
  }

}

void sendUartByte(uint8_t data) {
  while( !(USARTE0_STATUS & USART_DREIF_bm) ); //Wait until DATA buffer is empty
  USARTE0_DATA = data;

}

void sendUartStr(char *data)
{
   while( *data != '\0' ){
      sendUartByte(*data++);
   }// End while( *data != '\0' )
}

void writeUartBuffer(const void* Buffer, uint16_t ByteCount) {
  uint8_t* data = (uint8_t*)Buffer;
  for (uint16_t i=0;i < ByteCount; i++) {
    sendUartByte(*(data+i));
  }

}
