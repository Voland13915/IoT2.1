#include "SerialStdio.h"
#include <Arduino.h>
#include <stdio.h>

#if defined(ARDUINO_ARCH_AVR)
// AVR: в avr-libc stdout не привязан к UART — создаём поток вручную
namespace
{
FILE serialStdout;

int serialPutChar(char character, FILE* stream)
{
    (void)stream;
    if (character == '\n')
    {
        Serial.write('\r');
    }
    Serial.write(character);
    return 0;
}
} // namespace

void serialStdioInit(unsigned long baudRate)
{
    Serial.begin(baudRate);
    fdev_setup_stream(&serialStdout, serialPutChar, nullptr, _FDEV_SETUP_WRITE);
    stdout = &serialStdout;
}
#else
// ESP32: stdout уже направлен в UART0, достаточно настроить скорость
void serialStdioInit(unsigned long baudRate)
{
    Serial.begin(baudRate);
}
#endif
