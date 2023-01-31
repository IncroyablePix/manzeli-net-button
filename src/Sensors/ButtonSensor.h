#ifndef BUTTONSENSOR_INCLUDED
#define BUTTONSENSOR_INCLUDED

#include <functional>

class Button
{
    public:
        Button(int pin);
        void CheckButton();
        void SetOnPressedListener(std::function<void(bool)> onPressed);
        bool IsPressed() const;

    private:
        uint8_t m_pin;
        int m_prevBtnState;
        std::function<void(bool)> m_onPressed;
};

#endif
