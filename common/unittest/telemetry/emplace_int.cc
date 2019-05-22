//
// Created by igor on 5/21/19.
//

#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/emplace_int]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)


TEST (emplace_int8)
{
    TM_msg dummy;
    int8_t buf = 64;
    dummy.type = TM_int8;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    int8_t destination;

    if(!emplace_i8(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%u");
}

TEST (emplace_int8_neg)
{
    TM_msg dummy;
    int8_t buf = -64;
    dummy.type = TM_int8;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    int8_t destination;

    if(!emplace_i8(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%u");
}

TEST (emplace_int16)
{
    TM_msg dummy;
    int16_t buf = 64;
    dummy.type = TM_int16;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    int16_t destination;

    if(!emplace_i16(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%d");

}

TEST (emplace_int16_neg)
{
    TM_msg dummy;
    int16_t buf = -64;
    dummy.type = TM_int16;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    int16_t destination;

    if(!emplace_i16(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%d");
}

TEST (emplace_int32)
{
    TM_msg dummy;
    int32_t buf = 64;
    dummy.type = TM_int32;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    int32_t destination;

    if(!emplace_i32(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%d");

}

TEST (emplace_int32_neg)
{
    TM_msg dummy;
    int32_t buf = -64;
    dummy.type = TM_int32;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    int32_t destination;

    if(!emplace_i32(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%d");
}

TEST (emplace_uint8)
{
    TM_msg dummy;
    uint8_t buf = 64;
    dummy.type = TM_uint8;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    uint8_t destination;

    if(!emplace_u8(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%u");

}

TEST (emplace_uint16)
{
    TM_msg dummy;
    uint16_t buf = 64;
    dummy.type = TM_uint16;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    uint16_t destination;

    if(!emplace_u16(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%d");
}

TEST (emplace_uint32)
{
    TM_msg dummy;
    uint32_t buf = 64;
    dummy.type = TM_uint32;
    dummy.buffer = (void *)&buf;
    dummy.size = 1;

    uint32_t destination;

    if(!emplace_u32(&dummy, &destination))
    {
        FAIL();
    }

    ASSERT_EQ_FMT(buf, destination,"%d");

}
