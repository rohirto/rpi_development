set(LIB_SOURCES
    user_lib/src/SSD1306.cpp
)

include_directories(user_lib/inc)
include_directories(../lib/inc)



add_library(SSD1306_lib ${LIB_SOURCES})

target_link_libraries(SSD1306_lib rpi_lib)