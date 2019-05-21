#ifndef CRC16_H_
#define CRC16_H_

//From : https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks

#include <stdint.h>
#include "telemetry/cppext.h"

TELEMETRY_EXTERN_C uint16_t crc16(uint8_t * data, uint32_t lenght);
TELEMETRY_EXTERN_C uint16_t crc16_recursive(uint8_t byte, uint16_t remainder);

#endif
