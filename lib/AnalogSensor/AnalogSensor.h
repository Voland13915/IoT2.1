#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include <stdint.h>

// Аналоговый датчик (потенциометр, фоторезистор и т. п.) на входе АЦП.
// Сглаживание — экспоненциальное скользящее среднее с коэффициентом 1 / 2^filterShift.
// adcMaxValue зависит от МК: 1023 (Uno, 10 бит), 4095 (ESP32, 12 бит).
class AnalogSensor
{
public:
    AnalogSensor(uint8_t pin, uint8_t filterShift, uint16_t adcMaxValue);

    void init();
    uint16_t readRaw();     // отфильтрованное значение 0..adcMaxValue
    uint8_t readPercent();  // отфильтрованное значение 0..100 %

    static constexpr uint8_t PERCENT_MAX = 100;

private:
    uint8_t pin;
    uint8_t filterShift;
    uint16_t adcMaxValue;
    uint32_t filterState; // значение, умноженное на 2^filterShift
    bool isFilterReady;
};

#endif
