################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/locate_line.c" \
"../Sources/main.c" \
"../Sources/pid.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/locate_line.c \
../Sources/main.c \
../Sources/pid.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/locate_line.o \
./Sources/main.o \
./Sources/pid.o \
./Sources/sa_mtb.o \

OBJS_QUOTED += \
"./Sources/locate_line.o" \
"./Sources/main.o" \
"./Sources/pid.o" \
"./Sources/sa_mtb.o" \

C_DEPS += \
./Sources/locate_line.d \
./Sources/main.d \
./Sources/pid.d \
./Sources/sa_mtb.d \

OBJS_OS_FORMAT += \
./Sources/locate_line.o \
./Sources/main.o \
./Sources/pid.o \
./Sources/sa_mtb.o \

C_DEPS_QUOTED += \
"./Sources/locate_line.d" \
"./Sources/main.d" \
"./Sources/pid.d" \
"./Sources/sa_mtb.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/locate_line.o: ../Sources/locate_line.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/locate_line.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/locate_line.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/pid.o: ../Sources/pid.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/pid.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/pid.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


