//
// Created by igor on 5/21/19.
//

#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/emplace_float]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)

TEST (emplace_float32)
{
  TM_msg dummy;
  float buf = 64;
  dummy.type = TM_float32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  float destination;

  if(!emplace_f32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%f");


}

TEST (emplace_float32_neg)
{
  TM_msg dummy;
  float buf = -64;
  dummy.type = TM_float32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  float destination;

  if(!emplace_f32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%f");


}

TEST (emplace_float32_decimals)
{
  TM_msg dummy;
  float buf = 64.123456;
  dummy.type = TM_float32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  float destination;

  if(!emplace_f32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%f");


}

TEST (emplace_float32_decimals_neg)
{
  TM_msg dummy;
  float buf = -64.123456;
  dummy.type = TM_float32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  float destination;

  if(!emplace_f32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%f");


}
