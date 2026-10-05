#include "Signals.h"
#include "AppConfig.h"

volatile bool led1State = false;
volatile bool led2State = false;
volatile uint8_t blinkRecurrences = BLINK_RECURRENCES_DEFAULT;
volatile uint8_t levelPercent = 0;

volatile bool toggleButtonEvent = false;
volatile bool incrementButtonEvent = false;
volatile bool decrementButtonEvent = false;
volatile bool levelChangedEvent = false;
