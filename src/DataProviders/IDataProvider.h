#ifndef IDATAPROVIDER_INCLUDED
#define IDATAPROVIDER_INCLUDED

#include <string>
#include "Settings/Command.h"

class IDataProvider
{
    public:
        IDataProvider() = default;
        virtual void GetHostname(std::string& hostname) = 0;
        virtual void GetWiFiCredentials(std::string& ssid, std::string& password) = 0;  
        virtual void GetEndpoint(std::string& url, std::string& method, std::string& auth) = 0;
        virtual void GetMessageInput(std::string& messageInput) = 0;
        virtual void Helo() = 0;
        virtual Command ReadCommand() = 0;
        virtual ~IDataProvider() = default;
};

#endif
