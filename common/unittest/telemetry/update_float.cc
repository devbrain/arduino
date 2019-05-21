//
// Created by igor on 5/21/19.
//

#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/update_float]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)

TEST (update_float32)
{
    TM_msg dummy;
    char topic[128] = "float32";
    float buf = -64;
    dummy.type = TM_float32;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    float destination;

    if(!update_f32(&dummy, "float32",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");
}

TEST (update_float32_neg)
{
    TM_msg dummy;
    char topic[128] = "float32_neg";
    float buf = -64;
    dummy.type = TM_float32;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    float destination;

    if(!update_f32(&dummy, "float32_neg",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");
}


TEST (update_float32_decimals)
{
    TM_msg dummy;
    char topic[128] = "float32_decimals";
    float buf = -64.1235;
    dummy.type = TM_float32;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    float destination;

    if(!update_f32(&dummy, "float32_decimals",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");
}
