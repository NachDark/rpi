cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(app C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# Initialize the SDK
pico_sdk_init()

add_executable(app
        main.cc font.cc
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(app pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(app)

add_custom_target(flash
    COMMAND cp app.uf2 /media/pi/RPI-RP2
    DEPENDS app
)
