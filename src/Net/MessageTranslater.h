#ifndef MESSAGETRANSLATER_INCLUDED
#define MESSAGETRANSLATER_INCLUDED

#include "ArduinoJson.h"
#include <sstream>
#include <string>
#include <vector>

class MessageTranslater
{
    public:
        std::string FormatMessage(const std::string& message, const std::string& formatter);

    private:
        void Translate(const char* chars, int& i, std::stringstream& ss, DynamicJsonDocument& doc);
        std::vector<std::string> Split(const std::string& input, const std::string& delimiter);
        std::string GetValueFromKey(JsonVariant &document, std::string &keys);

    int ToInt(const std::string &str);
};

#endif
