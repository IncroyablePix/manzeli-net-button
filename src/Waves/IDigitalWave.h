#ifndef MANZELI_NET_BUTTON_IDIGITALWAVE_H
#define MANZELI_NET_BUTTON_IDIGITALWAVE_H
#include <memory>

class IDigitalWave : public std::enable_shared_from_this<IDigitalWave>
{
public:
    virtual ~IDigitalWave() = default;
    virtual bool GetSignal(double time) const = 0; // Time in percents
};

#endif //MANZELI_NET_BUTTON_IDIGITALWAVE_H
