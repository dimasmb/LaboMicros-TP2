################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LaboMicros-TP2/I2C/source/App.c \
../source/LaboMicros-TP2/I2C/source/SysTick.c \
../source/LaboMicros-TP2/I2C/source/gpio.c \
../source/LaboMicros-TP2/I2C/source/i2cm.c \
../source/LaboMicros-TP2/I2C/source/template.c \
../source/LaboMicros-TP2/I2C/source/timer.c 

OBJS += \
./source/LaboMicros-TP2/I2C/source/App.o \
./source/LaboMicros-TP2/I2C/source/SysTick.o \
./source/LaboMicros-TP2/I2C/source/gpio.o \
./source/LaboMicros-TP2/I2C/source/i2cm.o \
./source/LaboMicros-TP2/I2C/source/template.o \
./source/LaboMicros-TP2/I2C/source/timer.o 

C_DEPS += \
./source/LaboMicros-TP2/I2C/source/App.d \
./source/LaboMicros-TP2/I2C/source/SysTick.d \
./source/LaboMicros-TP2/I2C/source/gpio.d \
./source/LaboMicros-TP2/I2C/source/i2cm.d \
./source/LaboMicros-TP2/I2C/source/template.d \
./source/LaboMicros-TP2/I2C/source/timer.d 


# Each subdirectory must supply rules for building sources it contributes
source/LaboMicros-TP2/I2C/source/%.o: ../source/LaboMicros-TP2/I2C/source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


