#ifndef core_mock_hpp
#define core_mock_hpp

#include "gmock/gmock.h"

namespace rocord {
class core_mock : public core_interface
{
public:
  MOCK_METHOD3(ban_member, void(member& memb, const std::string& reason,
                                int delete_message_days));
  MOCK_METHOD2(change_nick, void(member& memb, const std::string& new_nick));
  MOCK_METHOD3(to_discord, int(std::string& msg, const std::string& channel,
                               std::string* name));
  MOCK_METHOD1(set_display_name, void(const std::string& display_name));
  MOCK_METHOD0(handle_events, void());
  MOCK_METHOD0(connect, void());
  MOCK_METHOD0(info, void());
};
}

#endif /* core_mock_hpp */
