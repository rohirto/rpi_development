/**
 * @file rpi_init.h
 * @author rohit S
 * @brief raspberry pi init header file
 * @version 0.1
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024 Volansys technologies
 * 
 */

 #ifndef RPI_INIT_H
 #define RPI_INIT_H

//Includes 
#include <sys/mman.h> //Needed for memory mapping
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "rpi_common.h"
#include "rpi_mem_ops.h"

#define __IO volatile

#define RPI_VERSION 10000

#define HIGH 0x01
#define LOW  0x00

//RPI peripheral addresses
#define RPI_CORE_CLK_HZ        250000000 //NOTE: UART0 use UART_CLK_HZ = 50000000
#define RPI_GPIO_BASE          0x200000
#define RPI_SYS_TIMER          0x3000
#define RPI_PWM                0x20C000
#define RPI_PWM_CLK	           0x1010a0
#define RPI_I2C0               0x205000
#define RPI_I2C1               0x804000
#define RPI_SPI0               0x204000
#define RPI_UART               0x201000

/*! Peripherals block base address on RPi 1 */
#define BCM2835_PERI_BASE               0x20000000
/*! Size of the peripherals block on RPi 1 */
#define BCM2835_PERI_SIZE               0x01000000
/*! Alternate base address for RPI  2 / 3 */
#define BCM2835_RPI2_PERI_BASE          0x3F000000
/*! Alternate base address for RPI  4 */
#define BCM2835_RPI4_PERI_BASE          0xFE000000
/*! Alternate size for RPI  4 */
#define BCM2835_RPI4_PERI_SIZE          0x01800000

#define BCM2835_RPI5_PERI_BASE          0x7C000000

#ifdef __cplusplus
extern "C" {
#endif

    int rpi_init(void);
    int rpi_close(void);

    static inline void print_version(void)
    {
        printf("Version: %d \n", RPI_VERSION);
    }

#ifdef __cplusplus
}
#endif

 #endif