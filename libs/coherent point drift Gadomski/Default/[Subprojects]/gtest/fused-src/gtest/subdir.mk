################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../vendor/gtest-1.7.0/fused-src/gtest/gtest-all.cc \
../vendor/gtest-1.7.0/fused-src/gtest/gtest_main.cc 

CC_DEPS += \
./[Subprojects]/gtest/fused-src/gtest/gtest-all.d \
./[Subprojects]/gtest/fused-src/gtest/gtest_main.d 

OBJS += \
./[Subprojects]/gtest/fused-src/gtest/gtest-all.o \
./[Subprojects]/gtest/fused-src/gtest/gtest_main.o 


# Each subdirectory must supply rules for building sources it contributes
[Subprojects]/gtest/fused-src/gtest/gtest-all.o: C:/workspace/coherent\ point\ drift/vendor/gtest-1.7.0/fused-src/gtest/gtest-all.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

[Subprojects]/gtest/fused-src/gtest/gtest_main.o: C:/workspace/coherent\ point\ drift/vendor/gtest-1.7.0/fused-src/gtest/gtest_main.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


