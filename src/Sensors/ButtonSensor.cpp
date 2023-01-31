#include <esp32-hal.h>
#include "ButtonSensor.h"

Button::Button(int pin) :
        m_pin(pin),
        m_prevBtnState(LOW)
{
    pinMode(m_pin, INPUT_PULLUP);
}

void Button::CheckButton()
{
    auto btnState = digitalRead(m_pin);
    if(btnState == LOW && btnState != m_prevBtnState)
    {
        if(m_onPressed)
            m_onPressed(btnState);
    }

    m_prevBtnState = btnState;
}

void Button::SetOnPressedListener(std::function<void(bool)> onPressed)
{
    m_onPressed = std::move(onPressed);
}

bool Button::IsPressed() const
{
    return digitalRead(m_pin) == HIGH;
}
