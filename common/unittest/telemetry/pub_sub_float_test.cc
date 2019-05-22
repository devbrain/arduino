//
// Created by igor on 5/22/19.
//

#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/pub_sub_float]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)
#define ASSERT_STR_EQ(X, Y) do { auto s1 = std::string(X); auto s2 = std::string(Y); REQUIRE(s1 == s2); } while (false)
#define ASSERT_EQ(X, Y) REQUIRE(X == Y)

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;
static uint32_t sizeRead;

static int32_t read_float(uint8_t * buf, uint32_t sizeToRead)
{
    int32_t rem = sizeWritten - sizeRead;
    uint16_t range = sizeToRead > rem ? rem : sizeToRead;
    int32_t i;
    for(i = 0 ; i < range ; i++)
    {
        buf[i] = endBuffer[sizeRead + i];
        sizeRead++;
    }

}

static int32_t readable_float()
{
    return sizeWritten;
}

static int32_t write_float(uint8_t * buf, uint32_t sizeToWrite)
{
    sizeWritten = sizeToWrite;
    int32_t i;
    for(i = 0 ; i < sizeToWrite ; i++)
    {
        endBuffer[i] = buf[i];
    }
}

static int32_t writeable_float()
{
    return 1;
}

/// end of mock

struct TM_state {
    uint8_t called;
    char rcvTopic[OUTGOING_BUFFER_SIZE];
    float rcvFloat;
};

void callback_float(TM_state* s, TM_msg* m)
{
    s->called = 1;
    float f32 = 0;
    strcpy(s->rcvTopic,m->topic);
    if(emplace_f32(m,&f32))
    {
        s->rcvFloat = f32;
    }
}

TEST (publish_float)
{
    TM_state state;
    uint16_t i;
    for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
    {
        endBuffer[i] = 0;
        state.rcvTopic[i] = 0;
    }
    sizeWritten = 0;
    sizeRead = 0;
    state.rcvFloat = 0;
    state.called = 0;

    TM_transport transport;
    transport.read = read_float;
    transport.write = write_float;
    transport.readable = readable_float;
    transport.writeable = writeable_float;

    char topic[] = "topic";
    float value = 1.23E4;

    init_telemetry(&transport);

    subscribe(callback_float,&state);

    publish_f32(topic, value);

    update_telemetry();

    ASSERT_EQ(state.called, 1);
    ASSERT_STR_EQ(topic,state.rcvTopic);
    ASSERT_EQ_FMT(value,state.rcvFloat,"%f");

}

TEST (publish_float_neg)
{
    TM_state state;
    uint16_t i;
    for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
    {
        endBuffer[i] = 0;
        state.rcvTopic[i] = 0;
    }
    sizeWritten = 0;
    sizeRead = 0;
    state.rcvFloat = 0;
    state.called = 0;

    TM_transport transport;
    transport.read = read_float;
    transport.write = write_float;
    transport.readable = readable_float;
    transport.writeable = writeable_float;

    char topic[] = "topic";
    float value = -1.23E4;

    init_telemetry(&transport);

    subscribe(callback_float,&state);

    publish_f32(topic, value);

    update_telemetry();

    ASSERT_EQ(state.called, 1);
    ASSERT_STR_EQ(topic,state.rcvTopic);
    ASSERT_EQ_FMT(value,state.rcvFloat,"%f");

}
