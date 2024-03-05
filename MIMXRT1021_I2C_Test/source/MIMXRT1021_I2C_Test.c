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
