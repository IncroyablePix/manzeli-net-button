#ifndef MANZELI_NET_BUTTON_CONFIGWAVE_H
#define MANZELI_NET_BUTTON_CONFIGWAVE_H

#include "IDigitalWave.h"

class ConfigWave : public IDigitalWave
{
public:
    ConfigWave() = default;
    bool GetSignal(double time) const override;
};


#endif //MANZELI_NET_BUTTON_CONFIGWAVE_H
