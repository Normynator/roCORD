#ifndef fake_http_hpp
#define fake_http_hpp

#include "../src/discord_http.hpp"

class fake_http : public rocord::http
{

public:
  fake_http(std::string token, std::shared_ptr<rocord::log> logger)
    : rocord::http(token, logger)
  {
  }
};

#endif /* fake_http_hpp */
