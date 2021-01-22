################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/COM.c \
../Src/FLASH_SECTOR.c \
../Src/buttons.c \
../Src/gfx.c \
../Src/main.c \
../Src/menu.c \
../Src/motor.c \
../Src/rng.c \
../Src/ssd1351.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c \
../Src/tlc5971.c 

OBJS += \
./Src/COM.o \
./Src/FLASH_SECTOR.o \
./Src/buttons.o \
./Src/gfx.o \
./Src/main.o \
./Src/menu.o \
./Src/motor.o \
./Src/rng.o \
./Src/ssd1351.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o \
./Src/tlc5971.o 

C_DEPS += \
./Src/COM.d \
./Src/FLASH_SECTOR.d \
./Src/buttons.d \
./Src/gfx.d \
./Src/main.d \
./Src/menu.d \
./Src/motor.d \
./Src/rng.d \
./Src/ssd1351.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d \
./Src/tlc5971.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/onedrive/TBZ/Projekt BMS LM - Dokumente/SW/FINAL/Inc" -I"D:/onedrive/TBZ/Projekt BMS LM - Dokumente/SW/FINAL/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/onedrive/TBZ/Projekt BMS LM - Dokumente/SW/FINAL/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/onedrive/TBZ/Projekt BMS LM - Dokumente/SW/FINAL/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/onedrive/TBZ/Projekt BMS LM - Dokumente/SW/FINAL/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


