################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/serial_manager/fsl_component_serial_manager.c \
../component/serial_manager/fsl_component_serial_port_uart.c 

C_DEPS += \
./component/serial_manager/fsl_component_serial_manager.d \
./component/serial_manager/fsl_component_serial_port_uart.d 

OBJS += \
./component/serial_manager/fsl_component_serial_manager.o \
./component/serial_manager/fsl_component_serial_port_uart.o 


# Each subdirectory must supply rules for building sources it contributes
component/serial_manager/%.o: ../component/serial_manager/%.c component/serial_manager/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DSDK_OS_BAREMETAL -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\board" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\source" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\device" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\serial_manager" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\uart" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\drivers" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\CMSIS" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\xip" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\utilities" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\lists" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-serial_manager

clean-component-2f-serial_manager:
	-$(RM) ./component/serial_manager/fsl_component_serial_manager.d ./component/serial_manager/fsl_component_serial_manager.o ./component/serial_manager/fsl_component_serial_port_uart.d ./component/serial_manager/fsl_component_serial_port_uart.o

.PHONY: clean-component-2f-serial_manager

