#include <algorithm>
#include "SerialDataProvider.h"

Command SerialDataProvider::ReadCommand()
{
    if(Serial.available() > 0)
    {
        String message = Serial.readString();
        message.trim();

        if(message == "NONE" || message.length() == 0)
        {
            return NONE;
        }
        else if(message == "HELP")
        {
            return HELP;
        }
        else if(message == "HELO")
        {
            return HELO;
        }
        else if(message == "CONF")
        {
            return CONF;
        }
        else if(message == "WIFI")
        {
            return WIFI;
        }
        else if(message == "REST")
        {
            return REST;
        }
        else if(message == "GLBL")
        {
            return GLBL;
        }
        else if(message == "SHOW")
        {
            return SHOW;
        }
        else if(message == "CLRS")
        {
            return CLRS;
        }
        else if(message == "EXIT")
        {
            return EXIT;
        }
    }

    return NONE;
}

void SerialDataProvider::GetHostname(std::string& hostname)
{
    GetString("Please enter a hostname: ", hostname);
    Serial.println();
}

void SerialDataProvider::GetWiFiCredentials(std::string& ssid, std::string& password)
{
    GetString("Please enter SSID: ", ssid);
    GetString("\nEnter WiFi password: ", password);
    Serial.println();
}

void SerialDataProvider::GetEndpoint(std::string& url, std::string& method, std::string& auth)
{
    GetString("Please enter the endpoint: ", url);
    while(true)
    {
        GetString("\nEnter HTTP method: ", method);
        if(IsValid(method))
            break;
        else
            Serial.println("Invalid method. Please try again: ");
    }
    GetString("\nEnter auth scheme and token: ", auth);
    Serial.println();
}

void SerialDataProvider::GetMessageInput(std::string& messageInput)
{
    GetString("Enter message: ", messageInput);
    Serial.println();
}

void SerialDataProvider::GetString(const std::string& message, std::string& userInput)
{
    Serial.print(message.c_str());
    while(true)
    {
        if(Serial.available() > 0)
        {
            auto input = Serial.readString();
            input.trim();
            userInput = ToStdString(input);
            break;
        }
    }
}

void SerialDataProvider::Helo()
{
    Serial.println("HELO");
}

bool SerialDataProvider::IsValid(std::string &method)
{
    std::transform(method.begin(), method.end(), method.begin(), ::toupper);
    return method == "GET" || method == "POST" || method == "PUT" || method == "PATCH";
}
