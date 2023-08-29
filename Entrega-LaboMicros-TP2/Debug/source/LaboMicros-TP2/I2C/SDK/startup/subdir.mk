################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LaboMicros-TP2/I2C/SDK/startup/hardware.c \
../source/LaboMicros-TP2/I2C/SDK/startup/main.c \
../source/LaboMicros-TP2/I2C/SDK/startup/semihost_hardfault.c \
../source/LaboMicros-TP2/I2C/SDK/startup/startup_mk64f12.c 

OBJS += \
./source/LaboMicros-TP2/I2C/SDK/startup/hardware.o \
./source/LaboMicros-TP2/I2C/SDK/startup/main.o \
./source/LaboMicros-TP2/I2C/SDK/startup/semihost_hardfault.o \
./source/LaboMicros-TP2/I2C/SDK/startup/startup_mk64f12.o 

C_DEPS += \
./source/LaboMicros-TP2/I2C/SDK/startup/hardware.d \
./source/LaboMicros-TP2/I2C/SDK/startup/main.d \
./source/LaboMicros-TP2/I2C/SDK/startup/semihost_hardfault.d \
./source/LaboMicros-TP2/I2C/SDK/startup/startup_mk64f12.d 


# Each subdirectory must supply rules for building sources it contributes
source/LaboMicros-TP2/I2C/SDK/startup/%.o: ../source/LaboMicros-TP2/I2C/SDK/startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


