################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/widget.cc \
../vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/widget_test.cc 

CC_DEPS += \
./[Subprojects]/gtest/xcode/Samples/FrameworkSample/widget.d \
./[Subprojects]/gtest/xcode/Samples/FrameworkSample/widget_test.d 

OBJS += \
./[Subprojects]/gtest/xcode/Samples/FrameworkSample/widget.o \
./[Subprojects]/gtest/xcode/Samples/FrameworkSample/widget_test.o 


# Each subdirectory must supply rules for building sources it contributes
[Subprojects]/gtest/xcode/Samples/FrameworkSample/widget.o: C:/workspace/coherent\ point\ drift/vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/widget.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

[Subprojects]/gtest/xcode/Samples/FrameworkSample/widget_test.o: C:/workspace/coherent\ point\ drift/vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/widget_test.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


