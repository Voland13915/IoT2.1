#include "PwmLed.h"
#include <Arduino.h>

PwmLed::PwmLed(uint8_t pin) : pin(pin), brightnessPercent(0) {}

void PwmLed::init()
{
    pinMode(pin, OUTPUT);
    setBrightnessPercent(0);
}

void PwmLed::setBrightnessPercent(uint8_t percent)
{
    brightnessPercent = (percent > PERCENT_MAX) ? PERCENT_MAX : percent;
    const uint16_t duty = static_cast<uint16_t>(brightnessPercent) * PWM_MAX_VALUE / PERCENT_MAX;
    analogWrite(pin, static_cast<int>(duty));
}

uint8_t PwmLed::getBrightnessPercent() const
{
    return brightnessPercent;
}
