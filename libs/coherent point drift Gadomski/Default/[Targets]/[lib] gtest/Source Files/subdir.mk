################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_DEPS += \
./[Targets]/[lib]\ gtest/Source\ Files/gtest-all.d 

OBJS += \
./[Targets]/[lib]\ gtest/Source\ Files/gtest-all.o 


# Each subdirectory must supply rules for building sources it contributes
[Targets]/[lib]\ gtest/Source\ Files/gtest-all.o: C:/workspace/coherent\ point\ drift/vendor/gtest-1.7.0/src/gtest-all.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"[Targets]/[lib] gtest/Source Files/gtest-all.d" -MT"[Targets]/[lib]\ gtest/Source\ Files/gtest-all.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


