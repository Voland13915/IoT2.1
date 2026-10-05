#include "Led.h"
#include <Arduino.h>

Led::Led(uint8_t pin) : pin(pin), state(false) {}

void Led::init()
{
    pinMode(pin, OUTPUT);
    off();
}

void Led::on()
{
    state = true;
    digitalWrite(pin, HIGH);
}

void Led::off()
{
    state = false;
    digitalWrite(pin, LOW);
}

void Led::toggle()
{
    if (state)
    {
        off();
    }
    else
    {
        on();
    }
}

bool Led::isOn() const
{
    return state;
}
