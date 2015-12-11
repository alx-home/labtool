################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_DEPS += \
./vendor/gtest-1.7.0/samples/sample1.d \
./vendor/gtest-1.7.0/samples/sample10_unittest.d \
./vendor/gtest-1.7.0/samples/sample1_unittest.d \
./vendor/gtest-1.7.0/samples/sample2.d \
./vendor/gtest-1.7.0/samples/sample2_unittest.d \
./vendor/gtest-1.7.0/samples/sample3_unittest.d \
./vendor/gtest-1.7.0/samples/sample4.d \
./vendor/gtest-1.7.0/samples/sample4_unittest.d \
./vendor/gtest-1.7.0/samples/sample5_unittest.d \
./vendor/gtest-1.7.0/samples/sample6_unittest.d \
./vendor/gtest-1.7.0/samples/sample7_unittest.d \
./vendor/gtest-1.7.0/samples/sample8_unittest.d \
./vendor/gtest-1.7.0/samples/sample9_unittest.d 

OBJS += \
./vendor/gtest-1.7.0/samples/sample1.o \
./vendor/gtest-1.7.0/samples/sample10_unittest.o \
./vendor/gtest-1.7.0/samples/sample1_unittest.o \
./vendor/gtest-1.7.0/samples/sample2.o \
./vendor/gtest-1.7.0/samples/sample2_unittest.o \
./vendor/gtest-1.7.0/samples/sample3_unittest.o \
./vendor/gtest-1.7.0/samples/sample4.o \
./vendor/gtest-1.7.0/samples/sample4_unittest.o \
./vendor/gtest-1.7.0/samples/sample5_unittest.o \
./vendor/gtest-1.7.0/samples/sample6_unittest.o \
./vendor/gtest-1.7.0/samples/sample7_unittest.o \
./vendor/gtest-1.7.0/samples/sample8_unittest.o \
./vendor/gtest-1.7.0/samples/sample9_unittest.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/gtest-1.7.0/samples/%.o: ../vendor/gtest-1.7.0/samples/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


