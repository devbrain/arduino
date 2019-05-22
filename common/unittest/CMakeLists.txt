set (hdr catch.hpp)
set (src main.cc
        telemetry/dictionary_test.cc
        telemetry/attach_test.cc
        telemetry/emplace_float.cc
        telemetry/emplace_string.cc
        telemetry/emplace_int.cc
        telemetry/update_float.cc
        telemetry/update_string.cc
        telemetry/update_int.cc
        telemetry/match_test.cc
        telemetry/pub_sub_float_test.cc
        telemetry/pub_sub_string_test.cc
        telemetry/pub_sub_int_test.cc
        telemetry/pub_sub_uint_test.cc
        telemetry/framing_test.cc
        )

add_executable(unittest ${src} ${hdr})
target_link_libraries(unittest telemetry)
