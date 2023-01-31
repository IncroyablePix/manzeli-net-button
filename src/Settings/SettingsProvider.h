#ifndef CREDENTIALSPROVIDER_INCLUDED
#define CREDENTIALSPROVIDER_INCLUDED

#include <Preferences.h>
#include "DataProviders/IDataProvider.h"
#include "Utils.h"
#include "Command.h"

#define APP_KEY                 ("MY_APPLICATION")
#define SSID_KEY                ("SSID_KEY")
#define PASSWD_KEY              ("PASSWORD_KEY")
#define HOSTNAME_KEY            ("HOSTNAME_KEY")
#define URL_KEY                 ("URL_KEY")
#define METHOD_KEY              ("METHOD_KEY")
#define AUTH_KEY                ("AUTH_KEY")
#define MESSAGE_KEY             ("MESSAGE_KEY")

class SettingsProvider
{
    public:
        SettingsProvider(Preferences& store, IDataProvider& provider);
        void Begin();
        int Update();
        void ShowHelp() const;
        void AskWiFiCredentials();
        void AskHttpSettings();
        void AskMessage();
        void Save();

        inline std::string& GetHostname() { return m_hostname; }
        inline std::string& GetSsid() { return m_ssid; }
        inline std::string& GetPassword() { return m_password; }
        inline std::string& GetURL() { return m_url; }
        inline std::string& GetMethod() { return m_method; }
        inline std::string& GetAuth() { return m_auth; }
        inline std::string& GetMessage() { return m_message; }

    private:
        std::string m_ssid;
        std::string m_password;
        std::string m_hostname;

        std::string m_url;
        std::string m_method;
        std::string m_auth;

        std::string m_message;
        
        Preferences& m_store;
        IDataProvider& m_provider;

    void DeleteSettings();
};

#endif
