################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_DEPS += \
./vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/widget.d \
./vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/widget_test.d 

OBJS += \
./vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/widget.o \
./vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/widget_test.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/%.o: ../vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


