#ifndef TELEMETRY_CORE_H_
#define TELEMETRY_CORE_H_

#include <stddef.h>
#include <stdint.h>
#include "telemetry_utils.h"
#include "telemetry/cppext.h"

#define INCOMING_BUFFER_SIZE 128
#define OUTGOING_BUFFER_SIZE 128
#define TOPIC_BUFFER_SIZE 64

TELEMETRY_EXTERN_C void attach(const char * name, void (*callback)(TM_msg * m));
TELEMETRY_EXTERN_C void attach_f32(const char * name, float * variable);
TELEMETRY_EXTERN_C void attach_u8(const char * name, uint8_t * variable);
TELEMETRY_EXTERN_C void attach_u16(const char * name, uint16_t * variable);
TELEMETRY_EXTERN_C void attach_u32(const char * name, uint32_t * variable);
TELEMETRY_EXTERN_C void attach_i8(const char * name, int8_t * variable);
TELEMETRY_EXTERN_C void attach_i16(const char * name, int16_t * variable);
TELEMETRY_EXTERN_C void attach_i32(const char * name, int32_t * variable);

TELEMETRY_EXTERN_C void init_telemetry(TM_transport * t);

TELEMETRY_EXTERN_C void publish(const char * topic, const char * msg);
TELEMETRY_EXTERN_C void publish_u8(const char * topic, uint8_t msg);
TELEMETRY_EXTERN_C void publish_u16(const char * topic, uint16_t msg);
TELEMETRY_EXTERN_C void publish_u32(const char * topic, uint32_t msg);
TELEMETRY_EXTERN_C void publish_i8(const char * topic, int8_t msg);
TELEMETRY_EXTERN_C void publish_i16(const char * topic, int16_t msg);
TELEMETRY_EXTERN_C void publish_i32(const char * topic, int32_t msg);
TELEMETRY_EXTERN_C void publish_f32(const char * topic, float msg);

// subscribe a function to be called everytime a frame is received
// second argument is a data structure that you can implement to access your program data inside the function
TELEMETRY_EXTERN_C void subscribe(void (*callback)(TM_state * s, TM_msg * m), TM_state * s);

TELEMETRY_EXTERN_C void update_telemetry();

#endif
