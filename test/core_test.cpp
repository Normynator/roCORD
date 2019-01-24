#include "../src/discord_core.hpp"
#include "fake_http.hpp"
#include "fake_websocket.hpp"
#include "gmock/gmock-matchers.h"
#include "gmock/gmock-more-matchers.h"
#include "gmock/gmock.h"
#include "gtest/gtest-spi.h"
#include "gtest/gtest.h"
#include <chrono>
#include <limits.h>
#include <stdio.h>
#include <thread>

namespace testing {
namespace gmock_matchers_test {

class CoreTest : public ::testing::Test
{
protected:
  // You can remove any or all of the following functions if its body
  // is empty.
  CoreTest()
  {
    // You can do set-up work for each test here.
  }

  virtual ~CoreTest()
  {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp()
  {
    // Code here will be called immediately after the constructor (right
    // before each test).
    /*std::string temp_token =
    "NDY4NTM2MTUyNjE4Njk2NzA4.DpWT3w.p0CGUK72FSvt0qcKr8XwtsmCdNE";
    auto channel_mapping =
        std::make_shared<std::vector<std::pair<std::string, std::string>>>();
    channel_mapping->push_back(
        std::make_pair<std::string, std::string>("Name", "ID"));

    std::unique_ptr<rocord::websocket> dwss(new fake_websocket(
       temp_token , "wss://gateway.discord.gg/?v=6&encoding=json"));
    std::unique_ptr<rocord::http> dhttps(new fake_http(temp_token));

    dcore = std::unique_ptr<rocord::core>(
        new rocord::core("Test Name", temp_token, "Test Presence", 0,
                         channel_mapping, std::move(dwss),
    std::move(dhttps)));*/
  }

  virtual void TearDown()
  {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for
  // CoreTest.
  //  std::unique_ptr<rocord::core> dcore;
};

/*TEST(CoreTest, True){
        EXPECT_TRUE(true);
}*/

TEST_F(CoreTest, Constructor)
{
  // std::unique_ptr<discord_core> dcore = CoreTest::create_core();
  std::string temp_token =
    "NDY4NTM2MTUyNjE4Njk2NzA4.DpWT3w.p0CGUK72FSvt0qcKr8XwtsmCdNE";
  auto channel_mapping =
    std::make_shared<std::vector<std::pair<std::string, std::string>>>();
  channel_mapping->push_back(
    std::make_pair<std::string, std::string>("Name", "ID"));

  std::shared_ptr<rocord::log> logger(new rocord::log());

  std::unique_ptr<rocord::websocket> dwss(new fake_websocket(
    temp_token, "wss://gateway.discord.gg/?v=6&encoding=json", logger));
  std::unique_ptr<rocord::http> dhttps(new fake_http(temp_token, logger));

  auto dcore = std::unique_ptr<rocord::core>(new rocord::core(
    "Test Name", temp_token, "Test Presence", 0, channel_mapping,
    std::move(dwss), std::move(dhttps), logger));

  EXPECT_TRUE(dcore != nullptr);
}

/*TEST(CoreTestAdv, reconnect)
{
  // run();
}*/

/*TEST(CoreTest, channelName) {

}

TEST(CoreTest, toDiscordSimple) {
        // Send a simple message
}

TEST(CoreTest, toDiscordSpecialMessage) {
        // Send a message with "äöü"
}

TEST(CoreTest, toDiscordSpecialName) {
        // Send a message with name containing "äüö"
}

TEST(CoreTest, handleMessageEventSimple) {

}

TEST(CoreTest, handleMessageEventSpecialMessage) {
        // Message contains "äöü"
}*/
}
}
