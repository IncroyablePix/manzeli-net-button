#include "ConfigWave.h"

bool ConfigWave::GetSignal(double time) const
{
    return time >= 50;
}
