################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LaboMicros-TP2/App.c \
../source/LaboMicros-TP2/DRV_MCP25625.c \
../source/LaboMicros-TP2/FXOS8700CQ.c \
../source/LaboMicros-TP2/SPI_DRV.c \
../source/LaboMicros-TP2/SysTick.c \
../source/LaboMicros-TP2/gpio.c \
../source/LaboMicros-TP2/i2cm.c \
../source/LaboMicros-TP2/timer.c \
../source/LaboMicros-TP2/uart_drv.c 

OBJS += \
./source/LaboMicros-TP2/App.o \
./source/LaboMicros-TP2/DRV_MCP25625.o \
./source/LaboMicros-TP2/FXOS8700CQ.o \
./source/LaboMicros-TP2/SPI_DRV.o \
./source/LaboMicros-TP2/SysTick.o \
./source/LaboMicros-TP2/gpio.o \
./source/LaboMicros-TP2/i2cm.o \
./source/LaboMicros-TP2/timer.o \
./source/LaboMicros-TP2/uart_drv.o 

C_DEPS += \
./source/LaboMicros-TP2/App.d \
./source/LaboMicros-TP2/DRV_MCP25625.d \
./source/LaboMicros-TP2/FXOS8700CQ.d \
./source/LaboMicros-TP2/SPI_DRV.d \
./source/LaboMicros-TP2/SysTick.d \
./source/LaboMicros-TP2/gpio.d \
./source/LaboMicros-TP2/i2cm.d \
./source/LaboMicros-TP2/timer.d \
./source/LaboMicros-TP2/uart_drv.d 


# Each subdirectory must supply rules for building sources it contributes
source/LaboMicros-TP2/%.o: ../source/LaboMicros-TP2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


