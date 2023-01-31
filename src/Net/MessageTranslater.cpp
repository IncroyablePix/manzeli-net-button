#include "MessageTranslater.h"

std::string MessageTranslater::FormatMessage(const std::string& message, const std::string& formatter)
{
    std::stringstream ss;
    DynamicJsonDocument doc(8192);
    deserializeJson(doc, message.c_str());

    auto chars = formatter.c_str();
    auto len = strlen(chars);
    for(int i = 0; i < len; i ++)
    {
        char c = chars[i];
        if(c == '{')
            Translate(chars, i, ss, doc);
        else
            ss << c;
    }

    return ss.str();
}

void MessageTranslater::Translate(const char* chars, int& i, std::stringstream& ss, DynamicJsonDocument& doc)
{
    auto start = i;
    auto end = i;
    bool noEnd = false;

    do
    {
        ++end;

        if(chars[end] == '\0')
        {
            ss << chars[start];
            noEnd = true;
            break;
        }
    }
    while(chars[end] != '}');

    if(!noEnd)
    {
        std::string key(&chars[start + 1], &chars[end]);
        auto variant = doc.as<JsonVariant>();
        ss << GetValueFromKey(variant, key);
    }

    i = end;
}

int MessageTranslater::ToInt(const std::string& str)
{
    std::stringstream ss(str);
    int i;
    ss >> i;
    return i;
}

std::vector<std::string> MessageTranslater::Split(const std::string& input, const std::string& delimiter)
{
    std::vector<std::string> result;
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = input.find_first_of(delimiter, pos)) != std::string::npos)
    {
        std::string substring(input.substr(prev, pos - prev));
        result.push_back(substring);
        prev = ++pos;
    }

    result.push_back(input.substr(prev, pos - prev)); // Last word
    return result;
}

std::string MessageTranslater::GetValueFromKey(JsonVariant &document, std::string &keys)
{
    JsonVariant variant = document;
    size_t delimiterPos = keys.find('.');
    if (delimiterPos == std::string::npos)
    {
        variant = variant[keys];
        if (!variant.isNull()) return variant.as<std::string>();
        else return "";
    }

    std::string key = keys.substr(0, delimiterPos);
    std::string rest = keys.substr(delimiterPos + 1);

    if (variant.is<JsonObject>())
    {
        variant = variant[key];
        return GetValueFromKey(variant, rest);
    }
    else if (variant.is<JsonArray>())
    {
        JsonArray array = variant.as<JsonArray>();
        int index = atoi(key.c_str());
        if (index >= 0 && index < array.size())
        {
            variant = array[index];
            return GetValueFromKey(variant, rest);
        }
        else
        {
            return "N/A";
        }
    }
    else
    {
        return "N/A";
    }
}
