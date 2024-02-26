/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MIMXRT1021_Test.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1021.h"
#include "fsl_debug_console.h"
#include "PID.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */


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

    PRINTF("Hello World\r\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}

float temperature_calc()
{
	pid_Typedef *p;
	float temp_now;
	float R_Set_temp;
	float R_Power;
	//通过读取寄存器或者操控AD转换，读取温度传感器值
	p->ActualVaule=temp_now;
	p->SetPoint=30;//可以再设置另一个函数操控目标温度值，这里默认为30
	p->P=0.5;
	p->I=0.2;
	p->D=0.1;
	p->dError=0;
	p->PreError=0;
	p->SumError=0;
	p->LastError=0;
	p->IMax=10;
	p->DOut=0;
	p->IOut=0;
	p->POut=0;//参数初始化
	R_Set_temp=PID_Calc(p,temp_now);
	R_Power=R_Set_temp;//需要一个从目标温度到电阻功率的算法
	return R_Power;
}
/*PID温度控制算法
 * 输入：无
 * 返回值：电阻R功率
 * */
