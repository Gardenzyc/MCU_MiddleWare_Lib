################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/algorithm/filter/filter.c 

OBJS += \
./include/algorithm/filter/filter.o 

C_DEPS += \
./include/algorithm/filter/filter.d 


# Each subdirectory must supply rules for building sources it contributes
include/algorithm/filter/filter.o: ../include/algorithm/filter/filter.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -c -I"D:/resource/shared_file/my_mcu_lib_c/include" -I"D:/resource/shared_file/my_mcu_lib_c/include/algorithm/filter" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"include/algorithm/filter/filter.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

