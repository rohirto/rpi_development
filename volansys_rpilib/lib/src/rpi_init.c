/**
 * @file rpi_init.c
 * @author rohit S
 * @brief Init functions for rpi defined here
 * @version 0.1
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024 Volansys Technologies
 * 
 */

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "rpi_init.h"
#include "rpi_gpio.h"
#include "rpi_i2c.h"


//Globals
uint32_t *rpi_peripherals_base;
uint32_t rpi_peripherals_size;
uint32_t *rpi_peripherals;

static uint8_t pud_type_rpi4 = 0;

//Func prototypes
static void *mapmem(const char *msg, size_t size, int fd, off_t off);
static void unmapmem(void **pmem, size_t size);

/**
 * @brief Init the rpi
 * In the init process (assuming that program is executed with sudo command), the program will read the peripherals adderess and create a memoery map
 * to share the peripherals with user application
 * 
 * /dev/mem provides access to the system's physical memory, not the virtual memory.
 * The mapmem function internally calls mmap to map a region of memory. 
 * mmap then maps a region of memory starting from the specified base address (rpi_peripherals_base) with a size equal to rpi_peripherals_size. 
 * The mapped memory is set to allow both reading and writing (PROT_READ | PROT_WRITE) and is shared with other processes (MAP_SHARED). 
 * The mapping is performed using the file descriptor memfd associated with /dev/mem.
 * 
 * @return int 
 */
int rpi_init(void)
{
    int  memfd;
    int  ok;
    FILE *fp;

    if ((fp = fopen("/proc/device-tree/soc/ranges" , "rb")))
    {
        unsigned char buf[16];
        uint32_t base_address;
        uint32_t peri_size;

        if (fread(buf, 1, sizeof(buf), fp) >= 8)
        {
            base_address = (buf[4] << 24) |
              (buf[5] << 16) |
              (buf[6] << 8) |
              (buf[7] << 0);
            
            peri_size = (buf[8] << 24) |
              (buf[9] << 16) |
              (buf[10] << 8) |
              (buf[11] << 0);
            
            if (!base_address)
            {
                /* looks like RPI 4 */
                base_address = (buf[8] << 24) |
                      (buf[9] << 16) |
                      (buf[10] << 8) |
                      (buf[11] << 0);
                      
                peri_size = (buf[12] << 24) |
                (buf[13] << 16) |
                (buf[14] << 8) |
                (buf[15] << 0);
            }
            /* check for valid known range formats */
            if ((buf[0] == 0x7e) &&
                    (buf[1] == 0x00) &&
                    (buf[2] == 0x00) &&
                    (buf[3] == 0x00) &&
                    ((base_address == BCM2835_PERI_BASE) || (base_address == BCM2835_RPI2_PERI_BASE) || (base_address == BCM2835_RPI4_PERI_BASE)))
            {
                rpi_peripherals_base = (uint32_t *)(intptr_t)base_address;
                rpi_peripherals_size = (size_t)peri_size;
                if( base_address == BCM2835_RPI4_PERI_BASE )  //If pi4 base address
                {
                    pud_type_rpi4 = 1;
                }
            }
        
        }

        printf("rpi peripherals physical address:%p\n",(rpi_peripherals_base));
        
        fclose(fp);
    }

    memfd = -1;
    ok = -1;

    if (geteuid() == 0)
    {
        if ((memfd = open("/dev/mem", O_RDWR | O_SYNC) ) < 0) 
        {
            fprintf(stderr, "rpi_init: Unable to open /dev/mem: %s\n",
                    strerror(errno)) ;
            goto exit;
        }

        rpi_peripherals = mapmem("gpio",
                                 rpi_peripherals_size,
                                 memfd,
                                 (uint32_t)(intptr_t)rpi_peripherals_base);
        
        if (rpi_peripherals == MAP_FAILED) 
        {
            goto exit;
        }


        //All this registers are mapped as structs and defined in their individual file
        
        rpi_gpio      = (rpi_gpio_t*)(rpi_peripherals + RPI_GPIO_BASE/4);
        rpi_i2c0      = (rpi_i2c_t*)(rpi_peripherals + RPI_I2C0/4);
        rpi_i2c1      = (rpi_i2c_t*)(rpi_peripherals + RPI_I2C1/4);
        /*
        rpi_sys_timer = (rpi_sys_timer_t*)(rpi_peripherals + RPI_SYS_TIMER/4);
        rpi_pwm       = (rpi_pwm_t*)(rpi_peripherals + RPI_PWM/4);
        rpi_pwm_clk   = (rpi_pwm_clk_t*) (rpi_peripherals + RPI_PWM_CLK/4);
        
        rpi_spi0      = (rpi_spi_t*)(rpi_peripherals + RPI_SPI0/4);
        rpi_uart      = (rpi_uart_t*) (rpi_peripherals + RPI_UART/4);
        */

        ok = 0;

    }
    else
    {
	    /* Not root, try /dev/gpiomem */
	    /* Open the master /dev/mem device */
	    if ((memfd = open("/dev/gpiomem", O_RDWR | O_SYNC) ) < 0) 
	    {
	        fprintf(stderr, "bcm2835_init: Unable to open /dev/gpiomem: %s\n",
		        strerror(errno)) ;
	        goto exit;
	    }
	
	    /* Base of the peripherals block is mapped to VM */
	    rpi_peripherals_base = 0;
	    rpi_peripherals = mapmem("gpio", rpi_peripherals_size, memfd, (uint32_t)(intptr_t)rpi_peripherals_base);

	    if (rpi_peripherals == MAP_FAILED) goto exit;

        
	    rpi_gpio = (rpi_gpio_t *)rpi_peripherals;
        
	    ok = 1;
    }

     exit:
    if (memfd >= 0)
        close(memfd);

    if (ok)
        rpi_close();
    return ok;
}


/**
 * @brief Close the peripherals, unmap the mapped mem
 * 
 * @return int 
 */
int rpi_close(void)
{
    unmapmem((void**) &rpi_peripherals, rpi_peripherals_size);
    rpi_peripherals = MAP_FAILED;
    rpi_gpio = MAP_FAILED;
    return 0;
}


static void *mapmem(const char *msg, size_t size, int fd, off_t off)
{
    void *map = mmap(NULL, size, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, off);
    if (map == MAP_FAILED)
        fprintf(stderr, "rpi_init: %s mmap failed: %s\n", msg, strerror(errno));
    return map;
}
static void unmapmem(void **pmem, size_t size)
{
    if (*pmem == MAP_FAILED) return;
    munmap(*pmem, size);
    *pmem = MAP_FAILED;
}