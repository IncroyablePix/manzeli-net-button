#include "HttpQuerier.h"

HttpQuerier::HttpQuerier(WiFiClientSecure& client, std::string url, bool https) :
        m_url(std::move(url)),
        m_client(client),
        m_secure(https)
{

}

HttpResponse HttpQuerier::Execute()
{
    HttpResponse response;
    m_client.setInsecure();
    HTTPClient https;
    https.setTimeout(5000);

    if(!https.begin(m_client, m_url.c_str()))
    {
        response.ResponseCode = -1;
        return response;
    }

    if(m_auth.length() > 0)
    {
        https.setAuthorization(m_auth.c_str());
    }

    if(m_method == "GET")
        response.ResponseCode = https.GET();
    else if(m_method == "POST")
        response.ResponseCode = https.POST("");
    else if(m_method == "PUT")
        response.ResponseCode = https.PUT("");
    else if(m_method == "PATCH")
        response.ResponseCode = https.PATCH("");

    if(response.ResponseCode == HTTP_CODE_OK || response.ResponseCode == HTTP_CODE_MOVED_PERMANENTLY)
    {
        auto result = ToStdString(https.getString());
        https.end();
        response.SetContent(result);
        return response;
    }

    https.end();
    return response;
}

void HttpQuerier::SetEndpoint(std::string url)
{
    m_url = std::move(url);
    m_secure = (m_url.length() >= 5 && m_url[4] == 's');
}

void HttpQuerier::SetMethod(std::string method)
{
    m_method = std::move(method);
}

void HttpQuerier::SetAuth(std::string auth)
{
    m_auth = std::move(auth);
}
