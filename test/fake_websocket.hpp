#ifndef fake_websocket_hpp
#define fake_websocket_hpp

#include "../src/discord_websocket.hpp"

class fake_websocket : public rocord::websocket
{

public:
  fake_websocket(std::string token, std::string uri,
                 std::shared_ptr<rocord::log> logger)
    : rocord::websocket(token, uri, logger)
  {
  }
};

#endif /*fake_websocket_hpp*/
