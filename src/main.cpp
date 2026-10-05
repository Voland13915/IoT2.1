#include <Arduino.h>
#include <stdio.h>
#include "AppConfig.h"
#include "Scheduler.h"
#include "SerialStdio.h"
#include "Signals.h"
#include "Tasks.h"

namespace
{
// Порядок в таблице = порядок обхода в тике
SchedulerTask taskTable[] = {
    {taskButtonLed, msToTicks(TASK_BUTTON_LED_RECURRENCE_MS), msToTicks(TASK_BUTTON_LED_OFFSET_MS), 0},
    {taskBlinkControl, msToTicks(TASK_BLINK_CONTROL_RECURRENCE_MS), msToTicks(TASK_BLINK_CONTROL_OFFSET_MS), 0},
    {taskBlinkLed, msToTicks(TASK_BLINK_LED_RECURRENCE_MS), msToTicks(TASK_BLINK_LED_OFFSET_MS), 0},
    {taskLevelIndicator, msToTicks(TASK_LEVEL_INDICATOR_RECURRENCE_MS), msToTicks(TASK_LEVEL_INDICATOR_OFFSET_MS), 0},
};
constexpr uint8_t TASK_COUNT = sizeof(taskTable) / sizeof(taskTable[0]);

const char* onOffText(bool state)
{
    return state ? "ON" : "OFF";
}
} // namespace

void setup()
{
    serialStdioInit(SERIAL_BAUD_RATE);
    tasksInit();
    printf("Lab 2.1: sequential OS started\n");
    schedulerInit(taskTable, TASK_COUNT);
}

// Idle — consumer: читает сигналы и сбрасывает флаги событий.
// printf и delay выполняются только здесь, вне прерывания.
void loop()
{
    noInterrupts(); // атомарно: копия сигналов + сброс флагов
    const bool led1 = led1State;
    const bool led2 = led2State;
    const uint8_t recurrences = blinkRecurrences;
    const uint8_t level = levelPercent;
    const bool toggleEvent = toggleButtonEvent;
    const bool incrementEvent = incrementButtonEvent;
    const bool decrementEvent = decrementButtonEvent;
    const bool levelEvent = levelChangedEvent;
    toggleButtonEvent = false;
    incrementButtonEvent = false;
    decrementButtonEvent = false;
    levelChangedEvent = false;
    interrupts();

    const unsigned int stateDurationMs = recurrences * TASK_BLINK_LED_RECURRENCE_MS;

    if (toggleEvent)
    {
        printf("[BTN1] LED1 -> %s\n", onOffText(led1));
    }
    if (incrementEvent)
    {
        printf("[BTN+] recurrences = %u (%u ms)\n", recurrences, stateDurationMs);
    }
    if (decrementEvent)
    {
        printf("[BTN-] recurrences = %u (%u ms)\n", recurrences, stateDurationMs);
    }

    if (levelEvent)
    {
        printf("[POT] LED3 brightness = %u %%\n", level);
    }

    printf("LED1: %-3s | LED2: %-3s | LED2 state time: %u x %u ms = %u ms | LED3: %u %%\n",
           onOffText(led1), onOffText(led2), recurrences,
           TASK_BLINK_LED_RECURRENCE_MS, stateDurationMs, level);

    delay(IDLE_REPORT_PERIOD_MS);
}
