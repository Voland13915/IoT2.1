#ifndef SIGNALS_H
#define SIGNALS_H

#include <stdint.h>

// Глобальные сигналы для обмена между задачами (provider -> consumer).
// volatile: пишутся в прерывании таймера, читаются в main loop.

// Состояния
extern volatile bool led1State;           // provider: Task1;  consumers: Task2, Idle
extern volatile bool led2State;           // provider: Task2;  consumer: Idle
extern volatile uint8_t blinkRecurrences; // provider: Task3;  consumers: Task2, Idle
extern volatile uint8_t levelPercent;     // provider: Task4;  consumer: Idle

// События нажатий: provider ставит флаг, Idle выводит сообщение и сбрасывает
extern volatile bool toggleButtonEvent;    // provider: Task1
extern volatile bool incrementButtonEvent; // provider: Task3
extern volatile bool decrementButtonEvent; // provider: Task3
extern volatile bool levelChangedEvent;    // provider: Task4

#endif
