#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <string>

void reboot();
std::string ToStdString(const String& str);
String ToArduinoString(const std::string& str);

#endif
