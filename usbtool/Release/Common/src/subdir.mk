################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea.c \
/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea_comm.c \
/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea_payload.c \
/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea_rx_cmd.c \
/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea_tx_cmd.c 

OBJS += \
./Common/src/flexsea.o \
./Common/src/flexsea_comm.o \
./Common/src/flexsea_payload.o \
./Common/src/flexsea_rx_cmd.o \
./Common/src/flexsea_tx_cmd.o 

C_DEPS += \
./Common/src/flexsea.d \
./Common/src/flexsea_comm.d \
./Common/src/flexsea_payload.d \
./Common/src/flexsea_rx_cmd.d \
./Common/src/flexsea_tx_cmd.d 


# Each subdirectory must supply rules for building sources it contributes
Common/src/flexsea.o: /home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/inc" -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/usbtool/inc" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/src/flexsea_comm.o: /home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea_comm.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/inc" -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/usbtool/inc" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/src/flexsea_payload.o: /home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea_payload.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/inc" -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/usbtool/inc" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/src/flexsea_rx_cmd.o: /home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea_rx_cmd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/inc" -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/usbtool/inc" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Common/src/flexsea_tx_cmd.o: /home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/src/flexsea_tx_cmd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/common/inc" -I"/home/jfduval/Documents/biomech-ee-svn/Code/flexsea_1_0/usbtool/inc" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


