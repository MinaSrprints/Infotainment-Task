################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_operations.c \
../Keybad.c \
../LCD.c \
../OS.c \
../OS_cfg.c \
../Timer0_function.c \
../keypad.c \
../main.c 

OBJS += \
./DIO_operations.o \
./Keybad.o \
./LCD.o \
./OS.o \
./OS_cfg.o \
./Timer0_function.o \
./keypad.o \
./main.o 

C_DEPS += \
./DIO_operations.d \
./Keybad.d \
./LCD.d \
./OS.d \
./OS_cfg.d \
./Timer0_function.d \
./keypad.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


