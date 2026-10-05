#ifndef SERIAL_STDIO_H
#define SERIAL_STDIO_H

// Перенаправление stdout (printf) в последовательный порт
void serialStdioInit(unsigned long baudRate);

#endif
