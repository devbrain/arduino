cmake_minimum_required (VERSION 3.10)

project(duino)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

string(COMPARE EQUAL "${CMAKE_CFG_INTDIR}" "." ONYX_IS_SINGLE_CONFIGURATION)

if (ONYX_IS_SINGLE_CONFIGURATION)
    if ( NOT CMAKE_BUILD_TYPE )
        set ( CMAKE_BUILD_TYPE Debug ... FORCE )
    endif()
endif ()

include_directories (${CMAKE_SOURCE_DIR}/common)

# =============================================================================
# OUTPUT
# =============================================================================

set (PRODUCT_PREFIX ${CMAKE_BINARY_DIR}/product)
message (STATUS "Product prefix : ${PRODUCT_PREFIX}")

if (ONYX_IS_SINGLE_CONFIGURATION)
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PRODUCT_PREFIX}/lib)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PRODUCT_PREFIX}/lib)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRODUCT_PREFIX}/bin)
else ()
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PRODUCT_PREFIX}/Debug/lib)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PRODUCT_PREFIX}/Debug/lib)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PRODUCT_PREFIX}/Debug/bin)

  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PRODUCT_PREFIX}/Release/lib)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PRODUCT_PREFIX}/Release/lib)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PRODUCT_PREFIX}/Release/bin)
endif ()

set (SRC_ROOT ${CMAKE_SOURCE_DIR})

include_directories (${SRC_ROOT})

add_subdirectory(desktop)
add_subdirectory(common/telemetry)
add_subdirectory(common/unittest)
