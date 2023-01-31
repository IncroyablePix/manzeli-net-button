#include <Esp.h>
#include <Utils.h>

void reboot()
{
    ESP.restart();
}

std::string ToStdString(const String& str)
{
    return std::move(std::string(str.c_str()));
}

String ToArduinoString(const std::string& str)
{
    return std::move(String(str.c_str()));
}