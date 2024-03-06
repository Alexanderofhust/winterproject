/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MIMXRT1021_I2C_Test.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1021.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
#include "sht30_i2c_drv.h"
#include "sht30.h"
#include <stdlib.h> /* exit, size_t, malloc, free */
#include <math.h> /* demo */
#include "st7735s.h"
/* SPI buffer size of Wiring Pi; http://wiringpi.com/reference/spi-library/ */
#define WPI_SPI_BUFFER_SIZE  4096 /* x * 1024 */
#define WPI_SPI_CHANNEL         0
#define PIN_COMMUNICATION_MODE  9 /* Wiring Pi pin numbering */
#define PIN_RESET               8
#define PIN_CHIP_SELECT        10
int main(void) {

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    /* USER CODE BEGIN 1 */
       uint8_t recv_dat[6] = {0};
       float temperature = 0.0;
       float humidity = 0.0;
       /* USER CODE END 1 */

       //HAL_Init();

      // SystemClock_Config();

     //  MX_GPIO_Init();
      // MX_I2C1_Init();
      // MX_USART1_UART_Init();

       /* USER CODE BEGIN 2 */
       SHT30_reset();
       if(SHT30_Init() == 0x00U)
           printf("sht30 init ok.\n");
       else
           printf("sht30 init fail.\n");
     /* USER CODE END 2 */

       /*LCD code begin*/
       lcd_ptr_t my_lcd_settings = NULL;
       my_lcd_settings = lcd_createSettings(
               128, /* width */
               160, /* height */
               0,   /* width_offset */
               0,   /* height_offset */
               PIN_COMMUNICATION_MODE, /* Wiring Pi pin numbering */
               PIN_RESET
           );
       /* deselect display module; deactivation of communication */
        //   digitalWrite(10, 1);
       lcd_setSettingsActive(my_lcd_settings);
           /* free memory; prevent memory leak */
           lcd_deleteSettings(my_lcd_settings);

       /*LCD code END*/

     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
     while (1)
     {
       /* USER CODE END WHILE */

       /* USER CODE BEGIN 3 */
          // HAL_Delay(1000);
           if(SHT30_Read_Dat(recv_dat) == 0x00U)
           {
               if(SHT30_Dat_To_Float(recv_dat, &temperature, &humidity)==0)
               {
                   printf("temperature = %f, humidity = %f\n", temperature, humidity);
               }
               else
               {
                   printf("crc check fail.\n");
               }
           }
           else
           {
               printf("read data from sht30 fail.\n");
           }
       }
     /* USER CODE END 3 */
}
//addition to LCE begin
void fail_handler() {
    printf("[!] FAILURE OCCURRED WHILE PROCESSING [!]\n");
    exit(EXIT_FAILURE);
}
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} color_t;
lcd_status_t demo() {
    unsigned short int width, height;
    unsigned char pixel_size;
    unsigned char *framebuffer;
    size_t length_framebuffer;
    size_t address;
    color_t palette[256];
    unsigned char formula; /* max 255 for palette */
    unsigned short int x, y;
    size_t i, p;

    /* Prevent a bug of NULL pointer. 'lcd_settings' is required. */
    if(lcd_settings == NULL) {
        return LCD_FAIL;
    }

    /* get width and height */
    width  = lcd_settings->width;
    height = lcd_settings->height;

    /* get pixel size */
    switch(lcd_settings->interface_pixel_format) {
        /* case LCD_PIXEL_FORMAT_444 is not supported for this function */

        case LCD_PIXEL_FORMAT_565:
            pixel_size = 2; /* two bytes required */
            break;

        case LCD_PIXEL_FORMAT_666:
            pixel_size = 3; /* three bytes required */
            break;

        /* unknown interface pixel format */
        default:
            return LCD_FAIL;
    }

    /* allocate memory */
    length_framebuffer = width * height * pixel_size;
    framebuffer = malloc(length_framebuffer);

    /* if out of RAM memory */
    if(framebuffer == NULL) {
        return LCD_FAIL;
    }

    /* set window position */
    if(lcd_setWindowPosition(0, 0, width - 1, height - 1) < LCD_OK) {
        free(framebuffer);
        return LCD_FAIL;
    }

    /* activate memory write */
    if(lcd_activateMemoryWrite() < LCD_OK) {
        free(framebuffer);
        return LCD_FAIL;
    }

    /* draw */
    for(i = 128; i < 1024; i++) {
        /* create palette */
        for(p = 0; p < 256; p++) {
            palette[p].red   = ((i % 512) - 128) / 1.8;
            palette[p].green = 128 + 127 * sin((3.14159 * p /  64.0) + 1);
            palette[p].blue  = 128 + 127 * sin((3.14159 * p / 128.0) + 1);
        }

        /* populate framebuffer */
        for(x = 0; x < width; x++) {
            for(y = 0; y < height; y++) {
                formula = 128 + 127 * sin(
                    3.14159 *
                    (x - width  / (2 + 2 * sin(3.14159 * ((i % 512) - 128) / 384))) *
                    (y - height / (2 + 2 * sin(3.14159 * ((i % 512) - 128) / 384))) /
                    ((i % 512) * 10.0)
                );

                /* calculate pixel address */
                address = (y * width + x) * pixel_size;

                /* write pixel to framebuffer */
                switch(lcd_settings->interface_pixel_format) {
                    /* case LCD_PIXEL_FORMAT_444 is not supported
                     * for this function
                     */

                    case LCD_PIXEL_FORMAT_565:
                        framebuffer[address] = (palette[formula].red & 0xF8) |
                            ((palette[formula].green >> 5) & 0x07);

                        framebuffer[address + 1] =
                            ((palette[formula].green << 3) & 0xE0) |
                            ((palette[formula].blue  >> 3) & 0x1F);
                        break;

                    case LCD_PIXEL_FORMAT_666:
                        framebuffer[address]     = palette[formula].red;
                        framebuffer[address + 1] = palette[formula].green;
                        framebuffer[address + 2] = palette[formula].blue;
                        break;

                    /* unknown interface pixel format */
                    default:
                        free(framebuffer);
                        return LCD_FAIL;
                }
            }
        }

        /* send framebuffer */
        if(
            lcd_framebuffer_send(
                framebuffer,
                length_framebuffer,
                WPI_SPI_BUFFER_SIZE
            ) < LCD_OK
        ) {
            free(framebuffer);
            return LCD_FAIL;
        }
    }

    /* free memory */
    free(framebuffer);

    return LCD_OK;
}
//addition to LCD end
