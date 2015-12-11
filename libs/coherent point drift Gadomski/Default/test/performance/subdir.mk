################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
./test/performance/nonrigid_lowrank_performance_test.o \
./test/performance/rigid_performance_test.o \
./test/performance/timer.o 

CPP_DEPS += \
./test/performance/nonrigid_lowrank_performance_test.d \
./test/performance/rigid_performance_test.d \
./test/performance/timer.d 


# Each subdirectory must supply rules for building sources it contributes
test/performance/%.o: ../test/performance/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


