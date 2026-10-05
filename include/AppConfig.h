#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <Arduino.h>
#include <stdint.h>
#include "Scheduler.h"

// ---------- Пины ----------
constexpr uint8_t LED1_PIN = 12;              // LED задачи 1 (красный)
constexpr uint8_t LED2_PIN = 11;              // мигающий LED задачи 2 (зелёный)
constexpr uint8_t TOGGLE_BUTTON_PIN = 2;      // кнопка задачи 1
constexpr uint8_t INCREMENT_BUTTON_PIN = 3;   // кнопка "+" задачи 3
constexpr uint8_t DECREMENT_BUTTON_PIN = 4;   // кнопка "-" задачи 3
constexpr uint8_t LED3_PIN = 6;               // LED-индикатор уровня задачи 4 (ШИМ, Timer0)
constexpr uint8_t POTENTIOMETER_PIN = A0;     // потенциометр задачи 4

// ---------- Последовательный порт ----------
constexpr unsigned long SERIAL_BAUD_RATE = 9600;

// ---------- Кнопки ----------
// Сколько подряд одинаковых опросов считать устойчивым состоянием
constexpr uint8_t BUTTON_DEBOUNCE_SAMPLES = 2;

// ---------- Планирование задач (мс) ----------
// Периоды кратны 20 мс, смещения различны по модулю 20 мс,
// поэтому задачи никогда не активируются в одном и том же тике.
// Порядок внутри 20 мс: Task1 (1) -> Task3 (6) -> Task2 (11) -> Task4 (16)
constexpr uint16_t TASK_BUTTON_LED_RECURRENCE_MS = 20;
constexpr uint16_t TASK_BUTTON_LED_OFFSET_MS = 1;

constexpr uint16_t TASK_BLINK_CONTROL_RECURRENCE_MS = 20;
constexpr uint16_t TASK_BLINK_CONTROL_OFFSET_MS = 6;

constexpr uint16_t TASK_BLINK_LED_RECURRENCE_MS = 100;
constexpr uint16_t TASK_BLINK_LED_OFFSET_MS = 11;

constexpr uint16_t TASK_LEVEL_INDICATOR_RECURRENCE_MS = 40;
constexpr uint16_t TASK_LEVEL_INDICATOR_OFFSET_MS = 16;

// ---------- Мигание LED2 ----------
// Длительность одного состояния LED2 = blinkRecurrences * TASK_BLINK_LED_RECURRENCE_MS
constexpr uint8_t BLINK_RECURRENCES_MIN = 1;       // 100 мс
constexpr uint8_t BLINK_RECURRENCES_MAX = 20;      // 2000 мс
constexpr uint8_t BLINK_RECURRENCES_DEFAULT = 5;   // 500 мс
constexpr uint8_t BLINK_RECURRENCES_STEP = 1;

// ---------- Индикатор уровня (Task 4) ----------
constexpr uint8_t POTENTIOMETER_FILTER_SHIFT = 2;      // сглаживание 1/4
constexpr uint16_t ADC_MAX_VALUE = 1023;               // АЦП Uno — 10 бит
constexpr uint8_t LEVEL_CHANGE_THRESHOLD_PERCENT = 2;  // гистерезис сообщений

// ---------- Idle (отчётность) ----------
constexpr unsigned long IDLE_REPORT_PERIOD_MS = 500;

// Перевод миллисекунд в тики планировщика
constexpr uint16_t msToTicks(uint16_t milliseconds)
{
    return static_cast<uint16_t>(
        static_cast<uint32_t>(milliseconds) * SCHEDULER_TICK_HZ / MILLISECONDS_PER_SECOND);
}

#endif
