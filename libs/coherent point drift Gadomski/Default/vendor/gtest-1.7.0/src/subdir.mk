################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_DEPS += \
./vendor/gtest-1.7.0/src/gtest-all.d \
./vendor/gtest-1.7.0/src/gtest-death-test.d \
./vendor/gtest-1.7.0/src/gtest-filepath.d \
./vendor/gtest-1.7.0/src/gtest-port.d \
./vendor/gtest-1.7.0/src/gtest-printers.d \
./vendor/gtest-1.7.0/src/gtest-test-part.d \
./vendor/gtest-1.7.0/src/gtest-typed-test.d \
./vendor/gtest-1.7.0/src/gtest.d \
./vendor/gtest-1.7.0/src/gtest_main.d 

OBJS += \
./vendor/gtest-1.7.0/src/gtest-all.o \
./vendor/gtest-1.7.0/src/gtest-death-test.o \
./vendor/gtest-1.7.0/src/gtest-filepath.o \
./vendor/gtest-1.7.0/src/gtest-port.o \
./vendor/gtest-1.7.0/src/gtest-printers.o \
./vendor/gtest-1.7.0/src/gtest-test-part.o \
./vendor/gtest-1.7.0/src/gtest-typed-test.o \
./vendor/gtest-1.7.0/src/gtest.o \
./vendor/gtest-1.7.0/src/gtest_main.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/gtest-1.7.0/src/%.o: ../vendor/gtest-1.7.0/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


