################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/config.cpp \
../test/performance/nonrigid_lowrank_performance_test.cpp \
../test/performance/rigid_performance_test.cpp \
../test/performance/timer.cpp 

OBJS += \
./[Targets]/[exe]\ Performance/Source\ Files/config.o \
./[Targets]/[exe]\ Performance/Source\ Files/nonrigid_lowrank_performance_test.o \
./[Targets]/[exe]\ Performance/Source\ Files/rigid_performance_test.o \
./[Targets]/[exe]\ Performance/Source\ Files/timer.o 

CPP_DEPS += \
./[Targets]/[exe]\ Performance/Source\ Files/config.d \
./[Targets]/[exe]\ Performance/Source\ Files/nonrigid_lowrank_performance_test.d \
./[Targets]/[exe]\ Performance/Source\ Files/rigid_performance_test.d \
./[Targets]/[exe]\ Performance/Source\ Files/timer.d 


# Each subdirectory must supply rules for building sources it contributes
[Targets]/[exe]\ Performance/Source\ Files/config.o: C:/workspace/coherent\ point\ drift/test/config.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"[Targets]/[exe] Performance/Source Files/config.d" -MT"[Targets]/[exe]\ Performance/Source\ Files/config.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

[Targets]/[exe]\ Performance/Source\ Files/nonrigid_lowrank_performance_test.o: C:/workspace/coherent\ point\ drift/test/performance/nonrigid_lowrank_performance_test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"[Targets]/[exe] Performance/Source Files/nonrigid_lowrank_performance_test.d" -MT"[Targets]/[exe]\ Performance/Source\ Files/nonrigid_lowrank_performance_test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

[Targets]/[exe]\ Performance/Source\ Files/rigid_performance_test.o: C:/workspace/coherent\ point\ drift/test/performance/rigid_performance_test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"[Targets]/[exe] Performance/Source Files/rigid_performance_test.d" -MT"[Targets]/[exe]\ Performance/Source\ Files/rigid_performance_test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

[Targets]/[exe]\ Performance/Source\ Files/timer.o: C:/workspace/coherent\ point\ drift/test/performance/timer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"[Targets]/[exe] Performance/Source Files/timer.d" -MT"[Targets]/[exe]\ Performance/Source\ Files/timer.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


