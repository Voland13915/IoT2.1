#include "Tasks.h"
#include "AppConfig.h"
#include "Signals.h"
#include "Led.h"
#include "Button.h"
#include "PwmLed.h"
#include "AnalogSensor.h"

namespace
{
Led led1(LED1_PIN);
Led led2(LED2_PIN);
Button toggleButton(TOGGLE_BUTTON_PIN, BUTTON_DEBOUNCE_SAMPLES);
Button incrementButton(INCREMENT_BUTTON_PIN, BUTTON_DEBOUNCE_SAMPLES);
Button decrementButton(DECREMENT_BUTTON_PIN, BUTTON_DEBOUNCE_SAMPLES);
PwmLed led3(LED3_PIN);
AnalogSensor potentiometer(POTENTIOMETER_PIN, POTENTIOMETER_FILTER_SHIFT, ADC_MAX_VALUE);
} // namespace

void tasksInit()
{
    led1.init();
    led2.init();
    toggleButton.init();
    incrementButton.init();
    decrementButton.init();
    led3.init();
    potentiometer.init();
}

// Task 1 — provider: led1State, toggleButtonEvent
void taskButtonLed()
{
    if (toggleButton.update())
    {
        led1.toggle();
        led1State = led1.isOn();
        toggleButtonEvent = true;
    }
}

// Task 2 — consumer: led1State, blinkRecurrences; provider: led2State
void taskBlinkLed()
{
    static uint8_t recurrenceCounter = 0;

    if (led1State)
    {
        led2.off();            // LED2 активен только при выключенном LED1
        recurrenceCounter = 0;
    }
    else
    {
        recurrenceCounter++;
        if (recurrenceCounter >= blinkRecurrences)
        {
            led2.toggle();
            recurrenceCounter = 0;
        }
    }
    led2State = led2.isOn();
}

// Task 3 — provider: blinkRecurrences, increment/decrement events
void taskBlinkControl()
{
    if (incrementButton.update())
    {
        if (blinkRecurrences + BLINK_RECURRENCES_STEP <= BLINK_RECURRENCES_MAX)
        {
            blinkRecurrences += BLINK_RECURRENCES_STEP;
        }
        incrementButtonEvent = true;
    }

    if (decrementButton.update())
    {
        if (blinkRecurrences >= BLINK_RECURRENCES_MIN + BLINK_RECURRENCES_STEP)
        {
            blinkRecurrences -= BLINK_RECURRENCES_STEP;
        }
        decrementButtonEvent = true;
    }
}

// Task 4 (доп.) — провайдер: levelPercent, levelChangedEvent.
// Яркость LED3 следует за потенциометром на каждом запуске; сигнал для Idle
// обновляется только при изменении больше порога, чтобы шум АЦП не засорял вывод.
void taskLevelIndicator()
{
    const uint8_t percent = potentiometer.readPercent();
    led3.setBrightnessPercent(percent);

    const uint8_t published = levelPercent;
    const uint8_t difference = (percent > published) ? (percent - published) : (published - percent);
    if (difference >= LEVEL_CHANGE_THRESHOLD_PERCENT)
    {
        levelPercent = percent;
        levelChangedEvent = true;
    }
}
