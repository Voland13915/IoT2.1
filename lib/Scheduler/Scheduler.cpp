#include "Scheduler.h"
#include <Arduino.h>

namespace
{
constexpr uint32_t TIMER1_PRESCALER = 64;
constexpr uint32_t TIMER1_COMPARE_VALUE = F_CPU / (TIMER1_PRESCALER * SCHEDULER_TICK_HZ) - 1;
static_assert(TIMER1_COMPARE_VALUE <= UINT16_MAX, "Timer1 compare value must fit in 16 bits");

SchedulerTask* taskTable = nullptr;
uint8_t taskTableSize = 0;

void timer1Init()
{
    noInterrupts();
    TCCR1A = 0;
    TCCR1B = (1 << WGM12)                 // режим CTC: сброс по совпадению с OCR1A
           | (1 << CS11) | (1 << CS10);   // делитель 64
    TCNT1 = 0;
    OCR1A = static_cast<uint16_t>(TIMER1_COMPARE_VALUE);
    TIMSK1 |= (1 << OCIE1A);              // прерывание по совпадению
    interrupts();
}
} // namespace

void schedulerInit(SchedulerTask* tasks, uint8_t taskCount)
{
    taskTable = tasks;
    taskTableSize = taskCount;

    for (uint8_t i = 0; i < taskTableSize; i++)
    {
        taskTable[i].counter = taskTable[i].offsetTicks; // смещение = первая задержка
    }

    timer1Init();
}

// Каждый тик: обход таблицы задач в порядке их объявления
ISR(TIMER1_COMPA_vect)
{
    for (uint8_t i = 0; i < taskTableSize; i++)
    {
        SchedulerTask& task = taskTable[i];
        if (task.counter == 0)
        {
            task.run();
            task.counter = task.recurrenceTicks;
        }
        task.counter--;
    }
}
