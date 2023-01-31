#include <esp32-hal.h>
#include "LedSensor.h"

LedSensor::LedSensor(int pin) :
    m_pin(pin),
    m_enabled(false),
    m_on(false)
{
    pinMode(m_pin, OUTPUT);
}

void LedSensor::Update()
{
    if(m_enabled)
    {
        digitalWrite(m_pin, HIGH);
    }
}

void LedSensor::Enable(bool ena)
{
    m_enabled = ena;
    digitalWrite(m_pin, m_enabled ? HIGH : LOW);
}

void LedSensor::Toggle()
{
    Enable(!m_enabled);
}
