/*
 * resistence.c
 *
 *  Created on: 2024年3月8日
 *      Author: 86135
 */
#include "pin_mux.h"
#include "fsl_gpio.h"

gpio_pin_config_t resistence_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

void Resistence_Init(void)
{
	GPIO_PinInit(BOARD_INITPINS_U_Re0_GPIO,BOARD_INITPINS_U_Re0_GPIO_PIN,&resistence_config);
}

void Resistence_Set(void)
{
	GPIO_PortSet(BOARD_INITPINS_U_Re0_GPIO,BOARD_INITPINS_U_Re0_GPIO_PIN_MASK);
}

void Resistence_Clear(void)
{
	GPIO_PortClear(BOARD_INITPINS_U_Re0_GPIO,BOARD_INITPINS_U_Re0_GPIO_PIN_MASK);
}

int Resistence_Status(int flag)
{
	if (flag==1)
	{
		Resistence_Set();
	}
	else
	{
		Resistence_Clear();
	}
		return 0;
}
