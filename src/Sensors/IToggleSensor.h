#ifndef ITOGGLESENSOR_INCLUDED
#define ITOGGLESENSOR_INCLUDED

#include <memory>

class IToggleSensor : public std::enable_shared_from_this<IToggleSensor>
{
    public:
        virtual ~IToggleSensor() = default;
        virtual void Enable(bool ena) = 0;
        virtual void Toggle() = 0;
        virtual void Update() = 0;
};

#endif
