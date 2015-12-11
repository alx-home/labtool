################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_DEPS += \
./vendor/gtest-1.7.0/codegear/gtest_all.d \
./vendor/gtest-1.7.0/codegear/gtest_link.d 

OBJS += \
./vendor/gtest-1.7.0/codegear/gtest_all.o \
./vendor/gtest-1.7.0/codegear/gtest_link.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/gtest-1.7.0/codegear/%.o: ../vendor/gtest-1.7.0/codegear/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


