################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del

# All of the sources participating in the build are defined here
-include sources.mk
-include vendor/gtest-1.7.0/xcode/Samples/FrameworkSample/subdir.mk
-include vendor/gtest-1.7.0/test/subdir.mk
-include vendor/gtest-1.7.0/src/subdir.mk
-include vendor/gtest-1.7.0/samples/subdir.mk
-include vendor/gtest-1.7.0/fused-src/gtest/subdir.mk
-include vendor/gtest-1.7.0/codegear/subdir.mk
-include test/performance/subdir.mk
-include test/subdir.mk
-include src/subdir.mk
-include example/subdir.mk
-include cli/subdir.mk
-include build/vendor/gtest-1.7.0/CMakeFiles/gtest_main.dir/src/subdir.mk
-include build/vendor/gtest-1.7.0/CMakeFiles/gtest.dir/src/subdir.mk
-include build/test/performance/CMakeFiles/Performance.dir/__/subdir.mk
-include build/test/performance/CMakeFiles/Performance.dir/subdir.mk
-include build/test/CMakeFiles/Test.dir/subdir.mk
-include build/src/CMakeFiles/Library.dir/subdir.mk
-include build/src/subdir.mk
-include build/CMakeFiles/3.0.1/CompilerIdCXX/subdir.mk
-include build/CMakeFiles/3.0.1/CompilerIdC/subdir.mk
-include [Targets]/[lib]\ gtest_main/Source\ Files/subdir.mk
-include [Targets]/[lib]\ gtest/Source\ Files/subdir.mk
-include [Targets]/[lib]\ Library/Source\ Files/subdir.mk
-include [Targets]/[exe]\ Test/Source\ Files/subdir.mk
-include [Targets]/[exe]\ Performance/Source\ Files/subdir.mk
-include [Subprojects]/gtest/xcode/Samples/FrameworkSample/subdir.mk
-include [Subprojects]/gtest/test/subdir.mk
-include [Subprojects]/gtest/src/subdir.mk
-include [Subprojects]/gtest/samples/subdir.mk
-include [Subprojects]/gtest/fused-src/gtest/subdir.mk
-include [Subprojects]/gtest/codegear/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: coherent\ point\ drift

# Tool invocations
coherent\ point\ drift: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C++ Linker'
	g++  -o "coherent point drift" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) "coherent point drift"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
