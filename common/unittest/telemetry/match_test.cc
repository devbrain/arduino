//
// Created by igor on 5/22/19.
//

#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/match]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)

TEST (match_simple)
{
    TM_msg dummy;
    char topic[] = "foo";
    dummy.topic = topic;

    ASSERT_EQ_FMT(match(&dummy, topic),1,"%u");
    ASSERT_EQ_FMT(match(&dummy, "foo"),1,"%u");
    ASSERT_EQ_FMT(match(&dummy, "bar"),0,"%u");
}

TEST (match_with_spaces)
{
    TM_msg dummy;
    char topic[] = "foo with spaces";
    dummy.topic = topic;

    ASSERT_EQ_FMT(match(&dummy, topic),1,"%u");
    ASSERT_EQ_FMT(match(&dummy, "foo with spaces"),1,"%u");
    ASSERT_EQ_FMT(match(&dummy, "foo"),0,"%u");
    ASSERT_EQ_FMT(match(&dummy, "bar"),0,"%u");
}

TEST (match_with_special_chars)
{
    TM_msg dummy;
    char topic[] = "/:@#";
    dummy.topic = topic;

    ASSERT_EQ_FMT(match(&dummy, topic),1,"%u");
    ASSERT_EQ_FMT(match(&dummy, "/:@#"),1,"%u");
    ASSERT_EQ_FMT(match(&dummy, "$#@:/"),0,"%u");
    ASSERT_EQ_FMT(match(&dummy, "bar"),0,"%u");
}

TEST (fullmatch_test)
{
    TM_msg dummy;
    char topic[] = "foo";
    dummy.topic = topic;
    dummy.type = TM_uint8;

    ASSERT_EQ_FMT(fullmatch(&dummy, topic, TM_uint8),1,"%u");
    ASSERT_EQ_FMT(fullmatch(&dummy, topic, TM_int8),0,"%u");
    ASSERT_EQ_FMT(fullmatch(&dummy, "foo", TM_uint8),1,"%u");
    ASSERT_EQ_FMT(fullmatch(&dummy, "foo", TM_int8),0,"%u");
    ASSERT_EQ_FMT(fullmatch(&dummy, "bar", TM_uint8),0,"%u");
    ASSERT_EQ_FMT(fullmatch(&dummy, "bar", TM_int16),0,"%u");
}


