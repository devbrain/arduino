//
// Created by igor on 5/21/19.
//
#include <string>
#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/emplace_string]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)
#define ASSERT_STR_EQ(X, Y) do { auto s1 = std::string(X); auto s2 = std::string(Y); REQUIRE(s1 == s2); } while (false)

TEST (emplace_string)
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);

  char destination[32];

  if(!emplace(&dummy, destination, 32))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(strlen(destination), strlen(buf),"%d");
  ASSERT_STR_EQ(destination, buf);


}

TEST (emplace_string_exact_fit)
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);

  char destination[14];

  if(!emplace(&dummy, destination, 14))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(strlen(destination), strlen(buf),"%d");
  ASSERT_STR_EQ(destination, buf);


}

TEST (emplace_string_truncated)
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);

  char destination[10];

  if(!emplace(&dummy, destination, 10))
  {
    FAIL();
  }

  char expected[] = "Hello, Wo";

  ASSERT_EQ_FMT(strlen(destination), strlen(expected),"%d");
  ASSERT_STR_EQ(destination, expected);


}
