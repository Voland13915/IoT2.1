#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

// Драйвер кнопки: подключение к GND, внутренний подтягивающий резистор
// (нажата = LOW). Антидребезг по числу одинаковых опросов подряд,
// поэтому update() нужно вызывать с постоянным периодом.
class Button
{
public:
    Button(uint8_t pin, uint8_t debounceSamples);

    void init();
    bool update();          // true — только в момент нажатия (фронт)
    bool isPressed() const; // устойчивое (отфильтрованное) состояние

private:
    uint8_t pin;
    uint8_t debounceSamples;
    uint8_t sameSampleCount;
    bool lastRawPressed;
    bool stablePressed;
};

#endif
