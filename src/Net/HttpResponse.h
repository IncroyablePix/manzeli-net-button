#ifndef HTTPRESPONSE_INCLUDED
#define HTTPRESPONSE_INCLUDED

#include <string>

struct HttpResponse
{
    std::string Content;
    uint32_t ResponseCode;

    inline bool Success() const { return 299 >= ResponseCode && ResponseCode >= 200; }
    inline void SetContent(std::string content) { Content = std::move(content); }
};

#endif
