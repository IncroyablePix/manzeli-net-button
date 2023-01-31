#ifndef HTTPGETTER_INCLUDED
#define HTTPGETTER_INCLUDED

#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "HttpResponse.h"
#include "Utils.h"
#include <string>

class HttpQuerier : std::enable_shared_from_this<HttpQuerier>
{
    public:
        HttpQuerier(WiFiClientSecure& client, std::string url, bool https = true);
        HttpResponse Execute();
        void SetEndpoint(std::string url);
        void SetMethod(std::string method);
        void SetAuth(std::string auth);
        
    private:  
        std::string m_url;
        std::string m_auth;
        std::string m_method;
        
        WiFiClientSecure& m_client;
        bool m_secure;
};

#endif
