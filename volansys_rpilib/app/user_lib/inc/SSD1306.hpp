/**
 * @file SSD1306.hpp
 * @author rohit S
 * @brief Header file for User Library for SSD1306 OLED I2C display
 * @version 0.1
 * @date 2024-02-06
 * 
 * @copyright Copyright (c) 2024 Volansys Technologies
 * 
 */

 #ifndef SSD1306_HPP
 #define SSD1306_HPP
 
 #include "rpi_init.h"
 #include "rpi_gpio.h"
 #include "rpi_i2c.h"

 #define WIDTH  128
 #define HEIGHT 32



 class SSD1306{

    public:
        SSD1306();

 };

 void dummy_func();
 
 #endif