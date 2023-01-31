#include "WiFiCommunicator.h"

WiFiCommunicator::WiFiCommunicator(uint8_t connectionAttempts = 25) :
m_connectionAttempts(connectionAttempts)
        {

        }

bool WiFiCommunicator::Begin(const std::string& ssid, const std::string& password, const std::string& hostname, std::function<void()> onFailed)
{
    if(hostname.length() == 0)
    {
        return false;
    }

    WiFi.setHostname(hostname.c_str());
    return Begin(ssid, password, std::move(onFailed));
}

bool WiFiCommunicator::Begin(const std::string& ssid, const std::string& password, std::function<void()> onFailed)
{
    WiFi.mode(WIFI_STA);
    WiFi.Begin(ssid.c_str(), password.c_str());

    int attempts = 0;

    while(WiFi.status() != WL_CONNECTED)
    {
        attempts ++;

        if(onFailed)
            onFailed();

        if(attempts == m_connectionAttempts)
            return false;

        delay(500);
    }

    return true;
}

WiFiClientSecure WiFiCommunicator::GetClient() const
{
    return WiFiClientSecure();
}
