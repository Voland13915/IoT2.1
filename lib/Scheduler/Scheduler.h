#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

// Последовательный (неприоритетный) планировщик.
// Timer1 генерирует прерывание каждый тик; в обработчике для каждой задачи
// уменьшается счётчик, и при нуле задача выполняется до конца (без вытеснения).

constexpr uint32_t SCHEDULER_TICK_HZ = 1000;       // тик = 1 мс
constexpr uint32_t MILLISECONDS_PER_SECOND = 1000;

typedef void (*TaskFunction)(void);

struct SchedulerTask
{
    TaskFunction run;          // функция задачи (короткая, без delay)
    uint16_t recurrenceTicks;  // период повторения
    uint16_t offsetTicks;      // смещение первого запуска
    volatile uint16_t counter; // тиков до следующего запуска (служебное)
};

void schedulerInit(SchedulerTask* tasks, uint8_t taskCount);

#endif
