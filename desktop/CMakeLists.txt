set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Core REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(duino-desktop ${SOURCE_FILES})
qt5_use_modules(duino-desktop Core SerialPort)

