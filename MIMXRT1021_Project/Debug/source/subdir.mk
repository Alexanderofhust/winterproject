################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MIMXRT1021_I2C_Test.c \
../source/lcd.c \
../source/resistence.c \
../source/semihost_hardfault.c \
../source/sht30.c \
../source/st7735s.c \
../source/ui.c 

C_DEPS += \
./source/MIMXRT1021_I2C_Test.d \
./source/lcd.d \
./source/resistence.d \
./source/semihost_hardfault.d \
./source/sht30.d \
./source/st7735s.d \
./source/ui.d 

OBJS += \
./source/MIMXRT1021_I2C_Test.o \
./source/lcd.o \
./source/resistence.o \
./source/semihost_hardfault.o \
./source/sht30.o \
./source/st7735s.o \
./source/ui.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DSDK_OS_BAREMETAL -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\board" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\device" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\serial_manager" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\uart" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\drivers" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\CMSIS" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\xip" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\utilities" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\component\lists" -I"C:\Users\86135\Documents\MCUXpressoIDE_11.9.0_2144\workspace\MIMXRT1021_I2C_Test\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/MIMXRT1021_I2C_Test.d ./source/MIMXRT1021_I2C_Test.o ./source/lcd.d ./source/lcd.o ./source/resistence.d ./source/resistence.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sht30.d ./source/sht30.o ./source/st7735s.d ./source/st7735s.o ./source/ui.d ./source/ui.o

.PHONY: clean-source

