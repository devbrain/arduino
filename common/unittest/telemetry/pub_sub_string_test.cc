//
// Created by igor on 5/22/19.
//

#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/pub_sub_string]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)
#define ASSERT_STR_EQ(X, Y) do { auto s1 = std::string(X); auto s2 = std::string(Y); REQUIRE(s1 == s2); } while (false)
#define ASSERT_EQ(X, Y) REQUIRE(X == Y)

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;
static uint32_t sizeRead;

static int32_t read_str(uint8_t * buf, uint32_t sizeToRead)
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

static int32_t readable_str()
{
    return sizeWritten;
}

static int32_t write_str(uint8_t * buf, uint32_t sizeToWrite)
{
    sizeWritten = sizeToWrite;
    int32_t i;
    for(i = 0 ; i < sizeToWrite ; i++)
    {
        endBuffer[i] = buf[i];
    }
}

static int32_t writeable_str()
{
    return 1;
}

/// end of mock

struct TM_state {
    uint8_t called;
    char rcvString[OUTGOING_BUFFER_SIZE];
    char rcvTopic[OUTGOING_BUFFER_SIZE];
};

static void callback_str(TM_state* s, TM_msg* m)
{
    s->called = 1;
    char str[OUTGOING_BUFFER_SIZE] = {0};
    if(emplace(m,str,OUTGOING_BUFFER_SIZE))
    {
        strcpy(s->rcvString,str);
        strcpy(s->rcvTopic,m->topic);
    }
}

TEST (publish_string)
{
    TM_state state;
    uint16_t i;
    for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
    {
        endBuffer[i] = 0;
        state.rcvTopic[i] = 0;
        state.rcvString[i] = 0;
    }
    sizeWritten = 0;
    sizeRead = 0;
    state.called = 0;

    TM_transport transport;
    transport.read = read_str;
    transport.write = write_str;
    transport.readable = readable_str;
    transport.writeable = writeable_str;

    char topic[] = "topic";
    char message[] = "someMessage";

    init_telemetry(&transport);

    subscribe(callback_str,&state);

    publish(topic, message);

    update_telemetry();

    ASSERT_EQ(state.called, 1);
    ASSERT_STR_EQ(message,state.rcvString);
    ASSERT_STR_EQ(topic,state.rcvTopic);

}

