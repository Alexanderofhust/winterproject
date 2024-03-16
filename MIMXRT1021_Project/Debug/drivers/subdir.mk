################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_flexspi.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpi2c.c \
../drivers/fsl_lpspi.c \
../drivers/fsl_lpspi_cmsis.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_semc.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_flexspi.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpi2c.d \
./drivers/fsl_lpspi.d \
./drivers/fsl_lpspi_cmsis.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_semc.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_flexspi.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpi2c.o \
./drivers/fsl_lpspi.o \
./drivers/fsl_lpspi_cmsis.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_semc.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DSDK_OS_BAREMETAL -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\board" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\device" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\serial_manager" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\uart" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\drivers" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\CMSIS" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\xip" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\utilities" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\lists" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_flexspi.d ./drivers/fsl_flexspi.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpi2c.d ./drivers/fsl_lpi2c.o ./drivers/fsl_lpspi.d ./drivers/fsl_lpspi.o ./drivers/fsl_lpspi_cmsis.d ./drivers/fsl_lpspi_cmsis.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_semc.d ./drivers/fsl_semc.o

.PHONY: clean-drivers

