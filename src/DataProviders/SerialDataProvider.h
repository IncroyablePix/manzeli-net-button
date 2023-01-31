#ifndef SERIALDATAPROVIDER_INCLUDED
#define SERIALDATAPROVIDER_INCLUDED

#include "DataProviders/IDataProvider.h"
#include <HardwareSerial.h>
#include "Utils.h"
#include "Settings/Command.h"

class SerialDataProvider : public IDataProvider
{
    public:
        SerialDataProvider(const SerialDataProvider& provider) = default;
        SerialDataProvider() = default;
        ~SerialDataProvider() override = default;
        Command ReadCommand() override;
        void GetHostname(std::string& hostname) override;
        void GetWiFiCredentials(std::string& ssid, std::string& password) override;
        void GetEndpoint(std::string& url, std::string& method, std::string& auth) override;
        void GetMessageInput(std::string& messageInput) override;
        void Helo() override;

    private:
        void GetString(const std::string& message, std::string& userInput) ;

    static bool IsValid(std::string &method);
};

#endif
