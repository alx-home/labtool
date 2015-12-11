################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../vendor/gtest-1.7.0/codegear/gtest_all.cc \
../vendor/gtest-1.7.0/codegear/gtest_link.cc 

CC_DEPS += \
./[Subprojects]/gtest/codegear/gtest_all.d \
./[Subprojects]/gtest/codegear/gtest_link.d 

OBJS += \
./[Subprojects]/gtest/codegear/gtest_all.o \
./[Subprojects]/gtest/codegear/gtest_link.o 


# Each subdirectory must supply rules for building sources it contributes
[Subprojects]/gtest/codegear/gtest_all.o: C:/workspace/coherent\ point\ drift/vendor/gtest-1.7.0/codegear/gtest_all.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

[Subprojects]/gtest/codegear/gtest_link.o: C:/workspace/coherent\ point\ drift/vendor/gtest-1.7.0/codegear/gtest_link.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


