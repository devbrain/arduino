set (src
  dictionnary.c
  telemetry_utils.c
  crc16.c
  telemetry_core.c
  framing.c
  )


set (hdr
  telemetry_core.h
  dictionnary.h
  telemetry_utils.h
  crc16.h
  framing.h
        cppext.h
  )

include_directories (${SRC_ROOT}/common)

add_library (telemetry STATIC ${src} ${hdr})
