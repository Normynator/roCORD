#include "../src/discord_filter.hpp"
#include "core_mock.hpp"
#include "gmock/gmock-matchers.h"
#include "gmock/gmock-more-matchers.h"
#include "gmock/gmock.h"
#include "gtest/gtest-spi.h"
#include "gtest/gtest.h"

namespace testing {
namespace gmock_matchers_test {

class filter_test : public ::testing::Test
{
protected:
  // You can remove any or all of the following functions if its body
  // is empty.
  filter_test()
  {
    // You can do set-up work for each test here.

    members = std::vector<std::unique_ptr<rocord::member>>();

    std::vector<uint64_t> empty = std::vector<uint64_t>();

    members.push_back(std::unique_ptr<rocord::member>(new rocord::member(
      std::move(std::unique_ptr<rocord::user>(
        new rocord::user(1234, "BadName", "1337", "", false))),
      "GoodName", empty)));

    members.push_back(std::unique_ptr<rocord::member>(new rocord::member(
      std::move(std::unique_ptr<rocord::user>(
        new rocord::user(1234, "GoodName", "1337", "", false))),
      "GoodName", empty)));

    members.push_back(std::unique_ptr<rocord::member>(new rocord::member(
      std::move(std::unique_ptr<rocord::user>(
        new rocord::user(1234, "GoodName", "1337", "", false))),
      "BadName", empty)));
    members.push_back(std::unique_ptr<rocord::member>(new rocord::member(
      std::move(std::unique_ptr<rocord::user>(
        new rocord::user(1234, "BadName", "1337", "", false))),
      "BadName", empty)));
    members.push_back(std::unique_ptr<rocord::member>(new rocord::member(
      std::move(std::unique_ptr<rocord::user>(
        new rocord::user(1234, "GoodName", "1337", "", false))),
      "", empty)));
    members.push_back(std::unique_ptr<rocord::member>(new rocord::member(
      std::move(std::unique_ptr<rocord::user>(
        new rocord::user(1234, "BadName", "1337", "", false))),
      "", empty)));

    // members = {  good_nick_bad_user,
    //              good_nick_good_user,
    //              bad_nick_good_user,
    //              bad_nick_bad_user,
    //              no_nick_good_user,
    //              no_nick_bad_user
    //           }
    EXPECT_EQ(members.size(), 6);

    /*
        expect_nick = std::vector<std::string>();
    for (auto it = members.begin(); it != members.end(); ++it)
      expect_nick.push_back((*it)->get_nick());

    EXPECT_EQ(members.size(), expect_nick.size());
        */

    rocord::username_sensibility name_s = rocord::username_sensibility::nothing;
    rocord::word_sensibility word_s = rocord::word_sensibility::nothing;
    rocord::nickname_sensibility nick_s = rocord::nickname_sensibility::nothing;

    // std::shared_ptr<rocord::log> logger(new rocord::log());
    auto mapping =
      std::make_shared<std::vector<std::pair<std::string, std::string>>>();
    // dcore = std::unique_ptr<rocord::core>(new rocord::core("Testing Filter",
    //      "some Token", "some presence", 0, mapping, nullptr, nullptr,
    //      logger));

    filter_ = std::unique_ptr<rocord::filter>(
      new rocord::filter(name_s, nick_s, word_s, mcore));
  }

  virtual ~filter_test()
  {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp()
  {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown()
  {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  void check_name_run()
  {
    // Preparing expected calls.
    MockFunction<void(int check_point_name)> check;
    {
      InSequence s;
      for (unsigned int i = 0; i < members.size(); ++i) {
        EXPECT_CALL(mcore, ban_member(*members[i], "Reason: bad nickname", 7))
          .Times(ban_nickname[i]);
        EXPECT_CALL(mcore, ban_member(*members[i], "Reason: bad username", 7))
          .Times(ban_username[i]);
        if (force_nick[i] == "no_nick")
          EXPECT_CALL(mcore, change_nick(*members[i], _)).Times(0);
        else
          EXPECT_CALL(mcore, change_nick(*members[i], force_nick[i])).Times(1);
        EXPECT_CALL(mcore, change_nick(*members[i], "")).Times(delete_nick[i]);
        EXPECT_CALL(check, Call(i));
      }
    }

    // Run all tests in sequence
    for (unsigned int i = 0; i < members.size(); ++i) {
      std::string nick = members[i]->get_nick();
      std::cout << "Testing: Nickname=" << ((nick == "") ? "no_nick" : nick)
                << " Username=" << members[i]->get_username() << std::endl;
      filter_->check_name(*members[i]);
      check.Call(i);
    }
  }

  // Objects declared here can be used by all tests in the test case for
  // Filter Test.
  std::vector<int> ban_nickname = { 0, 0, 0, 0, 0, 0 };
  std::vector<int> ban_username = { 0, 0, 0, 0, 0, 0 };
  std::vector<int> delete_nick = { 0, 0, 0, 0, 0, 0 };
  std::vector<std::string> force_nick = { "no_nick", "no_nick", "no_nick",
                                          "no_nick", "no_nick", "no_nick" };

  std::unique_ptr<rocord::filter> filter_;
  // std::unique_ptr<rocord::core> dcore;
  rocord::core_mock mcore;
  std::vector<std::unique_ptr<rocord::member>> members;

  // std::vector<rocord::member> list;
};

TEST_F(filter_test, constructor)
{
  EXPECT_TRUE(filter_ != nullptr);
}

/* check_name tests
 *
 * Nickname   Username      Result
 * ban        ban           Bad user/nickname -> ban
 * ban        force_nick    If bad nick -> ban, if bad user -> enforce nickname
 * ban        nothing       If bad nick -> ban
 * remove     ban           If bad nick -> remove, if bad user -> ban
 * remove     force_nick    If bad nick/user -> remove and set new generic
 * Nickname else if only bad nick -> remove nick
 * remove     nothing       If bad nick -> remove
 * rename     ban           If bad nick -> rename, if bad user -> ban
 * rename     force_nick    If bad nick -> rename, if bad user -> enforce nick
 * rename     nothing       If bad nick -> rename
 * nothing    ban           If bad user -> ban
 * nothing    force_nick    If bad user -> force_nick
 * nothing    nothing       nothing
 */

// TODO check if EXPECT_EQ(string1, string2) tests content not object.

TEST_F(filter_test, check_name_ban_ban)
{
  // set the appropriate mode for the test
  // ban        ban           Bad user/nickname -> ban
  filter_->chmod_nickname(rocord::nickname_sensibility::ban);
  filter_->chmod_username(rocord::username_sensibility::ban);

  ban_nickname[2] = 1;
  ban_nickname[3] = 1;

  ban_username[0] = 1;
  ban_username[3] = 1;
  ban_username[5] = 1;

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_ban_force_nick)
{
  // set the appropriate mode for the test
  // ban        force_nick    If bad nick -> ban, if bad user -> enforce
  // nickname
  filter_->chmod_nickname(rocord::nickname_sensibility::ban);
  filter_->chmod_username(rocord::username_sensibility::force_nick);

  ban_nickname[2] = 1;
  ban_nickname[3] = 1;

  force_nick[5] = "Generic Nick";

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_ban_nothing)
{
  // set the appropriate mode for the test
  // ban        nothing       If bad nick -> ban
  filter_->chmod_nickname(rocord::nickname_sensibility::ban);
  filter_->chmod_username(rocord::username_sensibility::nothing);

  ban_nickname[2] = 1;
  ban_nickname[3] = 1;

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_remove_ban)
{
  // set the appropriate mode for the test
  // remove     ban           If bad nick -> remove, if bad user -> ban
  filter_->chmod_nickname(rocord::nickname_sensibility::remove);
  filter_->chmod_username(rocord::username_sensibility::ban);

  ban_username[0] = 1;
  ban_username[3] = 1;
  ban_username[5] = 1;

  delete_nick[2] = 1;
  delete_nick[3] = 1;

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_remove_force_nick)
{
  // set the appropriate mode for the test
  // remove     force_nick    If bad nick/user -> remove and set new generic
  // Nickname else if only bad nick -> remove nick
  filter_->chmod_nickname(rocord::nickname_sensibility::remove);
  filter_->chmod_username(rocord::username_sensibility::force_nick);

  force_nick[3] = "Generic Nick";
  force_nick[5] = "Generic Nick";

  delete_nick[2] = 1;

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_remove_nothing)
{
  // set the appropriate mode for the test
  // remove     nothing       If bad nick -> remove
  filter_->chmod_nickname(rocord::nickname_sensibility::remove);
  filter_->chmod_username(rocord::username_sensibility::nothing);

  delete_nick[2] = 1;
  delete_nick[3] = 1;

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_rename_ban)
{
  // set the appropriate mode for the test
  // rename     ban           If bad nick -> rename, if bad user -> ban
  filter_->chmod_nickname(rocord::nickname_sensibility::rename);
  filter_->chmod_username(rocord::username_sensibility::ban);

  ban_username[0] = 1;
  ban_username[3] = 1;
  ban_username[5] = 1;

  force_nick[2] = "Renamed Nick";
  force_nick[3] = "Renamed Nick";

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_rename_force_nick)
{
  // set the appropriate mode for the test
  // rename     force_nick    If bad nick -> rename, if bad user -> enforce nick
  filter_->chmod_nickname(rocord::nickname_sensibility::rename);
  filter_->chmod_username(rocord::username_sensibility::force_nick);

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_nothing_nothing)
{
  filter_->chmod_nickname(rocord::nickname_sensibility::nothing);
  filter_->chmod_username(rocord::username_sensibility::nothing);

  filter_test::check_name_run();
}

TEST_F(filter_test, check_name_4)
{
}
/*TEST_F(filter_test, check_word_ban)
{
  // mock call core::ban
}

TEST_F(filter_test, check_word_censor)
{

}

TEST_F(filter_test, check_word_remove)
{
  // mock call core::delete_message
}

TEST_F(filter_test, check_word_nothing)
{

}*/
}
}
