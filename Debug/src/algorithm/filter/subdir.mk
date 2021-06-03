################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/algorithm/filter/filter.c 

OBJS += \
./src/algorithm/filter/filter.o 

C_DEPS += \
./src/algorithm/filter/filter.d 


# Each subdirectory must supply rules for building sources it contributes
src/algorithm/filter/filter.o: ../src/algorithm/filter/filter.c
	arm-none-eabi-gcc "$<" -std=gnu11 -g3 -c -I"D:/resource/shared_file/my_mcu_lib_c/include" -I"D:/resource/shared_file/my_mcu_lib_c/include/crypto" -I"D:/resource/shared_file/my_mcu_lib_c/include/algorithm/filter" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/algorithm/filter/filter.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

