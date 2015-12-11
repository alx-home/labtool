################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
./src/affinity_eigenvectors.o \
./src/affinity_matrix.o \
./src/find_P.o \
./src/nonrigid.o \
./src/nonrigid_lowrank.o \
./src/registration.o \
./src/rigid.o \
./src/sigma2.o 

CPP_DEPS += \
./src/affinity_eigenvectors.d \
./src/affinity_matrix.d \
./src/find_P.d \
./src/nonrigid.d \
./src/nonrigid_lowrank.d \
./src/registration.d \
./src/rigid.d \
./src/sigma2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


