#include "SettingsProvider.h"

SettingsProvider::SettingsProvider(Preferences& store, IDataProvider& provider) : m_store(store), m_provider(provider)
{

}

void SettingsProvider::Begin()
{
    m_store.begin(APP_KEY, false);
    m_ssid = ToStdString(m_store.getString(SSID_KEY, ""));
    m_password = ToStdString(m_store.getString(PASSWD_KEY, ""));
    m_hostname = ToStdString(m_store.getString(HOSTNAME_KEY, ""));
    m_url = ToStdString(m_store.getString(URL_KEY, ""));
    m_method = ToStdString(m_store.getString(METHOD_KEY, ""));
    m_auth = ToStdString(m_store.getString(AUTH_KEY, ""));
    m_message = ToStdString(m_store.getString(MESSAGE_KEY, ""));
}

int SettingsProvider::Update()
{
    auto cmd = m_provider.ReadCommand();
    switch(cmd)
    {
        case CONF:
            AskWiFiCredentials();
            AskHttpSettings();
            AskMessage();
            Save();
            reboot();
            return 1;
        case WIFI:
            AskWiFiCredentials();
            Save();
            reboot();
            return 1;
        case REST:
            AskHttpSettings();
            Save();
            reboot();
            return 1;
        case GLBL:
            AskMessage();
            Save();
            reboot();
            return 1;
        case HELP:
            ShowHelp();
            return 1;
        case CLRS:
            DeleteSettings();
            return 1;
        case SHOW:
            m_provider.Helo();
            return 1;
        case HELO:
            return 1;
        case NONE:
            return -1;
        case EXIT:
            return 0;
    }

    return 0;
}

void SettingsProvider::ShowHelp() const
{
    Serial.println("HELP - Show this help");
    Serial.println("HELO - Echoes HELO to the serial port");
    Serial.println("CONF - Configure all settings");
    Serial.println("WIFI - Configure WiFi settings");
    Serial.println("REST - Configure HTTP settings");
    Serial.println("GLBL - Configure global settings");
    Serial.println("SHOW - Show current settings");
    Serial.println("CLRS - Delete all settings");
    Serial.println("EXIT - Exit configuration mode");
}

void SettingsProvider::AskWiFiCredentials()
{
    m_provider.GetHostname(m_hostname);
    m_provider.GetWiFiCredentials(m_ssid, m_password);
}

void SettingsProvider::AskHttpSettings()
{
    m_provider.GetEndpoint(m_url, m_method, m_auth);
}

void SettingsProvider::AskMessage()
{
    m_provider.GetMessageInput(m_message);
}

void SettingsProvider::Save()
{
    m_store.putString(HOSTNAME_KEY, ToArduinoString(m_hostname));
    m_store.putString(SSID_KEY, ToArduinoString(m_ssid));
    m_store.putString(PASSWD_KEY, ToArduinoString(m_password));
    m_store.putString(URL_KEY, ToArduinoString(m_url));
    m_store.putString(METHOD_KEY, ToArduinoString(m_method));
    m_store.putString(AUTH_KEY, ToArduinoString(m_auth));
    m_store.putString(MESSAGE_KEY, ToArduinoString(m_message));
}

void SettingsProvider::DeleteSettings()
{
    m_store.clear();
}

