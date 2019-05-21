//
// Created by igor on 5/8/19.
//
#include "common/unittest/catch.hpp"
#include "common/telemetry/dictionnary.h"

#define TEST(X) TEST_CASE(#X, "[telemetry/dictionary]")

TEST (dictionnary_insert_f32)
{
    struct nlist *hashtab[HASHSIZE];
    init_table(hashtab);

    float testvar = 0.f;

    install(hashtab, "foo", (void *) (&testvar), ptr_f32);

    // Test installed structure can be retrieved
    struct nlist *np = lookup(hashtab, "foo");

    REQUIRE(np != NULL);


    REQUIRE(np->ptr_f32 == &testvar);

    REQUIRE(np->ptr_u8 == NULL);
    REQUIRE(np->ptr_u16 == NULL);
    REQUIRE(np->ptr_u32 == NULL);
    REQUIRE(np->ptr_i8 == NULL);
    REQUIRE(np->ptr_i16 == NULL);
    REQUIRE(np->ptr_i32 == NULL);
    REQUIRE(np->ptr_function == NULL);

    REQUIRE(*(np->ptr_f32) == testvar);

}


TEST(dictionnary_insert_u8)
{
    struct nlist *hashtab[HASHSIZE];
    init_table(hashtab);

    uint8_t testvar = 255;

    install(hashtab, "bar", (void *) (&testvar), ptr_u8);

    // Test installed structure can be retrieved
    struct nlist *np = lookup(hashtab, "bar");
    REQUIRE(np != NULL);


    REQUIRE(np->ptr_u8 == &testvar);

    REQUIRE(np->ptr_f32 == NULL);
    REQUIRE(np->ptr_u16 == NULL);
    REQUIRE(np->ptr_u32 == NULL);
    REQUIRE(np->ptr_i8 == NULL);
    REQUIRE(np->ptr_i16 == NULL);
    REQUIRE(np->ptr_i32 == NULL);
    REQUIRE(np->ptr_function == NULL);

    REQUIRE(*(np->ptr_u8) == testvar);

}

#define ASSERT_EQ(X, Y) REQUIRE(X == Y)


TEST_CASE("dictionnary_insert_u16", "[telemetry/dictionary]")
{
    struct nlist *hashtab[HASHSIZE];
    init_table(hashtab);

    uint16_t testvar = 65535;

    install(hashtab, "bar", (void *) (&testvar), ptr_u16);

    // Test installed structure can be retrieved
    struct nlist *np = lookup(hashtab, "bar");
    REQUIRE(np != nullptr);


    ASSERT_EQ(np->ptr_u16, &testvar);

    ASSERT_EQ(np->ptr_f32, NULL);
    ASSERT_EQ(np->ptr_u8, NULL);
    ASSERT_EQ(np->ptr_u32, NULL);
    ASSERT_EQ(np->ptr_i8, NULL);
    ASSERT_EQ(np->ptr_i16, NULL);
    ASSERT_EQ(np->ptr_i32, NULL);
    ASSERT_EQ(np->ptr_function, NULL);

    ASSERT_EQ(*(np->ptr_u16), testvar);
}


TEST(dictionnary_insert_u32)
{
    struct nlist *hashtab[HASHSIZE];
    init_table(hashtab);

    uint32_t testvar = 4294967295;

    install(hashtab, "bar", (void *) (&testvar), ptr_u32);

    // Test installed structure can be retrieved
    struct nlist *np = lookup(hashtab, "bar");

    REQUIRE(np != nullptr);

    ASSERT_EQ(np->ptr_u32, &testvar);

    ASSERT_EQ(np->ptr_f32, NULL);
    ASSERT_EQ(np->ptr_u8, NULL);
    ASSERT_EQ(np->ptr_u16, NULL);
    ASSERT_EQ(np->ptr_i8, NULL);
    ASSERT_EQ(np->ptr_i16, NULL);
    ASSERT_EQ(np->ptr_i32, NULL);
    ASSERT_EQ(np->ptr_function, NULL);

    ASSERT_EQ(*(np->ptr_u32), testvar);
}

TEST (dictionnary_insert_i8)
{
    struct nlist *hashtab[HASHSIZE];
    init_table(hashtab);

    int8_t testvar = -127;

    install(hashtab, "bar", (void *) (&testvar), ptr_i8);

    // Test installed structure can be retrieved
    struct nlist *np = lookup(hashtab, "bar");
    REQUIRE(np != nullptr);


    ASSERT_EQ(np->ptr_i8, &testvar);

    ASSERT_EQ(np->ptr_f32, NULL);
    ASSERT_EQ(np->ptr_u8, NULL);
    ASSERT_EQ(np->ptr_u16, NULL);
    ASSERT_EQ(np->ptr_u32, NULL);
    ASSERT_EQ(np->ptr_i16, NULL);
    ASSERT_EQ(np->ptr_i32, NULL);
    ASSERT_EQ(np->ptr_function, NULL);

    ASSERT_EQ(*(np->ptr_i8), testvar);

}

TEST(dictionnary_insert_i16)
{
    struct nlist *hashtab[HASHSIZE];
    init_table(hashtab);

    int16_t testvar = -32767;

    install(hashtab, "bar", (void *) (&testvar), ptr_i16);

    // Test installed structure can be retrieved
    struct nlist *np = lookup(hashtab, "bar");
    REQUIRE(np != nullptr);

    ASSERT_EQ(np->ptr_i16, &testvar);

    ASSERT_EQ(np->ptr_f32, NULL);
    ASSERT_EQ(np->ptr_u8, NULL);
    ASSERT_EQ(np->ptr_u16, NULL);
    ASSERT_EQ(np->ptr_u32, NULL);
    ASSERT_EQ(np->ptr_i8, NULL);
    ASSERT_EQ(np->ptr_i32, NULL);
    ASSERT_EQ(np->ptr_function, NULL);

    ASSERT_EQ(*(np->ptr_i16), testvar);
}

TEST(dictionnary_insert_i32)
{
    struct nlist *hashtab[HASHSIZE];
    init_table(hashtab);

    int32_t testvar = -2147483647;

    install(hashtab, "bar", (void *) (&testvar), ptr_i32);

    // Test installed structure can be retrieved
    struct nlist *np = lookup(hashtab, "bar");

    REQUIRE(np != nullptr);

    ASSERT_EQ(np->ptr_i32, &testvar);

    ASSERT_EQ(np->ptr_f32, NULL);
    ASSERT_EQ(np->ptr_u8, NULL);
    ASSERT_EQ(np->ptr_u16, NULL);
    ASSERT_EQ(np->ptr_u32, NULL);
    ASSERT_EQ(np->ptr_i8, NULL);
    ASSERT_EQ(np->ptr_i16, NULL);
    ASSERT_EQ(np->ptr_function, NULL);

    ASSERT_EQ(*(np->ptr_i32), testvar);
}

static void callback()
{

}

TEST (dictionnary_insert_function)
{
    struct nlist *hashtab[HASHSIZE];
    init_table(hashtab);

    install(hashtab, "bar", (void *) (callback), ptr_function);

    // Test installed structure can be retrieved
    struct nlist *np = lookup(hashtab, "bar");
    REQUIRE(np != nullptr);


    ASSERT_EQ(np->ptr_function, callback);

    ASSERT_EQ(np->ptr_f32, NULL);
    ASSERT_EQ(np->ptr_u8, NULL);
    ASSERT_EQ(np->ptr_u16, NULL);
    ASSERT_EQ(np->ptr_u32, NULL);
    ASSERT_EQ(np->ptr_i8, NULL);
    ASSERT_EQ(np->ptr_i16, NULL);
    ASSERT_EQ(np->ptr_i32, NULL);
}
