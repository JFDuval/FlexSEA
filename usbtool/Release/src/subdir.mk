################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/flexsea_console.c \
../src/flexsea_local.c \
../src/main.c \
../src/usbtool_serial.c 

OBJS += \
./src/flexsea_console.o \
./src/flexsea_local.o \
./src/main.o \
./src/usbtool_serial.o 

C_DEPS += \
./src/flexsea_console.d \
./src/flexsea_local.d \
./src/main.d \
./src/usbtool_serial.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"D:\Biomech-EE-SVN2\Code\flexsea_1_0\usbtool\inc" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


