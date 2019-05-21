#ifndef FRAMING_H_
#define FRAMING_H_

#include <stddef.h>
#include <stdint.h>

#include "telemetry/cppext.h"

TELEMETRY_EXTERN_C void initialize_framing();
// Outgoing data
// Set storage for the outgoing frame
TELEMETRY_EXTERN_C void outgoing_storage(uint8_t * buf, uint32_t bufSize);

TELEMETRY_EXTERN_C void begin_frame();
TELEMETRY_EXTERN_C void append(uint8_t byte);
TELEMETRY_EXTERN_C void append2(uint16_t twobytes);
TELEMETRY_EXTERN_C void append4(uint32_t fourbytes);
TELEMETRY_EXTERN_C uint32_t end_frame();

// Incoming data
// Set storage for the incoming data
TELEMETRY_EXTERN_C void incoming_storage(uint8_t * buf, uint32_t bufSize);

TELEMETRY_EXTERN_C void set_on_incoming_frame(void (*callback)(uint8_t * storage, uint32_t occupiedSize));
TELEMETRY_EXTERN_C void set_on_incoming_error(void (*callback)(int32_t errCode));
TELEMETRY_EXTERN_C void feed(uint8_t byte);
#endif
