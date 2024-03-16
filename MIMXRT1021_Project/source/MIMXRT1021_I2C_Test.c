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
#include <string.h>
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
#include "resistence.h"
#include "lcd.h"
#include "ui.h"
/* SPI buffer size of Wiring Pi; http://wiringpi.com/reference/spi-library/ */
#define WPI_SPI_BUFFER_SIZE  4096 /* x * 1024 */
#define WPI_SPI_CHANNEL         0
#define PIN_COMMUNICATION_MODE  9 /* Wiring Pi pin numbering */
#define PIN_RESET               8
#define PIN_CHIP_SELECT        10
int main(void) {

	gpio_pin_config_t resistence_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
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


       /* USER CODE BEGIN 2 */
       SHT30_reset();
       if(SHT30_Init() == 0x00U)
           printf("sht30 init ok.\n");
       else
           printf("sht30 init fail.\n");

     /* USER CODE END 2 */

       /*LCD code begin*/
       ui_init();
           Text txtA = ui_label("   The temperature is   ", S_RED, S_WHITE, true);
           Text txtB = ui_label("The humidity is", S_BLUE, S_WHITE, true);
           Text txtC = ui_label("Heating", S_RED, S_BLACK, true);
           Text txtD = ui_label("Stop heating", S_GREEN, S_BLACK, true);
           Text txtE = ui_label("The setpoint is", S_GREEN, S_BLACK, true);

       /*LCD code END*/

     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
           int flag;
           int heatflag;
           float setpoint=30;//默认预定温度为30摄氏度
           char tempe[10];
           char humid[10];
           Resistence_Init();
           if(flag==0)//温湿度检测模式
    {
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
           sprintf(tempe,"%s",temperature);
           sprintf(humid,"%s",humidity);
           Text txtF = ui_label((char*)&tempe, S_RED, S_WHITE, true);
           Text txtG = ui_label((char*)&humid, S_BLUE, S_WHITE, true);
           ui_displayText(&txtA, 2, 121, false);
           ui_displayText(&txtF,2, 129, false);
           ui_displayText(&txtB, 2, 137, false);
           ui_displayText(&txtG, 2, 145, false);
           SDK_DelayAtLeastUs(100000,SystemCoreClock);
       }
}
           else//加热模式
        {
        	   while(1){
        SHT30_Read_Dat(recv_dat);
        SHT30_Dat_To_Float(recv_dat, &temperature, &humidity);
        Text txtF = ui_label((char*)&tempe, S_RED, S_WHITE, true);
           if(temperature<setpoint)
           {
        	   heatflag=1;
        	   ui_displayText(&txtA, 2, 121, false);
        	   ui_displayText(&txtF,2, 129, false);
        	   ui_displayText(&txtC, 2, 137, false);

           }
           else{
        	   heatflag=0;
        	   ui_displayText(&txtA, 2, 121, false);
        	   ui_displayText(&txtF,2, 129, false);
        	   ui_displayText(&txtD, 2, 137, false);
           }
           Resistence_Status(heatflag);
           }

        }
     /* USE.R CODE END 3 */
}
//addition to LCE begin
void fail_handler() {
    printf("[!] FAILURE OCCURRED WHILE PROCESSING [!]\n");
    exit(EXIT_FAILURE);
}

