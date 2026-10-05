#ifndef PWM_LED_H
#define PWM_LED_H

#include <stdint.h>

// Светодиод с регулировкой яркости (ШИМ, analogWrite).
// Uno: только пины 3, 5, 6, 11 — ШИМ на 9 и 10 даёт Timer1, занятый планировщиком ЛР 2.1.
// ESP32: ШИМ формирует модуль LEDC, подходит любой выходной GPIO.
class PwmLed
{
public:
    explicit PwmLed(uint8_t pin);

    void init();
    void setBrightnessPercent(uint8_t percent);
    uint8_t getBrightnessPercent() const;

    static constexpr uint8_t PWM_MAX_VALUE = 255;
    static constexpr uint8_t PERCENT_MAX = 100;

private:
    uint8_t pin;
    uint8_t brightnessPercent;
};

#endif
