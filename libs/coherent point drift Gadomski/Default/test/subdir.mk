################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/arma_32bit_test.cpp 

OBJS += \
./test/affinity_eigenvectors_test.o \
./test/affinity_matrix_test.o \
./test/arma_32bit_test.o \
./test/arma_64bit_test.o \
./test/config.o \
./test/exceptions_test.o \
./test/find_P_test.o \
./test/nonrigid_lowrank_test.o \
./test/nonrigid_test.o \
./test/rigid_test.o \
./test/sigma2_test.o \
./test/version_test.o 

CPP_DEPS += \
./test/affinity_eigenvectors_test.d \
./test/affinity_matrix_test.d \
./test/arma_32bit_test.d \
./test/arma_64bit_test.d \
./test/config.d \
./test/exceptions_test.d \
./test/find_P_test.d \
./test/nonrigid_lowrank_test.d \
./test/nonrigid_test.d \
./test/rigid_test.d \
./test/sigma2_test.d \
./test/version_test.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


