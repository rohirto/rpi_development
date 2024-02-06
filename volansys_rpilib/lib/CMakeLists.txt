# Add the library source files
set(LIB_SOURCES
    src/rpi_init.c 
    src/rpi_mem_ops.c
    src/rpi_gpio.c
    src/rpi_i2c.c
)

include_directories(inc)

add_library(rpi_lib ${LIB_SOURCES})