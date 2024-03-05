################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/HAL/DCmotor.c \
../APP/HAL/buzzer.c \
../APP/HAL/external_EEPROM.c 

OBJS += \
./APP/HAL/DCmotor.o \
./APP/HAL/buzzer.o \
./APP/HAL/external_EEPROM.o 

C_DEPS += \
./APP/HAL/DCmotor.d \
./APP/HAL/buzzer.d \
./APP/HAL/external_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
APP/HAL/%.o: ../APP/HAL/%.c APP/HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


