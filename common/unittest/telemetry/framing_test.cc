//
// Created by igor on 5/22/19.
//

#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"
#include "common/telemetry/telemetry_core.h"
#include "common/telemetry/framing.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/framing_incoming]")
#define ASSERT_EQ_FMT(X,Y,Z) REQUIRE(X == Y)
#define ASSERT_STR_EQ(X, Y) do { auto s1 = std::string(X); auto s2 = std::string(Y); REQUIRE(s1 == s2); } while (false)
#define ASSERT_EQ(X, Y) REQUIRE(X == Y)
#define ASSERTm(X, Y) while (!Y) {FAIL(X); break;}
#define ASSERT_FALSEm(X, Y) while (Y) {FAIL(X); break;}

static uint8_t rcv_data[12];
static uint32_t rcv_size;
static uint8_t complete;

static void callback_incoming(uint8_t * storage, uint32_t occupiedSize)
{
    complete = 1;
    uint32_t amount = occupiedSize > 12 ? 12 : occupiedSize;
    rcv_size = amount;
    memcpy(rcv_data, storage, amount);
}

TEST (framing_simple_feed)
{
    uint8_t incomingBuffer[12] = {0};
    complete = 0;
    rcv_size = 0;
    uint32_t i;
    for(i = 0 ; i < 12 ; i++)
        rcv_data[i] = 0;

    initialize_framing();
    incoming_storage(incomingBuffer,12);
    set_on_incoming_frame(callback_incoming);

    uint8_t feed_data[] = {0xF7,0xFF,0x7F};

    for(i = 0 ; i < 3 ; i++)
    {
        feed(feed_data[i]);
    }

    ASSERTm("Valid frame was not detected. callback not triggered.", complete);
    ASSERT_EQ_FMT(feed_data[1],rcv_data[0],"%d");
    ASSERT_EQ_FMT(1,rcv_size,"%d");

}

TEST (framing_corrupted_then_valid_feed)
{
    uint8_t incomingBuffer[12] = {0};
    complete = 0;
    rcv_size = 0;
    uint32_t i;
    for(i = 0 ; i < 12 ; i++)
        rcv_data[i] = 0;

    initialize_framing();
    incoming_storage(incomingBuffer,12);
    set_on_incoming_frame(callback_incoming);

    uint8_t feed_data[] = {0xF7,0xFF,0xF7,0xDD,0x7F};

    for(i = 0 ; i < 5 ; i++)
    {
        feed(feed_data[i]);
    }

    ASSERTm("Valid frame was not detected. callback not triggered.", complete);
    ASSERT_EQ_FMT(1,rcv_size,"%d");
    ASSERT_EQ_FMT(feed_data[3],rcv_data[0],"%d");

}

TEST (framing_basic_escaping_feed)
{
    uint8_t incomingBuffer[12] = {0};
    complete = 0;
    rcv_size = 0;
    uint32_t i;

    for(i = 0 ; i < 12 ; i++)
        rcv_data[i] = 0;

    initialize_framing();
    incoming_storage(incomingBuffer,12);
    set_on_incoming_frame(callback_incoming);

    uint8_t feed_data[] = {0xF7,0x7D,0xFF,0xDD,0x7F}; // useless ESC for test only

    for(i = 0 ; i < 5 ; i++)
    {
        feed(feed_data[i]);
    }

    ASSERTm("Valid frame was not detected. callback not triggered.", complete);
    ASSERT_EQ_FMT(2,rcv_size,"%d");
    ASSERT_EQ_FMT(feed_data[2],rcv_data[0],"%d");
    ASSERT_EQ_FMT(feed_data[3],rcv_data[1],"%d");

}

TEST(framing_all_escaped_flags_feed)
{
    uint8_t incomingBuffer[12] = {0};
    complete = 0;
    rcv_size = 0;
    uint32_t i;

    for(i = 0 ; i < 12 ; i++)
        rcv_data[i] = 0;

    initialize_framing();
    incoming_storage(incomingBuffer,12);
    set_on_incoming_frame(callback_incoming);

    uint8_t feed_data[] = {0xF7,0x7D,0x7F,0x7D,0xF7,0x7D,0x7D,0x7F};

    for(i = 0 ; i < 8 ; i++)
    {
        feed(feed_data[i]);
    }

    ASSERTm("Valid frame was not detected. callback not triggered.", complete);
    ASSERT_EQ_FMT(3,rcv_size,"%d");
    ASSERT_EQ_FMT(feed_data[2],rcv_data[0],"%d");
    ASSERT_EQ_FMT(feed_data[4],rcv_data[1],"%d");
    ASSERT_EQ_FMT(feed_data[6],rcv_data[2],"%d");


}

TEST (framing_overflowing_feed)
{
    uint8_t incomingBuffer[3] = {0};
    complete = 0;
    rcv_size = 0;
    uint32_t i;

    for(i = 0 ; i < 12 ; i++)
        rcv_data[i] = 0;

    initialize_framing();
    incoming_storage(incomingBuffer,3);
    set_on_incoming_frame(callback_incoming);

    uint8_t feed_data[] = {0xF7,0x7D,0x7F,0x7D,0xF7,0x7D,0x7D,0x7F};

    for(i = 0 ; i < 8 ; i++)
    {
        feed(feed_data[i]);
    }

    ASSERT_FALSEm("Valid frame was detected while not expected to.", complete);
    ASSERT_EQ_FMT(0,rcv_size,"%d");

}


TEST (framing_simple_frame)
{
    uint8_t outgoingBuffer[12] = {0};

    initialize_framing();
    outgoing_storage(outgoingBuffer,12);

    begin_frame();
    append(0xFF);
    uint32_t amount = end_frame();

    ASSERT_EQ_FMT(3,amount,"%d");

    uint8_t expected[] = {0xF7, 0xFF, 0x7F};
    uint16_t range = amount > 3 ? 3 : amount;
    uint16_t i;

    for(i = 0 ; i < range ; i++)
    {
        ASSERT_EQ_FMT(expected[i],outgoingBuffer[i],"%x");
    }

}

TEST (framing_with_escaping)
{
    uint8_t outgoingBuffer[12] = {0};

    initialize_framing();
    outgoing_storage(outgoingBuffer,12);

    begin_frame();
    append(0xF7);
    append(0x7F);
    append(0x7D);
    uint32_t amount = end_frame();

    ASSERT_EQ_FMT(8,amount,"%d");

    uint8_t expected[] = {0xF7, 0x7D, 0xF7, 0x7D, 0x7F, 0x7D, 0x7D, 0x7F};
    uint16_t range = amount > 8 ? 8 : amount;
    uint32_t i;
    for(i = 0 ; i < range ; i++)
    {
        ASSERT_EQ_FMT(expected[i],outgoingBuffer[i],"%x");
    }

}

TEST (framing_overflow)
{
    uint8_t outgoingBuffer[3] = {0};

    initialize_framing();
    outgoing_storage(outgoingBuffer,3);

    begin_frame();
    append(0xFF);
    append(0xFF);
    uint32_t amount = end_frame();

    ASSERT_EQ_FMT(0,amount,"%d");

}
