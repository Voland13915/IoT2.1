#include "AnalogSensor.h"
#include <Arduino.h>

AnalogSensor::AnalogSensor(uint8_t pin, uint8_t filterShift, uint16_t adcMaxValue)
    : pin(pin), filterShift(filterShift), adcMaxValue(adcMaxValue), filterState(0), isFilterReady(false)
{
}

void AnalogSensor::init()
{
    pinMode(pin, INPUT);
}

uint16_t AnalogSensor::readRaw()
{
    const uint32_t sample = static_cast<uint32_t>(analogRead(pin));

    if (!isFilterReady)
    {
        filterState = sample << filterShift; // первое измерение — без задержки фильтра
        isFilterReady = true;
    }
    else
    {
        filterState = filterState - (filterState >> filterShift) + sample;
    }
    return static_cast<uint16_t>(filterState >> filterShift);
}

uint8_t AnalogSensor::readPercent()
{
    const uint32_t raw = readRaw();
    const uint32_t percent = raw * PERCENT_MAX / adcMaxValue;
    return static_cast<uint8_t>((percent > PERCENT_MAX) ? PERCENT_MAX : percent);
}
