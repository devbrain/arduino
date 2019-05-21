//
// Created by igor on 5/21/19.
//

#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/update_int]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)


TEST (update_int8)
{
    TM_msg dummy;
    char topic[128] = "int8";
    int8_t buf = -64;
    dummy.type = TM_int8;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    int8_t destination;

    if(!update_i8(&dummy, "int8",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");

}

TEST (update_int16)
{
    TM_msg dummy;
    char topic[128] = "int16";
    int16_t buf = -64;
    dummy.type = TM_int16;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    int16_t destination;

    if(!update_i16(&dummy, "int16",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");

}


TEST (update_int32)
{
    TM_msg dummy;
    char topic[128] = "int32";
    int32_t buf = -64;
    dummy.type = TM_int32;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    int32_t destination;

    if(!update_i32(&dummy, "int32",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");

}


TEST (update_uint8)
{
    TM_msg dummy;
    char topic[128] = "uint8";
    uint8_t buf = 64;
    dummy.type = TM_uint8;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    uint8_t destination;

    if(!update_u8(&dummy, "uint8",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");

}

TEST (update_uint16)
{
    TM_msg dummy;
    char topic[128] = "uint16";
    uint16_t buf = 64;
    dummy.type = TM_uint16;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    uint16_t destination;

    if(!update_u16(&dummy, "uint16",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");

}


TEST (update_uint32)
{
    TM_msg dummy;
    char topic[128] = "uint32";
    uint32_t buf = 64;
    dummy.type = TM_uint32;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;
    dummy.topic = topic;

    uint32_t destination;

    if(!update_u32(&dummy, "uint32",  &destination))
    {
        FAIL();
    }
    ASSERT_EQ_FMT(buf, destination,"%u");

}
