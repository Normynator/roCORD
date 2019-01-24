#include "../src/discord_bot.hpp"
#include "fake_http.hpp"
#include "fake_websocket.hpp"
#include "gmock/gmock-matchers.h"
#include "gmock/gmock-more-matchers.h"
#include "gmock/gmock.h"
#include "gtest/gtest-spi.h"
#include "gtest/gtest.h"
#include <limits.h>
#include <stdio.h>

namespace testing {
namespace gmock_matchers_test {

class Bot_test : public ::testing::Test
{
protected:
  // You can remove any or all of the following functions if its body
  // is empty.
  Bot_test()
  {
    // You can do set-up work for each test here.
  }

  virtual ~Bot_test()
  {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp()
  {
    // Code here will be called immediately after the constructor (right
    // before each test).
    discord_init();
  }

  virtual void TearDown()
  {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for
  // CoreTest.
};

/*TEST_F(Bot_test, drop_announce) {
  discord_announce_drop("My test drop message!");
  // TODO validate
}

add test for discord_send nullptr! TODO
*/
}
}
