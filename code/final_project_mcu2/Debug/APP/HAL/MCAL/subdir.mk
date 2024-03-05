################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/HAL/MCAL/PWM.c \
../APP/HAL/MCAL/TWI.c \
../APP/HAL/MCAL/UART.c \
../APP/HAL/MCAL/gpio.c \
../APP/HAL/MCAL/timer1.c 

OBJS += \
./APP/HAL/MCAL/PWM.o \
./APP/HAL/MCAL/TWI.o \
./APP/HAL/MCAL/UART.o \
./APP/HAL/MCAL/gpio.o \
./APP/HAL/MCAL/timer1.o 

C_DEPS += \
./APP/HAL/MCAL/PWM.d \
./APP/HAL/MCAL/TWI.d \
./APP/HAL/MCAL/UART.d \
./APP/HAL/MCAL/gpio.d \
./APP/HAL/MCAL/timer1.d 


# Each subdirectory must supply rules for building sources it contributes
APP/HAL/MCAL/%.o: ../APP/HAL/MCAL/%.c APP/HAL/MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


