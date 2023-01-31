#ifndef LEDSENSOR_INCLUDED
#define LEDSENSOR_INCLUDED

#include "IToggleSensor.h"

class LedSensor : public IToggleSensor
{
    public:
        LedSensor(int pin);
        void Enable(bool ena) override;
        void Toggle() override;
        void Update() override;

    private:
        int m_pin;
        bool m_on;
        bool m_enabled;
};

#endif
