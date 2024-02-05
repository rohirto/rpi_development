/**
 * @file app.cpp
 * @author rohit S
 * @brief Appilcation Code to demonstrate the capabilites of Rpi Lib
 * @version 0.1
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024 Volansys Technologies
 * 
 */

 #include "rpi_init.h"
 #include <iostream>

 int main()
 {
    if(rpi_init() != -1)
    {
        std::cout << "Hello World! Init successful!" << std::endl;

    }
    else
    {
        std::cout << "Init failed!" << std::endl;
    }

    

    return 0;
 }
 