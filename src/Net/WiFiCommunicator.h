#ifndef INCLUDED_WIFICOMMUNICATOR
#define INCLUDED_WIFICOMMUNICATOR

#include <WiFiClientSecure.h>
#include <memory>

class WiFiCommunicator
{
    public:
        WiFiCommunicator(uint8_t connectionAttempts = 25);
        bool Begin(const std::string& ssid, const std::string& password, const std::string& hostname, std::function<void()> onFailed);
        bool Begin(const std::string& ssid, const std::string& password, std::function<void()> onFailed);
        WiFiClientSecure GetClient() const;
        inline IPAddress getIpAddress() const { return WiFi.localIP(); }

    private:
        uint8_t m_connectionAttempts;
};

#endif
