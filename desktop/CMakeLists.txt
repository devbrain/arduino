find_package(Qt5 REQUIRED COMPONENTS Core SerialPort)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

set(src
        main.cpp
        arduino.cpp
        )

set (hdr
        arduino.h)

add_executable(duino-desktop ${src} ${hdr})
target_link_libraries(duino-desktop Qt5::Core Qt5::SerialPort)

