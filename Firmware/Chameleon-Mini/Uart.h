#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#include "Common.h"


void initUart(void);
uint8_t readUartByte(void);
void sendUartByte(uint8_t data);
void writeUartBuffer(const void* Buffer, uint16_t ByteCount);
